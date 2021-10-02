
#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

Stepper my_Stepper(200, D8, D7, D6, D5);

bool Right = false;
bool Left = false;

char auth[] = "Authentication Token";
char ssid[] = "WIFI SSID";
char pass[] = "WIFI Password";


void setup(){

  Serial.begin(9600);                                 // baudrate for serial comunication
  Blynk.begin(auth, ssid, pass);                      // network information 
  my_Stepper.setSpeed(70);                            // Stepper motor speed
  
}
//-- Setup End ---------------------------------------------------------------------------------------------------------------------


BLYNK_WRITE(V1){                                      // read input from virtual pin V1
  Right = param.asInt();                              // assigning incoming value from pin V§1 to a variable
  }
  
BLYNK_WRITE(V0){                                      // read input from virtual pin V0
  Left = param.asInt();                               // assigning incoming value from pin V0 to a variable
  }
  
void Stepper1 (int Direction, int Rotation){          // function for stepper motor control with 2 parameters
  for (int i = 0; i < Rotation; i++){                 // for loop 
  my_Stepper.step(Direction * 50);                    // 100 is 180 degree
  Blynk.run();
  }
}

//++ Start Loop +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop() {   
  
  Blynk.run();
  
  if (Right){                                          // if condition 
  Stepper1(1, 2);                                     // steppermotor rotates 2 times 96 degree right
  Serial.println("Right turn");
  }
  delay(20);                                           // delay 20ms
  
  if (Left){                                           // if condition 
  Stepper1(-1, 2);                                    // steppermotor rotates 2 times 90 degree left
  Serial.println("Left turn");
  }
  delay(20);                                           // delay 20ms
}
//-- Loop End ---------------------------------------------------------------------------------------------------------------------
