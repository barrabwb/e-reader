## Description
Components used:
- ESP8266
- Adafruit OLED 128x32
- 2 push buttons

Displays any text within 3 lines of the OLED, and uses 2 push buttons to "scroll down" or "scroll up"
In the repository there's a few more files. One file is to locate the physical address of your OLED (the I2C device), the other is to test that your pull-up resistor in the ESP8266 works (so that you can register a button push), and the other file is to display a "Hello World" text on your OLED.
