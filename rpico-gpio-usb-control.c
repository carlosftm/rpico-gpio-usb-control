/**
 *  Serial GPIO Controller
 * 
 *  Nokia - CTM
 * 
 *  v0.1
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define STATE_WAIT_START_CMD    0
#define STATE_WAIT_CMD          1
#define STATE_WAIT_VALUE        2
#define STATE_DO_ACTION         3

#define ACTION_LED              0
#define ACTION_RELAY            1
#define ACTION_GPIO             2

const uint32_t LED = 25;
const uint32_t RELAY = 15;
const uint32_t GPIO0 = 0;
const uint32_t GPIO1 = 1;
const uint32_t GPIO2 = 2;
const uint32_t GPIO3 = 3;

void printInfo(void) {
    printf("********************************************************\n");
    printf("* Serial GPIO Controller\n");
    printf("********************************************************\n");
    printf("* Press '>' to enter a command followed by an argument. \n");
    printf("* \n");
    printf("* - Command 'r' or 'R': Controls the relay GPIO %d\n", RELAY);
    printf("*   Aeguments: 0 = Normal Close\n");
    printf("*              1 = Normal Open\n");
    printf("*\n");
    printf("* - Command 'l' or 'L': Controls OnBoard LED\n");
    printf("*   Aeguments: 0 = LED off \n");
    printf("*              1 = LED on  \n");
    printf("*\n");
    printf("* - Command '0','1','2','3': Controls GPIO 0, 1, 2 & 3\n");
    printf("*   Aeguments: 0 = GPIO Low \n");
    printf("*              1 = GPIO High  \n");
    printf("********************************************************\n\n");
}

int main() {
    
    gpio_init(LED);
    gpio_init(RELAY);
    gpio_init(GPIO0);
    gpio_init(GPIO1);
    gpio_init(GPIO2);
    gpio_init(GPIO3);
    
    gpio_set_dir(LED, GPIO_OUT);
    gpio_set_dir(RELAY, GPIO_OUT);
    gpio_set_dir(GPIO0, GPIO_OUT);
    gpio_set_dir(GPIO1, GPIO_OUT);
    gpio_set_dir(GPIO2, GPIO_OUT);
    gpio_set_dir(GPIO3, GPIO_OUT);

    // All GPIO set to 'high' by default
    gpio_put(LED, 1);
    gpio_put(RELAY, 1);
    gpio_put(GPIO0, 1);
    gpio_put(GPIO1, 1);
    gpio_put(GPIO2, 1);
    gpio_put(GPIO3, 1);

    stdio_init_all();
    
    //Blink Led to indicate user of BootUp
    uint32_t cnt = 0;
    while (cnt++ < 4) {
        gpio_put(LED,0);
        sleep_ms(500);
        gpio_put(LED,1);
        sleep_ms(500);
    }
    cnt = 0;
    while (cnt++ < 40) {
        gpio_put(LED,0);
        sleep_ms(50);
        gpio_put(LED,1);
        sleep_ms(25);
    }
        
    uint32_t fsmState = STATE_WAIT_START_CMD;
    uint32_t fsmAction = 0;
    uint32_t fsmGpioNum = 0;
    int8_t rxChar;
    cnt = 0;
    
    printInfo();

    while (true)
    {
        rxChar = getchar_timeout_us(0);
        if (rxChar != PICO_ERROR_TIMEOUT )
        {

            switch(fsmState)
            {
                
                case STATE_WAIT_START_CMD:
                    if (rxChar == '>')
                    {
                        printf("\n> Enter command ('r' = relay, 'l' = led, '0' to '3' = GPIO0 to GPIO3): ");
                        fsmState = STATE_WAIT_CMD;
                    }
                    else if (rxChar == '?')
                    {
                        printInfo();
                    }
                    else
                    {
                        printf("Type '?' for info\n");
                    }
                break;

                case STATE_WAIT_CMD:
                    if ( (rxChar == 'r') || (rxChar == 'R') )
                    {
                        printf(" %c\n  (0 = NC, 1 = NO ) > ", rxChar);
                        fsmAction = ACTION_RELAY;
                        fsmState = STATE_DO_ACTION;
                    }
                    else if ( (rxChar == 'l') || (rxChar == 'L') )
                    {
                        printf(" %c\n  (0 = OFF, 1 = ON ) > ", rxChar);
                        fsmAction = ACTION_LED;
                        fsmState = STATE_DO_ACTION;
                    }
                    else if ( (rxChar == '0') )
                    {
                        printf(" %c\n  (0 = OFF, 1 = ON ) > ", rxChar);
                        fsmGpioNum = GPIO0;
                        fsmAction = ACTION_GPIO;
                        fsmState = STATE_DO_ACTION;
                    }
                    else if ( (rxChar == '1') )
                    {
                        printf(" %c\n  (0 = OFF, 1 = ON ) > ", rxChar);
                        fsmGpioNum = GPIO1;
                        fsmAction = ACTION_GPIO;
                        fsmState = STATE_DO_ACTION;
                    }
                    else if ( (rxChar == '2') )
                    {
                        printf(" %c\n  (0 = OFF, 1 = ON ) > ", rxChar);
                        fsmGpioNum = GPIO2;
                        fsmAction = ACTION_GPIO;
                        fsmState = STATE_DO_ACTION;
                    }
                    else if ( (rxChar == '3') )
                    {
                        printf(" %c\n  (0 = OFF, 1 = ON ) > ", rxChar);
                        fsmGpioNum = GPIO3;
                        fsmAction = ACTION_GPIO;
                        fsmState = STATE_DO_ACTION;
                    }
                    else
                    {
                        printf("\n  ERROR: %c is an invalid command \n\n", rxChar);
                        fsmState = STATE_WAIT_START_CMD;
                    }
                break;

                case STATE_DO_ACTION:
                    if ( fsmAction == ACTION_RELAY )
                    {
                        if (rxChar == '0')
                        {
                            printf(" %c\n  RELAY = NC \n");
                            gpio_put(RELAY, 1);
                            fsmState = STATE_WAIT_START_CMD;
                        }
                        else if (rxChar == '1')
                        {
                            printf(" %c\n  RELAY = NO \n");
                            gpio_put(RELAY, 0);
                            fsmState = STATE_WAIT_START_CMD;
                        }
                        else
                        {
                            printf("\n  ERROR: %c is an invalid parameter \n\n", rxChar);
                        }
                    }
                    else if ( fsmAction == ACTION_LED )
                    {
                        if (rxChar == '0')
                        {
                            printf(" %c\n  LED = OFF \n");
                            gpio_put(LED, 0);
                            fsmState = STATE_WAIT_START_CMD;
                        }
                        else if ( rxChar == '1' )
                        {
                            printf(" %c\n  LED = ON \n");
                            gpio_put( LED, 1 );
                            fsmState = STATE_WAIT_START_CMD;
                        }
                        else
                        {
                            printf("\n  ERROR: %c is an invalid parameter \n\n", rxChar);
                        }
                    }
                    else if ( fsmAction == ACTION_GPIO )
                    {
                        if (rxChar == '0')
                        {
                            printf(" %c\n  GPIO%d = LOW \n", rxChar, fsmGpioNum);
                            gpio_put(fsmGpioNum, 0);
                            fsmState = STATE_WAIT_START_CMD;
                        }
                        else if ( rxChar == '1' )
                        {
                            printf(" %c\n  GPIO%d = HIGH \n", rxChar, fsmGpioNum);
                            gpio_put( fsmGpioNum, 1 );
                            fsmState = STATE_WAIT_START_CMD;
                        }
                        else
                        {
                            printf("\n  ERROR: %c is an invalid parameter \n\n", rxChar);
                        }
                    }
                    else
                    {
                        printf("\n  ERROR: %c is an invalid parameter \n\n", rxChar);
                    }
                    fsmState = STATE_WAIT_START_CMD;
                break;
                
                default:
                    fsmState = STATE_WAIT_START_CMD;;
            }
        }
        sleep_ms(100);
    }

    return 0;

}
    

