#include "dataStructures.h"
#include "trig.h"
#include "HW6_2_Utilities.h"
#include<fstream>
#include<SDL/SDL.h>
#include<math.h>

/******************************************************************
	Notes:
	This is the same utility as in the earlier homework assignment.
	Image size is 400 by 400 by default.  You may adjust this if
		you want to.
	You can assume the window will NOT be resized.
	Call clearFramebuffer to clear the entire framebuffer.
	Call setFramebuffer to set a pixel.  This should be the only
		routine you use to set the color (other than clearing the
		entire framebuffer).  drawit() will cause the current
		framebuffer to be displayed.
	As is, your ray tracer should probably be called from
		within the display function.  There is a very short sample
		of code there now.  You can replace that with a call to a
		function that raytraces your scene (or whatever other
		interaction you provide.
	You may add code to any of the subroutines here,  You probably
		want to leave the drawit, clearFramebuffer, and
		setFramebuffer commands alone, though.
  *****************************************************************/

//extern float g_framebuffer[ImageH][ImageW][3];
SDL_Surface *screen;
SDL_Event event;

// Draws the scene
void drawit(void)
{
//   glDrawPixels(ImageW,ImageH,GL_RGB,GL_FLOAT,g_framebuffer);
//   glFlush();
}

// Clears g_framebuffer to black
//void clearFramebuffer()
//{
//	int i,j;
//
//	for(i=0;i<ImageH;i++) {
//		for (j=0;j<ImageW;j++) {
//			g_framebuffer[i][j][0] = 0.0;
//			g_framebuffer[i][j][1] = 0.0;
//			g_framebuffer[i][j][2] = 0.0;
//		}
//	}
//}

// Sets pixel x,y to the color RGB
//void setFramebuffer(int x, int y, float R, float G, float B)
//{
//	if (R<=1.0)
//		if (R>=0.0)
//			g_framebuffer[x][y][0]=R;
//		else
//			g_framebuffer[x][y][0]=0.0;
//	else
//		g_framebuffer[x][y][0]=1.0;
//	if (G<=1.0)
//		if (G>=0.0)
//			g_framebuffer[x][y][1]=G;
//		else
//			g_framebuffer[x][y][1]=0.0;
//	else
//		g_framebuffer[x][y][1]=1.0;
//	if (B<=1.0)
//		if (B>=0.0)
//			g_framebuffer[x][y][2]=B;
//		else
//			g_framebuffer[x][y][2]=0.0;
//	else
//		g_framebuffer[x][y][2]=1.0;
//}

void calculate_image(void)
{
	//The next two lines of code are for demonstration only.
	//They show how to draw a line from (0,0) to (100,100)
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
//            c = c * 5;

            /* Make p point to the place we want to draw the pixel */
            p = (Uint8 *)screen->pixels + ((ImageW - 1) - j) * screen->pitch + i * screen->format->BytesPerPixel;

            /* Draw the pixel! */
            *p=(Uint8)(0xFF * c.b);
            p++;
            *p=(Uint8)(0xFF * c.g);
            p++;
            *p=(Uint8)(0xFF * c.r);

            //setFramebuffer(j, i, c.r, c.g, c.b);
//            sdl_color = SDL_MapRGB( screen->format, 255, 255, 255);
//            pixmem32 = (Uint32*) screen->pixels  + j + i;
//            *pixmem32 = sdl_color;
        }
    }


}

void init(void)
{
//	clearFramebuffer();
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

//	glutInit(&argc,argv);
//	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//	glutInitWindowSize(ImageW,ImageH);
//	glutInitWindowPosition(100,100);

    if(argc > 1) {
        readInGlobals(argv[1]);
    } else {
        readInGlobals("tester.dat");
    }

	init();	
	run();
    deleteGlobals();
	return 0;
}
