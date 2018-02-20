#ifndef ANIMATORABLE_I_H_
#define ANIMATORABLE_I_H_

#include <chrono>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Animatorable_I
    {

	/*--------------------------------------*\
 |*		Methodes		*|
	 \*-------------------------------------*/

    public :

	virtual void animationStep(void)=0;

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

    public:

	virtual ~Animatorable_I()
	    {
	    // Nothing its an interface
	    }

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
