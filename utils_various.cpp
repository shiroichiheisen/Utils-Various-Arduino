#include "utils_various.h"

aw::aw(uint8_t pin)
{
  pinMode(pin, OUTPUT);
  pino = pin;
}

void aw::w(uint16_t value)
{
  analogWrite(pino, value);
}

dw::dw(uint8_t pin, uint8_t initState)
{
  pinMode(pin, OUTPUT);
  pino = pin;
  switch (initState)
  {
  case 1:
    h();
    break;
  case 2:
    l();
    break;
  }
}

void dw::h()
{
  digitalWrite(pino, HIGH);
}

void dw::l()
{
  digitalWrite(pino, LOW);
}

dr::dr(uint8_t pin)
{
  pinMode(pin, INPUT);
  pino = pin;
}

bool dr::r()
{
  return digitalRead(pino);
}

ar::ar(uint8_t pin, uint8_t analog_resolution, uint16_t mVoltage, float r1_r2)
{
  pinMode(pin, INPUT);
  pino = pin;
  resolution = analog_resolution;
  mVolt = mVoltage;
  resistor_r1_r2 = r1_r2;
}

float ar::r()
{
  if (resolution)
  {
    if (resistor_r1_r2)
      reading = (map(analogRead(pino), 0, pow(2, resolution), 0, mVolt) * (resistor_r1_r2 + 1));
    else
      reading = map(analogRead(pino), 0, pow(2, resolution), 0, mVolt);
  }
  else
    reading = analogRead(pino);
  return reading;
}

ss::ss(String data)
{
  data_received = data;
}

void ss::newData(String data)
{
  data_received = data;
}

void ss::rnw(char separator, uint8_t index, char separator2, int8_t index2)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data_received.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data_received.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  data_received = found > index ? data_received.substring(strIndex[0], strIndex[1]) : "";
  if (index2 < 0)
    return;
  else
  {
    int found2 = 0;
    int strIndex2[] = {0, -1};
    int maxIndex2 = data_received.length() - 1;

    for (int i2 = 0; i2 <= maxIndex2 && found2 <= index2; i2++)
    {
      if (data_received.charAt(i2) == separator2 || i2 == maxIndex2)
      {
        found2++;
        strIndex2[0] = strIndex2[1] + 1;
        strIndex2[1] = (i2 == maxIndex2) ? i2 + 1 : i2;
      }
    }
    data_received = found2 > index2 ? data_received.substring(strIndex2[0], strIndex2[1]) : "";
  }
}

String ss::get(char separator, uint8_t index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data_received.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data_received.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data_received.substring(strIndex[0], strIndex[1]) : "";
}

vs::vs(String initialString,
       uint8_t indexInitialString,
       char charSeparator,
       String verifyError,
       String finalString,
       uint8_t indexFinalString)
{
  initial = initialString;
  final = finalString;
  separator = charSeparator;
  verError = verifyError;
  initialI = indexInitialString;
  finalI = indexFinalString;
}

void vs::verify(String input, String &result, uint8_t resultIndex)
{
  ss data_split(input);
  if (data_split.get(separator, initialI).equals(initial) && data_split.get(separator, finalI).equals(final))
    result = data_split.get(separator, resultIndex);
  else
    result = verError;
}

String vs::verify(String input, uint8_t resultIndex)
{
  ss data_split(input);
  if (data_split.get(separator, initialI).equals(initial) && data_split.get(separator, finalI).equals(final))
    return data_split.get(separator, resultIndex);
  else
    return verError;
}

ntc::ntc(uint8_t pin, float vcc, uint32_t resistor, uint8_t analog_resolution, uint16_t kelvin, uint32_t resistance_25c)
{
  p = pin;
  v = vcc;
  r1 = resistor;
  ar = analog_resolution;
  k = kelvin;
  r25c = resistance_25c;
}

int16_t ntc::r(String reading)
{
  float RT, VR, ln, TX, T0, VRT;
  uint16_t choose = 0;
  T0 = 25 + 273.15;

  VRT = analogRead(p);
  VRT = (v / (pow(2, ar) - 1)) * VRT;
  VR = v - VRT;
  RT = VRT / (VR / r1);

  ln = log(RT / r25c);
  TX = (1 / ((ln / k) + (1 / T0)));

  TX = TX - 273.15;

  if (reading == "C")
    choose = TX;
  if (reading == "F")
    choose = ((TX * 1.8) + 32);
  if (reading == "K")
    choose = TX + 273.15;

  return choose;
}

RdividerCalc::RdividerCalc(uint8_t analog_resolution, uint16_t mVoltage, float r1_r2)
{
  resolution = pow(2, analog_resolution);
  mVolt = mVoltage;
  resistor_r1_r2 = r1_r2 + 1;
}

float RdividerCalc::r(uint16_t reading)
{
  float read = map(reading, 0, resolution, 0, mVolt);
  read = (read * resistor_r1_r2);
  return read;
}