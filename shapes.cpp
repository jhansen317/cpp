#include <iostream>
#include "point3D.h"
#include "shapelib.h"
#include "ccc_win.h"

using namespace std;



int ccc_win_main(void)
{
    vector<point3D> pointvec;


    point3D point1(-15, 10, 0), point2(-11, 10, 0),
            point3(-7, 10, 0), point4(-3, 10, 0), 
            point5(-15, 5, 0), point6(-11, 5, 0),
            point7(-7, 5, 0), point8(-3, 5, 0), point9(-3, 3, 0);

    shape * shptr[9];
    
    circle circlederived(point5, 1.5);
    circle circle2(point6, 1.5, 45, 0, 0);
    circle circle3(point7, 1.5, 0, 45, 0);
    circle circle4(point8, 1.5, 0, 0, 45);
    cube cubederived(point1, 2.0);
    cube cube2(point2, 2.0, 45, 0, 0);
    cube cube3(point3, 2.0, 0, 45, 0);
    cube cube4(point4, 2.0, 0, 0, 45);

    curve curvetest(point3D(4, 6, 0), point3D(3, 10, 0), 
                    point3D(7, 6, 0), point3D(6, 10, 0));
 
    drawAxes();
    
  
    
    shptr[0] = &cubederived;
    shptr[1] = &cube2;
    shptr[2] = &cube3;
    shptr[3] = &cube4;
    shptr[4] = &circlederived;
    shptr[5] = &circle2;
    shptr[6] = &circle3;
    shptr[7] = &circle4;
    shptr[8] = &curvetest; 
    
    
    for (short i = 0; i<9; i++)
    {
        shptr[i]->printInfo();
    }
    
    
    return 0;  
}



