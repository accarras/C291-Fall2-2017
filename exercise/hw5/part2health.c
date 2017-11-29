/****************************************************************
Tony Carrasco
11/28/17
C291
Assignment 5
Part 2
part2health.c
****************************************************************/

#include <stdio.h>
#include <time.h>

int getAge(int days, int month, int year);
int isLeapYear(int year, int mon);

int main()
{
  // structure stores all user data 
  struct healthProfile {
      char lastName[ 15 ];
      char firstName[ 15 ];
      char gender[1];
      int height;
      int weight;
      // separate structure within for DOB
      struct {
        int day;
        int month;
        int year;
      } dob;
  } person1;
   
  printf("Enter First Name\n");
  scanf("%s", &person1.firstName);
  
  printf("Enter Last Name\n");
  scanf("%s", &person1.lastName);
  
  printf("Enter Gender as Character(m/f)\n");
  scanf("%s", &person1.gender);
  
  printf("Enter Height in inches as Integer\n");
  scanf("%d", &person1.height);
  
  printf("Enter Weight in pounds as Integer\n");
  scanf("%d", &person1.weight);
  
  
  printf("Enter birtdate details\n");
  
  printf("Enter Year of birth: ");
  scanf("%d", &person1.dob.year);
  
  printf("Enter Month of birth: ");
  scanf("%d", &person1.dob.month);
  
  printf("Enter Day of birth: ");
  scanf("%d", &person1.dob.day);
  
  int age = getAge(person1.dob.day, 
                   person1.dob.month, 
                   person1.dob.year);
                   
  int maxHeartRate = 220 - age;
  
  float bmi = float(float(person1.weight*703)/float((person1.height)*(person1.height)));
 
  printf("Your name is %s %s.\n", person1.firstName, person1.lastName);
  printf("Your gender was input as %s.\n", person1.gender);
  printf("Your max Heart Rate is %d beats per minute.\n", maxHeartRate);
  printf("Your best Heart Rate Range is between %d and %d beats per minute.\n", (maxHeartRate/2), (int((0.85)*maxHeartRate)));
  
  printf("Your BMI is %f\n", bmi);
  printf("BMI Values:\n");
  printf("Underweight: less than 18.5\n");
  printf("Normal: between 18.5 and 24.9\n");
  printf("Overweight: etween 25 and 29.9\n");
  printf("Obese: 30 or greater\n");
  
  
                   
 
  return 0;
}


 
// calculates age in a way
// more precise and complicated than needed
int getAge(int days, int month, int year)
{
    int DaysInMon[] = {31, 28, 31, 30, 31, 30,
                       31, 31, 30, 31, 30, 31};
    char dob[100];
    time_t ts;
    struct tm *ct;
 
    /*get current date.*/
    ts = time(NULL);
    ct = localtime(&ts);
 
   /* printf("Current Date: %d/%d/%d\n",
            ct->tm_mday, ct->tm_mon + 1, ct->tm_year + 1900);*/
 
    days = DaysInMon[month - 1] - days + 1;
 
    /* leap year checking*/
    if (isLeapYear(year, month)) 
    {
            days = days + 1;
    }
 
    /* calculating age in no of days, years and months */
    days = days + ct->tm_mday;
    month = (12 - month) + (ct->tm_mon);
    year = (ct->tm_year + 1900) - year - 1;
 
    /* checking for leap year feb - 29 days */
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1))) 
    {
            if (days >= (DaysInMon[ct->tm_mon] + 1)) 
            {
                    days = days - (DaysInMon[ct->tm_mon] + 1);
                    month = month + 1;
            }
    } 
    else if (days >= DaysInMon[ct->tm_mon]) 
    {
            days = days - (DaysInMon[ct->tm_mon]);
            month = month + 1;
    }
 
    if (month >= 12) 
    {
            year = year + 1;
            month = month - 12;
    }
 
    /* print age */
    //printf("\n## You are  %d years %d months and %d days old. ##\n", year, month, days);
 
    return year;
}

// gotta account for leap years too!
int isLeapYear(int year, int mon) 
{
    int flag = 0;
    if (year % 100 == 0) 
    {
            if (year % 400 == 0) 
            {
                    if (mon == 2) 
                    {
                            flag = 1;
                    }
            }
    } 
    else if (year % 4 == 0) 
    {
            if (mon == 2) 
            {
                    flag = 1;
            }
    }
    return (flag);
}
