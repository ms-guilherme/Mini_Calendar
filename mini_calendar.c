#include <stdio.h>
#include <stdbool.h>

bool LeapYear(int);
int MonthLength(int*, int*, bool);
void newDate(int*, int*, int*, bool, int);

bool LeapYear(int year) {
  //If the year is divisible by four, it's a leap year. But if the year can be divided by 100 as well as four, it's not a leap year. However, if the year is divisible by 400, it is a leap year.
  if (year % 4 == 0) {

    if (year % 100 != 0 || year % 400 == 0) return true;
  else return false;

  } else return false;
}

int MonthLength(int *month_length, int *month, bool leap) {
  if (*month != 2) {
    switch(*month) {case 1: case 3: case 5: case 7: case 8: case 10: case 12: *month_length = 31; 
    break; 
    default: *month_length = 30;} 
  } else *month_length = leap ? 29 : 28;
  return *month_length;
}

void newDate(int *month, int *day, int *year, bool leap, int skip) {
  int month_length;

  while (skip > 0) {
    month_length = MonthLength(&month_length, month, leap);

    /*Prototype For big distances/skips
    int feb_distance = *month > 2 ? -1 * (*month - 14) : *month % 2;
    if (feb_distance == 0 && skip > 31) {*month += leap ? 29 : 28; skip -= leap ? 29 : 28; feb_distance = 11;} //February to March
    while (skip > 31) {
      *month += (int)(skip / 30.5) % feb_distance; //Jump all months there's in 'skip', to the maximum of 'feb_distance' months
      skip -= ((int)(skip / 30.5) % feb_distance) * 30.5; //Discounts the days used to jump the months above
      //We're now, if after full cycle, in February, the month where it's dangerous to use the medium of 30.5 days/month
    }
    */

    while (*day <= month_length && skip > 0) {
      if (skip >= month_length - *day && *day != month_length) {
        skip -= month_length - *day;
        *day += month_length - *day;
      }
      else {
        *day += 1;
        skip--;
      }
    }
    if (*day > month_length) {
      *month += 1;
      *day = 1;
      if (*month > 12) {
        *year += 1;
        *month = 1;
        leap = LeapYear(year);
      }
    }
  }
}

int main() {

  int month, day, year, skip;
  bool leap, repeatInput;

  printf("Hey! What about we build a calendar and check future dates? \n");

  repeatInput = true;
  do { //Date choose
    printf("Choose a Date of whole number (mm dd yyyy): \n");
    scanf(" %i %i %i", &month, &day, &year);
    if (day < 1 || day > 31) printf("Invalid entries! Please, check your Day! (Example of entrie: 9 30 2024)\n");
    else if (month < 1 || month > 12) printf("Invalid Month!\n");
    else repeatInput = false;
  } while (repeatInput == true);


  leap = LeapYear(year);
  if (leap) printf("So, your leap date is %i/%i/%i. ", month, day, year);
  else printf("So, your date is %i/%i/%i. ", month, day, year);
  do { //Data skip choose

    printf("Now, how much days from now do you want to skip to? ");
    scanf(" %i", &skip);
    if (skip < 0 || skip > 100000000000) printf("\nOps! That's number is impossible...\n");

  } while (skip < 0 || skip > 100000000000);

  newDate(&month, &day, &year, leap, skip);
  printf("This would be the date of %i/%i/%i\n", month, day, year);
}