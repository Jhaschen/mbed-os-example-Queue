/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


DigitalOut led0(D2);
DigitalOut led1(D3);
DigitalOut led2(D4);

//------------------------------------------------------------------------------

Queue<uint8_t,1>Queue12;
Queue<uint8_t,1>Queue23;
Queue<uint8_t,1>Queue31;


void Task_1(void) // Task 1
{
    uint8_t Q31;
    Queue12.try_put(&Q31);
    
    while(1) {

        osEvent event = Queue31.get();
        ThisThread::sleep_for(100ms);
        led0=!led0;
        Queue12.try_put(&Q31);



    }
}

void Task_2(void )    // Task 2
{
    uint8_t Q12;
    while(1) {
        osEvent event = Queue12.get();
        ThisThread::sleep_for(100ms);
        led1=!led1;
        Queue23.try_put(&Q12);
    }

}

void Task_3(void)  // Task 3
{
    uint8_t Q23;
    while(1) {
        osEvent event =Queue23.get();
        ThisThread::sleep_for(100ms);
        led2=!led2;
        Queue31.try_put(&Q23);
    }


}




//------------------------------------------------------------------------------
//  Funktionsdefinition:
//------------------------------------------------------------------------------
int main()
{
    
        
    Thread thread_Task_1(osPriorityNormal, OS_STACK_SIZE, NULL, NULL); // Task 1 Thread mit default Einstellungen initialisieren
    Thread thread_Task_2(osPriorityNormal, OS_STACK_SIZE, NULL, NULL); // Task 2 Thread mit default Einstellungen initialisieren
    Thread thread_Task_3(osPriorityNormal, OS_STACK_SIZE, NULL, NULL); // Task 3 Thread mit default Einstellungen initialisieren



    
    thread_Task_1.start(Task_1);  // Thread mit der Funktion Task_1 und dem Argument NULL aufrufen
    thread_Task_2.start(Task_2);  // Thread mit der Funktion Task_2 und dem Argument NULL aufrufen
    thread_Task_3.start(Task_3);  // Thread mit der Funktion Task_3 und dem Argument NULL aufrufen


    while(1) {
        ThisThread::sleep_for(2000ms);
    }
}
