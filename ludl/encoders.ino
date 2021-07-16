
#define encoder_a_pin 2
#define encoder_b_pin 3

#define home_pin 7

// Motor A encoder:
Encoder encoder(encoder_a_pin, encoder_b_pin);


inline void setupEncoders()
{
  pinMode(home_pin, INPUT); //Home switch
}


inline void loopEncoders()
{
  //if(ishome())
  {
    Serial.print(getpos());
    Serial.print("\t");
    Serial.println(ishome());
    delay(10);
  }

}

inline int ishome()
{
  return digitalRead(home_pin); 
}

void enforcebounds()
{
  long pos = encoder.read();
  while(pos<0)
    pos+=1440; 
  pos = pos%1440;  
  encoder.write(pos);
}

inline long getpos()
{
  return encoder.read();   
}


inline void sethome() 
{
  encoder.write(0);
}
