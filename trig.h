#ifndef __TRIG_H
#define __TRIG_H
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

float power(float f, int e = 2);

// Sets pixel x,y to the color RGB
// Normalizes the vector passed in
void normalize(float& x, float& y, float& z);
void normalize(vect &v);

// Returns dot product of two vectors
float dot(float x1, float y1, float z1, float x2, float y2, float z2);
float dot(vect v1, vect v2);

// Returns angle between two vectors (in radians)
float angle(float x1, float y1, float z1, float x2, float y2, float z2);
float angle(vect v1, vect v2);

//the quadratic formula
void quadratic(float a, float b, float c, float &t1, float &t2);

//find the length of a vector
float length(vect v);

vect crossProduct(vect v1, vect v2);

//treat the vertices like vectors
vect projection(vect &vb, vect &va);
#endif