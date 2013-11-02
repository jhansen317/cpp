#ifndef DATE_H
#define DATE_H


// Modified binary search. Returns the lower of two adjacent indices between
// which the searched-for object lies: returns n when a[n] <= findMe < a[n+1].  
template <typename arrT>
arrT rangesearch(const arrT * a, long max, const arrT & findMe)
{
    arrT low = 0;
    arrT mid;
    arrT found = -1;
    
    while (low <= max && found == -1)
    {
        mid = (low+max)/2;
        if (a[mid] < findMe)
        {
            low = mid+1;
        }
        else if (a[mid] > findMe)
        {
            max = mid-1;
        }
        
        if (a[mid] <= findMe && findMe < a[mid+1])
        {
            found = mid;
        }
    }
    return found;
}


class Date 
{
    long total_days, flags;
    static long WHOLE_MONTHS [];
    static long WHOLE_MONTHS_LEAP [];
    static long WHOLE_YEARS [];
    
    public:  
    enum { day_bound = 1, month_bound = 2, year_bound = 4, 
                      notation_fail = 8, fail_bit = 15, leap_bit = 16 };
    Date(void) : total_days(0), flags(0) { }
    Date(long days) : total_days(days), flags(0) 
    {
        set_date(days);
    }
    Date(short day, short month, short year) : total_days(0), flags(0) 
    {
        set_date(day, month, year);
    }
    Date(const Date & other) : 
                       total_days(other.total_days), flags(other.flags) { }
    bool good(void) const
    {
        return (flags & fail_bit) == 0;
    }
    bool bad_days(void) const
    {
        return (flags & day_bound) != 0;
    }
    bool bad_month(void) const
    {
        return (flags & month_bound) != 0;
    }
    bool bad_year(void) const
    {
        return (flags & year_bound) != 0;
    }
    bool bad_notation(void) const
    {
        return (flags & notation_fail) != 0;
    }
    bool is_leap(void) const
    {
        return (flags & leap_bit) != 0;
    }
    void set_flag(long flagbit)
    {
        flags |= flagbit;
    }
    void unset_flag(long flagbit)
    {
        flags &= ~flagbit;
    }
    void clear_flags(void)
    {
        unset_flag(fail_bit);
    }
    void set_date(long days)
    {
        if (days+total_days > WHOLE_YEARS[700] || days+total_days < 0)
        {
            set_flag(year_bound);
        }
        else
        {
            total_days = days;
            unset_flag(year_bound);
        }
        if(good())
        {
            long year = get_year();
            if (((year % 4 == 0) && (year % 100 != 0)) || 
            ((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0)))
            {
                set_flag(leap_bit);
            }
            else
            {
                unset_flag(leap_bit);
            }
        }
        return;
    }
    void set_date(short month, short day, short year)
    {
        if (((year % 4 == 0) && (year % 100 != 0)) || 
            ((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0)))
        {
            set_flag(leap_bit);
        }
        else
        {
            unset_flag(leap_bit);
        }       
        if (month > 12)
        {
            set_flag(month_bound);
        }
        if (year > 2500 || year < 1800)
        {
            set_flag(year_bound);
        }
        if ((day > 30 && (month==4 || month==6 || month==9 || month==11)) ||            
           (day > 31) ||         
           ((day > 28 && month == 2 && !is_leap()) || 
             (day > 29 && month == 2 && is_leap())))
        {
            set_flag(day_bound);
        }
        if (good())
        {
            total_days += WHOLE_YEARS[year-1800];
            total_days += is_leap() ? WHOLE_MONTHS_LEAP[month-1] 
                                    : WHOLE_MONTHS[month-1];
            total_days += day-1;
        }
        return;
    }
    long get_year(void) const
    {
        return rangesearch(WHOLE_YEARS, 700, total_days) + 1800;
    }

    long get_month(void) const
    {
        return rangesearch(is_leap() ? WHOLE_MONTHS_LEAP 
                                               : WHOLE_MONTHS, 11, 
                                   total_days - WHOLE_YEARS[get_year()-1800])+1;
    }
    long get_day(void) const
    {
        return total_days - WHOLE_YEARS[get_year()-1800] - 
                         (is_leap() ? WHOLE_MONTHS_LEAP[get_month()-1] 
                                              : WHOLE_MONTHS[get_month()-1])+1;
    }
    Date & operator+=(long days)
    {
        set_date(total_days+days);
        return *this;
    }
    long operator-(const Date & right) const
    {
        return total_days - right.total_days;
    }
    bool operator<(const Date & right) const
    {
        return total_days < right.total_days;
    }
    
};

std::istream & operator>>(std::istream & in, Date & d);
std::ostream & operator<<(std::ostream & out, Date & d);

#endif     

