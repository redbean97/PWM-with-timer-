#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

void TM_TIMER_Init(void);
void TM_PWM_Init(void);
void TM_LEDS_Init(void);
void TM_LEDS_Init(void);

uint16_t duty=0,fade = 4;

void TM_LEDS_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7   ;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void TM_TIMER_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    TIM_BaseStruct.TIM_Prescaler = 7199;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseStruct.TIM_Period = 9999; /* 10kHz PWM */
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);
    TIM_Cmd(TIM3, ENABLE);
}

void TM_PWM_Init(void) {
  TIM_OCInitTypeDef TIM_OCStruct;
    
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
    
    // pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1
    
    TIM_OCStruct.TIM_Pulse = 5000; /* 25% duty cycle */
    TIM_OC1Init(TIM3, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    
    TIM_OCStruct.TIM_Pulse = 5000; /* 50% duty cycle */
    TIM_OC2Init(TIM3, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    
   


int main(void)
{
    SystemInit();
    /* Init leds */
    TM_LEDS_Init();
    /* Init timer */
    TM_TIMER_Init();
    /* Init PWM */
    TM_PWM_Init();
    TIM_SetCompare1(TIM3,2000);
    TIM_SetCompare2(TIM3,1000);
    
  while(1) 
  {
   
}
