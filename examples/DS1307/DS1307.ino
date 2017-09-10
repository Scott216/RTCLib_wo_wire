/* 
This library communicates with the DS1307 Real Time Clock 
This version doesn't use wire.h library, it uses the I2C.h library by Wayne Truchsess from DSS Circuits
   http://dsscircuits.com/articles/arduino-i2c-master-library.html  
   http://github.com/rambo/I2C

Library is based on Adafruit's RTCLib http://github.com/adafruit/RTClib which is a fork of JeeLab's Library: http://github.com/jcw/rtclib 

Released to the public domain! Enjoy!

Simple general-purpose date/time class (no TZ / DST / leap second handling!)
*/

#include <RTClib_DSSI2C.h>  // http://github.com/Scott216/RTCLib_wo_wire
#include <I2C.h>            // http://dsscircuits.com/articles/arduino-i2c-master-library.html     
                            // http://github.com/rambo/I2C

RTC_DS1307 RTC;

void setup()
{

  Serial.begin(9600);
  I2c.begin();
  I2c.timeOut(30000);
  RTC.begin();
  
  Serial.println("Communicate with DS1307 using I2C.h library instead of wire.h\n");
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");

    // following line sets the RTC to the date & time this sketch was compiled
    // sample input: date: "Dec 26 2009", time: "12:34:56"
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop () {
    DateTime now;
	RTC.now(now);
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now.unixtime() + 7 * 86400L + 30);
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(3000);
}
