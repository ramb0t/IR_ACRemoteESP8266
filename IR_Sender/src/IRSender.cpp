#include <Arduino.h>

/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.0 April, 2017
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to ESP8266 pin 4 (D2).
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)

// Example of data captured by IRrecvDumpV2.ino
uint16_t C16OnFH[211] = {8900, 4554,  526, 1692,  496, 1722,  472, 644,  464, 632,
  466, 630,  466, 630,  490, 1728,  450, 1748,  470, 1750,  470, 1750,  466, 1752,
  468, 650,  468, 628,  494, 602,  494, 1724,  448, 650,  492, 606,  462, 632,
  494, 602,  494, 602,  494, 602,  494, 1724,  448, 1752,  466, 1752,  466, 650,
  492, 606,  466, 628,  492, 604,  492, 606,  466, 630,  466, 632,  464, 632,
  464, 632,  464, 632,  464, 634,  462, 634,  442, 654,  444, 1754,  528, 590,
  444, 652,  446, 650,  448, 648,  450, 646,  450, 646,  450, 648,  474, 622,
  450, 646,  476, 620,  504, 592,  502, 594,  504, 594,  504, 592,  532, 564,
  534, 1644,  586, 554,  538, 558,  540, 556,  540, 556,  540, 556,  540, 556,
  540, 556,  540, 556,  540, 556,  540, 556,  542, 554,  542, 556,  542, 554,
  540, 556,  540, 556,  542, 554,  542, 554,  542, 556,  540, 554,  542, 554,
  542, 554,  542, 556,  542, 554,  542, 1678,  536, 560,  540, 556,  540, 556,
  542, 554,  540, 558,  564, 530,  540, 558,  540, 556,  538, 558,  538, 558,
  540, 1680,  532, 564,  538, 1682,  536, 560,  538, 558,  538, 558,  538, 558,
  538, 558,  538, 1682,  532, 1686,  532, 1686,  532, 1688,  534, 562,  536,
  562,  536, 1684,  532, 564,  562};  // 16'C Fan High On F638D84B

uint16_t C16OffFH[211] = {8886, 4566,  500, 1718,  474, 1746,  474, 626,  470, 626,  496, 598,  472, 624,  472, 1746,  472, 1746,  474, 1746,  474, 1744,  474, 1746,  474, 626,  470, 626,  470, 626,  470, 1746,  474, 626,  472, 624,  472, 626,  470, 624,  472, 626,  470, 624,  472, 1746,  474, 1746,  474, 1744,  474, 624,  474, 622,  474, 624,  474, 622,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  474, 622,  472, 624,  474, 624,  472, 624,  472, 1744,  476, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  474, 622,  472, 624,  472, 622,  474, 624,  472, 624,  472, 624,  472, 624,  474, 622,  472, 1744,  476, 622,  474, 622,  472, 624,  472, 624,  498, 598,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 624,  472, 626,  472, 624,  470, 624,  472, 624,  470, 626,  472, 624,  472, 624,  472, 624,  472, 624,  470, 626,  472, 624,  472, 624,  470, 626,  472, 624,  472, 624,  470, 626,  498, 598,  470, 626,  470, 626,  472, 624,  470, 1746,  472, 626,  470, 1748,  472, 626,  470, 626,  470, 626,  470, 626,  496, 598,  470, 1748,  472, 1748,  472, 1746,  472, 1746,  474, 626,  468, 1750,  474, 624,  494, 602,  496};  // 16'C Fan High Off 62788A1D


uint16_t rawData1[211] = {8908, 4540,  500, 1720,  498, 1722,  498, 600,  496, 602,  496, 598,  498, 598,  498, 1720,  500, 1722,  498, 1720,  498, 1720,  498, 1722, 498, 600,  496, 1720,  498, 598,  498, 1720,  500, 596,  500, 602,  494, 624,  472, 598,  498, 598,  498, 598,  498, 1720,  498, 1722,  498, 1720,  500, 600,  496, 598,  498, 600,  496, 598,  498, 600,  496, 624,  472, 598,  498, 600,  496, 600,  498, 598,  498, 600,  496, 600,  496, 624,  472, 1722,  498, 624,  472, 1720,498, 624,  472, 624,  472, 624,  472, 624,  472, 624,  470, 600,  498, 624,  472, 624,  472, 624,  472, 598,  498, 624,  472, 602,  496, 622,  474, 1720,  500, 624,472, 624,  474, 622,  472, 598,  498, 624,  472, 624,  474, 600,  496, 622,  474, 624,  472, 602,  494, 624,  472, 624,  472, 602,  494, 624,  474, 624,  472, 624,  472, 624,  472, 624,  470, 626,  472, 624,  472, 624,  472, 598,  496, 624,  472, 1722,  496, 600,  496, 624,  472, 598,  500, 624,  472, 600,  498, 622,  472, 600,  498, 624,  472, 600,  498, 622,  472, 1722,  498, 624,  472, 1720,  500, 600,  496, 624,  474, 622,  474, 622,  474, 622,  472, 1722,  498, 1720,  498, 1720, 500, 1718,  500, 1720,  498, 602,  494, 1722,  498, 1720,  524};  // UNKNOWN B1CE6B7C

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

  Serial.println("Hello World! Time to send some IR stuff :D");
}

void loop() {
// #if SEND_NEC
//   Serial.println("NEC");
//   irsend.sendNEC(0x00FFE01FUL, 32);
// #endif  // SEND_NEC
//   delay(2000);
// #if SEND_SONY
//   Serial.println("Sony");
//   irsend.sendSony(0xa90, 12, 2);
// #endif  // SEND_SONY
//   delay(2000);

  Serial.println("16'C On Fan High");
  irsend.sendRaw(C16OnFH, 211, 38);  // Send a raw data capture at 38kHz.

  delay(5000);

  Serial.println("16'C Off Fan High");
  irsend.sendRaw(C16OffFH, 211, 38);  // Send a raw data capture at 38kHz.

  delay(5000);

}
