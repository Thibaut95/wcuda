#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
#include "cudaTools.h"
#include "Sphere.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RaytracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RaytracingMath(int w, int h, int nbSphere, Sphere* ptrDevTabSphere)
	    {
	    this->nbSphere = nbSphere;
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    this->ptrDevCurrentSphere = nullptr;
	    this->ptrDevCandidatSphere = nullptr;
	    this->dim2 = w / 2.f;
	    this->xySol = make_float2(0, 0);
	    }

	// constructeur copie automatique car pas pointeur dans RaytracingMath

	__device__
	       virtual ~RaytracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    initParams(i, j);
	    computeColorPixel();
	    ptrColor = colorPixel(t, ptrColor);
	    ptrColor->w = 255; // opaque
	    }

    private:
	__device__
	void computeColorPixel()
	    {
	    for (int a = 0; a < nbSphere; a++)
		{
		ptrDevCurrentSphere = &ptrDevTabSphere[a];
		hCarree = ptrDevCurrentSphere->hCarre(xySol);
		if (ptrDevCurrentSphere->isEnDessous(hCarree))
		    {
		    hasColor = true;
		    dzCurrent = ptrDevCurrentSphere->dz(hCarree);
		    distanceCurrent = ptrDevCurrentSphere->distance(dzCurrent);
		    if (distanceCurrent < distance || a == 0)
			{
			dz = dzCurrent;
			distance = distanceCurrent;
			ptrDevCandidatSphere = ptrDevCurrentSphere;
			}
		    }
		}
	    }
	
	__device__
	void initParams(int i, int j)
	    {
	    xySol.x = i;
	    xySol.y = j;
	    hCarree = 0;
	    dz = 0;
	    distance = 0;
	    hasColor = false;
	    }

	__device__
	uchar4* colorPixel(float t, uchar4* ptrColor)
	    {
	    if (hasColor)
		{
		brightness = ptrDevCandidatSphere->brightness(dz);
		float h = ptrDevCandidatSphere->getHueStart() + ptrDevCandidatSphere->hue(t);
		ColorTools::HSB_TO_RVB(h, 1, brightness, ptrColor);
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    return ptrColor;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float hCarree;
	float2 xySol;
	float dz;
	float dzCurrent;
	float distance;
	float distanceCurrent;
	float brightness;
	bool hasColor;
	float dim2;
	int nbSphere;
	Sphere* ptrDevTabSphere;
	Sphere* ptrDevCurrentSphere;
	Sphere* ptrDevCandidatSphere;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
