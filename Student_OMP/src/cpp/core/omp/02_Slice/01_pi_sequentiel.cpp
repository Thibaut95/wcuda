#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiSequentiel_OK(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piSequentiel(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiSequentiel_OK(int n)
    {
    return isAlgoPI_OK(piSequentiel, n, "Pi Sequentiel");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piSequentiel(int n)
    {
    const double DX = 1 / (double) n;
    double xi;
    double somme = 0;

    for (int i = 0; i <= n; i++)
	{
	xi = i * DX;
	somme += fpi(xi);
	}
    return somme * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
