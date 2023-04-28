
/* Virtual PINS */
#define V_MOP V2
#define V_PUMP V3
#define V_VACCUM V4
#define V_FWD V5
#define V_RIGHT V6
#define V_BACK V7
#define V_LEFT V8

/* Hardware PINS */

#define MOP_RELAY 19
#define PUMP_RELAY 18
#define VACCUM_RELAY 5

// Motor pins - L293D Motor Driver
#define MOTOR_FR0 17
#define MOTOR_FR1 16
#define MOTOR_BR0 4
#define MOTOR_BR1 0
#define MOTOR_FL0 2
#define MOTOR_FL1 15
#define MOTOR_BL0 13
#define MOTOR_BL1 12

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3RLsnDUSl"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "ODkOOyVAV1Mt0X3qJWm6XxvjGFfBVky9"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Flamingo";
char pass[] = "123456789";

void initVirtualPins(int v_pin, int h_pin, boolean inverted)
{
  if (digitalRead(h_pin) == (inverted ? 0 : 1))
  {
    Blynk.virtualWrite(v_pin, digitalRead(h_pin));
  }
  else
    Blynk.syncVirtual(v_pin);
}

void initVirtualPins(int v_pin, int h_pin)
{
  initVirtualPins(v_pin, h_pin, true);
}

void go_forward()
{

  digitalWrite(MOTOR_FR0, HIGH);
  digitalWrite(MOTOR_FR1, 0);
  digitalWrite(MOTOR_BR0, HIGH);
  digitalWrite(MOTOR_BR1, 0);
  digitalWrite(MOTOR_FL0, HIGH);
  digitalWrite(MOTOR_FL1, 0);
  digitalWrite(MOTOR_BL0, HIGH);
  digitalWrite(MOTOR_BL1, 0);
}

void go_right()
{

  digitalWrite(MOTOR_FR0, 0);
  digitalWrite(MOTOR_FR1, HIGH);
  digitalWrite(MOTOR_BR0, 0);
  digitalWrite(MOTOR_BR1, HIGH);
  digitalWrite(MOTOR_FL0, HIGH);
  digitalWrite(MOTOR_FL1, 0);
  digitalWrite(MOTOR_BL0, HIGH);
  digitalWrite(MOTOR_BL1, 0);
}

void go_back()
{

  digitalWrite(MOTOR_FR0, 0);
  digitalWrite(MOTOR_FR1, HIGH);
  digitalWrite(MOTOR_BR0, 0);
  digitalWrite(MOTOR_BR1, HIGH);
  digitalWrite(MOTOR_FL0, 0);
  digitalWrite(MOTOR_FL1, HIGH);
  digitalWrite(MOTOR_BL0, 0);
  digitalWrite(MOTOR_BL1, HIGH);
}

void go_left()
{

  digitalWrite(MOTOR_FR0, HIGH);
  digitalWrite(MOTOR_FR1, 0);
  digitalWrite(MOTOR_BR0, HIGH);
  digitalWrite(MOTOR_BR1, 0);
  digitalWrite(MOTOR_FL0, 0);
  digitalWrite(MOTOR_FL1, HIGH);
  digitalWrite(MOTOR_BL0, 0);
  digitalWrite(MOTOR_BL1, HIGH);
}

void go_stop()
{
  digitalWrite(MOTOR_FR0, 0);
  digitalWrite(MOTOR_FR1, 0);
  digitalWrite(MOTOR_BR0, 0);
  digitalWrite(MOTOR_BR1, 0);
  digitalWrite(MOTOR_FL0, 0);
  digitalWrite(MOTOR_FL1, 0);
  digitalWrite(MOTOR_BL0, 0);
  digitalWrite(MOTOR_BL1, 0);
}

BLYNK_CONNECTED()
{
  // if your relay is HIGH triggering
  // if (digitalRead(2) == 1)
  //   Blynk.virtualWrite(V2, digitalRead(2));
  // else
  //   Blynk.syncVirtual(V2);

  /* uncomment this section if your relay is LOW triggering
   * if (digitalRead(2) == 0) Blynk.virtualWrite(V2, digitalRead(2));
    else Blynk.syncVirtual(V2);
   */

  initVirtualPins(V_MOP, MOP_RELAY);
  initVirtualPins(V_PUMP, PUMP_RELAY);
  initVirtualPins(V_VACCUM, VACCUM_RELAY);

  Blynk.syncVirtual(V_FWD);
  Blynk.syncVirtual(V_RIGHT);
  Blynk.syncVirtual(V_BACK);
  Blynk.syncVirtual(V_LEFT);
}

BLYNK_WRITE(V_MOP)
{
  int pinData = param.asInt();
  digitalWrite(MOP_RELAY, pinData);
}

BLYNK_WRITE(V_PUMP)
{
  int pinData = param.asInt();
  digitalWrite(PUMP_RELAY, pinData);
}

BLYNK_WRITE(V_VACCUM)
{
  int pinData = param.asInt();
  digitalWrite(VACCUM_RELAY, pinData);
}

BLYNK_WRITE(V_FWD)
{
  int pinData = param.asInt();
  if (pinData == 1)
  {
    go_forward();
  }
  else
  {
    go_stop();
  }
}

BLYNK_WRITE(V_RIGHT)
{
  int pinData = param.asInt();
  if (pinData == 1)
  {
    go_right();
  }
  else
  {
    go_stop();
  }
}

BLYNK_WRITE(V_BACK)
{
  int pinData = param.asInt();
  if (pinData == 1)
  {
    go_back();
  }
  else
  {
    go_stop();
  }
}

BLYNK_WRITE(V_LEFT)
{
  int pinData = param.asInt();
  if (pinData == 1)
  {
    go_left();
  }
  else
  {
    go_stop();
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(MOP_RELAY, OUTPUT);
  pinMode(PUMP_RELAY, OUTPUT);
  pinMode(VACCUM_RELAY, OUTPUT);

  pinMode(MOTOR_FR0, OUTPUT);
  pinMode(MOTOR_FR1, OUTPUT);
  pinMode(MOTOR_BR0, OUTPUT);
  pinMode(MOTOR_BR1, OUTPUT);
  pinMode(MOTOR_FL0, OUTPUT);
  pinMode(MOTOR_FL1, OUTPUT);
  pinMode(MOTOR_BL0, OUTPUT);
  pinMode(MOTOR_BL1, OUTPUT);

  // digitalWrite(2, LOW); // if your relay is HIGH triggering
  digitalWrite(MOP_RELAY, HIGH);
  digitalWrite(PUMP_RELAY, HIGH);
  digitalWrite(VACCUM_RELAY, HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
