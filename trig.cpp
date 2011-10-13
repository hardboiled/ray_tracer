#include "HW6_2_Utilities.h"
#include "dataStructures.h"
#include "trig.h"
#include<math.h>

float power(float f, int e)
{
    float p = f;
    for(int i = 1; i<e; ++i)
    {
        p*=f;
    }
    return p;
}

// Sets pixel x,y to the color RGB
// Normalizes the vector passed in
void normalize(float& x, float& y, float& z) {
	float temp = sqrt(x*x+y*y+z*z);
	if (temp > 0.0) {
		x /= temp;
		y /= temp;
		z /= temp;
	} else {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
}

void normalize(vect &v) {
	float temp = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	if (temp > 0.0) {
		v.x /= temp;
		v.y /= temp;
		v.z /= temp;
	} else {
		v.x = 0.0;
		v.y = 0.0;
		v.z = 0.0;
	}
}

// Returns dot product of two vectors
float dot(float x1, float y1, float z1, float x2, float y2, float z2) {
	return (x1*x2+y1*y2+z1*z2);
}

float dot(vect v1, vect v2) {
	return (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}
// Returns angle between two vectors (in radians)
float angle(float x1, float y1, float z1, float x2, float y2, float z2) {
	normalize(x1,y1,z1);
	normalize(x2,y2,z2);
	return  acos(dot(x1,y1,z1,x2,y2,z2));
}

float angle(vect v1, vect v2) {
	normalize(v1);
	normalize(v2);
	return  acos(dot(v1,v2));
}


vect crossProduct(vect v1, vect v2)
{
   vect v3;
   //[i  j  k]
   //[x1 y1 z1]
   //[x2 y2 z2]
   v3.x = v1.y * v2.z - v2.y * v1.z;
   v3.y = v1.z * v2.x - v2.z * v1.x;
   v3.z = v1.x * v2.y - v2.x * v1.y;
   return v3;
}

//treat the vertices like vectors
vect projection(vect &vb, vect &va)
{
    return (vb + va)/(sqrt(power((va.x)) + power(va.y) + power(va.z)));
}

void quadratic(float a, float b, float c, float &t1, float &t2)
{
    t1 = (-b + sqrt(power(b) - 4 * a * c))/(2*a);
    t2 = (-b - sqrt(power(b) - 4 * a * c))/(2*a);
}

float length(vect v)
{
    return sqrt(power(v.x) + power(v.y) + power(v.z));
}