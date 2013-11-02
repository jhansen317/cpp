#include <sys/time.h>
#include <iostream>
#include <cmath>
#include <climits>
#include "ccc_win.h"
#include <string>
#include <vector>

using namespace std;

template <typename argT, typename intT, typename funcT>
vector<double> timevec(argT n, intT rate, funcT & algo)
{
    vector<double> times;
    double diff;
    timeval start, end;
    for (argT i=0; i<n; i+=rate)
    {
        gettimeofday(&start,NULL);
        algo(i);
        gettimeofday(&end,NULL);
    diff = end.tv_sec+end.tv_usec*1e-6 -
                  (start.tv_sec+start.tv_usec*1e-6);
    times.push_back(diff);
    }
    return times;
}
    
void drawAxes(double scale=15.0);

vector<double> quadraticvec(double coeff, double xmin, double xmax, double ymax, 
                            double xint, double scale=15.0);
vector<double> linearvec(double coeff, double xmin, double xmax, double ymax, 
                            double xint, double scale=15.0);
vector<double> cubicvec(double coeff, double xmin, double xmax, double ymax, 
                            double xint, double scale=15.0);

void plotvector(vector<double> vec, long n, double ymax, bool drawline=false, double scale=15.0);
void function1(long n);
void function2(long n);
void function3(long n);
void function4(long n);
void function5(long n);
void function6(long n);
void function7(long n);

int ccc_win_main(void)
{
    unsigned long lots, max;
    double diff, xval, ymax, coef;
    long sum=0, interval;
    string in; 
    vector<double> times, refvec;
    timeval start, end;
    
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    
    times = timevec(max, interval, function1);
    
    do
    {
        drawAxes();  
        
        plotvector(times, max, floor((times[times.size()-1]/0.001)+0.5)*0.001);
        
        coef = cwin.get_double("Enter a coefficient for a linear function: ");
        
        refvec = linearvec(coef, 0.0, max, 
                     floor((times[times.size()-1]/0.001)+0.5)*0.001, interval*0.001);
        cout << "\nCoefficent is: " << coef
             << "\nxmax is: " << max
             << "\nymax is: " << floor((times[times.size()-1]/0.001)+0.5)*0.001;
        
        plotvector(refvec, max, 
                   floor((times[times.size()-1]/0.001)+0.5)*0.001, true);
        
        in = cwin.get_string("Would you like to try again? ");
        cwin.clear();
        refvec.clear();
    }while(in == "Y");
    
    times.clear();
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    cwin.clear();
    times = timevec(max, interval, function2);
    do
    {
        drawAxes();     
        plotvector(times, max, floor((times[times.size()-1]/0.001)+0.5)*0.001);
        coef = cwin.get_double("Enter a coefficient for a linear function: ");
        refvec = linearvec(coef, 0.0, max, floor((times[times.size()-1]/0.001)+0.5)*0.001, interval);
        plotvector(refvec, max, floor((times[times.size()-1]/0.001)+0.5)*0.001, true);
        in = cwin.get_string("Would you like to try again? ");
        cwin.clear();
        refvec.clear();
    }while(in == "Y");

    times.clear();
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    cwin.clear();
    times = timevec(max, interval, function3);
    do
    {
        drawAxes();     
        plotvector(times, max, floor(times[times.size()-1]+0.5));
        coef = cwin.get_double("Enter a coefficient for a quadratic function: ");
        refvec = quadraticvec(coef, 0.0, max, floor(times[times.size()-1]+0.5), interval);
        plotvector(refvec, max, floor(times[times.size()-1]+0.5), true);
        in = cwin.get_string("Would you like to try again? ");
        cwin.clear();
        refvec.clear();
    }while(in == "Y");
    times.clear();
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    cwin.clear();
    times = timevec(max, interval, function4);
    do
    {
        drawAxes();     
        plotvector(times, max, floor(times[times.size()-1]/0.001+0.5)*0.001);
        coef = cwin.get_double("Enter a coefficient for a linear function: ");
        refvec = linearvec(coef, 0.0, max, floor(times[times.size()-1]/0.001+0.5)*0.001, interval);
        plotvector(refvec, max, floor(times[times.size()-1]/0.001+0.5)*0.001, true);
        in = cwin.get_string("Would you like to try again? ");
        cwin.clear();
        refvec.clear();
    }while(in == "Y");

    times.clear();
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    cwin.clear();
    times = timevec(max, interval, function5);
    do
    {
        drawAxes();     
        plotvector(times, max, floor(times[times.size()-1]+0.5));
        coef = cwin.get_double("Enter a coefficient for a cubic function: ");
        refvec = cubicvec(coef, 0.0, max, floor(times[times.size()-1]+0.5), interval);
        plotvector(refvec, max, floor(times[times.size()-1]+0.5), true);
        in = cwin.get_string("Would you like to try again? ");
        cwin.clear();
        refvec.clear();
    }while(in == "Y");
    drawAxes();    
    plotvector(times, max, floor(times[times.size()-1]+0.5));
    times.clear();
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    cwin.clear();
    times = timevec(max, interval, function6);
   
    drawAxes();    
    plotvector(times, max, floor(times[times.size()-1]+0.5));
    times.clear();
    max = cwin.get_int("Please enter a value for n: ");
    interval = cwin.get_int("Enter a sampling interval: ");
    cwin.clear();
    times = timevec(max, interval, function7);
 
    drawAxes();    
    plotvector(times, max, floor(times[times.size()-1]+0.5));

    return 0;
}

