#include <string.h>
#include <time.h>
#include <stdio.h>
#include "datetime.h"

DateTime getCurrentDateTime()
{
	time_t t = time(NULL);
	struct tm dateNow = *localtime(&t);
	
	/**
	int    tm_sec   seconds [0,61]
	int    tm_min   minutes [0,59]
	int    tm_hour  hour [0,23]
	int    tm_mday  day of month [1,31]
	int    tm_mon   month of year [0,11]
	int    tm_year  years since 1900
	int    tm_wday  day of week [0,6] (Sunday = 0)
	int    tm_yday  day of year [0,365]
	int    tm_isdst daylight savings flag
	* time.h
	 */
	
	int year = dateNow.tm_year % 100;
	int month = dateNow.tm_mon + 1;
	int day = dateNow.tm_mday;
	int hour = dateNow.tm_hour;
	int minutes = dateNow.tm_min;
	
	DateTime dt;
	
	dt.date = (day & DATETIME_PARCEL_MASK) << DATETIME_DAY_POSITION_BIT |
			  (month & DATETIME_PARCEL_MASK) << DATETIME_MONTH_POSITION_BIT |
			  (year & DATETIME_PARCEL_MASK) << DATETIME_YEAR_POSITION_BIT 
			  ;
	
	dt.time = (hour & DATETIME_PARCEL_MASK) << DATETIME_HOUR_POSITION_BIT |
			  (minutes & DATETIME_PARCEL_MASK) << DATETIME_MINUTE_POSITION_BIT;
	
	return dt;
}

void datetimeToString(DateTime dt, char buffer[])
{
	int year = (dt.date >> DATETIME_YEAR_POSITION_BIT) & DATETIME_PARCEL_MASK;
	int month = (dt.date >> DATETIME_MONTH_POSITION_BIT) & DATETIME_PARCEL_MASK;
	int day =(dt.date >> DATETIME_DAY_POSITION_BIT) & DATETIME_PARCEL_MASK;
	int hour = (dt.time >> DATETIME_HOUR_POSITION_BIT) & DATETIME_PARCEL_MASK;
	int minutes = (dt.time >> DATETIME_MINUTE_POSITION_BIT) & DATETIME_PARCEL_MASK;
	
	sprintf(buffer, "%02d/%02d/%02d - %02d:%02d",day,month,year,hour,minutes);
}
