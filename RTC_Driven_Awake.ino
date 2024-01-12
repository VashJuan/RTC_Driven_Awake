// From: https://forum.arduino.cc/t/external-rtc-to-wake-arduino-up-on-interrupt/321707
// also see: https://github.com/JChristensen/DS3232RTC#setalarmalarm_types_t-alarmtype-uint8_t-minutes-uint8_t-hours-uint8_t-daydate
// & https://github.com/JChristensen/DS3232RTC/blob/master/alarm-primer.md
// On Nano:
// Need to specify: Tools > Processor > ATmega328P (Old Bootloader)  https://arduino.stackexchange.com/questions/51771/cant-upload-to-my-nano-after-updating-to-arduino-avr-boards-1-6-21
// (Also not have anything connected to pins 1 & 2 while uploading...???)

#include <avr/sleep.h>
#include <avr/power.h>
#include <DS3232RTC.h>  // https://github.com/JChristensen/DS3232RTC/
#include <Time.h>
#include <Wire.h>


tmElements_t tm;

DS3232RTC myRTC;  // https://github.com/JChristensen/DS3232RTC/issues/49

//CONVERT __DATE__ and __TIME__ to time_t
time_t cvt_date(char const *date, char const *time) {
    char s_month[5];
    int year;
    tmElements_t t;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(date, "%s %hhd %d", s_month, &t.Day, &year);
    sscanf(time, "%2hhd %*c %2hhd %*c %2hhd", &t.Hour, &t.Minute, &t.Second);

    t.Month = (strstr(month_names, s_month) - month_names) / 3 + 1;
   
    /*
    if( year > 99)
      t.Year = year - 1970;
    else
      t.Year = year + 30;
    */
    t.Year = year - 1970;

    return makeTime(t);
}

int pin2 = 2;

void pin2Interrupt(void) {

  detachInterrupt(0);
}

void enterSleep(void) {
  
  /* Setup pin2 as an interrupt and attach handler. */
  attachInterrupt(0, pin2Interrupt, LOW);
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  sleep_enable();
  
  sleep_mode();
  
  /* The program will continue from here. */
  
  /* First thing to do is disable sleep. */
  sleep_disable(); 
}

void setup() {
  Serial.begin(9600);
  
  myRTC.begin();

  /* Setup the pin direction. */
  pinMode(pin2, INPUT);
  
  setTime(cvt_date(__DATE__, __TIME__));
  myRTC.set(now());
  myRTC.squareWave(DS3232RTC::SQWAVE_NONE); 
  // https://github.com/JChristensen/DS3232RTC#alarm-functions
  // ALM2_MATCH_MINUTES triggers once an hour
  myRTC.setAlarm(DS3232RTC::ALM2_EVERY_MINUTE,0,0,0);
  myRTC.alarmInterrupt(DS3232RTC::ALARM_2, true);
  
  Serial.println(String("System date = ") + month() + "/" + day() + "/" + year() + " " + hour() + ":" + minute() + ":" + second() + "\n");
  
  Serial.println("Initialisation complete.");
}

int seconds = 0;

void loop() {
  delay(1000);
  seconds++;
  
  Serial.print("Awake for ");
  Serial.print(seconds, DEC);
  Serial.println(" second");
  digitalClockDisplay(); // print time and date
  
  if(seconds == 4) {
    Serial.println("Entering sleep");
    digitalClockDisplay();
    delay(200);
    seconds = 0;
    enterSleep();
  }
  
}

//PRINT TIME FROM RDS3231
void digitalClockDisplay(void) {
  // digital clock display of the time  MM/DD/YY
  myRTC.read(tm);
  Serial.print(tm.Month, DEC);
  Serial.print('/');
  Serial.print(tm.Day,DEC);
  Serial.print('/');
  Serial.print(tm.Year+1970, DEC);
  Serial.print("   ");
  Serial.print(tm.Hour, DEC);
  Serial.print(':');
  Serial.print(tm.Minute, DEC);
  Serial.print(':');
  Serial.println(tm.Second, DEC);
  
  if(myRTC.alarm(DS3232RTC::ALARM_2)) {
    Serial.println("ALARM has been triggered, resetting...");
  }
}