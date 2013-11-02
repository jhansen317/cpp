class curve 
{
    Point start;
    Point control;
    Point end;
public:
    curve(Point s, Point c, Point e)
    : start(s), control(c), end(e) { }
    
    vector<Point> get_points(void)
    {
        vector<Point> storage;
        double inc=0.01;
        Point point1, point2, point3;
        
        for (double i=inc; i<=1; i+=inc)
        {
            point1 = Point(start.get_x() + (i*(control.get_x()-start.get_x())), 
                         start.get_y() + (i*(control.get_y()-start.get_y())));
            
            point2 = Point(control.get_x() +(i*( end.get_x()-control.get_x())),
                        control.get_y() + (i*(end.get_y()-control.get_y())));
            
            point3 = Point(point1.get_x() + (i*(point2.get_x()-point1.get_x())),
                         point1.get_y() + (i*(point2.get_y()-point1.get_y())));
            storage.push_back(point3);
        }
        return storage;
    }
};
