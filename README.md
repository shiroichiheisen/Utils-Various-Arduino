# Utils Various Arduino

Library with various functions for the Arduino framework.

## ☕ Using this library

To use this library, you need to download, install the library, and include the following file in your project:

```
#include <utils_various.h>
```

In this library, you have:

[dw - Digital Write](https://github.com/shiroichiheisen/Utils-Various-Arduino#dw-function)

[dr - Digital Read](https://github.com/shiroichiheisen/Utils-Various-Arduino#dr-function)

[ar - Analog Read](https://github.com/shiroichiheisen/Utils-Various-Arduino#ar-function)

[pwm - Control the PWM on Esp32](https://github.com/shiroichiheisen/Utils-Various-Arduino#pwm-function)

[ss - String Split](https://github.com/shiroichiheisen/Utils-Various-Arduino#ss-function)

[ntc - ntc Reading](https://github.com/shiroichiheisen/Utils-Various-Arduino#ntc-function)

[ntc_cal - ntc Reading Calibrated on the ESP32](https://github.com/shiroichiheisen/Utils-Various-Arduino#ntc_cal-function) 

---

## dw function:

The dw function is a wrapper on the digitalWrite, but with better code readability, to use, declare the dw object with the pin:

```
dw led(int Ledpin);
```

After declaring, you can activate and deactivate the pin:

```
led.h(); //Activate the pin

led.l(); //Deactivate the pin
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
```

---

## ar function:

The ar function is a wrapper on the analogRead, but with better code readability, to use, declare the ar object with the pin:

```
ar pot(int potPin);
```

After declaring, you can read the pin:

```
pot.r();
```

---

## pwm function:

The PWM function is a wrapper on the ledc PWM from the ESP32, this part only works with the ESP32, but with better code readability, to use declare the object with the pin, frequency of the PWM, resolution of the PWM, PWM channel and if you will use percentage or duty cycle:

```
pwm mosfet(int mosfetPin, int pwmFrequency, int pwmResolution, int pwmChannel, int porcentageORdutyCycle);
```

To change the PWM on the pin just call the object with the value you want to write:

```
mosfet.w(int pwmValue);
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

---

## ntc function:

Read an NTC with the following connection:

GND---NTC---PIN---RESISTOR---VCC

Declare the NTC object with the pin to read, VCC voltage on the resistor, analog read resolution, the NTC kelvin, and NTC resistance at 25° celsius:

```
ntc tempSensor(int sensorPin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c)
```

After declared, read the NTC with the celsius, fahrenheit or Kelvin temperature preference:

"c" for celsius

"f" for fahrenheit

"k" for kelvin

```
tempSensor.r(String temperatureSelection);
```

---

## ntc_cal function:

Read an NTC with the [Analog Read library](https://github.com/madhephaestus/ESP32AnalogRead) with the following connection:

GND---NTC---PIN---RESISTOR---VCC

Declare the NTC object with the pin to read, VCC voltage on the resistor, analog read resolution, the NTC kelvin and NTC resistance at 25° celsius:

```
ntc_cal tempSensor(int sensorPin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c)
```

After declared, read the NTC with the celsius, fahrenheit or Kelvin temperature preference:

"c" for celsius

"f" for fahrenheit

"k" for kelvin

```
tempSensor.r(String temperatureSelection);
```
