#define PULSE 58
int main(){
  uint8_t map0 [60] = {5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34};
  uint8_t map1 [60] = {5, 6, 7, 8, 9, 10, 15, 20, 25, 30, 35, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 37, 37, 37, 37, 36, 36, 36, 36, 35, 35, 35, 35, 34, 34, 34, 34, 33, 33, 33, 33};
  uint32_t LATE,TIMING;
  int LIMIT,count;
  PORTD = 0x18;
  DDRD  = 0x18;
  TCCR1B = 0x03;
  while (true){
    while ((PIND>>2&0x04>>2)==1);
    while ((PIND>>2&0x04>>2)==0);
    LATE = TCNT1;
    TCNT1 = 0;
    TIMING = 60000/LATE;
    if((PIND>>5&0x20>>5)==1){ // if d5 high
      LATE *= PULSE - map1[TIMING];
    }
    else{ // if d5 low
      LATE *= PULSE - map0[TIMING];
    }
    LATE /= 360;
    if((PIND>>6&0x40>>6)==1)LIMIT = 32; // if d6 high
    else{ // if d6 low
      LIMIT = 59;
    }
    if(TIMING<=LIMIT){
      while(TCNT1<LATE);
      if(TIMING<=7){
        if(count==2 || count==5 || count==7 || count==11 || count==14 || count==17 || count==20){
          PORTD = 0x10;
        }
        else{
          PORTD = 0x08;
        }
      }
      else{
        PORTD = 0x10;
      }
      count++;
      if(count > 20)count = 1;
      while(TCNT1<LATE+25);
      PORTD = 0x08;
    }
  }
}
