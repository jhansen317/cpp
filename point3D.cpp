#include "point3D.h"
#include <iostream>
#include <cmath>

using namespace std;

void point3D::print(void)
{
    cout << '(' << x << ", " << y << ", " << z << ')';
    return;
}

void point3D::read(void)
{
    char trash;
    cin >> trash >> x >> trash >> y >> trash >> z; 
    return; 
}

double point3D::distance(point3D other)
{
    return sqrt(pow(other.x-x, 2.0) + 
                pow(other.y-y, 2.0) + 
                pow(other.z-z, 2.0));
}
