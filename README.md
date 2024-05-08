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

## 1. Ngắt
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

## 2. Độ ưu tiên ngắt

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
##  3. Timer

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

SPI thường được sử dụng giao tiếp với bộ nhớ EEPROM, RTC (Đồng hồ thời gian thực), IC âm thanh, các loại cảm biến như nhiệt độ và áp suất, thẻ nhớ như MMC hoặc thẻ SD hoặc thậm chí các bộ vi điều khiển khác.

![image](https://github.com/hnaht1126/STM32/assets/152061415/1797aaad-8af1-4703-9cd9-b7c64ea1fb10)

## Hoạt động của SPI 
### Cấu tạo

* SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave. Xung này có chức năng giữ nhịp cho giao tiếp SPI. Mỗi nhịp trên chân SCK báo 1 bit dữ liệu đến hoặc đi → Quá trình ít bị lỗi và tốc độ truyền cao.
* MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master.
* MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. 
* SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). Chân SS của vi điều khiển (Master) có thể được người dùng tạo bằng cách cấu hình 1 chân GPIO bất kỳ chế độ Output.

###  Khung truyền SPI: 

![image](https://github.com/hnaht1126/STM32/assets/152061415/1f36941b-6f69-449e-a948-4d2bf91d86e9)

* Mỗi chip Master hay Slave đều có một thanh ghi dữ liệu 8 bits.

* Quá trình truyền nhận giữa Master và Slave xảy ra đồng thời sau 8 chu kỳ đồng hồ, một byte dữ liệu được truyền theo cả 2 hướng 

* Quá trình trao đổi dữ liệu bắt đầu khi Master tạo 1 xung clock từ bộ tạo xung nhịp (Clock Generator) và kéo đường SS của Slave mà nó truyền dữ liệu xuống mức Low.

* Cứ 1 xung clock, Master sẽ gửi đi 1 bit từ thanh ghi dịch (Shift Register) của nó đến thanh ghi dịch của Slave thông qua đường MOSI. Đồng thời Slave cũng gửi lại 1 bit đến cho Master qua đường MISO.Như vậy sau 8 chu kỳ clock thì hoàn tất việc truyền và nhận 1 byte dữ liệu.

* Dữ liệu của 2 thanh ghi được trao đổi với nhau nên tốc độ trao đổi diễn ra nhanh và hiệu quả.


**Lưu ý**: Trong giao tiếp SPI, chỉ có thể có 1 Master nhưng có thể 1 hoặc nhiều Slave cùng lúc. Ở trạng thái nghỉ, chân SS của các Slave ở mức 1, muốn giao tiếp với Slave nào thì ta chỉ việc kéo chân SS của Slave đó xuống mức 0.


### Quá trình truyền nhận SPI

1. **Khởi tạo:** Khởi tạo giao tiếp SPI trên các thiết bị tham gia. Bao gồm cấu hình các thông số như tốc độ truyền, chế độ truyền dữ liệu (full duplex, half duplex), và cài đặt các chân (pins) tương ứng.

2. **Chọn thiết bị:** Trong một hệ thống có nhiều thiết bị SPI, thiết bị gửi dữ liệu sẽ chọn thiết bị nhận dữ liệu bằng cách kích hoạt tín hiệu chọn thiết bị (chip select). Mỗi thiết bị SPI thường có một tín hiệu chip select riêng để đảm bảo chỉ có một thiết bị được kích hoạt trong mỗi thời điểm.

3. **Truyền dữ liệu:** Dữ liệu được truyền đi từ thiết bị gửi tới thiết bị nhận thông qua các chân MOSI (Master Out Slave In) và MISO (Master In Slave Out). Cả hai thiết bị cùng trao đổi dữ liệu theo cùng một thời gian, do đó giao tiếp SPI là giao tiếp đồng bộ.

4. **Xác nhận dữ liệu:** Sau khi dữ liệu được truyền, thiết bị nhận có thể xác nhận việc nhận dữ liệu bằng cách gửi một tín hiệu ACK (acknowledge) hoặc NACK (not acknowledge) tới thiết bị gửi.

5. **Giải phóng tín hiệu chip select:** Khi toàn bộ dữ liệu đã được truyền hoặc nhận, tín hiệu chip select sẽ được giải phóng, cho phép các thiết bị khác trong hệ thống được truy cập.

Quá trình truyền nhận SPI là một quy trình đồng bộ và nhanh chóng, thích hợp cho các ứng dụng yêu cầu truyền dữ liệu nhanh và tin cậy giữa các thiết bị trong hệ thống điện tử.

![image](https://github.com/hnaht1126/STM32/assets/152061415/a1575233-bd46-4068-ba77-8621d5e72f28)


* Bắt đầu quá trình, master sẽ kéo chân CS của slave muốn giao tiếp xuống 0 để báo hiệu muốn truyền nhận.
* Clock sẽ được cấp bởi master, tùy vào chế độ được cài, với mỗi xung clock,  1 bit sẽ được truyền từ master đến slave và slave cũng truyền 1 bit cho master.
* Các thanh ghi cập nhật giá trị và dịch 1 bit.
* Lặp lại quá trình trên đến khi truyền xong 8 bit trong thanh ghi.


![image](https://github.com/hnaht1126/STM32/assets/152061415/b563076e-83ae-4bf7-b6c1-81dfe5c1e55f)

### Các chế độ hoạt động của SPI

SPI có 4 chế độ hoạt động phụ thuộc Clock Polarity – CPOL và  Phase - CPHA.

* CPOL dùng để chỉ trạng thái của chân SCK ở trạng thái nghỉ. Chân SCK giữ ở mức cao khi CPOL=1 hoặc mức thấp khi CPOL=0.
* CPHA dùng để chỉ các mà dữ liệu được lấy mẫu theo xung. Dữ liệu sẽ được lấy ở cạnh lên của SCK khi CPHA=0 hoặc cạnh xuống khi CPHA=1.

![image](https://github.com/hnaht1126/STM32/assets/152061415/22139d22-c28a-4731-bcf5-a60c30e5998e)

* Mode 0 (mặc định) – xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh lên) (CPHA = 0).

* Mode 1 - xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh xuống) (CPHA = 1).

* Mode 2 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh lên) (CPHA = 0).

* Mode 3 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh xuống) (CPHA = 1).

