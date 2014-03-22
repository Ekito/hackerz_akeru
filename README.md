TrackMyPet - Akeru part
==

About
--

TrackMyPet is a proof of concept of a Sigfox enabled GPS tracked intended to show the last known position of your equiped pet (OK, a big pet, like a pony or a cow; don't try with your hamster).

TrackMyPet is based on the following technologies : 

* GPS Tracker : Ardunio board with [Sigfox modem](http://sigfox.com/) (named [Akeru](http://akeru.cc/), homemade battery shield and MTK3339 GPS module.
* Play! 2.2 application hosted on [Heroku](http://herokuapp.com/) Server and [Kinvey](http://kinvey.com/) datastore for GPS data persistence.


GPS Tracker
--
The GPS Tracker is composed of three main parts:

* Akeru board. It's the same board than a plain UNO Rev 3 one, except it embeds a Sigfox modem and the connection to  computer is made through a micro-USB connector and an FTDI USB to serial chipset.
* Battery shield. It's a mandatory part, but usefull if you don't want your pet to be plugged to the nearest electric outlet. It's made with a 3.7V lipo battery, and a Pololu 5V step-up/step-down voltage regulator (part number : S7V7F5). The output of the voltage regulator is connected to the 5V pin of the Akeru board, and the GND pin of the voltage regulator is connected to the GND pin of the Akeru board.
* GPS module. This serial GPS module, based on the MTK3339 chipset, outputs NEMA frames through its serial pins. Its TX pin is connected to the RX pin of the Akeru card, its GND pin is connected to GND pin of the Akeru card, and its VCC pin is connected to the 3V3 pin of the Akeru. If your version of this module doesn't accepts 5V input, DO NOT connect its RX pin to Akeru's TX pin, excepts if you want to fry it.

Using your Arduino IDE, you just have to upload “hackerz_akeru.ino” to your Akeru board.

The code is pretty simple :

* We first try to get valid GPS coordinates, and don't go further while we don't get them.
* Then we send these coordinates through Sigfox network
* Go to first step

As Sigfox network only allows one frame every 10 minutes, the second step will be skipped if the last message send didn't happen ten or more minutes ago.


Server part
--

Head over to the related [GitHub repository](https://github.com/Ekito/hackerz-server)!

You can see “live action” [here](http://hackerz-server.herokuapp.com/)


Arduino support
--

Head over to the related [GitHub repository](https://github.com/Ekito/hackerz_3d)!