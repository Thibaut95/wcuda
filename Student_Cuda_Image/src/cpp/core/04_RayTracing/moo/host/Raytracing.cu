#include <iostream>
#include <assert.h>

#include "Device.h"
#include <assert.h>
#include "Raytracing.h"
#include "SphereCreator.h"
#include "Sphere.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void raytracing(uchar4* ptrPixel, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h,float t);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Raytracing::Raytracing(int nbSphere, const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "Raytracing_Cuda_RGBA_uchar4")
    {
    assert(w == h); // specific rippling

    // Inputs
    this->dt = dt;

    // Tools
    this->t = 0; // protected dans Animable
    this->nbSphere = nbSphere;
    this->sizeOctetSpheres = nbSphere * sizeof(Sphere); //octets

    SphereCreator sphereCreator(nbSphere, w, h); //sur la pile

    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    toGM(ptrTabSphere);

    //toCM(ptrTabSphere); //a implémenter plus tard dans le TP Raytracing advanced

    }

Raytracing::~Raytracing()
    {
    //rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Raytracing::process(uchar4* ptrPixel, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("raytracing rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // le kernel est importer ci-dessus (ligne 19)
    raytracing<<<dg,db>>>(ptrPixel, ptrDevTabSphere, nbSphere ,w,h,t);

    Device::lastCudaError("raytracing rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release

    }

/**
 * Override
 * Call periodicly by the API
 */
void Raytracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
/**
 * Copy the host tab sphere to the device
 */
void Raytracing::toGM(Sphere* ptrDevSphere)
    {
     Device::memcpyHToD(ptrDevTabSphere, ptrDevSphere, sizeOctetSpheres);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

