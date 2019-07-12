# maxPhoton5Mqtt

Code to read a Maxbotix ultrasonic range sensor and capture a range reading for 
further processing. 

In the case of the MQTT version, a string is assembled from the individual characters
read from the sensor. This provides a ready to use object to publish through MQTT.

The code also demonstrates a method to convert the ASCII text to an integer value
that can be used for math operations.

The maxPhoton5 repo has code that returns an int value from the sensor reading. It uses 
a character array and atoi to derive int data.

Serial.print statements have been left in to aid understanding of the code and help debug. 

