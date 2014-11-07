river-monster
=============

River monitoring hack-a-thon at the Lowell Makerspace.

Goals:
 - Battery-less sensors using energy havevesting
 - Sensor gateway using SMS
 - Solar gateway charging


###Update: 11/6/2014

As a first pass project we're going to change the remote sensor design.  Each sensor node will use an inexpensive 433Mhz transmitter module (like this) and an Arduino pro mini.  Using the low power library we shuold be able to get month of battery life from a few AA batteries, maybe longer with a lithium-ion.

The gateway will be an Arduino Uno with a GPRS sheild, 433 Mhz reciever and a large antenna.

This will greatly simplify the design and allow us to quickly build a proof on concept that can be expanded.

See the wiki for more info. 


![River monster block diagram](https://raw.githubusercontent.com/bunedoggle/river-monster/master/images/River%20Monster.png)






Resources:
 - http://www.seeedstudio.com/depot/GPRS-Shield-V20-p-1379.html?cPath=132_134
 - http://publiclab.org/wiki/water-quality-sensor
 - https://www.enocean.com/en/enocean-pi/


Low Power Arduino lib:
 - http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/
 - https://github.com/rocketscream/Low-Power
