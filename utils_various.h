#ifndef utils_various
#define utils_various

#include <Arduino.h>

#define enabledebug(velocity) Serial.begin(velocity)
#define debug(message) Serial.println(message)

// Class for making an digitalwrite
class dw
{
public:
	dw(int pin);
	// Send a digitalWrite(PIN,HIGH);
	void high() { h(); };
	// Send a digitalWrite(PIN,HIGH);
	void open() { h(); };
	// Send a digitalWrite(PIN,HIGH);
	void on() { h(); };
	// Send a digitalWrite(PIN,HIGH);
	void h();
	// Send a digitalWrite(PIN,LOW);
	void low() { l(); };
	// Send a digitalWrite(PIN,LOW);
	void close() { l(); };
	// Send a digitalWrite(PIN,LOW);
	void off() { l(); };
	// Send a digitalWrite(PIN,LOW);
	void l();

private:
	int pino;
};

// Class for making an digitalread
class dr
{
public:
	dr(int pin);
	// Make a DigitalRead(PIN);
	int read() { return r(); };
	// Make a DigitalRead(PIN);
	int r();

private:
	int pino;
	int leitura;
};

// Class for making an analogread
class ar
{
public:
	ar(int pin, int analog_resolution = 0, int mVoltage = 0, int mV_or_V = 0, float r1_r2 = 0);
	// Make a AnalogRead(PIN);
	float read() { return r(); };
	// Make a AnalogRead(PIN);
	float r();

private:
	int pino, resolution, mVolt, mvouv;
	float reading, resistor_r1_r2;
};

// Class for making an string split
class ss
{
public:
	ss(String data = "");
	void new_data(String data);
	void rnw(char separator, int index, char separator2 = '/', int index2 = 0);
	String get(char separator, int index);

private:
	String data_received, data_reformed;
};

// Class to verify an string with the string split
class vs
{
public:
	vs(String initialString, int indexInitialString = 0, char charSeparator = '|', String verifyError = "", String finalString = "", int indexFinalString = 2);
	void verify(String input, String &result, int resultIndex = 1);
	String verify(String input, int resultIndex = 1);

private:
	String initial, final, verError;
	char separator;
	int initialI, finalI;
};

// NTC sensor class - VCC-Resistor-PIN-NTC-GND
class ntc
{
public:
	ntc(int pin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c);
	// Read the NTC();
	float read(String reading) { return r(reading); };
	// Read the NTC();
	float r(String reading);

private:
	float p, v, r1, ar, k, r25c;
};

#endif
