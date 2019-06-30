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
}

void loop()
{
  uint16_t range = maxRead();
  Serial.print("Range: ");
  Serial.println(range);
  delay(1000);
}

uint16_t maxRead()
{
char inChar;                        // type for data read
const uint8_t length = 3;           // number of ascii numeric characters in sensor data
char charArray[length];             // array to store range data
uint8_t i = 0;                      // initialize counter

  while (Serial1.available()) {
    inChar = Serial1.read();        // continuously read sensor input in while loop
    if (inChar == 'R') {            // test if char == R for beginning data
    // Serial.println("Got an R");  // Debug
      while (i < length) {
        charArray[i] = Serial1.read(); // assign input char to charArray index
        Serial.print("char: ");        // debug
        Serial.println(charArray[i]);
        i++;
      }
    }
  }
  return atoi(charArray);            // extract integer range from char charArray
  }



// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}