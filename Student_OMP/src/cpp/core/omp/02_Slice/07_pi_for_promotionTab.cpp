#include <omp.h>
#include <OmpTools.h>

#include "00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread, int n);
static void syntaxeFull(double* tabSumThread, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
    const double DX = 1 / (double) n;
    int sum = 0;
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    double tabSomme[NB_THREADS];

    for (int i = 0; i < n; i++)
	{
	tabSomme[i] = 0;
	}

#pragma omp parallel for
    for (int i = 0; i <= n; i++)
	{
	const int TID = OmpTools::getTid();
	double xi = i * DX;
	tabSomme[TID] += fpi(xi);
	}

    for (int i = 0; i < n; i++)
	{
	sum += tabSomme[i];
	}
    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

