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

#include "MQTT.h"  // Ensure library is added to project not just included

/**
 * To use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * To use domain name,
 * MQTT client("mqtt.eclipse.org", 1883, callback);
 **/

byte server1[] = {192, 168, 0, 103};

void callback(char *topic, byte *payload, unsigned int length) {}

String clientID = "maxPhoton5";

MQTT client(server1, 1883, callback);

// int alertLED = D7;

void setup()
{
  Serial.begin(57600); // Serial monitor
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
  mqttconnect();
  // client.connect(clientID);
  // if (client.isConnected()) {
  //   Serial.println("Connected to broker");
  // } else {
  //   Serial.println("Failed to connect to broker");
  //   alert();
  // }
  // pinMode(alertLED, OUTPUT);
}

void mqttconnect () {
client.connect(clientID);
  if (client.isConnected()) {
    Serial.println("Connected to broker");
  } else {
    Serial.println("Failed to connect to broker");
    alert();
  }
}

void alert () {
    uint16_t blinks = 10;
    uint16_t i;
    RGB.control(true);
    for ( i = 0; i <= blinks; i++ ) {
    RGB.color(255, 0, 0);     // Set the RGB LED to red
    delay(1000);              // Keep it on for 1 second...
    RGB.color(255, 255, 255); // Sets the RGB LED to white
    delay(500);               // Wait 0.5 second...
    }
    RGB.control(false);

}


void loop()
{
  String range = maxRead();
  Serial.print("Distance: ");
  Serial.println(range);
  if (client.isConnected())
  {
    client.publish("distance", range);
  }
  Serial.print("Int range: ");
  Serial.println((range).toInt());

  delay(5000);
}

// uint16_t maxRead() {
String maxRead()
{                           // get a data string back from reading sensor
  char inChar;              // type for data read
  const uint8_t length = 3; // number of ascii numeric characters in sensor data. Adjust for sensor type
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
        reading += (Serial1.read() - '0'); // convert ASCII DEC to single numeral, add to range reading
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