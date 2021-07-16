
#define button_pin 10

inline void setupButtons()
{
  pinMode(button_pin, INPUT_PULLUP); //Home switch
}


inline void loopButtons()
{
  if(digitalRead(button_pin)==LOW)
  {
    nextfilter();
    delay(10);
  }
}
