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
void dw::high()
{
  digitalWrite(pino, HIGH);
}
void dw::open()
{
  digitalWrite(pino, HIGH);
}
void dw::on()
{
  digitalWrite(pino, HIGH);
}
void dw::l()
{
  digitalWrite(pino, LOW);
}
void dw::low()
{
  digitalWrite(pino, LOW);
}
void dw::close()
{
  digitalWrite(pino, LOW);
}
void dw::off()
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
  leitura = digitalRead(pino);
  return leitura;
}

int dr::read()
{
  leitura = digitalRead(pino);
  return leitura;
}

ar::ar(int pin)
{
  pinMode(pin, INPUT);
  pino = pin;
}

int ar::r()
{
  leitura = analogRead(pino);
  return leitura;
}

int ar::read()
{
  leitura = analogRead(pino);
  return leitura;
}

pwm::pwm(int pin, int frequency, int adc_resolution, int channel, int porcentageORdutyCycle)
{
  pow_res = pow(2, adc_resolution);
  pOp = porcentageORdutyCycle;
  ch = channel;
  ledcSetup(channel, frequency, adc_resolution);
  ledcAttachPin(pin, channel);
}

void pwm::w(int valor)
{
  if (pOp)
    dutyCycle = map(valor, 0, 100, 0, pow_res);
  else
    dutyCycle = map(valor, 0, pow_res, 0, pow_res);
  ledcWrite(ch, dutyCycle);
}

void pwm::write(int valor)
{
  if (pOp)
    dutyCycle = map(valor, 0, 100, 0, pow_res);
  else
    dutyCycle = map(valor, 0, pow_res, 0, pow_res);
  ledcWrite(ch, dutyCycle);
}

ss::ss(String data)
{
  data_received = data;
}

void ss::new_data(String data)
{
  data_received = data;
}

void ss::rnw(char separator, int index)
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

float ntc::read(String reading)
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
ntc_cal::ntc_cal(int pin, float vcc, int resistor, int analog_resolution, int kelvin, int resistance_25c)
{
  // p = pin;
  v = vcc;
  r1 = resistor;
  ar = analog_resolution;
  k = kelvin;
  r25c = resistance_25c;
  NTCreading.attach(pin);
}

float ntc_cal::r(String reading)
{
  float RT, VR, ln, TX, T0, VRT;
  int choose = 0;
  T0 = 25 + 273.15;

  VRT = NTCreading.readRaw();
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
float ntc_cal::read(String reading)
{
  float RT, VR, ln, TX, T0, VRT;
  int choose = 0;
  T0 = 25 + 273.15;

  VRT = NTCreading.readRaw();
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

void enableDebug(int velocity)
{
  if (velocity)
  {
    debugenabled = 1;
    Serial.begin(velocity);
  }
  else
  {
    debugenabled = 0;
    Serial.end();
  }
}

void debug(String message)
{
  if (!debugenabled)
    return;
  Serial.println(message);
}

void debug(int integer)
{
  if (!debugenabled)
    return;
  Serial.println(integer);
}

void debug(float Float)
{
  if (!debugenabled)
    return;
  Serial.println(Float);
}