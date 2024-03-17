// nhay duoi 5 led 3 lần
#include<stm32f10x.h>
#include<stm32f10x_gpio.h>
#include<stm32f10x_rcc.h>
#include <stm32f10x_tim.h> // Thêm thư viện TIM (Timer)

// Hàm delay từ thư viện HAL
void HAL_Delay(uint32_t Delay);

void RCC_Config(){
    // turn on clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
} 

// cau hinh ngoai vi 
void GPIO_Config(){
GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}

/* void delay_ms(uint8_t timedelay)
	{
	TIM_SetCounter(TIM2,0);
	  while(TIM_GetCounter(TIM2)<timedelay*10){}
	} */


void offLed() {
    GPIO_Write(GPIOC, 0x0000); // Tắt all LED trên port C (ghi giá trị 0x0000 vào port C)
}

void chaseLed(uint8_t loop){
	uint16_t Ledval ; //  
	offLed();
	for(int j=0; j<loop; j++ ){
		Ledval = 0x0010; // 0x0010, LED thứ 5 (đếm từ phải qua trái) được bật
		for(int i =0; i<5; i++)
		{
			Ledval = Ledval<<1;
			GPIO_Write(GPIOC, Ledval);
			HAL_Delay(1000); //1000ms 
			// delay_ms(1000); 
		}
	}
}



int main (){
    RCC_Config();
    GPIO_Config();
    chaseLed(3);

    while(1){
       

    }
    return 0;
}

