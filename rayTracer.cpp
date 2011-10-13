#include "dataStructures.h"
#include "trig.h"
#include <cmath>
#include "HW6_2_Utilities.h"


////////////////////////////////////////
//private function declarations
////////////////////////////////////////
bool rayIntersect(Ray &ray, int &iObjectIndex, float &t);
//######################################
//end private function declarations
//######################################
float m_fXOffset = -ZMAX*tan(XVIEWINGANGLE* M_PI/180.0)/(2.0 * ImageW);
float m_fYOffset = -ZMAX*tan(YVIEWINGANGLE* M_PI/180.0)/(2.0 * ImageH);
bool inRange(Ray ray, float t)
{
    if(std::abs(ray.d.x*t + ray.p0.x) < -ZMAX*tan(XVIEWINGANGLE* M_PI/180.0)
        && std::abs(ray.d.y*t + ray.p0.y) < -ZMAX*tan(YVIEWINGANGLE* M_PI/180.0)
        && std::abs(ray.d.z*t + ray.p0.z) < -ZMAX)
    {
        return true;
    }
    return false;
}

Ray convertToRay(int x, int y)
{
    Ray ray;
    ray.d.x = ((x - (ImageW>>1))* -ZMAX*tan(XVIEWINGANGLE* M_PI/180.0))/ ImageW + m_fXOffset; //x * -ZMAX*tan(XVIEWINGANGLE* M_PI/180.0) / ImageW - ImageW/2.0 + -ZMAX*sin(XVIEWINGANGLE* M_PI/180.0);
    ray.d.y = ((y - (ImageH>>1))* -ZMAX*tan(YVIEWINGANGLE* M_PI/180.0))/ ImageH + m_fYOffset;//y * -ZMAX*tan(YVIEWINGANGLE* M_PI/180.0) / ImageH - ImageH/2.0 + -ZMAX*sin(XVIEWINGANGLE* M_PI/180.0);
    ray.d.z = ZMAX;
    normalize(ray.d);
    return ray;
}

color rayTrace(Ray &ray, int times)
{
	float t = (float)(~(1<<31));
    int iObjectIndex = 0;
    color c, cRefl;
    vect point;
	
    if(times < MAX_REFLECTION_TIMES_LIMIT)
    {
        if(rayIntersect(ray, iObjectIndex, t))
        {
            point = ray.d * t + ray.p0;
            Ray newRay= Ray(point, g_papoObjects[iObjectIndex]->getReflection((-1.0)*ray.d,point));
            cRefl = rayTrace(newRay, times + 1);
            c = getLighting(ray, point,iObjectIndex) *(1 - g_papoObjects[iObjectIndex]->reflPerc)  + g_papoObjects[iObjectIndex]->reflPerc * cRefl;
	    }
    }
	return c;
}


bool rayIntersect(Ray &ray, int &iObjectIndex, float &t)
{
	float tvalue = (float)(~(1<<31));
    t = tvalue;
    bool bFound = false;
    for(int i = 0; i<g_iNumSpheres + g_iNumPlanes; ++i)
	{
        if(g_papoObjects[i]->intersect(ray, tvalue))
		{
            if(tvalue < t)
            {
			    iObjectIndex = i;
			    t = tvalue;
                bFound = true;
            }
		}
	}
	return bFound;
}
