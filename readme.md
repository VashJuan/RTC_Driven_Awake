# RTC_Driven_Awake

This Arduino sketch demonstrates putting an Arduino into sleep mode and using the DS323x
Real Time Clock (RTC) to generate a wakeup interupt (every minute or hour, say) to restart
the Arduino from where it left off.

Based on https://forum.arduino.cc/t/external-rtc-to-wake-arduino-up-on-interrupt/321707
but updated for V 2.0 of J Christensen's library
[DS3232RTC](https://github.com/JChristensen/DS3232RTC) which supports both DS2331 & DS3232
devices.

## If using an Arduini Nano

- For Arduino IDE: specify: Tools > Processor > ATmega328P (Old Bootloader) per
  https://arduino.stackexchange.com/questions/51771/cant-upload-to-my-nano-after-updating-to-arduino-avr-boards-1-6-21
- For Visual Studio Code IDE: click on the board type on the (bottom) status bar & select
  ATmega328P (Old Bootloader) as the processor

## General

- Connect pin 2 of the Arduino to the DS2331 RTC's SQW pin to handle the interupt
- Great info at https://github.com/JChristensen/DS3232RTC/blob/master/alarm-primer.md

## DS323x RTC References

- https://www.analog.com/en/design-notes/feature-comparison-of-the-ds323x-realtime-clocks.html
