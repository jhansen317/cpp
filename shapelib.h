#ifndef SHAPELIB_H_INC
#define SHAPELIB_H_INC

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "point3D.h"
#include "ccc_win.h"
#include <vector>


using namespace std;

const double PI = 3.141592653589793238462;


/* Rotates a point3D around the origin of the coordinate system. Takes arguments
point3D and x, y, z rotation angles. Returns point3D */

point3D rotate(point3D apoint, double x_rot, double y_rot, double z_rot)
{
    double x = apoint.get_x(), y = apoint.get_y(), z = apoint.get_z();
    double xradns = PI/180*x_rot;
    double yradns = PI/180*y_rot;
    double zradns = PI/180*z_rot;
    
    double rot_mat[3][3];
    rot_mat[0][0] = cos(yradns)*cos(zradns);
    rot_mat[0][1] = -(cos(xradns)*sin(zradns)) + 
                     (sin(xradns)*sin(yradns)*cos(zradns));
    rot_mat[0][2] =  (sin(xradns)*sin(zradns)) + 
                     (cos(xradns)*sin(yradns)*cos(zradns));
    rot_mat[1][0] =  cos(yradns)*sin(zradns);
    rot_mat[1][1] =  (cos(xradns)*cos(zradns)) + 
                     (sin(xradns)*sin(yradns)*sin(zradns));
    rot_mat[1][2] = -(sin(xradns)*cos(zradns)) + 
                     (cos(xradns)*sin(yradns)*sin(zradns));
    rot_mat[2][0] = -sin(yradns);
    rot_mat[2][1] =  sin(xradns)*cos(yradns);
    rot_mat[2][2] =  cos(xradns)*cos(yradns);
    
    
    return point3D((rot_mat[0][0]*x + rot_mat[0][1]*y + rot_mat[0][2]*z), 
                   (rot_mat[1][0]*x + rot_mat[1][1]*y + rot_mat[1][2]*z),
                   (rot_mat[2][0]*x + rot_mat[2][1]*y + rot_mat[2][2]*z));
} 



/* Projects a 3D point onto a 2D plane (ie screen) as if the z-axis is 
prodtruding/receding at a given angle, defaults to 45 degrees. Takes arguments
point3D and optional z-axis projection angle. Returns 2D Point from the book's
graphics library. */

Point project(point3D apoint, double projAngle=45)
{
    double x = apoint.get_x(), y = apoint.get_y(), z = apoint.get_z();
    double rot_mat[3][3];
    rot_mat[0][0] = 1;
    rot_mat[0][1] = 0;
    rot_mat[0][2] = 0.5 * cos(PI/180 * projAngle);
    rot_mat[1][0] = 0;
    rot_mat[1][1] = 1;
    rot_mat[1][2] = 0.5 * sin(PI/180 * projAngle);
    rot_mat[2][0] = 0;
    rot_mat[2][1] = 0;
    rot_mat[2][2] = 0;
    
    
    return Point((rot_mat[0][0]*x + rot_mat[0][1]*y + rot_mat[0][2]*z), 
                   (rot_mat[1][0]*x + rot_mat[1][1]*y + rot_mat[1][2]*z));
}


/* draws a handy little coordinate plane for reference */
void drawAxes(void)
{
    Point x1 = project(point3D(-10, 0, 0));
    Point x2 = project(point3D(10, 0, 0));
    Point y1 = project(point3D(0, -10, 0));
    Point y2 = project(point3D(0, 10, 0));
    Point z1 = project(point3D(0, 0, -10));
    Point z2 = project(point3D(0, 0, 10));
    cwin << Line(x1, x2);
    cwin << Message(x1, "(-10, 0, 0)");
    cwin << Message(x2, "(10, 0, 0)");
    cwin << Line(y1, y2);
    cwin << Message(y1, "(0, -10, 0)");
    cwin << Message(y2, "(0, 10, 0)");
    cwin << Line(z1, z2);
    cwin << Message(z1, "(0, 0, -10)");
    cwin << Message(z2, "(0, 0, 10)");
    return;
}

/* Base class for all 1, 2, and 3 dimensional shapes. Contains a single point3D
and a name. */

class shape
{
    point3D myPoint;
    string myName;
    
public:
    virtual ~shape(void) { }
    
    shape(point3D p, const string & n = "") : 
        myPoint(p), myName(n) { }
    
    virtual string tellName(void) const {  return myName; }   
    
    point3D get_point(void) { return myPoint; }
    
    virtual void printInfo(void) = 0; 
    
    virtual void draw(void) = 0;
};

/* One dimensional derived abstract class. */

class OneD : public shape 
{
    string shapetype;
    
public:
    
    OneD(point3D one, const string & n = "", 
                      const string & t = "One Dimensional")
    : shape(one, n), shapetype(t) { }
    
    virtual string tellType(void) const { return shapetype; }
    
};

