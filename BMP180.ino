#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;
const int BUTTON_SET = A0;
const int BUTTON_RUN = A1;
const int LED_NEN = 2;
const int LED_XA = 3;
const int MTB = 6;
const int VXK = 7;
float P_max = 0.00;
float P_min = 2000.00;
unsigned long time_max;
unsigned long time_min;
unsigned long cycle_time;
void setup()
{
  //Serial.begin(9600);
  pinMode(BUTTON_SET, INPUT);
  pinMode(BUTTON_RUN, INPUT);
  pinMode(LED_NEN, OUTPUT);
  pinMode(LED_XA, OUTPUT);
  pinMode(MTB,OUTPUT);
  pinMode(VXK,OUTPUT);
  
//setup sensor BMP180 
//  if (pressure.begin())
//    Serial.println("BMP180 init success");
//  else
//  {
//    Serial.println("BMP180 init fail\n\n");
//    while(1); // Pause forever.
//  }
}

void loop()
{
  char status;
  double T,P;
  int button_set_state = digitalRead(BUTTON_SET);
  int button_run_state = digitalRead(BUTTON_RUN);
  if(button_set_state == LOW)
  {
    status = pressure.startTemperature();
    if (status != 0)
    {
      delay(status);
      status = pressure.getTemperature(T);
      if (status != 0)
      {
        status=pressure.startPressure(3);
        if(status!=0)
           {
              delay(status);
              status = pressure.getPressure(P,T);
              if (status != 0)
              {
//                Serial.print("Pressure: ");
//                Serial.print(P,2);
//                Serial.print(" mb, ");
                  if(P > P_max)
                  {
                    P_max = P;
                    time_max = millis();
                  }
                  if(P < P_min)
                  {
                    P_min = P;
                    time_min = millis();
                  }
              }
            }
      }
    }
  }
  
  else
  {
    //cycle_time = time_max - time_min;
    cycle_time = 2500;
    if(button_run_state == LOW)
    {
      while(true)
      {
        digitalWrite(LED_NEN, HIGH);
        digitalWrite(MTB, HIGH);
        digitalWrite(LED_XA, LOW);
        digitalWrite(VXK, LOW);
        delay(cycle_time);
        digitalWrite(LED_NEN, LOW);
        digitalWrite(MTB, LOW);
        digitalWrite(LED_XA, HIGH);
        digitalWrite(VXK, HIGH);
        delay(cycle_time);
      }
    }
  }
}
