#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#define __SYSTEM_CLOCK    (24000000UL)

uint8_t LED_D4 = 0;
uint32_t delay = 0;

void SysTick_Handler(void)
{
  LED_D4 ^= GPIO_PIN_4; // Troca estado do LED D4
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, LED_D4); // Acende ou apaga LED D4

    while(delay < 6000000)
    {
      delay++;
    }
    delay = 0;
} // SysTick_Handler

void main(void)
{
  SysTickPeriodSet(__SYSTEM_CLOCK); // f = 1Hz para clock = 24MHz
    
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4); // LEDs D3 e D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  SysTickIntEnable();
  SysTickEnable();

  while(1)
  {
    
  } // while
} // main

//Otimizações maiores geram uma comutação do LED maior. O mesmo ocorre para a otimização nula.
//None = 1,2s
//Low = 1s
//Medium = 0,3s
//High < 0,1s

//Alteração do clock do sistema não alterou a comutação.