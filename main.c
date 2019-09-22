//*****************************************************************************

//*****************************************************************************/
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

#include "button.h"
#include "uart.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif



int main(void)
{
    uint8_t start_seconds;
    uint8_t start_mintues;
    uint8_t start_hours;
    uint8_t start_speed;
    uint8_t end_seconds;
    uint8_t end_mintues;
    uint8_t end_hours;
    uint8_t end_speed = 0;
    uint32_t speed_avg;
    uint32_t total_sec_start;
    uint32_t total_sec_end;
    uint32_t distance;

    UART0_Init();
    UART1_Init();
    Button_Init();

    while(1)
    {
        switch(flag)
        {
        case 1:
            start_seconds = seconds;
            break;

        case 2:
            start_mintues = mintues;
            break;

        case 3:
            start_hours = hours;
            break;

        case 4:
            start_speed = speed;
            break;

        case 5:
            end_seconds = seconds;
            break;

        case 6:
            end_mintues = mintues;
            break;

        case 7:
            end_hours = hours;
            break;

        case 8:
            end_speed = speed;
            break;
        }
        if(end_speed != 0)
        {
            speed_avg =  (end_speed + start_speed)/2;

            total_sec_start = start_hours*3600 + start_mintues*60 + start_seconds;
            total_sec_end = end_hours*3600 + end_mintues*60 + end_seconds;
            distance = (speed_avg*(total_sec_end-total_sec_start));
            UARTprintf(distance);
        }

    }
}
