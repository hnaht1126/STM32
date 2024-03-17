#include<stm32f10x.h>
#include<stm32f10x_gpio.h>
#include<stm32f10x_rcc.h>


void RCC_Config(){
    // turn on clock
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
} 

// cau hinh ngoai vi 
void GPIO_Config(){
GPIO_InitTypeDef GPIO_InitStructure;

    //button  PA0 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    // mode Input Pull down 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    //led PC13
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    // mode Output Push&Pull
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

// void delay_ms(uint8_t timedelay)
// 	{
// 	TIM_SetCounter(TIM2,0);
// 	  while(TIM_GetCounter(TIM2)<timedelay*10){}
// 	}

int main (){
    RCC_Config();
    GPIO_Config();

    while(1){
        // nut nhan tich cuc muc thap (0)
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) // doc trang thai button PA0
        {
            while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)); //
            //do something
            if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)){ // kiem tra trang thai LED PC13
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
            } else {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
            }
        }

    // delay_ms(100); //giảm thiểu việc đọc trạng thái không mong muốn

    }
    return 0;
}

