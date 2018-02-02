# IR_ACRemoteESP8266
A network enabled IR AC remote controller using ESP8266!


Having a couple of aircon units in our office, we needed a solution to control them from a central location.
There are 2 goals:
1. Create a web / app interface to allow multiple users to control the aircons over the network or even remotely
1. Setup some automations using MQTT and a server or some other solution, to allow the aircons to be controlled automtically based on time of day and environmental conditions such as temp / humidity etc.

The inital solution idea is to build on the ESP8266 platform and use IR to control the aircons (Serial was investigated but no easy serial port was avaliable on these units)
IR decoding from the standard remotes, using the IRremoteESP8266 and other IR libraries did not yeild a recognised encoding structure. Rather the 'raw' codes will be used for now to set a predefined range of functions.

#Reference Links:
Lots of inspiration from:
http://rbaron.net/blog/2017/08/05/A-Slack-bot-for-controlling-the-offices-ac.html
https://github.com/rbaron/st-peter-esp8266
https://github.com/krzynio/esp8266-ir-ac-remote

IRremoteESP8266 library will be providing the IR functions for now:
https://github.com/markszabo/IRremoteESP8266

Great Arduino based IR library with lots of decoders:
https://github.com/z3t0/Arduino-IRremote
Another IR lib, havn't tried this one yet
https://github.com/ToniA/arduino-heatpumpir

#Future decoding of protocol:
Seems like our 'Aux' aircon units use a form of the AWIA_RC_T501 protocol, execpt 211 bytes? See IR_Codes.txt for raw data
https://github.com/z3t0/Arduino-IRremote/issues/197

IRScrutinizer seems like a great tool should we ever want to decode this protocol
http://www.harctoolbox.org/IrScrutinizer.html
http://www.hifi-remote.com/wiki/index.php?title=IrScrutinizer_Guide

IR decoding ideas
http://www.righto.com/2017/12/decoding-air-conditioner-controls.html

#Webserver Ideas
Particle based project with Webserver
https://www.hackster.io/yleguesse/spark-core-smart-air-conditioner-c147db
OpenHab Ideas
http://domoticforall.blogspot.co.za/2015/06/control-air-conditioner-with-openhab.html
MQTT Example of IR control:
https://github.com/zeroflow/ESPAircon
