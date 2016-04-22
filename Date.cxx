#include <iostream>
#include <exception>
#include <ctime>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "Date.h"
using namespace std;

DateFormat Date::format = DateFormat();


//class DateFormat {

	DateFormat::DateFormat(const char* d, const char* m, const char* y)throw(invalid_argument)
	{
		dateFormat = strdup(" ");
		monthFormat = strdup(" ");
		yearFormat = strdup(" ");
		if((strcmp("d",d)==0)||(strcmp("dd",d)==0)||strcmp("0",d)==0)
		{
			dateFormat = strdup(d);				//converting const char* to char*
		} 
		else
		{
			cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");
		}
		
		//monthFormat handling
		if((strcmp("m",m)==0)||(strcmp("mm",m)==0)||(strcmp("mmm",m)==0)||strcmp("0",m)==0)
		{
			monthFormat = strdup(m);
		}
		else 										//if not a valid month format
		{
			cout<<"\n";throw invalid_argument("Entered format for month is invalid !\n");

		} 
		
		//yearFormat handling
		if((strcmp("yy",y)==0)||(strcmp("yyyy",y)==0)||strcmp("0",y)==0)
		{
			yearFormat = strdup(y);
		}
		else 										//if not a valid year format
		{
			cout<<"\n";throw invalid_argument("Entered format for year is invalid !\n");

		} 
	}

		char breakPoint = '-';
		int monthStart,yearStart;
	// Single C-string format where dateFormat, monthFormat, and yearFormat are separated by ' - '
	// Example: "dd-mmm-yy", "d-mm-yyyy", etc
	
	
	DateFormat::DateFormat(const char* format)throw(invalid_argument)	//All strings of the form *-**-** are valid
	{								//that is , m-dd-yy will generate 1-03-16 for 1 March
		dateFormat = new  char();
		monthFormat = new char();
		yearFormat = new char();	
				
		if(format[1]==breakPoint)
		{
			dateFormat = strdup("d");
			monthStart = 2;
		}
		else if(format[2]==breakPoint)
		{
			dateFormat = strdup("dd");
			monthStart = 3;
		}
		else			//no other format than d or dd accepted
		{
			cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");

		}
		
		//month formulation
		if(format[monthStart+1]==breakPoint)
		{
			monthFormat = strdup("m");
			yearStart = monthStart + 2;
		}
		else if(format[monthStart+2]==breakPoint)
		{
			monthFormat = strdup("mm");
			yearStart = monthStart + 3;
		}
		else if(format[monthStart+3]==breakPoint)
		{
			monthFormat = strdup("mmm");
			yearStart = monthStart + 4;
		}
		else			//no other format than m or mm or mmm accepted
		{
			cout<<"\n";throw invalid_argument("Entered format for month is invalid !\n");

		}
		
		//year formulation
		// need to check all possibilities as yy or yyyy may not be the possible entry
		if(format[yearStart]=='\0')//end of string
		{
			cout<<"\n";throw invalid_argument("Entered format for year is invalid !\n");

		}
		else if(format[yearStart+1]=='\0')//end of string
		{
			cout<<"\n";throw invalid_argument("Entered format for year is invalid !\n");
		}
		else if(format[yearStart+2]=='\0')//end of string
		{
			yearFormat = strdup("yy");
		}
		else if(format[yearStart+3]==breakPoint)
		{
			cout<<"\n";throw invalid_argument("Entered format for year is invalid !\n");
		}	
		else if(format[yearStart+4]==breakPoint)
		{
			yearFormat = strdup("yyyy");
		}	
		else			//no other format than yy or yyyy accepted
		{
			cout<<"\n";throw invalid_argument("Entered format for year is invalid !\n");
		}
		
	}
	
	// Default DateFormat created as "dd-mmm-yy"
	DateFormat::DateFormat()
	{
		dateFormat = new  char();
		monthFormat = new char();
		yearFormat = new char();
		
			dateFormat = strdup("dd");
			monthFormat = strdup("mm");
			yearFormat = strdup("yy");

	}

	DateFormat::~DateFormat()
	{
		free(dateFormat);
		free(monthFormat);
		free(yearFormat);
	}
	
	const char* DateFormat::getDFormat()
	{
		return dateFormat;
	}
	
	const char* DateFormat::getMFormat()
	{
		return monthFormat;
	}
	
	const char* DateFormat::getYFormat()
	{
		return yearFormat;
	}
	
	void DateFormat::hideDFormat()
	{
		dateFormat=strdup("0");
	}
	
	void DateFormat::hideMFormat()
	{
		monthFormat=strdup("0");
	}
	
	void DateFormat::hideYFormat()
	{
		yearFormat=strdup("0");
	}
