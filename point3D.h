#ifndef POINT3D_H_INC
#define POINT3D_H_INC

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class point3D 
{
    double x, y, z;
public:
    point3D(void) : x(0.0), y(0.0), z(0.0) { }
    point3D(double new_x, double new_y, double new_z) : x(0.0), y(0.0), z(0.0)
    {
        set_x(new_x);
        set_y(new_y);
        set_z(new_z);
    }
    
    void print(void);
    void read(void);
    
    double distance(point3D other);
    
    point3D operator+(point3D other)
    {
        return point3D(x+other.x, y+other.y, z+other.z);
    }
    point3D operator-(point3D other)
    {
        return point3D(x-other.x, y-other.y, z-other.z);
    }
    point3D operator*(double mult)
    {
        return point3D(x*mult, y*mult, z*mult);
    }
    
    double get_x(void) const { return x; }
    double get_y(void) const { return y; }
    double get_z(void) const { return z; }
    
    void set_x(double new_x) 
    {
        x = new_x;
        return;
    }
    void set_y(double new_y)
    {
        y = new_y;
        return;
    }
    void set_z(double new_z)
    {
        z = new_z;
        return;
    }
    
    
};

inline point3D operator*(const double & m, const point3D & p)
{
    return point3D(p.get_x()*m, p.get_y()*m, p.get_z()*m);
}

#endif
