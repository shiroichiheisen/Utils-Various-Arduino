#include "utils_various.h"

dw::dw(int pin)
{
  pinMode(pin, OUTPUT);
  pino = pin;
}

void dw::h()
{
  digitalWrite(pino, HIGH);
}

void dw::l()
{
  digitalWrite(pino, LOW);
}

dr::dr(int pin)
{
  pinMode(pin, INPUT);
  pino = pin;
}

int dr::r()
{
  return digitalRead(pino);
}

ar::ar(int pin, int analog_resolution, int mVoltage, int mV_or_V, float r1_r2)
{
  pinMode(pin, INPUT);
  pino = pin;
  resolution = analog_resolution;
  mVolt = mVoltage;
  resistor_r1_r2 = r1_r2;
  if (mV_or_V > 0)
    mvouv = 1000;
  else
    mvouv = 1;
}

float ar::r()
{
  if (resolution)
    if (resistor_r1_r2)
      reading = (map(analogRead(pino), 0, pow(2, resolution), 0, mVolt) * (resistor_r1_r2 + 1));
    else
      reading = map(analogRead(pino), 0, pow(2, resolution), 0, mVolt);
  else
    reading = analogRead(pino);

  reading /= mvouv;
  return reading;
}

ss::ss(String data)
{
  data_received = data;
}

void ss::new_data(String data)
{
  data_received = data;
}

void ss::rnw(char separator, int index, char separator2, int index2)
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
  if (index2 == 0)
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

String ss::get(char separator, int index)
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
       int indexInitialString,
       char charSeparator,
       String verifyError,
       String finalString,
       int indexFinalString)
{
  initial = initialString;
  final = finalString;
  separator = charSeparator;
  verError = verifyError;
  initialI = indexInitialString;
  finalI = indexFinalString;
}

void vs::verify(String input, String &result, int resultIndex)
{
  ss data_split(input);
  if (data_split.get(separator, initialI).equals(initial) && data_split.get(separator, finalI).equals(final))
    result = data_split.get(separator, resultIndex);
  else
    result = verError;
}

String vs::verify(String input, int resultIndex)
{
  ss data_split(input);
  if (data_split.get(separator, initialI).equals(initial) && data_split.get(separator, finalI).equals(final))
    return data_split.get(separator, resultIndex);
  else
    return verError;
}

ntc::ntc(int pin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c)
{
  p = pin;
  v = vcc;
  r1 = resistor;
  ar = analog_resolution;
  k = kelvin;
  r25c = resistance_25c;
}

float ntc::r(String reading)
{
  float RT, VR, ln, TX, T0, VRT;
  int choose = 0;
  T0 = 25 + 273.15;

  VRT = analogRead(p);
  VRT = (v / (pow(2, ar) - 1)) * VRT;
  VR = v - VRT;
  RT = VRT / (VR / r1);

  ln = log(RT / r25c);
  TX = (1 / ((ln / k) + (1 / T0)));

  TX = TX - 273.15;

  if (reading == "c")
    choose = TX;
  if (reading == "f")
    choose = ((TX * 1.8) + 32);
  if (reading == "k")
    choose = TX + 273.15;

  return choose;
}
