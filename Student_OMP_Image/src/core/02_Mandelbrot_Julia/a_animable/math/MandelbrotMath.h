#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float n)
	    {
	    float z = f(x, y, n);

	    if (z == n)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float hue01  = (1/n)*z; //plus jolie :)
		//calibreur.calibrer(&hue01);
		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}
	    ptrColor->w = 255; // opaque
	    }

    private:

	float f(float x, float y, uint n)
	    {
	    double a = 0;
	    double b = 0;
	    double aCopy = 0;
	    int k = 0;

	    while (true)
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;

		if (a * a + b * b > 4 || k >= n)
		    {
		    break;
		    }
		k++;
		}
	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
