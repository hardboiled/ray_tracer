#ifndef __DATASTRUCTURES_H
#define __DATASTRUCTURES_H
enum EObjectType {
    TYPE_SPHERE,
    TYPE_PLANE
};

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
//data structures
////////////////////////////////////////
class color {
public:
	float r, g, b;		// Color (R,G,B values)
    color();
    color(float r,float g, float b);
    void scale();
};

class vect {
public:
	float x, y, z;		// Color (R,G,B values)
    vect();
    vect(float x, float y, float z);
};

class Ray
{
public:
    vect p0;
    vect d;
    Ray(){}
    Ray(vect p0, vect d);    
};

class object
{
public:
    EObjectType eType;
    color c;
    float reflPerc;
	float kamb;			// The coefficient of ambient reflection
	float kdiff;		// The coefficient of diffuse reflection
	float kspec;		// The coefficient of specular reflection
	int shininess;		// The exponent to use for Specular Phong Illumination
    virtual bool intersect(Ray const &ray, float &t){ return false; }
    vect getReflection(vect v, vect point);
    //this function assumes you already have a valid point
    virtual vect getNormal(const vect &point){ return vect();};
};

class sphere : public object
{
public:
    vect pc;
    float r;
    sphere();
    sphere(vect const &pc, float r);
    bool intersect(Ray const &ray, float &t);
    vect getNormal(vect const &point);
};

class plane : public object
{
public:
	float a0,b0,c0,d0;
    plane();
    plane(float a, float b, float c, float d);
    bool intersect(Ray const &ray, float &t);
    vect getNormal(vect const &point);
};

struct light {
	// Note: assume all lights are white
	vect p;		// x, y, z coordinates of light
	color brightness;	// Level of brightness of light (0.0 - 1.0)
};
//######################################
//end data structures
//######################################
////////////////////////////////////////
//overloaded operator declarations
////////////////////////////////////////
color operator* (float const &f, color const &c);
color operator* (color const &c, float const &f);
color operator* (color const &c1, color const &c2);
color operator/ (color const &c, float const &f);
color operator+ (color const &c1, color const &c2);
bool operator== (color const &c1, color const &c2);

vect operator- (vect const &v1, vect const &v2);
vect operator+ (vect const &v1, vect const &v2);
vect operator* (float const &f, vect const &v);
vect operator* (vect const &v, float const &f);
vect operator/ (vect const &v, float const &f);
//######################################
//end overloaded operator declarations
//######################################
#endif