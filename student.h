#ifndef STUDENT_H_INC
#define STUDENT_H_INC

#include<string>
#include<fstream>

using namespace std;

class student
{
    string name;
    long id; 
    double gpa;
    char gender;
    
public:
    
    student(void) : name(""), id(0), gpa(0.0), gender('\0') { }
    
    student(const student & s) : name(s.name), id(s.id), 
                                 gpa(s.gpa), gender(s.gender) { }
                                 
    student(const string newname, const long newid, const double newgpa, 
            const char newgender) : name(""), id(0), gpa(0.0), gender('\0')
    {
        set_name(newname);
        set_id(newid);
        set_gpa(newgpa);
        set_gender(newgender);
    }
    
    bool print(ofstream & output) const;
    bool read(ifstream & input);
    
    string get_name(void) const {return name;}
    long get_id(void) const {return id;}
    double get_gpa(void) const {return gpa;}
    char get_gender(void) const {return gender;}
    
    void set_name(string newname)
    {
        name = newname;
        return;
    }
    void set_id(long newid)
    {
        id = newid;
        return;
    }
    void set_gpa(double newgpa)
    {
        gpa = newgpa;
        return;
    }
    void set_gender(char newgender)
    {
        gender = newgender;
        return;
    }   
};

long strtolong(string & str);

double strtodub(string & str);

short char_to_ones(const char & c);


# endif