/* Two dimensional derived abstract class */

class TwoD : public shape
{
    string shapetype;
    
public:
    
    TwoD(point3D one, const string & n = "", 
                      const string & t = "Two Dimensional")
    : shape(one, n), shapetype(t) { }
    
    virtual string tellType(void) const { return shapetype; }
    

};

/* Three dimensional derived abstract class */

class ThreeD : public shape
{
    string shapetype;
public:
    ThreeD(point3D one, const string & n = "",
                        const string & t = "Three Dimensional")
    : shape(one, n), shapetype(t) { }
    
    virtual string tellType(void) const { return shapetype; }
};



class line : public OneD
{
    point3D endpoint;
public:
     line(point3D start, point3D end, const string & n ="Line") 
     : OneD(start, n), endpoint(end) { }
     
     point3D get_start(void) { return get_point(); }
        
     point3D get_end(void) { return endpoint; }
     
     double get_length(void) { return get_point().distance(endpoint); }
     
     virtual void printInfo(void) 
     {
         cout << "\nI'm a " << tellName() << '!';
         cout << "\nMy dimensionality is: " << tellType();      
         cout << "\nFirst point is: ";
         get_start().print();
         cout << "\nSecond point is: ";
         get_end().print();
         cout << "\nMy length is: " << get_length() << "\n";
         
     }
};

// takes in 4 points that define a cubic bezier curve
class curve : public OneD
{
    point3D control1;
    point3D control2;
    point3D end;
    vector<point3D> pointvec;
    
    // populates the point vector with 100 points 
    void fill_points(void)
    {
        double inc=0.01;
        point3D point1, point2, point3, point4, point5, point6;
         
        for (double i=inc; i<=1; i+=inc)
        {
            point1 = get_point() + (control1 - get_point()) * i;
            point2 = control1 + (control2 - control1) * i;
            point3 = control2 + (end - control2) * i;
            point4 = point1 + (point2 - point1) * i; 
            point5 = point2 + (point3 - point2) * i;
            point6 = point4 + (point5 - point4) * i;
            pointvec.push_back(point6);
        }
        return;
    }
    
public:
    curve(point3D s, point3D c1, point3D c2, 
          point3D e, const string & n="Curve")
    : OneD(s, n), control1(c1), control2(c2), 
      end(e), pointvec(vector<point3D>()) 
    {
        fill_points();
    }

    void draw(void)
    {
        cwin << project(get_point()) 
             << project(control1) 
             << project(control2) 
             << project(end);
        for(short i=0; i<pointvec.size()-2; i++)
        {
            cwin << Line(project(pointvec[i]), project(pointvec[i+1]));
        }
        return;
    }
    double get_length(void)
    {
        double accumulator;
        for(short i; i<pointvec.size()-2; i++)
        {
            accumulator += pointvec[i].distance(pointvec[i+1]);
        }
        return accumulator;
    }
    void printInfo(void)
    {
        cout << "\nI'm a " << tellName() << '!';
        cout << "\nMy dimensionality is: " << tellType();
        get_point().print();
        control1.print();
        control2.print();
        end.print();
        cout << "\nMy length is: " << get_length();
        draw();
    }
};

// inherits point and adds radius and 3 rotation angles
class circle : public TwoD 
{
    double radius, xrot, yrot, zrot;
    vector<point3D> pointvec;
public:
    circle(point3D one, double r, double x=0, 
                        double y=0, double z=0, const string & n = "Circle")
    : TwoD(one, n), radius(r), xrot(x), yrot(y), zrot(z), 
      pointvec(vector<point3D>())
    { 
        createPoints();
    }
    
    double get_area(void) { return PI * pow(radius, 2);  }
    
    double get_circumference(void)  { return 2 * PI * radius; }
    
    void createPoints(void)
    {
        point3D radpoint(radius, 0, 0);
        
        for (double i=0; i<360; i+=1)
        {
            pointvec.push_back(rotate(radpoint, 0, 0, i));  
        }
        for (short v=0; v<pointvec.size()-1; v++)
        {
            pointvec[v] = get_point()+rotate(pointvec[v], xrot, yrot, zrot);
        }      
        return;
    }
    void draw(void)
    {
        cwin << Line(project(pointvec[0]), project(pointvec[180]));
        cwin << Line(project(pointvec[90]), project(pointvec[270]));
        
        for (short i=0; i<pointvec.size()-2; i++)
        {
            cwin << Line(project(pointvec[i]), project(pointvec[i+1]));  
        }
        return;
    }
    
    virtual void printInfo(void)
    {
        
        cout << "\nI'm a " << tellName() << '!';
        cout << "\nMy dimensionality is: " << tellType(); 
        cout << "\nMy center is: ";
        get_point().print();
        cout << "\nMy radius is: " << radius;
        cout << "\nMy area is: " << get_area();
        cout << "\nMy circumference is: " << get_circumference() << '\n';
        draw();
        return;
    }
};

