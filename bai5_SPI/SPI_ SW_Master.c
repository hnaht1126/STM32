	#include<stm32f10x.h>
#include<stm32f10x_gpio.h>
#include<stm32f10x_rcc.h>


#define SPI_SCK_Pin 	GPIO_Pin_0
#define SPI_MISO_Pin 	GPIO_Pin_1
#define SPI_MOSI_Pin 	GPIO_Pin_2
#define SPI_CS_Pin 		GPIO_Pin_3
#define SPI_GPIO 			GPIOA
#define SPI_RCC 			RCC_APB2Periph_GPIOA

// cap xung RCC
void RCC_Config(){
	RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

// cau hinh GPIO
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin| SPI_MOSI_Pin| SPI_CS_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}

// cau hinh timer
void TIM_Config(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(int time){
	TIM_SetCounter(TIM2,0);
	while(TIM_GetCounter(TIM2)<time*10){}
}


// ham khoi tao SPI
void SPI_Init(){
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET); // muc 0
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET); // muc 1
	GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_RESET);
	GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
}

// ham Clock cua tin hieu SCK
void Clock(){
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);
	delay_ms(4);
	GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
	delay_ms(4);
}

// ham truyen Master
void SPI_Master_Transmit(uint8_t u8Data){
	uint8_t u8Mask = 0x80; //
	uint8_t tempData;
	//keo chan CS xuong 0
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_RESET);
	delay_ms(1);
	//truyen du lieu
	for(int i=0; i<8; i++){
		tempData = u8Data & u8Mask; // truyen trong so cao
		if(tempData){
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_SET);
			delay_ms(1);
		} else{
			GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
			delay_ms(1);
		}
		u8Data=u8Data<<1;
		Clock();
	}
	// keo thuc truyen CS ve 1
	GPIO_WriteBit(SPI_GPIO, SPI_CS_Pin, Bit_SET);
	delay_ms(1);
}

uint8_t DataTrans[] = {1,3,9,10,15,19,90};//Data


int main(){
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	SPI_Init();
	
	// mo phong qua trinh truyen Marter
	while(1)
		{	
			for(int i=0; i<7; i++){
			SPI_Master_Transmit(DataTrans[i]);
			delay_ms(500);
			}
		}

}



