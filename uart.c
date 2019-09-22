

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "inc/hw_uart.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/interrupt.h"
#include"driverlib/timer.h"


volatile uint8_t seconds;
volatile uint8_t mintues;
volatile uint8_t hours;
volatile uint8_t speed;
volatile uint8_t flag = 0;


void UART1_Handler(void);
void UART3_Handler(void);

void UART0_Init(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Wait for the GPIOB module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    //
    // Enable UART0
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Wait for the UART1 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    //
    // Configure GPIO Pins for UART mode.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

void UART1_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    // Wait for the GPIOB module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    // Wait for the UART1 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1));

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // Configure the UART for 115200, 8-N-1 operation.
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));

    UARTIntRegister(UART1_BASE, UART1_Handler);

    // Enable the UART1 interrupt.
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
}

void UART1_Send(const uint8_t a_Data)
{
    // Write the character to the UART.
    UARTCharPutNonBlocking(UART1_BASE, a_Data);
}

void UART1_Handler(void)
{
    flag++;
    if(flag == 8)
    {
        flag = 0;
    }
    static uint8_t i = 0;
    UARTIntClear(UART1_BASE, UART_INT_RX | UART_INT_RT);
    while(UARTCharsAvail(UART1_BASE))
    {
        switch(i)
        {
        case 0:
            seconds = UARTCharGet(UART1_BASE);
            i++;
            break;

        case 1:
            mintues = UARTCharGet(UART1_BASE);
            i++;
            break;


        case 2:
            hours = UARTCharGet(UART1_BASE);
            i++;
            break;


        case 3:
            speed = UARTCharGet(UART1_BASE);
            i++;
            break;
        }
    }
}


/*
void UART3_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // Wait for the GPIOC module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    // Wait for the UART3 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART3));

    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    // Configure the UART3 for 115200, 8-N-1 operation.
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));

    UARTIntRegister(UART3_BASE, UART3_Handler);
    // Enable the UART3 interrupt.
    IntEnable(INT_UART3);
    UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);

}


void UART3_Send(const uint8_t a_Data)
{
    // Write the character to the UART.
    UARTCharPutNonBlocking(UART3_BASE, a_Data);
}

void UART3_Handler(void)
{
    UARTIntClear(UART1_BASE, UART_INT_RX | UART_INT_RT);
    if(UARTCharsAvail(UART3_BASE))
    {
        if(UARTCharGet(UART3_BASE) == '#')
        {
            UARTprintf("send time\n");
            UARTCharPut(UART3_BASE, Time);
            UARTCharPut(UART3_BASE, Speed);
        }
    }
}


void UART3_Handler(void)
{
    static uint8_t i = 0;
    UARTIntClear(UART3_BASE, UART_INT_RX | UART_INT_RT);
    while(UARTCharsAvail(UART3_BASE))
    {
        switch(i)
        {
        case 0:
            seconds = UARTCharGet(UART3_BASE);
            i++;
            break;

        case 1:
            mintues = UARTCharGet(UART3_BASE);
            i++;
            break;


        case 2:
            hours = UARTCharGet(UART3_BASE);
            i++;
            break;


        case 3:
            speed = UARTCharGet(UART3_BASE);
            i++;
            break;
        }
    }
}

*/

