#ifndef __HW6_2_UTILITIES
#define __HW6_2_UTILITIES
////////////////////////////////////////
//class decls
////////////////////////////////////////
class Ray;
class sphere;
class plane;
class object;
class vect;
class color;
struct light;
//######################################
//end class decls
//######################################

////////////////////////////////////////
//constants
////////////////////////////////////////
#define ImageW 400
#define ImageH 400
#define XVIEWINGANGLE 60.0
#define YVIEWINGANGLE 60.0
#define ZMAX -50.0
#define XMIN tan(XVIEWINGANGLE) * -ZMAX
#define YMIN tan(YVIEWINGANGLE) * -ZMAX
#define XMAX tan(XVIEWINGANGLE) * -ZMAX //zmax is negative, whereas x & y max are positive
#define YMAX tan(YVIEWINGANGLE) * -ZMAX //zmax is negative, whereas x & y max are positive
#define MAX_REFLECTION_TIMES_LIMIT 5
#define M_PI       3.14159265358979323846
//######################################
//end constants
//######################################
////////////////////////////////////////
//globals
////////////////////////////////////////
//represents the image sent out to the screen
//extern float g_framebuffer[ImageH][ImageW][3];
extern color g_tAmbientLight;		// The coefficient of ambient light
extern light* g_patLightList;		// Array of lights
extern int g_iNumSpheres, g_iNumPlanes, g_iNumLights; // The number of lights (not including ambient) in the scene
extern object** g_papoObjects;
extern light* g_patLightList;		// Array of lights
//######################################
//end globals
//######################################

////////////////////////////////////////
//public function declarations
////////////////////////////////////////

//=====Implemented in skeleton6-2=======
void setFramebuffer(int x, int y, float R, float G, float B);

//=======Implemented in Lighting========
color getLighting(Ray const &ray, vect const &point, int iObjectIndex);

//=======Implemented in fileio========
void readInGlobals(char *acSrcFile);

//======Implemented in rayTrace=======
color rayTrace(Ray &ray, int times);
Ray convertToRay(int x, int y);
//void generateRays(int x,int y);
//######################################
//end public function declarations
//######################################
#endif
