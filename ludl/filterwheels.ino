
#include <EEPROM.h>

volatile int __current_position = 0;
volatile bool __step_by_step = false;

int __zero;

inline void setupFilterWheels()
{
  __zero = 138;
  EEPROM.put(0, __zero);
  EEPROM.get(0, __zero);
  gotohome();
  delay(100);
  gotopos(0);
  delay(100);
  setfilter(3);
  delay(100);
  setfilter(0);
  delay(100);
}

inline int getfilter()
{
  return __current_position % 6;
}

inline void setfilter(int index)
{
  index = index%6;
  __current_position = __current_position %6;

  if( abs(index+6-__current_position) < abs(index-__current_position) )
    index = index+6;
  else if( abs(index-6-__current_position) < abs(index-__current_position) )
    index = index-6;

  //if(__current_position==index)
  //return;

  if(__step_by_step)
  {
    if(index>=__current_position)
      for(int i=__current_position; i<=index; i++)
        gotopos(pos4index(i));
    else if(index<__current_position)
      for(int i=__current_position-1; i>=index; i--)
        gotopos(pos4index(i));
  }
  else
  {
    gotopos(pos4index(index));
  }

  __current_position = index;
}

inline void nextfilter()
{
  setfilter( (getfilter()+1)%6 );
}


inline long pos4index(int index)
{
  return __zero-240*index;
}
