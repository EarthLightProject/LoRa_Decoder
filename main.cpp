#include "mbed.h"

Serial A(D1,D0);
Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut led(LED1);
DigitalIn SW1(PA_1);
DigitalOut LED_G(PA_15);
//DigitalOut LED_Y(D7);
//DigitalOut LED_R(D9);

unsigned char dta[100];
unsigned char len = 0;

void pc_Get(){
    //LED_R=1;
    A.putc(pc.getc());
    }
    
void A_Get(){
    //LED_Y=1;
    pc.putc(A.getc());
    }
    
int main()
{
    pc.baud(115200);
    A.baud(115200);
    //LED_G=1;
    pc.attach(&pc_Get,Serial::RxIrq);
    A.attach(&A_Get,Serial::RxIrq);         //Radi受信割り込み
    pc.printf("SC-4 Ground Station Start!\r\n");
    while(1){
       if(SW1 == 1){
            LED_G = 1;
            while(SW1==1);
            pc.printf("REIG\r\n");
            LED_G = 0;
           }
    }
}