//};

	DateFormat defaultFormat = DateFormat();//default format if not set separately

// This class defines a date within 01/Jan/1950 and 31/Dec/2049
//class Date {
	
		//Array of char* required for checking of strings in explicit Date()
		const char* validMonth[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
		int i;
	
	// CONSTRUCTORS
	Date::Date(Day d, Month m, Year y)
			throw(
				invalid_argument,		// One or more of the arguments d or m is/are invalid (27, 13, 13)
				domain_error,			// (d, m, y) as a triplet does not define a valid date (30, 2, 61)
				out_of_range)			// Date is out of range (4, 7, 2053)
	{	// Construct a Date from (d, m, y)
		
		if(y>2049||y<1950)			//Invalid year
		{
			cout<<"\n";throw out_of_range("Entered year is not valid !\n");		//date out of range
				
		}
		else if(m<Jan||m>Dec)			//Invalid month
		{
			cout<<"\n";throw invalid_argument("Entered value for month is invalid !\n");	
		}
		else if(d<D01||d>D31)			//Invalid day
		{
			cout<<"\n";throw invalid_argument("Entered value for day is invalid !\n");	
		}	
		else
		{
			if(m==Feb)			//February has 28 or 29 days max . depending on whether the current year is leap yr or not
			{
				if(y%4)			//not a leap yr . Valid dates are 1 - 28
				{
					if(d<D01||d>D28)
					{
						cout<<"\n";throw domain_error("February does not have these many days\n");
																						//domain error implies invalid triplet for (d,m,y)
					}
				}
				else
				{
					if(d<D01||d>D29)				//leap yr has 29 feb , like this year
					{
						cout<<"\n";throw domain_error("February does not have these many days\n");	
					}
				}
			}
			else if( (m==Apr)||(m==Jun)||(m==Sep)||(m==Nov) )	//for these months,max number of days is 30 not 31 
			{
					if(d==D31)//accepted values in this loop are 1 - 30 . Hence , only one value needs to be checked				
					{
						cout<<"\n";throw domain_error("Number of days is incorrect\n");
					}
			} 
			//no need to handle odd months separately as we have already checked if d>31 so , always valid
			
			//if we are still here , it means that the date is valid
			day = d;
			month = m;
			year = y;
			(*this).setFormat(defaultFormat);
		}
	}
		
	Date::Date(const char* date)
	throw(invalid_argument, domain_error, out_of_range)		// date in string format -- to be parsed as static format member
	{
		char* temp;
		int monthStart,yearStart;
		char breakPoint = '-';
		int d,m,y;
		
		/*Identifying day from the string*/
		if(date[1]==breakPoint)		//format starts with d-*****
		{			
			d = (int)date[0]-48;
			/*
			stringstream s(date[0]);
			s >> d;
			*/	
			if(d<1||d>9)
			{
				cout<<"\n";throw invalid_argument("Entered value for day is not an integer !\n");
			}
			//cout<<"\nReporting date : "<<int(d)<<"\n";
			monthStart = 2;	
		}
		else if(date[2]==breakPoint)	//format starts with dd-****
		{
			d = (int)date[0]-48;
			d = 10*d + (int)date[1] - 48;	//12 = 1*10 + 2

			if(d<1||d>31)
			{
				cout<<"\n";throw invalid_argument("Entered value for day is invalid !\n");	
				//no need of monthStart here for invalid date
			}
			else
			{
				//cout<<"\nReporting date : "<<int(d)<<"\n";
				monthStart = 3;
			}
		}
		else									//incorrect date format
		{
				cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");
		}
		
		
		/*Identifying month ... */
		if(date[monthStart+1]==breakPoint)		//format contains m-*****
		{
			m = (int)date[monthStart] - 48;		//single digit monnth number

			if(m<1||m>9)
			{
				cout<<"\n";throw invalid_argument("Entered value for month is not an integer !\n");
			}	
			//cout<<"\nReporting month : "<<int(m)<<"\n";	
			yearStart = monthStart+2;
			
		}
		else if(date[monthStart+2]==breakPoint)			//month  present as mm-***
		{			
			m = (int)date[monthStart] - 48;
			m = 10*m + (int)date[monthStart+1] - 48;	//12 = 1*10 + 2

			if(m<1||m>12)
			{
				cout<<"\n";throw invalid_argument("Entered value for month is invalid !\n");	
			}
			else
			{
				//cout<<"\nReporting month : "<<int(m)<<"\n";
				yearStart = monthStart+3;
			}
		}
		else if(date[monthStart+3]==breakPoint)			//month  present as mmm-***
		{
			char temp[3];
			temp[0] = date[monthStart];
			temp[1] = date[monthStart+1];
			temp[2] = date[monthStart+2];		//rote copying
			
			m = -1;			//invalid month
			for(i = 0;i < 12; i++)
			{
				if(strcmp(temp,validMonth[i])==0)
				{
					m = i;
					//cout<<"\nReporting month : "<<temp<<"\n";
					yearStart = monthStart + 4;
					break;
				}
			}
			
			if(m==-1)		//It means we have *-mmm-** but mmm is not valid month name
			{
				cout<<"\n";throw invalid_argument("Entered string for month is invalid !\n");	
			}
		}
		else							// more than 3 chars between - & - => invalid format
		{
			cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");
		}
		
		
		/*Identifying year...*/
		// need to check all possibilities as yy or yyyy may not be the possible entry
		if(date[yearStart]=='\0')//end of string
		{
				cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");	
		}
		else if(date[yearStart+1]=='\0')//end of string
		{
				cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");
		}
		else if(date[yearStart+2]=='\0')//end of string
		{
			y = (int)date[yearStart] - 48;
			y = 10*y + (int)date[yearStart+1] - 48;	
			
			if(y<0||y>99)    //Possiblities are 50,51, 52 ,...,98,99,00,01,02,...,49 => 00-99
			{
				cout<<"\n";throw invalid_argument("Entered value for year is invalid !\n");	
			}
		//	cout<<"\nReporting year : "<<int(d)<<"\n";
			
		}
		else if(date[yearStart+3]=='\0')
		{
			cout<<"\n";throw invalid_argument("Entered format for date is invalid !\n");
		}	
		else if(date[yearStart+4]=='\0')
		{
			y = (int)date[yearStart] - 48;
			y = 10*y + (int)date[yearStart+1] - 48;	
			y = 10*y + (int)date[yearStart+2] - 48;
			y = 10*y + (int)date[yearStart+3] - 48;				
			
			if(y<1950||y>2049)    //Possiblities are 1950,...,2049 => 1950-2049
			{
				cout<<"\n";throw invalid_argument("Entered value for year is invalid !\n");	
			}	
		//	cout<<"\nReporting year : "<<int(d)<<"\n";

		}	
		else			//no other format than yy or yyyy accepted
		{
			cout<<"Need to put correct format !\n"<<endl;
			return;
		}
		
		//removing invalid dates like 31 Feb	
		if(m==Feb)			//February has 28 or 29 days max . depending on whether the current year is leap yr or not
		{
			if(y%4)			//not a leap yr . Valid dates are 1 - 28
			{
				if(d<D01||d>D28)
				{
					cout<<"\n";throw domain_error("February does not have these many days\n");		//domain error implies invalid triplet for (d,m,y)
				}
			}
			else
			{
				if(d<D01||d>D29)				//leap yr has 29 feb , like this year
				{
					cout<<"\n";throw domain_error("February does not have these many days\n");	
				}
			}
		}
		else if( (m==Apr)||(m==Jun)||(m==Sep)||(m==Nov) )	//for these months,max number of days is 30 not 31 
		{
				if(d==D31)//accepted values in this loop are 1 - 30 . Hence , only one value needs to be checked				
				{
					cout<<"\n";throw domain_error("Number of days is incorrect\n");
				}
		} 
		
		//no need to handle odd months separately as we have already checked if d>31 so , always valid

		//save current date
		day = static_cast<Day>(d);
		month = static_cast<Month>(m);
		year = static_cast<Year>(y);
		(*this).setFormat(defaultFormat);
		
	}			
																		
	Date::Date()throw(domain_error, out_of_range)	// Default Constructor - construct 'today' (get from system)
	{
	   time_t now = time(0);
   		tm *ltm = localtime(&now);
			//domain error will never be thrown as system stores valid date
			
		if(ltm->tm_year>149||ltm->tm_year<50)			//Invalid year //current yr = 1900 + ltm->tm_year
		{
			cout<<"\n";throw out_of_range("Current year is not valid !\n");		//date out of range
				
		}		
		//cout<<"Today's date : \n";
				
		day = static_cast<Day>(ltm->tm_mday);
		month = static_cast<Month>(ltm->tm_mon+1);
		year = static_cast<Year>(ltm->tm_year+1900);
			
		//set format to dd-mm-yy as in DateFormat
	}					

	Date::Date(const Date& otherDate) // Copy Constructor
	{
		day = otherDate.day;
		month = otherDate.month;
		year = otherDate.year;
	}
	
	// DESTRUCTOR
	Date::~Date() // No virtual destructor needed
	{
	//	delete(format);//delete with new 
	//	free(day);free(month);free(year);
	}

	// BASIC ASSIGNMENT OPERATOR
	Date& Date::operator=(const Date& otherDate)
	{
		day = otherDate.day;
		month = otherDate.month;
		year = otherDate.year;
	//	return reinterpret_cast<Date>(this);
	
		return *this;
	}

	// UNARY ARITHMETIC OPERATORS
	Date& Date::operator++()			// Next day
	{
		int pd = day;
		if(month==Feb)
		{
			if(day<D28)
			{
				day=Day(int(day)+1);
			}
			else if(day==D28 && year%4) ///not a leap yr
			{
				day = D01;
				month =Month(int(month)+1);
			}
			else if(day==D28 && !(year%4))
			{
				day = D29;
			}
			else if(day==D29)	//only possible for a leap yr
			{
				day = D01;
				month =Month(int(month)+1);
			}
			//no other case for feb
		}
		else 
		{
			if(day<D30)
			{
				day=Day(int(day)+1);
			}
			else if(month==Jan||month==Mar||month==May||month==Jul||month==Aug||month==Oct||month==Dec)
			{

				 if(day==D31)
				{
					//day = 1; Handled by enum as 31+1 = 1 in enum Day
					if(month==Dec)
					{
						year =Year(int(year)+1);
						if(year>2049)
						{
							cout<<"\n";throw invalid_argument("The arrived date is invalid!");
						}
					}
					month =Month(int(month)+1);
				}
				day=Day(int(day)+1);
			}
			else			//left out the months with 30 days
			{
				if(day==D30)
				{
					day = D01;
					month =Month(int(month)+1);
				}
			}
		}
		return *this;
	}
	
	
	Date& Date::operator++(int i)		// Same day next week
	{
		if(day<D22)
		{
			day=Day(int(day)+7);
		}
		else if(month==Feb)
		{
			if(year%4)
			{
				day = Day((int(day)+7) % 28);
				month =Month(int(month)+1);
			}
			else
			{
				if(day==D22)
				{
					day=Day(int(day)+7);
				}
				else
				{
					day = Day((int(day)+7) % 29);
					month =Month(int(month)+1); 
				}
			}
		}
		else if(month==Jan||month==Mar||month==May||month==Jul||month==Aug||month==Oct||month==Dec)
		{
			
			if(day>D24)
			{
				if(month==Dec)
				{
					year =Year(int(year)+1);
					if(year>2049)
					{
						cout<<"\n";throw invalid_argument("The arrived date is invalid!\n");
					}
				}
				month =Month(int(month)+1);
			}
			day=Day(int(day)+7);	//can't be taken common as Feb 28 and Feb 29 require special attention
		}
		else			//handle the months with 30 days
		{
			if(day>D30)
			{
				month =Month(int(month)+1); 
			}
			day=Day((int(day)+7) % 30);
		}
		return *this;
	}
	
	
	
	Date& Date::operator--()			// Previous day
	{
		if(day>D01)
		{
			day=Day(int(day)-1);
		}
		//remaining if D01 
		else 
		{
			if(month==Mar)
			{
				if(year%4)//not leap yr
				{
					day = D28;
				}
				else
				{
					day = D29;
				}
				
			}
			else if(month==Jan)
			{
				day = D31;
				year = Year(int(year)-1);
				if(year<1950)
				{
					cout<<"\n";throw invalid_argument("The arrived date is invalid!\n");
				}
			}
			else if(month==Feb||month==Apr||month==Jun||month==Sep||month==Nov)
			{
				day = D31;
			}
			else // months with 31 days eg, 1 May
			{
				day = D30;
			}
			month =Month(int(month)-1);
		}
		return *this;
	}
	
	
	Date& Date::operator--(int b)	// Same day previous week
	{
		//day=Day(int(day)-7);
		if(day>D07)
		{
			day=Day(int(day)-7);
		}	
		//month change guaranteed
		else
		{
			if(month==Mar)
			{
				day=Day(int(day)-7);
				if(year%4)
				{
					day = Day(int(day)-3);
				}	
				else
				{
					day = Day(int(day)-2);
				}
			}
			else if(month==Jan)
			{
				day=Day(int(day)-7);
				year = Year(int(year)-1);
				if(year<1950)
				{
					cout<<"\n";throw invalid_argument("The arrived date is invalid!\n");
				}
			}
			else if(month==Feb||month==Apr||month==Jun||month==Sep||month==Nov)
			{
				day=Day(int(day)-7);
			}
			else	//current months have 30 days
			{
				day=Day(int(day)-7);
				day = Day(int(day)-1);
			}
			month =Month(int(month)-1);
		}
	}		

	// BINARY ARITHMETIC OPERATORS
	double Date::operator-(const Date& otherDate)		//Needed to change return type to double as int gave erraneous outputs
									// Number of days between otherDate and current date
	{
		if(*this==otherDate)
		{
			return 0;
		}
		else if(!(year<1970)&&!(otherDate.year<1970))
		{
			struct tm a = {0,0,0,day,month-1,year-1900}; 
   			struct tm b = {0,0,0,otherDate.day,otherDate.month-1,otherDate.year-1900}; 
   			time_t x = std::mktime(&a);
    		time_t y = std::mktime(&b);
    		if ( x != (time_t)(-1) && y != (time_t)(-1) )
    		{
    		    double difference = difftime(x, y) / (60 * 60 * 24); // difftime returns difference in seconds . A day has 86,400 seconds
				return difference;
    		}
		
		}
		else if(year<1970||otherDate.year<1970)       //that is , before epoch by c++ definitions
		{
			cout<<"Computing...";
    		double diff=0;
			if(*this < otherDate)
			{
				
				while((*this)!=otherDate)
				{
					++(*this);//cout<<"..";
					diff++;
				}
			}
			else 
			{
				while((*this)!=otherDate)
				{
					--(*this);//cout<<"..";
					diff++;
				}
			}
			return diff;
    	}
	}
	
	
	Date Date::operator+(int noOfDays) throw(domain_error, out_of_range)						// Day noOfDays after (before) the current date
	{	
																						// (sign of noOfDays decides ahead or behind)
		if(year < 100)//need to check for certain formats
		{
				if(year<50)
				{
					year += 2000;
				}
				else
				{
						year += 1950;
				}
		}

		if(noOfDays==0)
		{
			return *this;
		}				
		else if(year<1970)
		{
			if(noOfDays < 0)
			{
				int howFurther = -noOfDays;
				cout<<"\nComputing ..";
				while(howFurther)
				{
					--(*this);
					//cout<<"..";
					if(year < 1950)
					{
						cout<<"\n Operation leads to invalid date!\n";
						break;
					}
					howFurther--;
				}
			}
			else
			{
				int howFurther = noOfDays;
				cout<<"\nComputing ..";
				while(howFurther)
				{
					++(*this);
					//cout<<"..";
					if(year > 2049)
					{
						cout<<"\n Operation leads to invalid date!\n";
						break;
					}
					howFurther--;
				}
			}
		}	
		else if(year > 1970)
		{
																												
			tm t = {};
    		t.tm_year = year-1900;
   	 		t.tm_mon  = month-1;
   			t.tm_mday = day;
    	
    		t.tm_mday += noOfDays;
    		mktime(&t);
    		
			int year2 = t.tm_year+1900;			//temporary copy to check if within range
			if((year2 > 2049)||(year2<1950))
			{
				cout<<"\nCannot perform operation as generated date is out of range\n";
			}
			else
			{
				day = Day(t.tm_mday);
				month = Month(1+t.tm_mon);
				year = year2;
			}
		}
	}

	// CAST OPERATORS
	Date::operator WeekNumber() const	// Cast to the week number of the year in which the current date falls
	{

		Date FirstDay = Date(D01,Jan,year);
		WeekDay w = WeekDay((year + year/4 - year/100 + year/400 + 1) % 7);
							
		Date FirstThursday=FirstDay;
		if(w<5)//week start day before or on thursday
		{
				FirstThursday = Date(Day(5-w),Jan,year);	
		}
		else//week starts after thursday
		{
			int i;
			for( i = 0; i < w-4 ; i++)
			{
				--FirstThursday;//firstThusday technically in last year
			}
		}
		Date FirstMonday = --(--(--FirstThursday));
		
		int Yr_53_mondays[11] = {1951,1957,1968,1979,1985,1996,2007,2013,2024,2035,2041};
		int j;
		
		double differBy = Date(*this)-Date(FirstMonday);
				
		int diff = differBy+1;
		if(diff < 3)//this belongs to week 52 or 53 of last year
		{
			//week 52 or 53 depends on number of mondays in last year
			int lastYr = year-1;

			for( j = 0; j < 11; j++)
			{
				if(lastYr==Yr_53_mondays[j])
				{
					return W53;
				}
			}
			//if here , lastYr had 52 Mondays
			return W52;
				
		}
		else
		{
				//cout<<diff<<"\n";
				diff = diff/7 + 1;
				
				int reduced = 0;
			for( j = 0; j < 11; j++)
			{
				if(year==Yr_53_mondays[j])
				{
					diff = diff%53;
					reduced = 1;break;
				}
			}
			if(reduced==0)
			{
					diff = diff%52;
			}
				return WeekNumber(diff);
		}
				
		return W01;
	}

	Date::operator Month() const		// Cast to the month of the year in which the current date falls
	{
		return month;
	}
	
	Date::operator WeekDay() const 	// Cast to the day of the week of the current date	
	{
	    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	    int y = year;
	    int m = month;
	    int d = day;
    	y -= m < 3;
   		WeekDay weekday = WeekDay((y + y/4 - y/100 + y/400 + t[m-1] + d) % 7);
    
    	return weekday;

	}


	bool Date::leapYear() const// True if the year of the current date is a leap year
	{
		if( year%4 )
		{
			return false;
		}
		else return true;
	}

	// BINARY RELATIONAL OPERATORS
	bool Date::operator==(const Date& otherDate)
	{
		if( (day==otherDate.day) && (month==otherDate.month) && (year==otherDate.year))
		{
			return true;
		}
		else return false;
		
	}

	bool Date::operator!=(const Date& otherDate)
	{
		if ( !(*this==otherDate) )
		{ 
			return true;
		}
		else return false;
	}
	
	bool Date::operator<(const Date& otherDate)
	{
		if(year < otherDate.year)
		{
			return true;
		}
		else if(year==otherDate.year)
		{
			if(month < otherDate.month)
			{
				return true;
			}
			else if(month==otherDate.month)
			{
				if(day < otherDate.day)
				{
					return true;
				}
				else return false;		// equality implies false
			}
			else return false;		//month > otherDate.month
		}
		else return false;		//year > otherDate.year
		
	}
	
	bool Date::operator<=(const Date& otherDate)
	{
		//  a  <= b  implies a<b or a==b
		if( (*this==otherDate) || (*this<otherDate) ) 
		{
			return true;
		}
		else return false;
	}
	
	
	bool Date::operator>(const Date& otherDate)
	{
		//a > b implies !(a < b) and (a!=b) i.e , !(a<=b)
		if( !(*this<=otherDate) )
		{
			return true;
		}
		else return false;
	}
	
	
	bool Date::operator>=(const Date& otherDate)
	{
		//a>=b implies !(a<b)
		if ( !(*this<otherDate) )
		{
			return true;
		}
		else return false;
	}

	Day Date::getDay()
	{
		return day;
	}
	Month Date::getMonth()
	{
		return month;
	}
	Year Date::getYear()
	{
		return year;
	}
	
	
	// BASIC I/O using FRIEND FUNCTIONS
	// These functions use Date::format to write or read
	ostream& operator<<(ostream& cout, const Date& date)
	{
		
		//static DateFormat form = date.format;
		char* printDate;
		cout<<"\nDate : ";
		char* pD;
		char* pM;
		char* pY;//char* for storing printing strings
		
		int dateCompletion = 0;//if = 3, it means all formats are correct
		Date d_temp = static_cast<Date>(date);		//Need to cast date to non-const object to use Date functions
		
		if(d_temp.format.getDFormat()==" ")
		{
			d_temp.setFormat(defaultFormat);
		}
		//day handling
		if(strcmp(d_temp.format.getDFormat(),"0")==0)
		{
			cout<<" ";
		}
		else if(strcmp(d_temp.format.getDFormat(),"d")==0)
		{
			cout<<d_temp.getDay()<<"-";
		}
		else if(strcmp(d_temp.format.getDFormat(),"dd")==0)//||strcmp(d_temp.format.getDFormat()," ")==0)
		{
				if(d_temp.getDay()<D10)
				{
					cout<<"0";
				}
				cout<<d_temp.getDay()<<"-";
		}
		
		//month handling
		if(strcmp(d_temp.format.getMFormat(),"0")==0)
		{
			cout<<" ";
		}
		else if(strcmp(d_temp.format.getMFormat(),"m")==0)
		{
			cout<<d_temp.getMonth()<<"-";
		}
		else if(strcmp(d_temp.format.getMFormat(),"mm")==0)//||strcmp(d_temp.format.getMFormat()," ")==0)
		{
				if(d_temp.getMonth()<Oct)
				{
					cout<<"0";
				}
				cout<<d_temp.getMonth()<<"-";
		}
		else if(strcmp(d_temp.format.getMFormat(),"mmm")==0)
		{
			switch(d_temp.getMonth())
			{
				case Jan : cout<<"Jan-";break;
				case Feb : cout<<"Feb-";break;
				case Mar : cout<<"Mar-";break;
				case Apr : cout<<"Apr-";break;
				case May : cout<<"May-";break;
				case Jun : cout<<"Jun-";break;
				case Jul : cout<<"Jul-";break;
				case Aug : cout<<"Aug-";break;
				case Sep : cout<<"Sep-";break;
				case Oct : cout<<"Oct-";break;
				case Nov : cout<<"Nov-";break;
				case Dec : cout<<"Dec-";break;
			}
		}
		
		//year handling
		if(strcmp(d_temp.format.getYFormat(),"0")==0)
		{
			cout<<" ";
		}
		else if(strcmp(d_temp.format.getYFormat(),"yy")==0)//||strcmp(d_temp.format.getYFormat()," ")==0)
		{
			Year py = d_temp.getYear()%100;
			cout<<py;//<<"\n";
		}
		else if(strcmp(d_temp.format.getYFormat(),"yyyy")==0)
		{
				cout<<d_temp.getYear();
				//cout<<"\n";
		}
	}
	
	
	istream& operator>>(istream& cin, Date& date)
	{
		time_t now = time(0);
   		tm *ltm = localtime(&now);			
		if(ltm->tm_year>149||ltm->tm_year<50)			//Invalid year //current yr = 1900 + ltm->tm_year
		{
			cout<<"\n";throw out_of_range("Current year is not valid !\n");		//date out of range
				
		}		
		//cout<<"Today's date : \n";
				
		date.day = static_cast<Day>(ltm->tm_mday);
		date.month = static_cast<Month>(ltm->tm_mon+1);
		date.year = static_cast<Year>(ltm->tm_year+1900);
	}
	// Format Function
	void Date::setFormat(DateFormat& dest_format)
	{
		format = dest_format;
		DateFormat(format);
	}

	DateFormat& Date::getFormat()
	{
		return format;
	}

//};

	//created dummy function for testing - not used anywhere as it was not possible to return a value and throw an excpeption at the same time
	bool validate(Day d,Month m,Year y)
	{
		if(m==Feb)			//February has 28 or 29 days max . depending on whether the current year is leap yr or not
			{
				if(y%4)			//not a leap yr . Valid dates are 1 - 28
				{
					if(d<D01||d>D28)
					{
					//	cout<<"\n";throw domain_error("February does not have these many days");		//domain error implies invalid triplet for (d,m,y)
						return false;
					}
				}
				else
				{
					if(d<D01||d>D29)				//leap yr has 29 feb , like this year
					{
					//	cout<<"\n";throw domain_error("February does not have these many days");	
						return false;
					}
				}
			}
			else if( (m==Apr)||(m==Jun)||(m==Sep)||(m==Nov) )	//for these months,max number of days is 30 not 31 
			{
					if(d==D31)//accepted values in this loop are 1 - 30 . Hence , only one value needs to be checked				
					{
					//	cout<<"\n";throw domain_error("Number of days is incorrect");
						return false;
					}
			} 
			//no need to handle odd months separately as we have already checked if d>31 so , always valid
			return true;
	}
