#ifndef utils_various
#define utils_various

#include <Arduino.h>

/**
 * @brief  Check if number is between min and max
 *
 * @param value The value to check
 * @param min The minimum value
 * @param max The maximum value
 *
 * @return
 * - True if the value is between min and max
 * - False if the value is not between min and max
 */
#define checkIfbetween(value, min, max) ((value >= min) && (value <= max))

/**
 * @brief  Serial.begin Wrapper
 *
 * Just a Wrapper on the Serial.begin function.
 *
 * @param velocity the velocity of the serial port
 */
#define enabledebug(velocity) Serial.begin(velocity)
#define enableserial(velocity) Serial.begin(velocity)

/**
 * @brief  Serial.println Wrapper
 *
 * Just a Wrapper on the Serial.println function.
 *
 * @param message the message to print
 */
#define debug(message) Serial.println(message)
#define debugM(message, mode) Serial.println(message, mode)
#define serial(message) Serial.println(message)

/**
 * @brief  Digital Write Wrapper
 *
 * Just a Wrapper on the digitalWrite function.
 *
 * @param pin the pin to write
 * @param initState the initial state of the pin (1 for HIGH, 2 for LOW) - not required
 */
class dw
{
public:
	dw(uint8_t pin, uint8_t initState);
	dw(uint8_t pin);
	/**
	 * @brief Turn the pin on.
	 */
	void high() { h(); };
	/**
	 * @brief Turn the pin on.
	 */
	void open() { h(); };
	/**
	 * @brief Turn the pin on.
	 */
	void on() { h(); };
	/**
	 * @brief Turn the pin on.
	 */
	void h();
	/**
	 * @brief Turn the pin off.
	 */
	void low() { l(); };
	/**
	 * @brief Turn the pin off.
	 */
	void close() { l(); };
	/**
	 * @brief Turn the pin off.
	 */
	void off() { l(); };
	/**
	 * @brief Turn the pin off.
	 */
	void l();

private:
	uint8_t pino;
};

/**
 * @brief  Digital Read Wrapper
 *
 * Just a Wrapper on the digitalRead function.
 *
 * @param pin the pin to read
 */
class dr
{
public:
	dr(uint8_t pin);
	/**
	 * @brief  Read and return the pin state.
	 *
	 * @return
	 *   - The pin state.
	 */
	bool operator()() { return r(); }
	/**
	 * @brief  Read and return the pin state.
	 *
	 * @return
	 *   - The pin state.
	 */
	bool read() { return r(); };
	/**
	 * @brief  Read and return the pin state.
	 *
	 * @return
	 *   - The pin state.
	 */
	bool r();

private:
	uint8_t pino;
};

/**
 * @brief  Analog Read Wrapper
 *
 * Just a Wrapper on the analogRead function with resistor divider calculator.
 *
 * @param pin The pin to read
 * @param analog_resolution The analog resolution of the adc - not required
 * @param mVoltage The vcc of the adc or microcontroler being used - not required
 * @param r1_r2 The calculation of r1/r2 - not required
 *
 * @return
 *   - The analog read of the pin or resistor divider calculation.
 */
class ar
{
public:
	ar(uint8_t pin);
	/**
	 * @brief  Read and return the analog read of the pin
	 *
	 * @return
	 *   - The analog read of the pin
	 */
	uint32_t operator()() { return r(); }
	/**
	 * @brief  Read and return the analog read of the pin
	 *
	 * @return
	 *   - The analog read of the pin
	 */
	uint32_t read() { return r(); };
	/**
	 * @brief  Read and return the analog read of the pin
	 *
	 * @return
	 *   - The analog read of the pin
	 */
	uint32_t r();

private:
	uint8_t pino;
};

/**
 * @brief  Analog Read Wrapper resistor divider calculator.
 *
 * Just a Wrapper on the analogRead function with resistor divider calculator.
 *
 * @param pin The pin to read
 * @param analog_resolution The analog resolution of the adc
 * @param mVoltage The vcc of the adc or microcontroler being used
 * @param r1_r2 The calculation of r1/r2
 *
 * @return
 *   - The resistor divider calculation.
 */
class ar_calc
{
public:
	ar_calc(uint8_t pin, uint8_t analog_resolution, uint16_t mVoltage, float r1_r2);
	/**
	 * @brief  Read and return the resistor divider calculation.
	 *
	 * @return
	 *   - The resistor divider calculation.
	 */
	float r_calc();

private:
	uint8_t pino, resolution;
	uint16_t mVolt, reading;
	float resistor_r1_r2;
};

/**
 * @brief  Analog Write Wrapper
 *
 * Just a Wrapper on the analogWrite function.
 *
 * @param pin The pin to write
 *
 */
class aw
{
public:
	aw(uint8_t pin);
	/**
	 * @brief  Write the value on pin using the analogWrite(pin,value);.
	 *
	 */
	void write(uint16_t value) { return w(value); };
	/**
	 * @brief  Write the value on pin using the analogWrite(pin,value);.
	 *
	 */
	void w(uint16_t value);

private:
	uint8_t pino;
};

/**
 * @brief  Split the String function
 *
 * You can split the string and return the index of the string splitted.
 *
 * @param String The string to split - not required on inicialization
 *
 * @return
 *   - The string splitted.
 */
