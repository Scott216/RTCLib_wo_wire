/* 
This library communicates with the DS1307 Real Time Clock 
This version doesn't use wire.h library, it uses the I2C.h library by Wayne Truchsess from DSS Circuits
http://dsscircuits.com/articles/arduino-i2c-master-library.html  
http://github.com/rambo/I2C

This is based on Adafruit's RTCLib http://github.com/adafruit/RTClib which is a fork of JeeLab's Library:  http://github.com/jcw/rtclib

Released to the public domain! Enjoy!

Simple general-purpose date/time class (no TZ / DST / leap second handling!)

Change Log
07/09/14 - Use __DATE__ __TIME__ from PROGMEM (this mirrors Adafruit change on 2/20/14)
07/09/14 - Add TimeSpan class and simple DateTime duration arithmetic support (mirrors Adafruit change on 6/12/14, see: bit.ly/1ojYKAL)


To Do:
Add square wave output support: http://github.com/adafruit/RTClib/commit/65ae8047d1c3e57bc9f1ccb09018f72cd29b19d4
Add NVRAM functions  http://github.com/adafruit/RTClib/commit/87624ede6728522d1457905754a6222ca54033b1

*/
#include <Arduino.h> 

#ifndef RTCLIB_DSSI2C_H
#define RTCLIB_DSSI2C_H

class TimeSpan;

class DateTime {
public:
    DateTime (uint32_t t =0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
    DateTime (const DateTime& copy);
    DateTime (const char* date, const char* time);
    DateTime (const __FlashStringHelper* date, const __FlashStringHelper* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    uint8_t dayOfWeek() const;

    // 32-bit times as seconds since 1/1/2000
    long secondstime() const;   
    // 32-bit times as seconds since 1/1/1970
    uint32_t unixtime(void) const;

    DateTime operator+(const TimeSpan& span);
    DateTime operator-(const TimeSpan& span);
    TimeSpan operator-(const DateTime& right);
    
protected:
    uint8_t yOff, m, d, hh, mm, ss;
};


// Timespan which can represent changes in time with seconds accuracy.
class TimeSpan {
public:
    TimeSpan (int32_t seconds = 0);
    TimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds);
    TimeSpan (const TimeSpan& copy);
    int16_t days() const         { return _seconds / 86400L; }
    int8_t  hours() const        { return _seconds / 3600 % 24; }
    int8_t  minutes() const      { return _seconds / 60 % 60; }
    int8_t  seconds() const      { return _seconds % 60; }
    int32_t totalseconds() const { return _seconds; }

    TimeSpan operator+(const TimeSpan& right);
    TimeSpan operator-(const TimeSpan& right);

protected:
    int32_t _seconds;
};


// RTC based on the DS1307 chip connected via I2C and the DSSI2C library
class RTC_DS1307 {
public:
  static uint8_t begin(void);
    //Returns 0 if no errors occured or 2 if communication errors occured.
    static uint8_t adjust(const DateTime& dt);
	//Returns 0 if clock is halted, 1 if clock is running or 2 if communication
	//errors occured.
    uint8_t isrunning(void);
	//Returns 0 if no errors occured or 2 if communication errors occured.
    static uint8_t now(DateTime& dt);
};

// RTC using the internal millis() clock, has to be initialized before use
// NOTE: this clock won't be correct once the millis() timer rolls over (>49d?)
class RTC_Millis {
public:
    static void begin(const DateTime& dt) { adjust(dt); }
    static void adjust(const DateTime& dt);
    static DateTime now();

protected:
    static long offset;
};

#endif // RTCLIB_DSSI2C_H