#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
#include "acl.h"
#define I2C_WAIT_TIMEOUT 0x0FFF
float gConversionRange;   
//Config_bits
//#pragma config JTAGEN = OFF     
//#pragma config FWDTEN = OFF      
//#pragma config FNOSC =	FRCPLL
//#pragma config FSOSCEN =	OFF
//#pragma config POSCMOD =	XT
//#pragma config OSCIOFNC =	ON
//#pragma config FPBDIV =     DIV_2
//#pragma config FPLLIDIV =	DIV_2
//#pragma config FPLLMUL =	MUL_20
//#pragma config FPLLODIV =	DIV_1

void I2C_Init(void){
    I2C1CON = 0;           
    I2C1BRG = 40000000 / (2 * 400000) - 2;;
    I2C1CONbits.ON = 1;   
    I2C1CONbits.ACKEN = 1;
}


unsigned char i2cWriteMultipleBytes(unsigned char memoryAddress,
                        unsigned char* dataBuffer,
                        unsigned char bytesNumber,
                        unsigned char lastBit){
    unsigned char update = 0;
    unsigned char ack = 0;
    unsigned char specifiedB = 0;
    I2C1CONbits.SEN = 1;            //Initiate a start condition
    
    
    while(I2C1CONbits.SEN);   // Wait for start condition    
    I2C1TRN = memoryAddress << 1;    //RW bit set to 0
    while(I2C1STATbits.TRSTAT);   //Wait for conversion 
    ack = I2C1STATbits.ACKSTAT;
    if(ack == 0){          //Acknowledge
        for(specifiedB = 0; specifiedB < bytesNumber; specifiedB++)
        {
            I2C1TRN = dataBuffer[specifiedB];
            while(I2C1STATbits.TRSTAT); // Wait for conversion
        }
    } else{
        update = 0xFF;
    }
    if(lastBit){
        I2C1CONbits.PEN = 1;//stop condition
        while(I2C1CONbits.PEN);
    }

    return update;
}

unsigned char i2cReadMultipleBytes(unsigned char memoryAddress,
                    unsigned char* dataBuffer,
                    unsigned char bytesNumber){
    unsigned char update = 0;
    unsigned char ack = 0;
    unsigned char specifiedB = 0;
    I2C1CONbits.RSEN = 1;            // Initiate a start condition
    while(I2C1CONbits.RSEN);         //Wait for start condition 
    I2C1TRN = (memoryAddress << 1) + 1;
    while(I2C1STATbits.TRSTAT);     // Wait for reception
    ack = I2C1STATbits.ACKSTAT;
    if(ack == 0){            //Acknowledge
        for(specifiedB = 0; specifiedB < bytesNumber; specifiedB++){
           I2C1CONbits.RCEN = 1;       //Enable receive mode for I2C
            if(specifiedB == (bytesNumber - 1)){
                I2C1CONbits.ACKDT = 1;
            }
            else{
                I2C1CONbits.ACKDT = 0;
            }
            while(I2C1CONbits.RCEN);    //Wait for reception to complete
            dataBuffer[specifiedB] = I2C1RCV;
            I2C1CONbits.ACKEN = 1;
            while(I2C1CONbits.ACKEN); 
        }
    }
    else{
        update = 0xFF;
    }
    I2C1CONbits.ACKEN = 1;          //Initiate Acknowledge sequence  
    I2C1CONbits.PEN = 1;            //Initiate a stop condition 
    while(I2C1CONbits.PEN);         //Wait for stop condition

    return update;
}

void InitAccelerometer()
{
    TRISGbits.TRISG0 = 1;
    I2C_Init();
    AccelerometerMemoryRange();
    AccelerometerSetReg(0x2A, 1);        
}

unsigned char AccelerometerSetReg(unsigned char bAddress, unsigned char bValue)
{
    unsigned char rgVals[2], bResult;
    rgVals[0] = bAddress;       // register address
    rgVals[1] = bValue;         // register value
    
    bResult = i2cWriteMultipleBytes(0x1D, rgVals, 2, 1);

    return bResult;
}


unsigned char AccelerometerMemoryRange(void){
    unsigned char aResult, aAddress = 0x0E;
    unsigned char bResult, y, bRange = 0;
    bRange &= 3;    // only 2 least significant bits from bRange are used
    i2cWriteMultipleBytes(0x1D, &aAddress, 1, 0);
    i2cReadMultipleBytes(0x1D, &aResult, 1);

    
    y = aResult; 
    y &= 0xFC;   // mask out the 2 LSBs
    y |= bRange; 
    bResult = AccelerometerSetReg(0x0E, y);

 
    unsigned char bValRange = 1<<(bRange + 2);
    gConversionRange = ((float)bValRange)/(1<<12);     // the range is divided to the resolution
    return bResult;
}

void AccelerometerMemory(unsigned char *rgRawVals)
{
    unsigned char bVal = 0x01;
    
    i2cWriteMultipleBytes(0x1D, &bVal, 1, 0);
    i2cReadMultipleBytes(0x1D, rgRawVals, 6);
}


float ACL_ConvertRawToValueG(unsigned char *rgRawVals){
    unsigned short unsignedReading = (((unsigned short)rgRawVals[0]) << 4) + (rgRawVals[1] >> 4);
    if(unsignedReading & (1<<11)){
        unsignedReading |= 0xF000;
    }
    float fResult = ((float)((short)unsignedReading)) * gConversionRange;
    return fResult;
}

void ACL_ReadGValues(float *rgGVals)
{
    unsigned char rgRawVals[6];
    AccelerometerMemory(rgRawVals);
    rgGVals[0] = ACL_ConvertRawToValueG(rgRawVals);
    rgGVals[1] = ACL_ConvertRawToValueG(rgRawVals + 2);
    rgGVals[2] = ACL_ConvertRawToValueG(rgRawVals + 4);
}


void DisplayAccelerometerToUART(void){
    float rgACLGVals[3];  
    char strMsg[120];    
    InitAccelerometer();
    initU4();

    while(1)
    {
            ACL_ReadGValues(rgACLGVals);
//            sprintf(strMsg, "X:%6.3f Y:%6.3f Z:%6.3f",rgACLGVals[0],rgACLGVals[1],rgACLGVals[2]);
            putsU4(strMsg);           
            delay_ms(10);
    }  
}