**Lưu ý**: Khi giao tiếp SPI giữa vi điều khiển và các thiết bị ngoại vi khác như IC, cảm biến thì 2 bên bắt buộc hoạt động cùng Mode, nếu không dữ liệu truyền nhận có thể bị đọc sai.


## 3. I2C
I2C là chuẩn giao tiếp nối tiếp, chỉ sử dụng 2 dây SDA, SCL.
* Một Master giao tiếp được với nhiều Slave.
* Truyền bán song công.

Các bit dữ liệu sẽ được truyền từng bit một theo các khoảng thời gian đều đặn được thiết lập bởi 1 tín hiệu đồng hồ. 

Bus I2C thường được sử dụng để giao tiếp ngoại vi cho rất nhiều loại IC khác nhau như các loại vi điều khiển, cảm biến, EEPROM, … .

![image](https://github.com/hnaht1126/STM32/assets/152061415/34189775-9e85-4e5b-bac3-3f997fc3790e)

## Hoạt động của giao tiếp I2C
### Cấu tạo :

I2C sử dụng 2 đường truyền tín hiệu:
* SCL -  Serial Clock Line : Tạo xung nhịp đồng hồ do Master phát đi
* SDA - Serial Data Line : Đường truyền nhận dữ liệu.
  ![image](https://github.com/hnaht1126/STM32/assets/152061415/6ce4db43-d2fd-4be6-8777-823e3149d848)

* Giao tiếp I2C bao gồm quá trình truyền nhận dữ liệu giữa các thiết bị chủ tớ, hay Master - Slave.  
* Thiết bị Master là 1 vi điều khiển, nó có nhiệm vụ điều khiển đường tín hiệu SCL và gửi nhận dữ liệu hay lệnh thông qua đường SDA đến các thiết bị khác.
* Các thiết bị nhận các dữ liệu lệnh và tín hiệu từ thiết bị Master được gọi là các thiết bị Slave. Các thiết bị Slave thường là các IC, hoặc thậm chí là vi điều khiển. 
* Master và Slave được kết nối với nhau như hình trên. Hai đường bus SCL và SDA đều hoạt động ở chế độ Open Drain, nghĩa là bất cứ thiết bị nào kết nối với mạng I2C này cũng chỉ có thể kéo 2 đường bus này xuống mức thấp (LOW), nhưng lại không thể kéo được lên mức cao. Vì để tránh trường hợp bus vừa bị 1 thiết bị kéo lên mức cao vừa bị 1 thiết bị khác kéo xuống mức thấp gây hiện tượng ngắn mạch. Do đó cần có 1 điện trờ ( từ 1 – 4,7 kΩ) để giữ mặc định ở mức cao.

### Khung truyền I2C : 

![image](https://github.com/hnaht1126/STM32/assets/152061415/18de2929-014e-4440-baec-940565a32212)

* Khối bit địa chỉ :
  
Thông thường quá trình truyền nhận sẽ diễn ra với rất nhiều thiết bị, IC với nhau. Do đó để phân biệt các thiết bị này, chúng sẽ được gắn 1 địa chỉ vật lý 7 bit cố định.

* Bit Read/Write:
  
Bit này dùng để xác định quá trình là truyền hay nhận dữ liệu từ thiết bị Master. Nếu Master gửi dữ liệu đi thì ứng với bit này bằng ‘0’, và ngược lại, nhận dữ liệu khi bit này bằng ‘1’.

* Bit ACK/NACK: 

Viết tắt của Acknowledged / Not Acknowledged. Dùng để so sánh bit địa chỉ vật lý của thiết bị so với địa chỉ được gửi tới. Nếu trùng thì Slave sẽ được đặt bằng ‘0’ và ngược lại, nếu không thì mặc định bằng ‘1’.

* Khối bit dữ liệu: 

Gồm 8 bit và được thiết lập bởi thiết bị gửi truyền đến thiết bị nhân. Sau khi các bit này được gửi đi, lập tức 1 bit ACK/NACK được gửi ngay theo sau để xác nhận rằng thiết bị nhận đã nhận được dữ liệu thành công hay chưa. Nếu nhận thành công thì bit ACK/NACK được set bằng ‘0’ và ngược lại.

### Quá trình truyền nhận dữ liệu: 
![image](https://github.com/hnaht1126/STM32/assets/152061415/ba566af9-890b-42fe-a619-595675c32b17)

* Bắt đầu: Thiết bị Master sẽ gửi đi 1 xung Start bằng cách kéo lần lượt các đường SDA, SCL từ mức 1 xuống 0.
* Tiếp theo đó, Master gửi đi 7 bit địa chỉ tới Slave muốn giao tiếp cùng với bit Read/Write.
* Slave sẽ so sánh địa chỉ vật lý với địa chỉ vừa được gửi tới. Nếu trùng khớp, Slave sẽ xác nhận bằng cách kéo đường SDA xuống 0 và set bit ACK/NACK bằng ‘0’. Nếu không trùng khớp thì SDA và bit ACK/NACK đều mặc định bằng ‘1’.
* Thiết bị Master sẽ gửi hoặc nhận khung bit dữ liệu. Nếu Master gửi đến Slave thì bit Read/Write ở mức 0. Ngược lại nếu nhận thì bit này ở mức 1.
* Nếu như khung dữ liệu đã được truyền đi thành công, bit ACK/NACK được set thành mức 0 để báo hiệu cho Master tiếp tục.
* Sau khi tất cả dữ liệu đã được gửi đến Slave thành công, Master sẽ phát 1 tín hiệu Stop để báo cho các Slave biết quá trình truyền đã kết thúc bằng các chuyển lần lượt SCL, SDA từ mức 0 lên mức 1.

### Các chế độ hoạt động của I2C: 
* Chế độ chuẩn (standard mode) với tốc độ 100 kBit/s.
* Chế độ tốc độ thấp (low speed mode) với tốc độ 10 kBit/s.

## 4. UART

UART (Universal Asynchronous Receiver-Transmitter) là một giao thức truyền thông phần cứng dùng giao tiếp nối tiếp không đồng bộ.

Gồm hai đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận). 
* Hoạt động song công.
* **Không cần chân Clock**.

![image](https://github.com/hnaht1126/STM32/assets/152061415/19a4ef7e-c94f-4c2e-81d5-e8b8257fd030)

 dữ liệu được truyền đi theo các chu kỳ đồng hồ được đồng bộ giữa các thiết bị liên quan

Baudrate: tốc độ truyền.

Baudrate = số bits truyền/1s. 

Ví dụ: baudrate =9600:  9600bits / 1s
                       9600bits / 1000ms
                =>	   1 bit  = 0.10467 ms.

=>> Timer (0->  0.10467 ms)

## Quá trình truyền nhận UART

![image](https://github.com/hnaht1126/STM32/assets/152061415/7cadd59a-b2a2-4b50-a01e-acb3e5cd269f)

1. **Khởi tạo**: Cả thiết bị gửi và thiết bị nhận được `cấu hình về các thông số cơ bản như tốc độ baud, độ dài bit dữ liệu, kiểu stop bit, và kiểu điều kiển parity (nếu cần)`.

2. **Truyền dữ liệu**: `Thiết bị gửi` (thường được gọi là trình điều khiển UART hoặc UART controller) `sẽ chuyển dữ liệu vào bộ đệm truyền` (TX buffer). Khi có dữ liệu trong bộ đệm truyền, `UART controller sẽ bắt đầu chuyển dữ liệu bit theo thứ tự từ bit thấp nhất đến bit cao nhất (hoặc ngược lại) qua chân truyền (TX) đến thiết bị nhận`.

3. **Nhận dữ liệu**: `Thiết bị nhận` (thường là một UART controller khác hoặc một vi điều khiển) `sẽ theo dõi chân nhận (RX) để nhận dữ liệu từ thiết bị gửi. Dữ liệu nhận được sẽ được đưa vào bộ đệm nhận (RX buffer) để xử lý sau này`.

4. **Kiểm tra lỗi và xử lý**: Trong quá trình truyền nhận, các lỗi có thể xảy ra như mất dữ liệu, lỗi định dạng, hoặc lỗi parity. Trong trường hợp này, hệ thống có thể `thực hiện các biện pháp sửa lỗi hoặc báo lỗi cho người dùng`.

5. **Hoàn tất truyền nhận**: `Quá trình truyền nhận có thể kết thúc khi dữ liệu đã được truyền hoàn tất hoặc khi gặp điều kiện kết thúc được xác định trước` (ví dụ: gửi một ký tự kết thúc).

Giao diện UART thường được sử dụng trong các ứng dụng như truyền dữ liệu giữa vi điều khiển và các cảm biến, mô-đun không dây, hoặc truyền dữ liệu giữa vi điều khiển và máy tính.

### Quá trình hoạt động của các chân tín hiệu khi truyền dữ liệu bằng UART:

1. Chuẩn bị dữ liệu: 

* Trước khi bắt đầu truyền dữ liệu, dữ liệu cần được chuẩn bị bởi thiết bị gửi (thường là một vi điều khiển hoặc trình điều khiển UART).

2. Bắt đầu truyền dữ liệu:

* Thiết bị gửi đặt tín hiệu TX (chân truyền) ở mức logic cao.
* Tín hiệu TX cao này là một tín hiệu đồng bộ để bắt đầu truyền dữ liệu.
* Đồng thời, tín hiệu RX (chân nhận) của thiết bị nhận được đặt ở mức logic cao.

3. Truyền dữ liệu bit theo thứ tự:

* Dữ liệu được truyền bit theo thứ tự, bắt đầu từ bit thấp nhất đến bit cao nhất (hoặc ngược lại).
* Mỗi bit dữ liệu được chuyển đổi thành một tín hiệu điện áp (thường là mức logic cao hoặc thấp) trên chân truyền TX.
* Tín hiệu điện áp này thường thay đổi tại các khoảng thời gian được xác định trước, phụ thuộc vào tốc độ baud được cấu hình.

4. Tín hiệu stop bit:

* Sau khi truyền xong các bit dữ liệu, một hoặc nhiều bit stop được truyền. * Số bit stop và kiểu stop bit được cấu hình trước.
* Tín hiệu stop bit thường là mức logic cao trên chân truyền TX.

5. Kết thúc truyền dữ liệu:

* Sau khi truyền dữ liệu và stop bit, chân truyền TX sẽ quay về mức logic cao, chờ sẵn sàng để truyền dữ liệu tiếp theo (nếu có).

6. Nhận dữ liệu (đối với thiết bị nhận):

* Thiết bị nhận sẽ theo dõi chân nhận RX để nhận dữ liệu.
* Dữ liệu được đọc từ chân nhận RX theo các khoảng thời gian đã được xác định.

Quá trình này tiếp tục lặp lại cho mỗi lần truyền dữ liệu mới, và các thiết bị truyền và nhận cần phải được cấu hình đồng bộ với nhau để đảm bảo truyền nhận dữ liệu chính xác.

# Bài 9 ADC

## 1. ADC 
ADC Analog to Digital Convert là bộ chuyển đổi tương tự sang số. Điện áp Vin được so sánh với điện áp mẫu Vref (giá trị lớn nhât), sau đó được chuyển đổi thành số 

2 tham số quan trọng của bộ ADC 
- Tốc độ lấy mẫu (sampling) được tính theo số chu kỳ chuyển đổi. 
(
    Tần số lấy mẫu càng lớn thì tín hiệu sau khi chuyển đổi sẽ có độ chính xác càng cao. Khả năng tái tạo lại tín hiệu càng chính xác.

    Tần số lấy mẫu =1/(thời gian lấy mẫu+ Tg chuyển đổi.)
    
)

![image](https://github.com/hnaht1126/STM32/assets/152061415/6333eab6-523f-4945-b1b4-f43f25839080)

Tần số lấy mẫu phải lớn hơn tần số của tín hiệu ít nhất 2 lần để đảm bảo độ chính xác khi khôi phục lại tín hiệu.


- Độ phân giải: Số bit bộ ADC sử dụng để mã hóa tín hiệu.
(bộ ADC có độ phân giải 10 Bit sẽ có 2^10 = 1024 giá trị)

![image](https://github.com/hnaht1126/STM32/assets/152061415/2ee319c4-7b34-478e-ba7c-9efc95c4ef37)

ADC có độ phân giải càng cao thì cho ra kết quả chuyển đổi càng chi tiết. 

## 2. ADC trong STM32

STM32F103C8 có 2 kênh ADC đó là ADC1 và ADC2, mỗi kênh có tối đa là 9 channel 

Kết quả chuyển đổi được lưu trữ trong thanh ghi 16 bit. 

 - Độ phân giải 12 bit. (2^12= 4096 - điện áp 0 → 3.3V sẽ thành 0 → 4095 khoảng giá trị)

 - Có các ngắt hỗ trợ. (ngắt tại các sự kiện End of convert, End of Injected, Analog Watchdog)

 - Có thể điều khiển hoạt động ADC bằng xung Trigger. (Xung Trigger là một tín hiệu đặc biệt được sử dụng để bắt đầu hoặc kích hoạt một quá trình hoạt động)
 
 - Thời gian chuyển đổi nhanh : 1us tại tần số 65Mhz.
 
 - Có bộ DMA (Direct Memory Access - truyền dữ liệu giữa các thiết bị ngoại vi và bộ nhớ không cần thông qua trung gian của CPU ) giúp tăng tốc độ xử lí.
 
## 3. Cấu hình ADC

Cấp xung ADC: 
Các bộ ADC được cấp xung từ RCC APB2, để bộ ADC hoạt động cần cấp xung cho cả ADC để tạo tần số lấy mẫu tín hiệu và cấp xung cho GPIO của Port ngõ vào.

  ```c
// cấp xung cho ADC1 
void RCC_Config(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

  ```
Cấu hình GPIO:
ADC hỗ trợ rất nhiều kênh, mỗi kênh lấy tín hiệu từ các chân GPIO của các Port và từ các chân khác. Các chân GPIO dùng làm ngõ vào cho ADC sẽ được cấu hình Mode AIN.(Analogue Input).

```c
void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; // chân GPIO sử dụng làm đầu vào analog
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```
Các tham số cấu hình cho bộ ADC được tổ chức trong Struct ADC_InitTypeDef, Gồm:

    - ADC_Mode:  Cấu hình chế độ hoạt động cho ADC là đơn kênh(Independent) hay đa kênh, ngoài ra còn có các chế độ ADC chuyển đổi tuần tự các kênh (regularly) hay chuyển đổi khi có kích hoạt từ phần 
    mềm hay các tín hiệu khác (injected).
    
    - ADC_NbrOfChannel: Số kênh ADC để cấu hình
    
    - ADC_ContinuousConvMode: Cấu hình bộ ADC có chuyển đổi liên tục hay không, Enable để cấu hình ADC  chuyển đổi lien tục, nếu cấu hình Disable, ta phải gọi lại lệnh đọc ADC để bắt đầu quá trình chuyển 
    đổi. 
    
    - ADC_ExternalTrigConv: Enable để sử dụng tín hiệu trigger để kích 
    hoạt ADC, Disable nếu không sử dụng.
    
    - ADC_ScanConvMode: Cấu hình chế độ quét ADC lần lượt từng kênh. 
    Enable nếu sử dụng chế độ quét này.
    
    - ADC_DataAlign: Cấu hình căn lề cho data. Vì bộ ADC xuất ra giá trị 12bit, được lưu vào biến 16 hoặc 32 bit nên phải căn lề các bit về trái hoặc phải.

Các hàm thông dụng:

Ngoài các tham số trên, cần cấu hình thêm thời gian lấy mẫu, thứ tự kênh ADC khi quét,

    ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime):

- Rank: Thứ tự của kênh ADC.
- SampleTime: Thời gian lấy mẫu tín hiệu.
- ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState): Bắt đầu quá trình chuyển đổi.
- ADC_GetConversionValue(ADC_TypeDef* ADCx): Đọc giá trị chuyển đổi được ở các kênh ADC tuần tự.
- ADC_GetDualModeConversionValue(void): Trả về giá trị chuyển đổi cuối cùng của ADC1, ADC2 ở chế độ kép.

Cấu hình ADC:
```c
void ADC_Config(){
    ADC_InitTypeDef ADC_InitStruct;
    
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; // mode ADC hoạt động độc lập 
    ADC_InitStruct.ADC_NbrOfChannel = 1; // số kênh ADC sử dụng
    ADC_InitStruct.ADC_ScanConvMode = DISABLE; //vô hiệu chế độ quét - chế độ đơn 
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //không sử dụng tính hiệu ngoại vi kích hoạt chuyển đổi ADC
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;  // chế độ chuyển đổi liên tục 
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; // căn chỉnh dữ liệu về bên phải 
    
    ADC_Init(ADC1, &ADC_InitStruct); // cấu hình ADC1 với các thiết lập
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);  //đọc dữ liệu  kênh ADC 0, thời gian lấy mẫu 55.5 chu kỳ 
    ADC_Cmd(ADC1, ENABLE); // kích hoạt ADC1 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);  // ADC được khởi động bằng phần mềm
}

```

## ACD một kênh chế độ Single và Continuous

Với chế độ Single bộ ADC chỉ chuyển đổi 1 lần rồi dừng, một sự kiện ngắt được sinh ra nếu bit EOCIR được set lên 1

Với chế độ Continuous bộ ADC sẽ chuyển đổi liên tục, một sự kiện ngắt được sinh ra nếu bit EOCIR được set lên 1

DMA sẽ sinh ra nếu bit DMA dc set lên 1(DMA chỉ có trên ADC1 và ADC3)

Kết quả convert được lưu vào thanh ghi DR

Bắt đầu convert bằng cách set bit ADON lên 1

Cơ chế để tạo ADC như sau:

1. Enable bộ clock cho ADC, ghi hệ số chia cho ADC prescaler
2. Chọn các kênh cần chuyển đổi
3. Chọn chế độ chuyển đổi Sinlge, Continuous, Scan, Discontinuous
4. Chọn thời gian lấy mẫu (Sampling Time)
5. Chọn Ngắt hoặc DMA
6. Start bộ chuyển đổi
7. Kiểm tra cờ EOC hoặc trong ngắt đọc dữ liệu từ thanh ghi DR về

EOC: End Of Conversion - Kết thúc quá trình chuyển đổi. Đây là một cờ (flag) hoặc bit được set khi quá trình chuyển đổi hoàn thành.

DMA: Direct Memory Access - Truy cập bộ nhớ trực tiếp. DMA cho phép truyền dữ liệu giữa bộ nhớ và các thiết bị ngoại vi mà không cần sự can thiệp của CPU.

DR: Data Register - Thanh ghi dữ liệu. Trong ngữ cảnh của ADC, DR là nơi mà kết quả chuyển đổi analog-to-digital được lưu trữ.

# Bài 10 DMA
## 1. Truy cập bộ nhớ trực tiếp (DMA)
bộ điều khiển DMA có thể thực hiện truyền dữ liệu bộ nhớ sang bộ nhớ cũng như truyền dữ liệu ngoại vi sang bộ nhớ hoặc ngược lại.

    DMA có thể điều khiển data truyền từ :
    Bộ nhớ đến Peripheral 
    Ngược lại, Periph đến Bộ nhớ.
    Giữa 2 vùng nhớ.
    Không thông qua data bus  của CPU. 
    -> Giữ cho tài nguyên của CPU được rảnh rỗi cho các thao tác khác. Đồng thời tránh việc data nhận về từ ngoại vi bị mất mát.

![image](https://github.com/hnaht1126/STM32/assets/152061415/0ca4d2cc-1162-4f2e-abf6-5c2cf1d47ede)

Các đơn vị DMA trong STM32F103 có các tính năng sau:
- 12 kênh (yêu cầu) có thể cấu hình độc lập: 7 cho DMA1 và 5 cho DMA2
- Các Channel đều có thể được cấu hình riêng biệt.
- Mỗi Channel được kết nối để dành riêng cho tín hiệu DMA từ các thiết bị ngoại vi hoặc tín hiệu từ bên trong MCU.
- Có 4 mức ưu tiên có thể lập trình cho mỗi Channel.
- Kích thước data được sử dụng là 1 Byte, 2 Byte (Half Word) hoặc 4byte (Word). Địa chỉ nguồn/đích phải được căn chỉnh theo kích thước dữ liệu.
- Hỗ trợ việc lặp lại liên tục Data.
- 5 cờ báo ngắt (DMA Half Transfer, DMA Transfer complete, DMA Transfer Error, DMA FIFO Error, Direct Mode Error).
- Quyền truy cập tới Flash, SRAM, APB1, APB2, APB.
- Số lượng data có thể lập trình được lên tới 65535.
- Đối với DMA2, mỗi luồng đều hỗ trợ để chuyển dữ liệu từ bộ nhớ đến bộ nhớ.

![image](https://github.com/hnaht1126/STM32/assets/152061415/dfd6ae74-6879-4487-bb56-6d4a82930345)

## 2. Chế độ hoạt động 
DMA có 2 chế độ hoạt động là normal và circular:
-  Normal mode: Với chế độ này, DMA truyền dữ liệu cho tới khi truyền đủ 1 lượng dữ liệu giới hạn đã khai báo DMA sẽ dừng hoạt động. Muốn nó tiếp tục hoạt động thì phải khởi động lại
 
- Circular mode: Với chế độ này, Khi DMA truyền đủ 1 lượng dữ liệu giới hạn đã khai báo thì nó sẽ truyền tiếp về vị trí ban đầu (Cơ chế như Ring buffer).

## 3. Cấu hình STM32 DMA
cấp xung từ AHB:
cả 2 bộ DMA đều có xung cấp từ AHB. Ngoài ra cần cấp xung cho AFIO.

```c
void RCC_Config(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_SPI1| RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

```
Các tham số cho bộ DMA được cấu hình trong struct DMA_InitTypeDef. Gồm:

    - DMA_Mode: Cấu hình mode hoạt động.
    - DMA_DIR: Cấu hình hướng truyền DMA, từ ngoại vi tới vùng nhớ hay từ vùng nhớ tới ngoại vi.
    - DMA_M2M: Cấu hình sử dụng truyền từ bộ nhớ đếm bộ nhớ cho kênh DMA.
    - DMA_BufferSize: Cấu hình kích cỡ buffer. Số lượng dữ liệu muốn gửi/nhận qua DMA.
    - DMA_MemoryBaseAddr: Cấu hình địa chỉ vùng nhớ cần ghi/ đọc data .
    - DMA_MemoryDataSize: Cấu hình độ lớn data của bộ nhớ.
    - DMA_MemoryInc: Cấu hình địa chỉ bộ nhớ có tăng lên sau khi truyền DMA hay không.
    - DMA_PeripheralBaseAddr: Cấu hình địa chỉ của ngoại vi cho DMA. Đây là địa chỉ mà DMA sẽ lấy data hoặc truyền data tới cho ngoại vi.
    - DMA_PeripheralDataSize: Cấu hình độ lớn data của ngoại vi.
    - DMA_PeripheralInc: Cấu hình địa chỉ ngoại vi có tăng sau khi truyền - DMA hay không.
    - DMA_Priority: Cấu hình độ ưu tiên cho kênh DMA.

```c
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStruct.DMA_BufferSize = 35;
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)buffer;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
```

Sau khi cấu hình cho DMA xong, chỉ cần gọi hàm DMACmd cho ngoại vi tương ứng. Bộ DMA sẽ tự động truyền nhận data cũng như ghi dữ liệu vào vùng nhớ cụ thể. 

```c
    DMA_Init(DMA1_Channel2, &DMA_InitStruct);
    DMA_Cmd(DMA1_Channel2, ENABLE);
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
/* Channel2: Ứng với ngoại vi SPI1, RX nhận.
EX: Hàm SPI_I2S_DMACmd(); cho phép truyền nhận DMA của bộ SPI.
 */
```
