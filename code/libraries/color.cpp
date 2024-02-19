/*

	color.cpp
	di Mario Gabriele Carofano

*/

/*	************************************************************************* */
//	LIBRERIE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*	************************************************************************* */
//	FUNZIONI ACCESSORIE

void getRandomColor(float* color) {
	color[0] = ((float) rand() / RAND_MAX);
	color[1] = ((float) rand() / RAND_MAX);
	color[2] = ((float) rand() / RAND_MAX);
}

void convertHEXtoRGB(float* color, int hexValue) {
	color[0] = ((hexValue >> 16) & 0xFF) / 255.0;
	color[1] = ((hexValue >> 8) & 0xFF) / 255.0;
	color[2] = ((hexValue) & 0xFF) / 255.0;
}

/*	************************************************************************* */
//	ENUMERAZIONI, COSTANTI E VARIABILI GLOBALI

const float WHITE[]		= {1.0, 1.0, 1.0};
const float GRAY_90[]	= {0.9, 0.9, 0.9};
const float GRAY_80[]	= {0.8, 0.8, 0.8};
const float GRAY_70[]	= {0.7, 0.7, 0.7};
const float GRAY_60[]	= {0.6, 0.6, 0.6};
const float GRAY_50[]	= {0.5, 0.5, 0.5};
const float GRAY_40[]	= {0.4, 0.4, 0.4};
const float GRAY_30[]	= {0.3, 0.3, 0.3};
const float GRAY_20[]	= {0.2, 0.2, 0.2};
const float GRAY_10[]	= {0.1, 0.1, 0.1};
const float BLACK[]		= {0.0, 0.0, 0.0};

const float RED[]	= {1.0, 0.0, 0.0};
const float GREEN[]	= {0.0, 1.0, 0.0};
const float BLUE[]	= {0.0, 0.0, 1.0};

const float CYAN[]		= {0.0, 1.0, 1.0};
const float PURPLE[]	= {1.0, 0.0, 1.0};
const float YELLOW[]	= {1.0, 1.0, 0.0};
const float YELLOW_20[]	= {0.2, 0.2, 0.0};

const float BROWN[]			= {0.43, 0.15, 0.05};
const float IVORY[]			= {1.0, 1.0, 0.941};
const float BEIGE[]			= {0.882, 0.776, 0.6};
const float BLUE_VIOLET[]	= {0.541, 0.168, 0.886};
const float LAVENDER[]		= {0.902, 0.902, 0.98};
const float DARK_BROWN[]	= {0.36, 0.25, 0.2};

const float CHRISTMAS_GREEN[]	= {0.192, 0.474, 0.345};
const float CHRISTMAS_RED[]		= {0.662, 0.211, 0.235};

/*	************************************************************************* */
/*	RIFERIMENTI
	
*/
