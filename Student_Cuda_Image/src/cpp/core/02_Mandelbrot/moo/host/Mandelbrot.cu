#include "Mandelbrot.h"

#include <iostream>
#include "Device.h"
#include <assert.h>
#include "MandelbrotMath.h"
#include <DomaineMath_GPU.h>
#include <Interval_GPU.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, int t, DomaineMath domaineMath);

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

Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h, int dt, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "MandelBrot_CUDA_rgba_uchar4", domaineMath), variateurAnimation(Interval<uint>(20, 120), dt)
    {
    // Input
    this->dt = dt;

    // Tools
    this->t = 0;					// protected dans super classe Animable

    }

Mandelbrot::~Mandelbrot(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Mandelbrot::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code entrainement cuda)
 */
void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("mandelbrot rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // le kernel est importer ci-dessus (ligne 19)
    float t = variateurAnimation.get();
    mandelbrot<<<dg,db>>>(ptrDevPixels,w,h,t, domaineMath);

    Device::lastCudaError("mandelbrot rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

