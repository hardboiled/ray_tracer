#include "dataStructures.h"
#include "trig.h"
#include <math.h>
#define MINIMUM_INTERSECTION_VALUE 0.01
////////////////////////////////////////
//class functions
////////////////////////////////////////
//color
color::color()
{
    r=0;
    g=0;
    b=0;
}
color::color(float r,float g, float b)
{
    this->r = r;
    this->g=g;
    this->b=b;
}
void color::scale()
{
    float fMax = this->r;
    if(fMax<this->g)
    {
        fMax = this->g;
    }
    if(fMax < this->b)
    {
        fMax = this->b;
    }

    if(fMax > 1.0)
    {
        *this = (*this)/fMax;
    }
}
//## end color
//vect
vect::vect()
{
    x=0.0;
    y=0.0;
    z=0.0;
}
vect::vect(float x,float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}
//## end vect
//Ray
Ray::Ray(vect p0, vect d)
{
    this->p0 = p0;
    this->d = d;
}
//## end ray
vect object::getReflection(vect v, vect point)
{
    vect n = getNormal(point);
    normalize(n);
    normalize(v);    
    return 2.0 * dot(n, v) * n - v;
}
//sphere
sphere::sphere()
{
    r = 0.0;
    eType = TYPE_SPHERE;
}

sphere::sphere(vect const &pc, float r)
{
    this->pc = pc;
    this->r = r;
    this->eType = TYPE_SPHERE;
}

bool sphere::intersect(Ray const &ray, float &t)
{
    vect e0 = this->pc - ray.p0;
    float v = dot(e0, ray.d), d, t1, t2;
    vect point;
    float disc = power(this->r) - (dot(e0,e0)- power(v));
    if(!(disc <= 0))
    {
        d = sqrt(disc);
        point = ray.p0 + (v - d) * ray.d;
        t1 = (point.z - ray.p0.z)/ray.d.z;
        
        d = -sqrt(disc);
        point = ray.p0 + (v - d) * ray.d;
        t2 = (point.z - ray.p0.z)/ray.d.z;
        
        if(t1 > MINIMUM_INTERSECTION_VALUE || t2 > MINIMUM_INTERSECTION_VALUE)
        {
            (t2 > MINIMUM_INTERSECTION_VALUE) ? t = t2 : t = t1;
            if(t1 > MINIMUM_INTERSECTION_VALUE && t1 < t)
            {
                t = t1;
            }
            return true;
        }
    }
    return false;
}
vect sphere::getNormal(const vect &point)
{
    vect n = point - this->pc;
    normalize(n);
    return n;
}
//## end sphere
//plane
plane::plane()
{
    a0=0;
    b0=0;
    c0=0;
    d0=0;
    eType = TYPE_PLANE;
}
plane::plane(float a, float b, float c, float d)
{
    this->a0 = a;
    this->b0 = b;
    this->c0 = c;
    this->d0 = d;

    this->eType = TYPE_PLANE;
}
bool plane::intersect(Ray const &ray, float &t)
{
	float dProd = dot(ray.d.x, ray.d.y, ray.d.z, this->a0, this->b0,this->c0);
	if(dProd <= 0)
	{
		t = -(dot(ray.p0.x, ray.p0.y, ray.p0.z, this->a0, this->b0,this->c0) + this->d0)/(dProd);
        if(t > MINIMUM_INTERSECTION_VALUE)
		{
			return true;
		}
	}
	return false;
}
vect plane::getNormal(const vect &point)
{
    vect v(a0,b0,c0);
    normalize(v);
    return v;
}
//## end plane
//######################################
//end class functions
//######################################
////////////////////////////////////////
//overloaded operators
////////////////////////////////////////
//color
color operator* (float const &f, color const &c)
{
    color t;
    t.r = c.r * f;
    t.g = c.g * f;
    t.b = c.b * f;
    return t;
}

color operator* (color const &c, float const &f)
{
    color t;
    t.r = c.r * f;
    t.g = c.g * f;
    t.b = c.b * f;
    return t;
}

color operator/ (color const &c, float const &f)
{
    color t;
    t.r = c.r/f;
    t.g = c.g/f;
    t.b = c.b/f;
    return t;
}
color operator+ (color const &c1, color const &c2)
{
    color t;
    t.r = c1.r + c2.r;
    t.g = c1.g + c2.g;
    t.b = c1.b + c2.b;
    return t;
}
color operator* (color const &c1, color const &c2)
{
    color t;
    t.r = c1.r * c2.r;
    t.g = c1.g * c2.g;
    t.b = c1.b * c2.b;
    return t;
}
bool operator== (color const &c1, color const &c2) 
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}
//##end color
//vect
vect operator- (vect const &v1, vect const &v2)
{
    vect v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}
vect operator+ (vect const &v1, vect const &v2)
{
    vect v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}
vect operator* (float const &f, vect const &v)
{
    vect t;
    t.x = v.x*f;
    t.y = v.y*f;
    t.z = v.z*f;
    return t;
}
vect operator* (vect const &v, float const &f)
{
    vect t;
    t.x = v.x*f;
    t.y = v.y*f;
    t.z = v.z*f;
    return t;
}

vect operator/ (vect const &v, float const &f)
{
    vect t;
    t.x = v.x/f;
    t.y = v.y/f;
    t.z = v.z/f;
    return t;
}
//##end vect
//######################################
//end overloaded operators
//######################################