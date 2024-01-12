# RTC_Driven_Awake

Based on (https://forum.arduino.cc/t/external-rtc-to-wake-arduino-up-on-interrupt/321707)
but updated for V 2.0 of J Christensen's library
[DS3232RTC](https://github.com/JChristensen/DS3232RTC)

## If using an Arduini Nano##

- Specify: Tools > Processor > ATmega328P (Old Bootloader) per
  (https://arduino.stackexchange.com/questions/51771/cant-upload-to-my-nano-after-updating-to-arduino-avr-boards-1-6-21)
- For Visual Studio Code, click on the board type on the (bottom) status bar & select
  ATmega328P (Old Bootloader) as the processor

## General

- Connect pin 2 of the Arduino to the DS2331 RTC's SQW pin to handle the interupt
- Great info at (https://github.com/JChristensen/DS3232RTC/blob/master/alarm-primer.md)