class square : public TwoD
{
    double sideLength;
public:
    square(point3D upperleft, double l, const string & n = "Square")
    : TwoD(upperleft, n), sideLength(l) { }
    
    double get_perimeter(void) { return sideLength * 4; }
    double get_area(void) { return pow(sideLength, 2); }
    
    virtual void printInfo(void)
    {
        cout << "\nI'm a " << tellName() << '!';
        cout << "\nMy Dimensionality is: " << tellType();
        cout << "\nMy upper left corner is: ";
        get_point().print();
        cout << "\nMy side length is: " << sideLength;
        cout << "\nMy perimeter is: " << get_perimeter();
        cout << "\nMy area is: " << get_area() << '\n';
    }
};



// inherits point as its center, and adds sidelengths and 3 rotation angles
class cube : public ThreeD
{
    double sidelength;
    double x_rot;
    double y_rot;
    double z_rot;
    point3D points[8];
public:
     cube(point3D center, double l, double xr = 0.0, double yr = 0.0, 
                          double zr = 0.0, const string & n = "Cube")
    : ThreeD(center, n), sidelength(l), x_rot(xr), y_rot(yr), z_rot(zr) 
    {
        fillPointArray();
    }
    
    void fillPointArray(void)
    {
        points[0] = get_point()+
                    rotate(point3D(-sidelength/2, sidelength/2, -sidelength/2),
                                                          x_rot, y_rot, z_rot);
        
        points[1] = get_point()+
                    rotate(point3D(-sidelength/2, sidelength/2, sidelength/2),
                                                         x_rot, y_rot, z_rot);

        points[2] = get_point()+
                    rotate(point3D(sidelength/2, sidelength/2, sidelength/2),
                                                        x_rot, y_rot, z_rot);
        
        points[3] = get_point()+
                    rotate(point3D(sidelength/2, sidelength/2, -sidelength/2),
                                                         x_rot, y_rot, z_rot);

        points[4] = get_point()+
                    rotate(point3D(-sidelength/2, -sidelength/2, -sidelength/2),
                                                           x_rot, y_rot, z_rot);

        points[5] = get_point()+
                    rotate(point3D(-sidelength/2, -sidelength/2, sidelength/2),
                                                          x_rot, y_rot, z_rot);

        points[6] = get_point()+
                    rotate(point3D(sidelength/2, -sidelength/2, sidelength/2),
                                                         x_rot, y_rot, z_rot);

        points[7] = get_point()+
                    rotate(point3D(sidelength/2, -sidelength/2, -sidelength/2),
                                                          x_rot, y_rot, z_rot);
        return;
    }
    
    point3D get_A(void) { return points[0]; }
    point3D get_B(void) { return points[1]; }
    point3D get_C(void) { return points[2]; }
    point3D get_D(void) { return points[3]; }
    point3D get_E(void) { return points[4]; }
    point3D get_F(void) { return points[5]; }
    point3D get_G(void) { return points[6]; }
    point3D get_H(void) { return points[7]; }
    
    virtual void draw(void)
    {
        cwin << project(get_point());
        cwin << Line(project(points[0]), project(points[7]));
        cwin << Line(project(points[3]), project(points[4]));
        
        cwin << Line(project(points[0]), project(points[1]));
        cwin << Line(project(points[1]), project(points[2]));
        cwin << Line(project(points[2]), project(points[3]));
        cwin << Line(project(points[3]), project(points[0]));
        cwin << Line(project(points[0]), project(points[4]));
        cwin << Line(project(points[1]), project(points[5]));
        cwin << Line(project(points[2]), project(points[6]));
        cwin << Line(project(points[3]), project(points[7]));
        cwin << Line(project(points[4]), project(points[5]));
        cwin << Line(project(points[5]), project(points[6]));
        cwin << Line(project(points[6]), project(points[7]));
        cwin << Line(project(points[4]), project(points[7]));
        return;
    }
    
    
    virtual void printInfo(void)
    {
        cout << "\nI'm a " << tellName() << '!';
        cout << "\nMy Dimensionality is: " << tellType();
        cout << "\nMy center is: ";
        get_point().print();
        cout << "\nMy side length is: " << sidelength;
        cout << "\nMy A point is: ";
        get_A().print();
        cout << "\nMy B point is: ";
        get_B().print();
        cout << "\nMy C point is: ";
        get_C().print();
        cout << "\nMy D point is: ";
        get_D().print();
        cout << "\nMy E point is: ";
        get_E().print();
        cout << "\nMy F point is: ";
        get_F().print();
        cout << "\nMy G point is: ";
        get_G().print();
        cout << "\nMy H point is: ";
        get_H().print();
        cout << '\n';
        draw();
        return;
    }
    
};



#endif
