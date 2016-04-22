#include<iostream>
#include <exception>
#include<stdexcept>				//Need to add to handle exceptions

#include "Date.h"
//#include "Date.cxx"
using namespace std;

void checkWeekDay(Date& d)
{
	int weekday = WeekDay(d);
	switch(weekday)
	{
   case Mon : cout<<"Monday";break;
   case Tue : cout<<"Tuesday";break;
   case Wed : cout<<"Wednesday";break;
   case Thr : cout<<"Thursday";break;
   case Fri : cout<<"Friday";break;
   case Sat : cout<<"Saturday";break;
   case 0 : cout<<"Sunday";break;  // 7 % 7 = 0
	}
	
}
void TestDate()
{
	cout<<"\nTest Date Class\n";
	
	const char* day1 = "d";
	const char* day2 = "dd";
	const char* day_err = "ddd";

	const char* m1 = "m";
	const char* m2 = "mm";
	const char* m3 = "mmm";
	const char* m_err = "minm";

	const char* y1 = "yy";
	const char* y2 = "yyyy";
	const char* y_e1 = "y";
	const char* y_e2 = "yyy";
 
	cout<<"\nGenerating format dF1 with parameters "<<day1<<" "<<m1<<" "<<y1<<"...\n"; 

	DateFormat dF1(day1,m1,y1);	

	cout<<"\nGenerating format dF2 with parameters "<<day1<<" "<<m1<<" "<<y_e1<<"...\n"; 
	DateFormat dF2;
	try
	{
		 dF2 = DateFormat(day1,m1,y_e1);	
	}
	catch(const invalid_argument& e)
	{
		cerr << "Invalid argument: " << e.what() << '\n';
	}
	
	
	cout<<"\nGenerating today's date... using void parameter\n";
	Date d = Date();
	cout<<"\nSetting dF1 as format..\n";
	d.setFormat(dF1);
	cout<<"\nPrinting date and format...\n";
	cout<<d;
	cout<<(d.getFormat().getDFormat());cout<<"-"<<(d.getFormat().getMFormat());cout<<"-"<<(d.getFormat().getYFormat());
	cout<<"\n";
	
	cout<<"\nGenerating format dF3 with parameters "<<day2<<" "<<m3<<" "<<y2<<"\n";
	DateFormat dF3(day2,m3,y2);
	
	cout<<"\nGenerating today's date with dF3 format\n";
	d.setFormat(dF3);
	cout<<"\nPrinting date...\n";
	cout<<d;
	
	cout<<"\nSetting dF2 as format and printing...\n";
	d.setFormat(dF2);
	cout<<d;
	cout<<"\nThe above should generate date as dd-mm-yy as dF2 will go to default state\n";
	
	cout<<"\nTesting if format parameters can be changed to 0... Not printing year\n";
	d.getFormat().hideYFormat();
	cout<<d;
	
	cout<<"\nSetting dF3 format and trying to print date 12 December 2012 using explicit function\n";
	Date d12("12-12-2012");
	d12.setFormat(dF3);
/*	Day dar = d12.getDay();
	Month m = d12.getMonth(); 
	Year y = d12.getYear();
	cout<<dar<<" "<<m<<" "<<y<<" ok\n";
	*/cout<<d12;
	
	Day da = D12;
	Month ma = Apr;
	Year ya = 2038;
	cout<<"\nTesting Date constructor with day , month , year preset and dF1 as format : d_specific\n";
	Date d_specific(da,ma,ya);
	d_specific.setFormat(dF1);
	cout<<d_specific;
	
	Year y_out = 2050;
	cout<<"\nTrying to set date with year 2050\n";
	try
	{
			Date d_out(da,ma,y_out);
			cout<<d_out;
	}
		catch(const out_of_range& e)
	{
		cerr << "Out of range : " << e.what() << '\n';
	}
	
	cout<<"\nTrying invalid triplet of d, m, y... i.e , 29 Feb 2017\n";
	da = D29;
	ma = Feb;
	ya = 2017;
	try
	{
			Date d_inv(da,ma,ya);
			cout<<d_inv;
	}
		catch(const domain_error& e)
	{
		cerr << "Domain error: " << e.what() << '\n';
	}
	
	cout<<"\nTrying other invalid triplet of d, m, y... i.e , 31 Sept 2017\n";
	da = D31;
	ma = Sep;
	ya = 2017;
	try
	{
			Date d_inv(da,ma,ya);
			cout<<d_inv;
	}
		catch(const domain_error& e)
	{
		cerr << "Domain error: " << e.what() << '\n';
	}
	
	Date d_critical("29-2-2016"); 
	
	cout<<"\nTesting operator = ... with d_specific\n";
	Date duplicate=d_specific;
	cout<<duplicate;
	
	cout<<"\nTesting operator++ ...\n";
	++duplicate;
	cout<<duplicate;
	cout<<"\ncritical date "<<d_critical;cout<<" gives";
	++d_critical;
	cout<<d_critical;

	cout<<"\nTesting operator++() ...\n";
	duplicate++;
	cout<<duplicate;
	
	cout<<"\nTesting operator-- ...\n";
	--duplicate;
	cout<<duplicate;
	cout<<"\ncritical date "<<d_critical;cout<<" gives";
	--d_critical;
	cout<<d_critical;
	
	cout<<"\nTesting copy constructor with";cout<<d_critical;
	Date d_crit(d_critical);
	cout<<"\nCopy is : ";cout<<d_crit;
	
	
	cout<<"\nTesting operator--() ...\n";
	cout<<duplicate;cout<<"gives ";
	duplicate--;
	cout<<duplicate;
	
	int daysAdded = 100;
	cout<<"\nTesting  operator + by adding "<<daysAdded<<" days\n";
	cout<<duplicate;cout<<"gives ";
	duplicate+daysAdded;
	cout<<duplicate;

	cout<<"\nTesting  operator + by subtracting ";cout<<daysAdded;cout<<" days\n";
	cout<<duplicate;cout<<"gives ";
	daysAdded = -daysAdded;
	duplicate+daysAdded;
	cout<<duplicate;
	
	daysAdded = 19234;
	cout<<"\nTesting  operator + by adding "<<daysAdded<<" days\n";
	cout<<duplicate;cout<<"gives ";
	duplicate+daysAdded;
	cout<<duplicate;	
	
	da = D20;
	Date diffDate(da,ma,ya);
	cout<<"\nTesting operator - subtracting ";cout<<d_critical;
	cout<<duplicate;cout<<" minus ";
	cout<<d_critical;
	
	double diff = duplicate-d_critical;
	cout<<" gives "<<diff<<" days\n";
	
	cout<<"\nComparison between ";cout<<d_specific;cout<<" & ";cout<<duplicate;
	cout<<"\n== ";cout<<(d_specific == duplicate);
	cout<<"\n!= ";cout<<(d_specific != duplicate);
	cout<<"\n > ";cout<<(d_specific > duplicate);
	cout<<"\n < ";cout<<(d_specific < duplicate);
	cout<<"\n>= ";cout<<(d_specific >= duplicate);
	cout<<"\n<= ";cout<<(d_specific <= duplicate);
	cout<<"\n";

	duplicate=d_critical;
	cout<<"\nComparison between ";cout<<d_specific;cout<<" & ";cout<<duplicate;
	cout<<"\n== ";cout<<(d_specific == duplicate);
	cout<<"\n!= ";cout<<(d_specific != duplicate);
	cout<<"\n > ";cout<<(d_specific > duplicate);
	cout<<"\n < ";cout<<(d_specific < duplicate);
	cout<<"\n>= ";cout<<(d_specific >= duplicate);
	cout<<"\n<= ";cout<<(d_specific <= duplicate);
	cout<<"\n";
	
	ya = 2025;
	Date d_new;
	cout<<"\nTesting istream friend function...\n";
	cin>>d_new;//(Day(da),Month(ma),Year(ya));
	cout<<d_new;
	
	cout<<"\nTesting leapYear function...";
	cout<<d_new;
	if(d_new.leapYear())
	{
			cout<<"\nIt is a leap year";
	}
	else
	{
		cout<<"\nNot a leap year";
	}
	
	cout<<"\nTesting leapYear function...";
	cout<<d_specific;
	if(d_specific.leapYear())
	{
			cout<<"\nIt is a leap year\n";
	}
	else
	{
		cout<<"\nNot a leap year\n";
	}
	
	cout<<"\nTesting month cast....";
	cout<<d_new;
	cout<<"\n Month number : "<<Month(d_new)<<"\n";
	cout<<d_specific;
	cout<<"\n Month number : "<<Month(d_specific)<<"\n";
	
	cout<<"\nTesting weekday cast....";
	cout<<d_new;
	cout<<"\n Weekday : ";checkWeekDay(d_new);
	cout<<d_specific;
	cout<<"\n Weekday : ";checkWeekDay(d_specific);
	cout<<"\n";	
	
	
	cout<<"\nTesting weeknumber cast.....";
	cout<<d_new;
	cout<<"\n Week Number : ";cout<<WeekNumber(d_new)<<"\n";
	cout<<d_specific;
	cout<<"\n Week Number : ";cout<<WeekNumber(d_specific)<<"\n";
}

int main()
{
	TestDate();
	cout<<"\nPrinting from main function...If this gets printed , it means TestDate() worked properly\n";
}
