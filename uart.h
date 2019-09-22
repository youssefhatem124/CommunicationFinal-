
#ifndef UART_H_
#define UART_H_

extern volatile uint8_t seconds;
extern volatile uint8_t mintues;
extern volatile uint8_t hours;
extern volatile uint8_t speed;
extern volatile uint8_t flag;


void UART0_Init(void);
void UART1_Init(void);
void UART3_Init(void);
void UART1_Send(const uint8_t a_Data);
void UART3_Send(const uint8_t a_Data);



#endif /* UART_H_ */
