#include "timer3.h"
#include "stm32f1xx.h"

extern void prvvTIMERExpiredISR( void ); //由定时器中断函数调用
TIM_HandleTypeDef TIM3_Handler;          //定时器句柄

void timer_init(uint32_t num_50us)
{
    TIM3_Handler.Instance	       = TIM3;                      //通用定时器3
    TIM3_Handler.Init.Prescaler    = 720-1;                     //分频系数 32Mhz/32 10us
    TIM3_Handler.Init.CounterMode  = TIM_COUNTERMODE_UP;        //向上计数器
    TIM3_Handler.Init.Period       = (num_50us*50)/10-1;        //自动装载值
    TIM3_Handler.Init.ClockDivision= TIM_CLOCKDIVISION_DIV1;    //时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE
}

#define TIME3_IRQ_PRIORITY 1
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM3_IRQn,TIME3_IRQ_PRIORITY,0);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}
}

void start_timer(void)
{
    HAL_TIM_Base_Start_IT(&TIM3_Handler);
}

void stop_timer(void)
{
    HAL_TIM_Base_Stop_IT(&TIM3_Handler);
}

extern void prvvTIMERExpiredISR( void );
void TIM3_IRQHandler(void) {
    if(__HAL_TIM_GET_FLAG(&TIM3_Handler, TIM_FLAG_UPDATE) != RESET){
	   if(__HAL_TIM_GET_IT_SOURCE(&TIM3_Handler, TIM_IT_UPDATE) !=RESET){
         
		  __HAL_TIM_CLEAR_IT(&TIM3_Handler, TIM_IT_UPDATE);    
          prvvTIMERExpiredISR();
       }
    }	
}
