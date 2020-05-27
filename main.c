

/**
 * main.c
 */

#include"stdtypes.h"
#include"util.h"
#include"Timer0.h"
#include"GPIO.h"
#include"UART .h"
#include"ultrasonic.h"
#include"PWM.h"


u8 res1 = 0 ;

u32 dist1 = 0;
u32 dist2 = 0;

u8 motorA1;
u8 motorA2;
 /*  Speed changes from change duty 0 to 1  */

int main(void)
{
    PWM_Init();

    GPIO_Initialize_Port(PD);
    GPIO_Set_Pin_Direction(PD, PIN0, OUT);          //MotorA1
    GPIO_Set_Pin_Direction(PD, PIN1, OUT);          //MotorA2

    GPIO_Set_Pin_Direction(PD, PIN2, OUT);          //streeingMotor1
    GPIO_Set_Pin_Direction(PD, PIN3, OUT);          //streeingMotor2


    GPIO_Initialize_Port(PA);
    GPIO_Set_Pin_Direction(PA, PIN2, OUT);
    GPIO_Set_Pin_Direction(PA, PIN3, OUT);
    UART_Initialization();
    Timer2_Count_Init();
    Timer3_Count_Init();

    while(1){

        dist1 = ultrasonic_1();
        Timer0_Delay(100);
        dist2 = ultrasonic_2();
        Timer0_Delay(100);


        if (dist1 > 100 && dist2 > 100){

            //forward
            change_duty(0.9);                   //MA1
            GPIO_Write_Pin(PD, PIN1, LOWV);     //MA2


//            change_duty(1);     //PB6 for enable pin


        }

        else{
//            change_duty(0.1);                   //MA1
//            GPIO_Write_Pin(PD, PIN1, HIGHV);     //MA2

            GPIO_Write_Pin(PD, PIN2, HIGHV);            //right
            GPIO_Write_Pin(PD, PIN3, LOWV);
                                                        //forward
            change_duty(0.9);                   //MA1
            GPIO_Write_Pin(PD, PIN1, LOWV);     //MA2

//            change_duty(0);     //PB6 for enable pin

        }

    }

    return 0;
}



void UART3_Handler()
{

    if(GET_BIT(UARTMIS,4)==1) //checking if an receive interrupt has occurred
    {
        res1=read();
        SET_BIT(UARTICR,4); // clearing the receive flag bit by setting corresponding bit in this register
    }
    if(GET_BIT(UARTMIS,5)==1) //checking if an transmit interrupt has occurred
    {

        SET_BIT(UARTICR,5); // clearing the transmit flag bit by setting corresponding bit in this register
    }
}

