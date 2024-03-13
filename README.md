# STM32
 <details><summary>Bài 2: GPIO </summary>
<p>

> ## GPIO

### các bước để sd ngoại vi 
![image](https://github.com/hnaht1126/STM32/assets/152061415/af48569a-81c7-4fcd-8b46-2889471ad967)

# 1. Cấp xung clock cho GPIO
   
Các API được cung cấp sẵn cho từng Bus. 

Các ngoại vi trên Bus được cấp xung thông qua truyền tham số vào API


![image](https://github.com/hnaht1126/STM32/assets/152061415/bdc5ed6a-b3a0-449b-8700-b1e6a93d219a)

Thanh ghi RCC cấp xung clock (ngưng cấp xung sd `DISABLE`)

```c
void RCC_Config(){
	// turn on clock 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
} 
```
## cấu hình GPIO (Pin, Mode, Speed)

> cấp xung cho bus->port-> pin 

```c
// cau hinh cho ngoai vi 
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	//IPD INput Pull down - keo dien ap xuong 0V
	//IPU INput Pull UP - keo dien ap lên 3.3V
	//Out PP Push&Pull 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//GPIOx : GPIO su dung, cau hinh GPIO da tao
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
```

* GPIO_Pin: chọn pin GPIO cần cấu hình. có thể kết hợp các pin lại với nhau bằng toán tử | . 

* GPIO_Mode: chế độ hoạt động của pin GPIO, có thể là đầu vào, đầu ra, hoặc một trong các chế độ chức năng khác như chế độ AF (chức năng thay thế).

* GPIO_Speed: tốc độ đáp ứng của pin GPIO.

* Hàm GPIO_Init() nhận hai tham số:

    - GPIO_TypeDef* GPIOx: Con trỏ đến cổng GPIO cần cấu hình.(ví dụ: GPIOA, GPIOB, v.v.).

    - &GPIO_InitStruct: Đây là một con trỏ tới biến kiểu GPIO_InitTypeDef đã được khởi tạo và chứa thông tin cấu hình của pin GPIO.

## Cấu hình cho các ngoại vi khác 

Cấu hình timer
```c
void TIM_Config(){
    TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;

    TIM_TimBaseInitStructure…;
TIM_TimBaseInitStructure…;

    TIM_TimeBaseInit(TIM2, &TIM_TimBaseInitStructure);
}

```
Cấu hình SPI ...

## Các hàm thông dụng 

1. `uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);`
   - Ví dụ: Đọc trạng thái của một nút nhấn kết nối với một chân GPIO cụ thể.
   ```c
   if (GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
       // Nút nhấn đã được nhấn
   } else {
       // Nút nhấn không được nhấn
   }
   ```

2. `uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);`
   - Ví dụ: Đọc trạng thái của tất cả các chân GPIO trong một cổng GPIO.
   ```c
   uint16_t inputData = GPIO_ReadInputData(GPIOC);
   // inputData chứa trạng thái của tất cả các chân GPIO trong cổng GPIOC
   ```

3. `uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);`
   - Ví dụ: Đọc trạng thái của một chân GPIO đang được cấu hình là đầu ra.
   ```c
   if (GPIO_ReadOutputDataBit(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET) {
       // Chân GPIOB_PIN_5 đang được đặt ở mức cao
   } else {
       // Chân GPIOB_PIN_5 đang được đặt ở mức thấp
   }
   ```

4. `uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);`
   - Ví dụ: Đọc trạng thái của tất cả các chân GPIO đang được cấu hình là đầu ra trong một cổng GPIO.
   ```c
   uint16_t outputData = GPIO_ReadOutputData(GPIOB);
   // outputData chứa trạng thái của tất cả các chân GPIO đang được cấu hình là đầu ra trong cổng GPIOB
   ```

5. `void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);`
   - Ví dụ: Đặt một chân GPIO cụ thể ở mức logic cao (1).
   ```c
   GPIO_SetBits(GPIOA, GPIO_PIN_1);
   ```

6. `void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);`
   - Ví dụ: Đặt một chân GPIO cụ thể ở mức logic thấp (0).
   ```c
   GPIO_ResetBits(GPIOC, GPIO_PIN_3);
   ```

7. `void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);`
   - Ví dụ: Viết một giá trị cụ thể (0 hoặc 1) vào một chân GPIO cụ thể.
   ```c
   GPIO_WriteBit(GPIOB, GPIO_PIN_7, Bit_SET); // Set chân GPIOB_PIN_7 ở mức logic cao
   ```

8. `void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);`
   - Ví dụ: Viết một giá trị 16-bit vào tất cả các chân GPIO trong một cổng GPIO.
   ```c
   GPIO_Write(GPIOC, 0x05); // Viết giá trị 0x05 vào tất cả các chân GPIO trong cổng GPIOC
   ```
</p>
</details>

