bool reallocate(double * & p, size_t & physical_size, size_t logical_size, 
                                                size_t more_space)
{
    double * t;
    bool okay = false;
    t = new double [physical_size+more_space];
    if (t != NULL)
    {
        okay = true;
        for (size_t i = 0; i != logical_size; i++)
        {
            t[i] = p[i];
        }
        delete [] p;
        p=t; 
        t = NULL;
        physical_size += more_space;
        }
        return okay; 
}



