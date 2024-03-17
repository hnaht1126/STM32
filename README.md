# STM32
# Bài 2: GPIO 

## GPIO

### các bước để sd ngoại vi 
![image](https://github.com/hnaht1126/STM32/assets/152061415/af48569a-81c7-4fcd-8b46-2889471ad967)

### 1. Cấp xung clock cho GPIO
   
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
### 2. cấu hình GPIO (Pin, Mode, Speed)

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

### Cấu hình cho các ngoại vi khác 

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
### 3. Sử dụng ngoại vi 
### Các hàm thông dụng 

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




# Bài 3: Ngắt & Timer 

## Ngắt
 Sự kiện diễn ra trong hoặc ngoài vđk, yêu cầu MCU dừng chương trình chính và thực thi chương trình ngắt 

 vd: đang chơi game má gọi đi rửa chén =)))

Mỗi ngắt có 1 trình phục vụ ngắt, sẽ yêu cầu MCU thực thi lệnh tại trình phục vụ ngắt khi có ngắt xảy ra.

Các ngắt có các địa chỉ cố định trong bộ nhớ để giữ các trình phục vụ.(vector ngắt.) 

![image](https://github.com/hnaht1126/STM32/assets/152061415/f37cec44-a5c0-4b71-b0e9-f29193ac21ae)

## Ngắt ngoài - tác động từ ngoài MCU  

Xảy ra khi có sự thay đổi điện áp trên các chân GPIO được cấu hình là ngõ vào ngắt 

* LOW - kích hoạt ngắt liên tục khi chân mức Thấp (0)
* High -  kích hoạt ngắt liên tục khi chân mức Cao (1)
* Rising - kích hoạt ngắt khi chuyển từ thấp lên cao 
* Falling - kích hoạt ngắt khi chyển từ cao xuống thấp 

## Ngắt timer  

Xảy ra khi giá trị thanh ghi đếm tràn. Giá trị được xác định bằng giá trị trong thanh ghi đếm của timer.

Vì đây là `ngắt nội trong MCU`, nên phải `reset giá trị thanh ghi timer` để có thể `tạo được ngắt tiếp theo`.

## Ngắt truyền thông 

Ngắt truyền thông xảy ra khi có sự kiện truyền/nhận dữ liệu giữ MCU với các thiết bị bên ngoài hay với MCU. 

sử dụng cho nhiêu phương thức như UART, SPI, I2C nhằm đảm bảo việc truyền nhận chính xác.



Ví dụ, trong trường hợp của UART, ngắt truyền thông UART được kích hoạt khi một byte dữ liệu mới được nhận vào từ thiết bị ngoại vi. Khi ngắt này xảy ra, vi điều khiển thực hiện một hàm callback được gọi là ngắt UART, trong đó bạn có thể đọc dữ liệu và thực hiện các hoạt động xử lý dữ liệu khác

```c
#include "stm32xxxx_hal.h" // Thay thế "xxxx" bằng dòng MCU đang sử dụng  

UART_HandleTypeDef huart;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    char rx_data; // Biến để lưu trữ dữ liệu nhận được từ UART

    while (1) {
        // Không cần làm gì trong vòng lặp chính, vì việc xử lý dữ liệu sẽ được thực hiện trong hàm callback ngắt UART
    }
}

void SystemClock_Config(void) {
    // Cấu hình hệ thống clock
}

static void MX_GPIO_Init(void) {
    // Khởi tạo GPIO nếu cần thiết
}

static void MX_USART1_UART_Init(void) {
    huart.Instance = USART1; // Sử dụng USART1
    huart.Init.BaudRate = 9600;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart);

    // Thiết lập ngắt UART
    HAL_UART_Receive_IT(&huart, (uint8_t*)&rx_data, 1);
}

// Ngắt UART callback
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        // Xử lý dữ liệu nhận được ở đây
        // Ví dụ: Gửi lại dữ liệu đã nhận
        HAL_UART_Transmit(huart, (uint8_t*)&rx_data, 1, HAL_MAX_DELAY);

        // Bắt đầu nhận dữ liệu mới
        HAL_UART_Receive_IT(huart, (uint8_t*)&rx_data, 1);
    }
}

// Ngắt Error callback (nếu cần)
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    // Xử lý lỗi nếu có
}

```

## Độ ưu tiên ngắt

Độ ưu tiên ngắt là khác nhau ở các ngắt. Nó xác định ngắt nào được quyền thực thi khi nhiều ngắt xảy ra đồng thời.

STM32 quy định ngắt nào có số thứ tự ưu tiên càng thấp thì có quyền càng cao (0->15). Các ưu tiên ngắt có thể lập trình được.


```c
#include "stm32xxxx_hal.h"

void HAL_MspInit(void) {
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); // Thiết lập nhóm ưu tiên ngắt

    HAL_NVIC_SetPriority(USARTx_IRQn, 0, 0); // Đặt độ ưu tiên ngắt cho USARTx
    HAL_NVIC_SetPriority(TIMx_IRQn, 1, 0);   // Đặt độ ưu tiên ngắt cho TIMx
    HAL_NVIC_SetPriority(ADC_IRQn, 2, 0);    // Đặt độ ưu tiên ngắt cho ADC
    // ...
}
```
##  Timer

timer thường được sử dụng để thực hiện các nhiệm vụ như đo thời gian, đếm xung, gửi ngắt theo chu kỳ, và các tác vụ liên quan đến thời gian.

Timer còn có thể hoạt động ở chế độ nhận xung clock từ các tín hiệu ngoài. Có thể là từ 1 nút nhấn, bộ đếm sẽ được tăng sau mỗi lần bấm nút (sườn lên hoặc sườn xuống tùy vào cấu hình). Ngoài ra còn các chế độ khác như PWM, định thời vvv.


Các timer này thường được điều khiển và cấu hình bằng phần mềm thông qua việc thiết lập các thanh ghi cụ thể trên vi điều khiển. Các sự kiện như đạt giá trị đếm cụ thể, tràn timer, hoặc các điều kiện khác có thể kích hoạt ngắt, cho phép hệ thống phản ứng và thực hiện các tác vụ tương ứng.

Đảm bảo chính xác thời gian và điều khiển các sự kiện theo chu kỳ trong hệ thống.

**STM32F103 có 7 Timer.**

## Cấu hình Timer 

Sau khi cấp clock cho timer, cấu hình các tham số cho timer trong struct TIM_TimeBaseInitTypeDef : gồm:

* Clock division - thiết lập chia clock cho timer 
* Prescaler 
* Period - giá trị chu kỳ timer
* Mode - chế độ đếm 

TimerClock = fSystem/Clock_Division

```c
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct; // Khởi tạo cấu hình timer
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Bạt Clock cho timer

// Cấu hinhfcacs thông số của timer
   TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1; 
   TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF-1;
   TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 

   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
   //Kích hoạt timer
   TIM_Cmd(TIM2, ENABLE);
```

## Hàm delay_ms

Với cài đặt thông số cho timer ở trên, ta cấu hình timer đếm lên mỗi 0.1ms.
Lặp lại timedelay*10 lần>> hàm delay_ms.

```c
void delay_ms(uint8_t timedelay)
   {
   TIM_SetCounter(TIM2,0);
     while(TIM_GetCounter(TIM2)<timedelay*10){}
   }


```

# Bài 4: Các chuẩn giao tiếp cơ bản

## 1. Truyền nhận dữ liệu 

Truyền nhận các tín hiệu điện áp biểu diễn cho các bit

điện áp được truyền nhận trên các chân của VĐK.

![image](https://github.com/hnaht1126/STM32/assets/152061415/bda2bf83-97af-4575-915f-28e0126191d2)

## 2. SPI

SPI – Serial Peripheral Interface: Là chuẩn `giao tiếp nối tiếp đồng bộ.`

Hoạt động ở chế độ `song công` (Có thể truyền - nhận cùng thời điểm).

Sử dụng 4 dây giao tiếp.

![image](https://github.com/hnaht1126/STM32/assets/152061415/1797aaad-8af1-4703-9cd9-b7c64ea1fb10)

* SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave.
* MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master.
* MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. 
* SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). 


## Quá trình truyền nhận SPI

**Khởi tạo:** Khởi tạo giao tiếp SPI trên các thiết bị tham gia. Bao gồm cấu hình các thông số như tốc độ truyền, chế độ truyền dữ liệu (full duplex, half duplex), và cài đặt các chân (pins) tương ứng.

**Chọn thiết bị:** Trong một hệ thống có nhiều thiết bị SPI, thiết bị gửi dữ liệu sẽ chọn thiết bị nhận dữ liệu bằng cách kích hoạt tín hiệu chọn thiết bị (chip select). Mỗi thiết bị SPI thường có một tín hiệu chip select riêng để đảm bảo chỉ có một thiết bị được kích hoạt trong mỗi thời điểm.

**Truyền dữ liệu:** Dữ liệu được truyền đi từ thiết bị gửi tới thiết bị nhận thông qua các chân MOSI (Master Out Slave In) và MISO (Master In Slave Out). Cả hai thiết bị cùng trao đổi dữ liệu theo cùng một thời gian, do đó giao tiếp SPI là giao tiếp đồng bộ.

**Xác nhận dữ liệu:** Sau khi dữ liệu được truyền, thiết bị nhận có thể xác nhận việc nhận dữ liệu bằng cách gửi một tín hiệu ACK (acknowledge) hoặc NACK (not acknowledge) tới thiết bị gửi.

**Giải phóng tín hiệu chip select:** Khi toàn bộ dữ liệu đã được truyền hoặc nhận, tín hiệu chip select sẽ được giải phóng, cho phép các thiết bị khác trong hệ thống được truy cập.

![image](https://github.com/hnaht1126/STM32/assets/152061415/a1575233-bd46-4068-ba77-8621d5e72f28)


* Bắt đầu quá trình, master sẽ kéo chân CS của slave muốn giao tiếp xuống 0 để báo hiệu muốn truyền nhận.
* Clock sẽ được cấp bởi master, tùy vào chế độ được cài, với mỗi xungc clock,  1 bit sẽ được truyền từ master đến slave và slave cũng truyền 1 bit cho master.
* Các thanh ghi cập nhật giá trị và dịch 1 bit.
* Lặp lại quá trình trên đến khi truyền xong 8 bit trong thanh ghi.
* Giao tiếp song công.

![image](https://github.com/hnaht1126/STM32/assets/152061415/b563076e-83ae-4bf7-b6c1-81dfe5c1e55f)

## Các chế độ hoạt động

SPI có 4 chế độ hoạt động phụ thuộc Clock Polarity – CPOL và  Phase - CPHA.

![image](https://github.com/hnaht1126/STM32/assets/152061415/22139d22-c28a-4731-bcf5-a60c30e5998e)

## 3. I2C
I2C là chuẩn giao tiếp nối tiếp, chỉ sử dụng 2 dây SDA, SCL.
* Một Master giao tiếp được với nhiều Slave.
* Truyền bán song công.

![image](https://github.com/hnaht1126/STM32/assets/152061415/34189775-9e85-4e5b-bac3-3f997fc3790e)

## Quá trình truyền nhận I2C




## 4. UART

UART (Universal Asynchronous Receiver-Transmitter) là một giao thức truyền thông phần cứng dùng giao tiếp nối tiếp không đồng bộ.

Gồm hai đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận). 
* Hoạt động song công.
* Không cần chân Clock.
