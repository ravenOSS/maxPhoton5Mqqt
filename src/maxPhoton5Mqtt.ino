/*
 * Project maxPhoton5Mqtt
 * Description: Interface Maxbotix serial sensor to Particle Photon or Arduino compatible
 * Add mqtt client to send range data to mqtt broker
 * Author: David Richards / ravenIoT LLC
 * Date: June 29, 2019
 * With thanks to:
 * https://github.com/nimasaj/Maxbotix_Ultrasonic/blob/master/Examples/Serial_read.ino
 * for the unwitting help in seeing 'while' as a replacement for a 'for' loop
*/

// Using hardware UART on Photon, Electron, Fio
// Maxbotix sensor with RS232 conversion to TTL with MAX3232

#include "MQTT.h"

byte server1[] = {192, 168, 0, 103};

void callback(char *topic, byte *payload, unsigned int length) {}

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * MQTT client("www.sample.com", 1883, callback);
 **/
MQTT client(server1, 1883, callback);

void setup()
{
  Serial.begin(57600);
  while (!Serial)
  {
    ; // wait for serial port to connect.
  }
  Serial.println("Serial open");
  // set the data rate from the sensor
  Serial1.begin(9600, SERIAL_8N1); // Default but set explicitly anyway
  while (!Serial1)
  {
    ; // wait for Serial1 port to connect.
  }
  Serial.println("Sensor connected");
  client.connect("maxphoton5");
  if (client.isConnected) {
    Serial.println("Connected to broker");
  } else {
    Serial.println("Failed to connect to broker");
  }
}

void loop()
{
  // uint16_t range = maxRead();
  String range = maxRead();
  Serial.print("Distance: ");
  Serial.println(range);
  String payload = range;
  if (client.isConnected())
  {
    client.publish("distance", payload);
  }
  Serial.print("Int range: ");
  Serial.println((range).toInt());

  delay(5000);
}

// uint16_t maxRead() {
String maxRead()
{                           // get a data string back from reading sensor
  char inChar;              // type for data read
  const uint8_t length = 3; // number of ascii numeric characters in sensor data
  // char charArray[length];       // array to store range data
  String reading = ""; // empty string to add data
  uint8_t i = 0;       // initialize counter

  while (Serial1.available())
  {
    inChar = Serial1.read(); // continuously read sensor input in while loop
    if (inChar == 'R')
    { // test if char == R for beginning data
      // Serial.println("Got an R");  // Debug
      while (i < length)
      {
        // charArray[i] = Serial1.read(); // assign input char to charArray index
        reading += (Serial1.read() - '0'); // convert ASCII to single numeral, add to range reading
                                           // Serial.print("char: ");        // debug
        Serial.print("reading: ");         // Display data accumulation
                                           // Serial.println(charArray[i]);
        Serial.println(reading);
        i++;
      }
    }
  }
  // return atoi(charArray);            // extract integer range from char charArray
  return reading; // return range reading as a string
}