#include "dataStructures.h"
#include "trig.h"
#include "HW6_2_Utilities.h"
#include<fstream>
#include<SDL/SDL.h>
#include<math.h>

SDL_Surface *screen;
SDL_Event event;

void calculate_image(void)
{
	color c;
    Ray ray;
    Uint32 *pixmem32;
    Uint32 sdl_color;
    Uint8 *p;

	for(int i=ImageH-1; i>=0; --i)
    {
        for(int j=ImageW-1;j>=0; --j)
        {
            ray = convertToRay(i, j);
            c = rayTrace(ray, 0);
            c.scale();

            /* Make p point to the place we want to draw the pixel */
            p = (Uint8 *)screen->pixels + ((ImageW - 1) - j) * screen->pitch + i * screen->format->BytesPerPixel;

            /* Draw the pixel! */
            *p=(Uint8)(0xFF * c.b);
            p++;
            *p=(Uint8)(0xFF * c.g);
            p++;
            *p=(Uint8)(0xFF * c.r);
        }
    }


}

void deleteGlobals()
{
    if(g_patLightList != 0)
    {
        delete[] g_patLightList;
    }
    if(g_papoObjects != 0)
    {
        for(int i=0; i<g_iNumPlanes + g_iNumSpheres;++i)
        {
            delete g_papoObjects[i];
        }
        delete[] g_papoObjects;
    }
}

void run()
{
    bool running = true;

    calculate_image();
    SDL_Flip(screen);

    while (running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            } else if(event.type == SDL_QUIT) {
                running = false;
            }
        }
    }
}


int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(ImageW, ImageH, 32, SDL_SWSURFACE);

    if(argc > 1) {
        readInGlobals(argv[1]);
    } else {
        readInGlobals("tester.dat");
    }

	run();
    deleteGlobals();
	return 0;
}
