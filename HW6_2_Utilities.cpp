#include "HW6_2_Utilities.h"
#include "dataStructures.h"
////////////////////////////////////////
//globals
////////////////////////////////////////

color g_tAmbientLight;		// The coefficient of ambient light

object** g_papoObjects;
light* g_patLightList;		// Array of lights
int g_iNumSpheres, g_iNumPlanes, g_iNumLights;	// The number of lights (not including ambient)
//######################################
//end globals
//######################################