vector<double> quadraticvec(double coeff, double xmin, double xmax, double ymax, 
                            double xint, double scale)
{
    double xval, yval;
    vector<double> returnvec;
    xval = xmin; 
    do
    {
        yval = (pow(xval, 2)*coeff)/(ymax/scale);
        returnvec.push_back(yval);
        xval += xint;
    } while(xval <= xmax && yval <= scale);
    return returnvec;
}
vector<double> linearvec(double coeff, double xmin, double xmax, double ymax, 
                            double xint, double scale)
{
    double xval, yval;
    vector<double> returnvec;
    xval = xmin; 
    do
    {
        yval = (xval*coeff)/(ymax/scale);
        returnvec.push_back(yval);
        xval += xint;
    } while(xval < xmax && yval < ymax);
    return returnvec;
}
vector<double> cubicvec(double coeff, double xmin, double xmax, double ymax, 
                            double xint, double scale)
{
    double xval, yval;
    vector<double> returnvec;
    xval = xmin; 
    do
    {
        yval = (pow(xval, 3)*coeff)/(ymax/scale);
        returnvec.push_back(yval);
        xval += xint;
    } while(xval <= xmax && yval <= scale);
    return returnvec;
}


void plotvector(vector<double> vec, long n, double ymax, bool drawline, double scale)
{
    double xmax = static_cast<double>(vec.size()-1);
    cwin << Message(Point(-1, scale), ymax);
    cwin << Message(Point(scale, -1), n);
    for (short i=0; i< xmax; i++)
    {
        if (drawline)
        {
            cwin << Line(Point(i/(xmax/scale), vec[i]/(ymax/scale)), 
                         Point((i+1)/(xmax/scale), vec[i+1]/(ymax/scale)));
        }
        else
        {
            cwin << Point(i/(xmax/scale), vec[i]/(ymax/scale));
        }
    }
    return; 
}
void drawAxes(double scale)
{
    cwin << Line(Point(0,0), Point(scale,0));
    cwin << Line(Point(0,0), Point(0, scale));
    return;
}

void function1(long n)
{
    long sum;
    for (long i=0; i<n; i++)
    {
        sum++;
    }
    return;
}
void function2(long n)
{
    long sum;
    for (long i = 0; i<n; i+=2)
    {
        sum++;
    }
    return;
}
void function3(long n)
{
    long sum;
    for (long i = 0; i<n; i++)
    {
        for (long j = 0; j<n; j++)
        {
            sum++;
        }
    }
    return;
}

void function4(long n)
{
    long sum;
    for (long i = 0; i<n; i++)
    {
        sum++;
    }
    for (long j = 0; j<n; j++)
    {
        sum++;
    }
    return;
}
void function5(long n)
{
    long sum;
    for (long i = 0; i<n; i++)
    {
        for (long j = 0; j<n*n; j++)
        {
            sum++;
        }
    }
    return;
}

void function6(long n)
{
    long sum;
    for (long i = 0; i < n; i++)
    {
        for (long j = 0; j < i; j++)
        {
            sum++;
        }
    }
    return;
}

void function7(long n)
{
    long sum;
    for (long i = 0; i < n; i++)
    {
        for (long j = 0; j < n*n; j++)
        {
            for (long k = 0; k < j; k++)
            {
                sum++;
            }
        }
    }
    return;
}
    
    
