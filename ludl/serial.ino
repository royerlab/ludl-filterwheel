

String command = "";                      // a String to hold incoming data
volatile bool command_complete = false;  // whether the string is complete

inline void setupSerial()
{
  Serial.begin(1000000); 
  Serial.println("LUDL Filterwheel controller (ROYER LAB)");

  // reserve 200 bytes for the inputString:
  command.reserve(200);
}

inline void loopSerial()
{

  if (command_complete) 
  {
    while(command.length()>0  && command[0]!='#')
      command.remove(0);
      
    //Serial.println(command);

    if(command[0]=='#')
    {
      if(command[1]=='z')
      {
        __zero = command.substring(2).toInt();
        setfilter(getfilter());
      }
      else if(command[1]=='h')
      {
        gotohome();
        setfilter(getfilter());
      }
      else if(command[1]=='s')
      {
        int index = ((int)command[2]-48);
        setfilter(index);
      }
      else if (command[1]=='g')
      {
        Serial.println(getfilter());
      }
      else if (command[1]=='v')
      {
        int index = ((int)command[2]-48);
        __speed = index;
      }
      else if (command[1]=='c')
      {
        __step_by_step=false;
      }
      else if (command[1]=='i')
      {
        __step_by_step=true;
      }
    }

    command = "";
    command_complete = false;
    Serial.print("done!\n");
  }
  
}


void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    command += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') 
    {
      command_complete = true;
    }
  }
}