class ss
{
public:
	ss(String data = "", uint16_t size = 0);
	/**
	 * @brief  Set new string to split.
	 *
	 * @param String The new string to split
	 *
	 */
	void newData(String data);
	/**
	 * @brief  Cut the string and get the index selected and use that index for next splits.
	 *
	 * @param separator The separator to split the string
	 * @param index The index of the string splitted
	 * @param separator2 The second separator to split the string if you want to use this function 2 times - not required
	 * @param index2 The index of the result from the first string splitted with the separator2 (default -> 0) - not required
	 *
	 */
	void rnw(char separator, uint8_t index, char separator2, int8_t index2 = -1);
	/**
	 * @brief  Get the result from selected index splitting the string with the separator.
	 *
	 * @param separator The separator to split the string
	 * @param index The index of the string splitted
	 *
	 * @return
	 *   - The result of the index of the string splitted.
	 */
	String get(char separator, uint8_t index);

private:
	String data_received, data_reformed;
};

/**
 * @brief  Split the String and verify if the string have 2 other strings to verify if comunication is correct
 *
 * You can use this function to verify if the string has reached correct to your code ("VerificationString|data|VerificationString2").
 * If you dont Want to verify the second string, just put "" on the finalString parameter.
 *
 * @param initialString The first string to verify if the string is correct
 * @param indexInitialString The index of the first string when separating with the charSeparator (default -> 0)
 * @param charSeparator The separator to split the string (default -> '|')
 * @param verifyError The string to return if the string dont have the 2 strings to verify (default -> "")
 * @param finalString The second string to verify if the string is correct (default -> "")
 * @param indexFinalString The index of the second string when separating with the charSeparator (default -> 2)
 *
 * @return
 *   - The data from the string if the string is correct or the verifyError string if the string is not correct.
 */
class vs
{
public:
	vs(String initialString, uint8_t indexInitialString = 0, char charSeparator = '|', String verifyError = "", String finalString = "", uint8_t indexFinalString = 2);
	/**
	 * @brief  Input the string to verify if the string is correct and return the data from the string if the string is correct or the verifyError string if the string is not correct.
	 *
	 * @param input The string to verify if the string is correct
	 * @param result The string to return if the string is correct (using reference)
	 * @param resultIndex The index of the string splitted to return if the string is correct (default -> 1)
	 */
	void verify(String input, String &result, uint8_t resultIndex = 1);
	/**
	 * @brief  Input the string to verify if the string is correct and return the data from the string if the string is correct or the verifyError string if the string is not correct.
	 *
	 * @param input The string to verify if the string is correct
	 * @param resultIndex The index of the string splitted to return if the string is correct (default -> 1)
	 *
	 * @return
	 *   - The string if the string is correct.
	 */
	String verify(String input, uint8_t resultIndex = 1);

private:
	String initial, final, verError;
	char separator;
	uint8_t initialI, finalI;
};

/**
 * @brief  NTC temperature calculator - VCC-Resistor-PIN-NTC-GND
 *
 * You can use this function to calculate the temperature of the NTC.
 *
 * @param pin The pin of the NTC
 * @param vcc The voltage of the VCC
 * @param resistor The resistor value
 * @param analog_resolution The analog resolution of the adc
 * @param kelvin The kelvin of the NTC
 * @param resistance_25c The resistance of the NTC at 25ºC
 *
 * @return
 *  - The temperature of the NTC.
 */
class ntc
{
public:
	ntc(uint8_t pin, float vcc, uint32_t resistor, uint8_t analog_resolution, uint16_t kelvin, uint32_t resistance_25c);
	/**
	 *  @brief  Read the NTC and return the temperature of the NTC.
	 *
	 * @param reading If you want to read on the Celcius scale, put "C", if you want to read on the Fahrenheit scale, put "F" or if you want to read on the Kelvin scale, put "K" (default -> "C")
	 *
	 * @return
	 * - The temperature of the NTC.
	 */
	int16_t read(String reading = "C") { return r(reading); };
	/**
	 *  @brief  Read the NTC and return the temperature of the NTC.
	 *
	 * @param reading If you want to read on the Celcius scale, put "C", if you want to read on the Fahrenheit scale, put "F" or if you want to read on the Kelvin scale, put "K" (default -> "C")
	 *
	 * @return
	 * - The temperature of the NTC.
	 */
	int16_t r(String reading = "C");

private:
	uint8_t p, ar;
	uint16_t k;
	uint32_t r1, r25c;
	float v;
};

/**
 * @brief   Resistor divider voltage calculation class - Vin-Resistor-PIN-Resistor-GND
 *
 * You can use this function to calculate the voltage of the resistor divider.
 *
 * @param analog_resolution The analog resolution of the adc
 * @param mVoltage The vcc of the adc or microcontroler being used
 * @param r1_r2 The value of the division of the resistors (r1/r2)
 *
 * @return
 * - The voltage on the Vin of the resistor divider on miliVolts.
 */
class RdividerCalc
{
public:
	RdividerCalc(uint8_t analog_resolution, uint16_t mVoltage, float r1_r2);
	/**
	 * @brief  Read the resistor divider and return the voltage on the Vin of the resistor divider on miliVolts.
	 *
	 * @param reading The reading of the adc realized on the PIN of the resistor divider
	 *
	 * @return
	 * - The voltage on the Vin of the resistor divider on miliVolts.
	 */
	float read(uint16_t reading) { return r(reading); };
	/**
	 * @brief  Read the resistor divider and return the voltage on the Vin of the resistor divider on miliVolts.
	 *
	 * @param reading The reading of the adc realized on the PIN of the resistor divider
	 *
	 * @return
	 * - The voltage on the Vin of the resistor divider on miliVolts.
	 */
	float r(uint16_t reading);

private:
	uint8_t resolution;
	uint16_t mVolt;
	float resistor_r1_r2;
};
#endif
