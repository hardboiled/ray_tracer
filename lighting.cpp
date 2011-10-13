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
/*//here for reference
color getDiffuse(vect &light, vect &n, in)
{
    //float d;
    color c;

 //   c.r = 0;
 //   c.g = 0;
 //   c.b = 0;
 //   color l;
 //   float nx, ny , nz;
	//vertex temp;
 //   for(int i = 0; i<g_iNumLights; ++i)
 //   {
	//   temp.x = -(p.x - g_patLightList[i].x);
	//   temp.y = -(p.y - g_patLightList[i].y);
	//   temp.z = -(p.z - g_patLightList[i].z);
	//   normalize(temp.x,temp.y,temp.z);
 //      d = dot(temp.x,temp.y,temp.z,
 //               p.nx, p.ny, p.nz);
 //       if(d>0.0f)
 //       {
 //          l = (d*g_patLightList[i].brightness);
 //    //      normalize(l.r, l.g, l.b);
 //          c = c + l;
 //       }
 //   }
 //   //scale(c);
 //   //c = c / ((float)g_iNumLights);
 //   if(c.r < 0.0f ||c.g < 0.0f ||c.b < 0.0f)
 //   {
 //       l = l;
 //   }
 //   c = k * c;
    return c;
}
*/
/*
color getSpecular(Ray &ray, vect &n, light &l, vect &r, float t, int alpha)
{
    color c;
    float d;
    color c;
    c.r = 0;
    c.g = 0;
    c.b = 0;
    color l;
    float nx, ny, nz, dotProd;
	vertex light, reflection, half;
    for(int i = 0; i<g_iNumLights; ++i)
    {
	   light.x = -(p.x - g_patLightList[i].x);
	   light.y = -(p.y - g_patLightList[i].y);
	   light.z = g_patLightList[i].z - p.z;
       
       dotProd = dot(light.x,light.y,light.z, p.nx, p.ny, p.nz);
       reflection.x =  dotProd * p.nx - light.x;
       reflection.y =  dotProd * p.ny - light.y;
       reflection.z =  dotProd * p.nz - light.z;
       reflection = -1.0 *light + -2.0 * reflection;
       normalize(reflection.x,reflection.y,reflection.z);
       
       d = power(dot(p.nx,p.ny,p.nz,
                reflection.x, reflection.y, reflection.z), alpha);
       if(d>0.0f)
       {
           l = (d*g_patLightList[i].brightness);
           c = c + l;
       }
    }
    c = k * c;


    return c;
}
*/
