#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 2 estados e 1 evento temporal que alterna entre eles
// Seleção por evento

typedef enum {_000, _001, _011, _010, _110, _111, _101, _100} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = _000; // estado inicial da MEF
  
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1)
  {
      switch(Estado)
      {
        case _000:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _001;
          }
          break;
          
        case _001:
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _011;
          }
          break;
          
        case _011:
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _010;
          }
          break;
          
        case _010:
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _110;
          }
          break;
          
        case _110:
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _111;
          }
          break;
          
        case _111:
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _101;
          }
          break;
          
        case _101:
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _100;
          }
          break;
          
        case _100:
          LEDOff(LED1);
          LEDOff(LED1);
          LEDOn(LED3);
          if(Evento)
          {
            Evento = 0;
            Estado = _000;
          }
          break;
          
      } // switch
  } // while
} // main
