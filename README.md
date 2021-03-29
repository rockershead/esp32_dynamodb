# esp32_dynamodb

This is a simple project where esp32 is used to send temperature readings to aws iot core and then recorded down in dynamodb. For exp32 the programming is done using arduino ide.

For the temperature portion you can use a dht-11 sensor to measure temperature.But for testing purposes, the temperature values were generated using random number generators.

For information on how to use esp32 to connect to the aws iot core, refer to https://exploreembedded.com/wiki/AWS_IOT_with_Arduino_ESP32.

As for the aws iot core setup and dynamodb setup, its simple.Under the aws iot dashboard remember to create a rule where data from iot core gets pushed to dynamodb.My partition key for the dynamodb is timestamp.

Libraries to install for esp32:
1)NTPClient(refer to:https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/.Dowmload the library and attach to libraries folder manually. Website shows how to use the library to output isoformat timestamps)
2)ArduinoJson(refer to:https://www.techcoil.com/blog/how-to-post-json-data-to-a-http-server-endpoint-from-your-esp32-development-board-with-arduinojson/)


I have added teh aws_sub.ino code to illustrate how to create a subscriber to subscribe to topic.And it is not involved in the dynamodb portion.
