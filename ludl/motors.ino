
#define min_speed 30
#define max_speed 255

#define motor_brake_pin 8
#define motor_direc_pin 13
#define motor_power_pin 11


volatile int __speed = 2;

inline void setupMotors()
{
  //Setup Channel B
  pinMode(motor_brake_pin, OUTPUT);  //Brake
  pinMode(motor_direc_pin, OUTPUT);  //Direction
  pinMode(motor_power_pin, OUTPUT);  //Power/Speed
  
  fastpwm();
}

void fastpwm()
{
//  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
//  TCCR2B = _BV(CS22);
//  OCR2A = 180;
//  OCR2B = 50;
}


inline void gotohome()
{
  power(240);
  
  while(true)
  {
    if(ishome())
    {
      sethome();
      break;  
    }
  }
  
  brake();
}

inline void gotopos(long pos)
{
  delay(100); 
  enforcebounds();
  
  // We adjust to a circular topology:
  if (abs((pos+1440)-getpos()) < abs(pos-getpos()))
    pos = pos+1440;
  else if (abs((pos-1440)-getpos()) < abs(pos-getpos()))
    pos = pos-1440;

  int dir = sign(pos-getpos());

  int delta;
  int lastdelta = getpos();
  int dterm= 0;
  int hit=0;
  do
  {
    const int current = getpos();
    delta = pos-current;
    dterm = delta-lastdelta;
    const int control = (1+__speed)*(delta)+dterm*1024;
    power(control);
    if(delta==0)
    {
      hit++;
      //brake();
    }

    delayMicroseconds(100);
    lastdelta = delta;
  } 
  while (hit<120);
  brake();
  
  //power(-dir*255);
  //delayMicroseconds(10000);
  
}


inline void brake()
{
  digitalWrite(motor_brake_pin, HIGH);  
  analogWrite(motor_power_pin,0);
}

inline void power(int mspeed)
{
  //Disengage the Brake:
  digitalWrite(motor_brake_pin, LOW);
  
  //Establishes forward direction:        
  digitalWrite(motor_direc_pin, mspeed>0); 

  //Spins the motor at given speed:
  analogWrite(motor_power_pin, constrain(abs(mspeed), min_speed, max_speed));  
}

inline int sign(int value)
{
  if(value>0)
    return 1;
  else if (value<0)
    return -1;
  else
    return 0;
}
