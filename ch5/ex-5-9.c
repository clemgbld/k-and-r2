static char (*daytab)[13] = (char[][13]){
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
/* day_of_year: set day of year from month & day */

int day_of_year(int year, int month, int day) {
  int leap;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  char *dayPtr = daytab[leap];
  char *dayMonth = dayPtr + month;
  if (day > *dayMonth || day < 1)
    return -1;
  dayPtr++;
  for (; dayPtr < dayMonth; dayPtr++)
    day += *dayPtr;
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  if (yearday < 1)
    return;
  int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  char *dayPtr = daytab[leap];
  char *start = dayPtr;
  dayPtr++;
  for (; yearday > *dayPtr; dayPtr++) {
    if ((dayPtr - start) > 12)
      return;
    yearday -= *dayPtr;
  }

  *pmonth = dayPtr - start;
  *pday = yearday;
}
