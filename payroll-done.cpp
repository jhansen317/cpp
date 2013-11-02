#include <iostream>
#include <climits>
#include <cctype>
#include <cmath>

using namespace std;

double moneyRounder(double money) // rounds monetary values appropriately
   {
      money = floor(money/.01 + .5) * .01;
      return money;
   }


int main(void)
{
   const double pay_rate = 16.78; 
   const double social_security = 0.06;
   const double fed_income_tax = 0.14;
   const double state_income_tax = 0.05;
   const short union_dues = 10; 
   short counter = 0,
         hours_worked, 
         tot_hours = 0, 
         children, 
         healthcare, 
         tot_healthcare = 0;
   double gross_pay, 
          tot_gross_pay = 0, 
          net_pay, 
          tot_net_pay = 0, 
          cur_ss_deduct,
          tot_ss_deduct = 0,
          cur_fit_deduct,
	  tot_fit_deduct = 0,
          cur_sit_deduct,
          tot_sit_deduct = 0;      
   char yes_no;
   
   
   cout << "\n\tWelcome to the Payroll Calculation Program!\n\n"
        << "I, the program, will be asking you a few yes/no questions.\n\n"
        << "If you mean to answer \"Yes, program\", press Y and hit Enter.\n\n"
        << "If not, press whatever you want and see what happens, I guess.\n\n"
        << "Are you ready to start some DATA ENTRY MADNESS?  ";
   cin >> yes_no;
   
   cin.ignore(INT_MAX, '\n');

   while ( toupper(yes_no) == 'Y' )
   { 
      cout << "\nPlease Enter Hours Worked This Week:  ";
      cin >> hours_worked;                                                     
      cout << "\nHow Many Children Does the Employee Have?  ";
      cin >> children;

      if (hours_worked > 40)
      {
         gross_pay = (pay_rate * 40.0) 
         + ((hours_worked - 40) 
         * (pay_rate * 1.50));  
      }
      else 
      {
         gross_pay = pay_rate * hours_worked;
      }

      if (children > 3)
      {
         healthcare = 35;
      }
      else
      {
         healthcare = 0;
      }
		
      if (children > 5)
      {
         cout << "\n\t\tHoly crap, that's a lot of kids.\n";
      }  
		
      net_pay = gross_pay - cur_ss_deduct - cur_fit_deduct - cur_sit_deduct  
       - union_dues - healthcare;

      net_pay = moneyRounder(net_pay);

      cur_ss_deduct = moneyRounder(gross_pay * social_security);

      cur_fit_deduct = moneyRounder(gross_pay * fed_income_tax);

      cur_sit_deduct = moneyRounder(gross_pay * state_income_tax);


      cout << "\nHere's the pay-stub:\n"
           << "\n                                Hours: "  << hours_worked 
           << "\n                            Gross Pay: $" << gross_pay
           << "\n            Social Security Deduction: $" << cur_ss_deduct
           << "\n         Federal Income Tax Deduction: $" << cur_fit_deduct
           << "\n           State Income Tax Deduction: $" << cur_sit_deduct
           << "\n  Union Dues(Uh, except in Wisconsin): $" << union_dues
           << "\n       Healthcare Insurance Deduction: $" << healthcare
           << "\n                              Net Pay: $" << net_pay << "\n"
           << "\nWould you like to enter more DATA?  ";

      counter = counter + 1;

      tot_hours = tot_hours + hours_worked;

      tot_gross_pay = tot_gross_pay + gross_pay;

      tot_net_pay = tot_net_pay + net_pay;		

      tot_ss_deduct = tot_ss_deduct + cur_ss_deduct;

      tot_fit_deduct = tot_fit_deduct + cur_fit_deduct;

      tot_sit_deduct = tot_sit_deduct + cur_sit_deduct;

      tot_healthcare = tot_healthcare + healthcare;
  
      cin >> yes_no;

      cin.ignore(INT_MAX, '\n');
   }
	
   cout << "\nOh well, thanks anyway...\n\n\tOh Wait!\n\n"
        << "Here are the totals from your data entry frenzy:\n\n"
        << "\tYou have entered the data for " << counter << " employees.\n"
        << "\n                          Total Hours: "  << tot_hours 
        << "\n                      Total Gross Pay: $" << tot_gross_pay
        << "\n      Total Social Security Deduction: $" << tot_ss_deduct
        << "\n   Total Federal Income Tax Deduction: $" << tot_fit_deduct
        << "\n     Total State Income Tax Deduction: $" << tot_sit_deduct
        << "\n Total Healthcare Insurance Deduction: $" << tot_healthcare
        << "\n                        Total Net Pay: $" << tot_net_pay 
        << "\n\t\t\tBye!\n\n";

   return 0;

}


