#ifndef utils_various
#define utils_various

#include <Arduino.h>
#include <ESP32AnalogRead.h>
// Class for making an digitalwrite
class dw
{
public:
	dw(int pin);
	void h();
	void l();

private:
	int pino;
};

// Class for making an digitalread
class dr
{
public:
	dr(int pin);
	int r();

private:
	int pino;
	int leitura;
};

// Class for making an analogread
class ar
{
public:
	ar(int pin);
	int r();

private:
	int pino;
	int leitura;
};

// Class for making an pwm write
class pwm
{
public:
	pwm(int pin, int frequency, int adc_resolution, int channel, int porcentageORdutyCycle);
	void w(int valor);

private:
	int ch, pOp, dutyCycle, pow_res;
};

// Class for making an string split
class ss
{
public:
	ss(String data);
	void new_data(String data);
	void rnw(char separator, int index);
	void rnw(char separator, int index, char separator2, int index2);
	String get(char separator, int index);

private:
	String data_received, data_reformed;
};

// Class to verify an string with the string split
class vs
{
public:
	vs(String initialString, int indexInitialString = 0, char charSeparator = '|', String finalString = "", int indexFinalString = 2);
	void verify(String input, String &result, int resultIndex = 1);

private:
	String initial, final;
	char separator;
	int initialI, finalI;
}

// NTC sensor class - VCC-Resistor-PIN-NTC-GND
class ntc
{
public:
	ntc(int pin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c);
	float r(String reading);

private:
	float p, v, r1, ar, k, r25c;
};

// NTC sensor class using AnalogRead library
class ntc_cal
{
public:
	ntc_cal(int pin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c);
	float r(String reading);

private:
	float p, v, r1, ar, k, r25c;
	ESP32AnalogRead NTCreading;
};
#endif
