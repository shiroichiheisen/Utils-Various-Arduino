# Utils Various Arduino

Library with various functions for the Arduino framework.

## ☕ Using this library

To use this library, you need to download, install the library, and include the following file in your project:

```
#include <utils_various.h>
```

In this library, you have:

[checkIfbetween - Check if a value is between two values](https://github.com/shiroichiheisen/Utils-Various-Arduino#checkIfbetween-function)

[debug - Debug function](https://github.com/shiroichiheisen/Utils-Various-Arduino#debug-function)

[dw - Digital Write](https://github.com/shiroichiheisen/Utils-Various-Arduino#dw-function)

[dr - Digital Read](https://github.com/shiroichiheisen/Utils-Various-Arduino#dr-function)

[aw - Analog Write](https://github.com/shiroichiheisen/Utils-Various-Arduino#aw-function)

[ar - Analog Read](https://github.com/shiroichiheisen/Utils-Various-Arduino#ar-function)

[ss - String Split](https://github.com/shiroichiheisen/Utils-Various-Arduino#ss-function)

[vs - String verifier with ss](https://github.com/shiroichiheisen/Utils-Various-Arduino#vs-function)

[ntc - ntc Reading](https://github.com/shiroichiheisen/Utils-Various-Arduino#ntc-function)

[RdividerCalc - Resistor divider mVoltage calculation](https://github.com/shiroichiheisen/Utils-Various-Arduino#rdividercalc-function)

---

## checkIfbetween function:

The checkIfbetween function is for checking if a value is between two values:

```
checkIfbetween(int value, int min, int max);
checkIfbetween(10, 0, 20); //will return true
checkIfbetween(10, 0, 5); //will return false
```

---

## debug function:

The debug function is for debbuging parts of your code and if you want to keep them for later use you can disable the debugs.

To use the debug function, you need to declare the following function in your project:

```
enableDebug(115200); 
//To enable the debug function just call the function with the baudrate of your serial monitor.
```

After declaring, you can send data so serial via the debug function:

```
debug("Hello World"); //To send data to the serial with string

debug(123); //To send data to the serial with integer

debug(123.456); //To send data to the serial with float
```

---

## dw function:

The dw function is a wrapper on the digitalWrite, but with better code readability, to use, declare the dw object with the pin:

```
dw led(int Ledpin, int initState);
```

if you dont want to inicialize the pin with a state, just dont write the initState on code -> dw led(int Ledpin);

initState = 1 -> pin will inicialize on high level

initState = 2 -> pin will inicialize on low level

After declaring, you can activate and deactivate the pin:

```
led.h(); //Activate the pin
led.high(); //Activate the pin
led.on(); //Activate the pin
led.open(); //Activate the pin

led.l(); //Deactivate the pin
led.low(); //Deactivate the pin
led.off(); //Deactivate the pin
led.close(); //Deactivate the pin
```

---

## dr function:

The dr function is a wrapper on the digitalRead, but with better code readability, to use just declare the dr object with the pin:

```
dr button(int buttonPin);
```

After declaring, you can read the state of the pin:

```
button.r();
button.read();
```

---

## aw function:

The aw function is a wrapper on the analogWrite, but with better code readability, to use, declare the aw object with the pin:

```
aw led(int pwmpin);
```

After declaring, you can use the pwm on the pin:

```
led.w(int value); //Write to pin
led.write(int value); //Write to pin
```

---

## ar function:

The ar function is a wrapper on the analogRead, but with better code readability.

To use declare the object with the:

potPin - Pin to read from - Mandatory

analog_resolution - analog resolution of the adc to convert the readings to milivolts or volts - Not Mandatory

mVoltage - Input volt on the device calculated on milivolts - Not Mandatory

mV_or_V - when reading do you want to get data on milivolts or volts - Not Mandatory

r1/r2 - for resistors dividers, the r1/r2 calculation -  Not Mandatory

Can be used to calculate the analogRead from the reading to miliVolts, just dont include the r1_r2 on the end of the declaration.


```

ar pot(int potPin); //to read the analog read
ar pot(int potPin, int analog_resolution, int mVoltage, int mV_or_V); //to read and calculate the miliVolts on the pin
ar pot(int potPin, int analog_resolution, int mVoltage, int mV_or_V, float r1_r2); //to read and calculate the voltage on the resistors dividers

```

After declaring, you can read the pin:

```
pot.r();
pot.read();
```

---

## ss function:

The ss function is a string split, to use, declare the object with the string to split:

```
ss stringSplit(String stringToCut);
```

After declaring, you can split the string:

```
stringSplit.get(char separator, int index);
```

The char separator is the char to split on the string, index is the part you want to get from the split of the string:


```
String stringToCut = "69/420";

ss stringSplit(String stringToCut);

stringSplit.get('/', 0); //will output the 69
stringSplit.get('/', 1); //will output the 420
```

If you want to get more inside of the split of the string you can use the rnw:

```
String stringToCut = "69/420:124/56";

ss stringSplit(String stringToCut);

stringSplit.rnw(':', 0); //will get the index 0 (69/420) and store for the get function

stringSplit.get('/', 0); //will output the 69
stringSplit.get('/', 1); //will output the 420
```

If you want to get more and more inside the string you can use the other rnw function:

```
String stringToCut = "69/420:124/56-187/1085:456/276";

ss stringSplit(String stringToCut);

stringSplit.rnw('-', 1,':',0); //will get the index 1 (187/1085:456/276 from the split of the char '-') and will get the index 0 (187/1085 from the split of the char ':') and store for the get function

stringSplit.get('/', 0); //will output the 187
stringSplit.get('/', 1); //will output the 1085
```

To change the string on the object just use the following function:

```
stringSplit.newData(String data);
```

---

## vs function:

I am using to verify if on the serial data received have the trailing and leading string to confirm that the data is complete.

To use declare the object with the:

Initial String - The first string to verify - Mandatory

Index Initial String - The index of the first string to verify - Default is 0

Char Separator - The char to split the string - Default is '|'

Verify Error - The string to send if the data is not complete - Default is ""

Final String - The final string to verify - Default is ''

Index Final String - The index of the final string to verify - Default is 2

```
vs verifySerialData(String initialString, int indexInitialString, char separator, String verifyError, String finalString, int indexFinalString);
```

To verify the data to see if it is complete and get the data without the trailing and leading string use the:

Input - The string to verify - Mandatory

Result - The string without the trailing and leading string if it is complete, otherwise it will return blank "" - Its an pointer to the string to change - Mandatory

ResultIndex - The index of the data without the trailing and leading string - Default is 1

```
verifySerialData.verify(String input, String &result, int resultIndex);
```

If you want to get the data without the result string being on a pointer and returning as string use the:

Input - The string to verify - Mandatory

ResultIndex - The index of the data without the trailing and leading string - Default is 1

```
verifySerialData.verify(String input, int resultIndex);
```

Example:


```
String received;

vs verifySerialData("test", 0, "/", "Error", "test0", 2); //Declare the object

verifySerialData.verify("test/dataReceived/test0", received, 1); 
//Will set the string received to "dataReceived"

verifySerialData.verify("test123/dataReceived/test0", received, 1); 
//Will set the string received to "Error" because the data is not complete 
(the initial string is not equal to the initial string set on the object verifySerialData (test123 != test))

received = verifySerialData.verify("test/dataReceived/test0", 1);
//Will set the string received to "dataReceived"
```
---

## ntc function:

Read an NTC with the following connection:

GND---NTC---PIN---RESISTOR---VCC

Declare the NTC object with the pin to read, VCC voltage on the resistor, analog read resolution, the NTC kelvin, and NTC resistance at 25° celsius:

The resistor value is in Ohms.
Vcc is in Volts.
Resistance on 25ºC is in Ohms.

```
ntc tempSensor(int sensorPin, float vcc, int resistorValue, int analog_resolution, int kelvin, int resistance_25c)
```

After declared, read the NTC with the celsius, fahrenheit or Kelvin temperature preference:

"c" for celsius

"f" for fahrenheit

"k" for kelvin

```
tempSensor.r(String temperatureSelection);
tempSensor.read(String temperatureSelection);
```

---

## RdividerCalc function:

The RdividerCalc function is a resistor divider voltage calculator.

To use declare the object with the:

potPin - Pin to read from - Mandatory

analog_resolution - analog resolution of the adc to convert the readings to milivolts or volts - Mandatory

mVoltage - Input volt on the device calculated on milivolts - Mandatory

r1/r2 - resistor divider, the r1/r2 calculation - Mandatory


```
ar pot(int potPin, int analog_resolution, int mVoltage, float r1_r2);

```

After declaring, you can read the pin:

```
pot.r();
pot.read();
```

---
