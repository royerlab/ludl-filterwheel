//#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

/*************************************************************
LUDL filter wheel controller
Royer Lab
*************************************************************/


void setup() 
{
  setupSerial();
  setupMotors();
  setupEncoders();
  setupFilterWheels();
  setupButtons();
}


void loop()
{
  loopSerial();
  loopButtons();
  loopEncoders();
  
}
