//地上局用
#include "mbed.h"

Serial LoRa ( D1 , D0);
Serial pc(SERIAL_TX , SERIAL_RX);
DigitalOut ledY(PB_3);
DigitalOut ledB(PB_4);
DigitalOut ledR(PA_15);
DigitalOut LoRaRESET(PA_8);
DigitalOut Button1(PB_1);
DigitalOut Button2(PB_0);
DigitalOut Button3(PA_1);

uint8_t read_c[40];
int count=0 , timer_r=0;
char c;


void LoRa_Get();

int main()
{
    int16_t Temp;
    uint16_t Hum , Press;
    long Lat , Long , Alt;
    int16_t RSSI;
    uint8_t data_length=1;
    LoRa.baud(115200);
    pc.baud(9600);
    LoRaRESET=1;
    wait(4);
    pc.printf("LoRa decoder\r\n");
    //pc.printf("Lat,Long,Alt,Temp,Hum,Press,RSSI\r\n");
    LoRa.attach(&LoRa_Get,Serial::RxIrq);
    while(1) 
    {
        for (timer_r=0; timer_r<10; timer_r++)
        {
            wait(0.01);
        }
        if( read_c[0]+1 == count)
        {
            for(int i=1; i<5; i++)
            {
                if(read_c[i] > 57) read_c[i]=read_c[i]- 55;
                else read_c[i]=read_c[i] - 48;
            }
            
            RSSI = (int16_t)((read_c[1]<<12)+(read_c[2]<<8)+(read_c[3]<<4)+read_c[4]);
            Temp = read_c[6];
            Temp = (Temp<<8)+read_c[5];
            Hum = read_c[8];
            Hum = (Hum<<8)+read_c[7];
            Press = read_c[10];
            Press = (Press<<8)+read_c[9];
            Lat = (long)((read_c[14]<<24)+(read_c[13]<<16)+(read_c[12]<<8)+read_c[11]);
            Long = (long)((read_c[18]<<24)+(read_c[17]<<16)+(read_c[16]<<8)+read_c[15]);
            Alt = (long)((read_c[22]<<24)+(read_c[21]<<16)+(read_c[20]<<8)+read_c[19]);
            
            //Amulapo Ver
            pc.printf("%d.%d,",Temp/100,abs(Temp%100)); 
            pc.printf("%u.%u,",Hum/100,Hum%100);
            pc.printf("%u.%u,",Press/10,Press%10);
            pc.printf("%ld.%ld,",Lat/10000000,Lat%10000000);
            pc.printf("%ld.%ld,",Long/10000000,Long%10000000);
            pc.printf("%ld.%ld",Alt/1000,Alt%1000);
            pc.printf(",%d",RSSI);
            pc.printf("\r\n");
            
            //船Ver
            /*
            pc.printf("%ld:%ld:%ld.%ld,",Lat/10000000,(Lat%10000000)*60/10000000,(Lat%10000000)*60%10000000*60/10000000,(Lat%10000000)*60%10000000*60%10000000/100);
            pc.printf("%ld:%ld:%ld.%ld,",Long/10000000,(Long%10000000)*60/10000000,(Long%10000000)*60%10000000*60/10000000,(Long%10000000)*60%10000000*60%10000000/100);
            pc.printf("%ld.%ld,",Alt/1000,Alt%1000);
            pc.printf("%d.%d,",Temp/100,abs(Temp%100));
            pc.printf("%u.%u,",Hum/100,Hum%100);
            pc.printf("%u.%u,",Press/10,Press%10);
            pc.printf("%d",RSSI);
            pc.printf("\r\n");
            */
        }
        else if(count>40) NVIC_SystemReset();    //割り込み受信暴走リセット
        count=0;
        if(Button3==1){
            ledY = 1;
            while(Button3==1);
            LoRa.putc(data_length);
            LoRa.putc('R');
            ledY = 0;
        }
    }
}

void LoRa_Get(){
    timer_r=0;
    ledB=1;
    c=LoRa.getc();
    read_c[count]=c;
    count++;
    ledB=0;
    }
