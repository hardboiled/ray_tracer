#include "HW6_2_Utilities.h"
#include "dataStructures.h"
#include "trig.h"
#include<math.h>


////////////////////////////////////////
//private function declarations
////////////////////////////////////////
bool obscured(vect const &point, int iObjectIndex, vect const &light);
//######################################
//end private function declarations
//######################################

////////////////////////////////////////
//private functions
////////////////////////////////////////
bool obscured(vect const &point, int iObjectIndex, vect const &light)
{
    float t = (float)(~(1<<31));
    Ray lightRay = Ray(light, point - light);
    normalize(lightRay.d);
    for(int i = 0; i<g_iNumPlanes + g_iNumSpheres; ++i)
    {
        if(i!=iObjectIndex && g_papoObjects[i]->intersect(lightRay, t))
        {   
            if(length(lightRay.d * t) < length(point - light))
            {
                return true;
            }
        }
    }
    return false;
}
//######################################
//end private functions
//######################################
////////////////////////////////////////
//public functions
////////////////////////////////////////
color getLighting(Ray const &ray, vect const &point, int iObjectIndex)
{
    //start with ambient light
    color c = g_papoObjects[iObjectIndex]->kamb * g_tAmbientLight, cDiffuse, cSpec;
    vect r, tLightVector;
    float dotDiffuse, dotSpec;
    for(int i = 0; i<g_iNumLights; ++i)
    {
        if(!obscured(point, iObjectIndex, g_patLightList[i].p))
        {
            tLightVector = g_patLightList[i].p - point;
            normalize(tLightVector);
            dotDiffuse = dot(tLightVector, g_papoObjects[iObjectIndex]->getNormal(point));
            dotSpec = dot(g_papoObjects[iObjectIndex]->getReflection(tLightVector, point), (-1.0*ray.d));
            if(dotDiffuse > 0.0)
            {
                cDiffuse = cDiffuse + g_patLightList[i].brightness * dotDiffuse;
            }
            if(dotSpec > 0.0)
            {
                cSpec = cSpec + g_patLightList[i].brightness * power(dotSpec, g_papoObjects[iObjectIndex]->shininess);
            }
        }
    }
    //final lighting calculation
    c = c + g_papoObjects[iObjectIndex]->kdiff * cDiffuse + g_papoObjects[iObjectIndex]->kspec * cSpec;
    //only the base of the object is shown
    c = c * g_papoObjects[iObjectIndex]->c;
    return c;
}
//######################################
//end public functions
//######################################
