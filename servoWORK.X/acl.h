/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    acl.h

  @Description
        This file groups the declarations of the functions that implement
        the ACL library (defined in acl.c).
        Include the file in the project when this library is needed.
        Use #include "acl.h" in the source files where the functions are needed.
 */
/* ************************************************************************** */

#ifndef _ACL_H    /* Guard against multiple inclusion */
#define _ACL_H


// function prototypes
void InitAccelerometer();
void AccelerometerMemory(unsigned char *rgRawVals);
void ACL_ReadGValues(float *rgGVals);
unsigned char AccelerometerMemoryRange(void);
float ACL_ConvertRawToValueG(unsigned char *rgRawVals);
unsigned char AccelerometerSetReg(unsigned char bAddress, unsigned char bValue);
unsigned char ACL_GetRegister(unsigned char bAddress);
void ACL_ConfigurePins(void);
//private functions:
void I2C_Init();
unsigned char i2cWriteMultipleBytes(unsigned char slaveAddress,
                        unsigned char* dataBuffer,
                        unsigned char bytesNumber,
                        unsigned char stopBit);
unsigned char i2cReadMultipleBytes(unsigned char slaveAddress,
                    unsigned char* dataBuffer,
                    unsigned char bytesNumber);

void DisplayAccelerometerToUART(void);

//#ifdef __cplusplus
//extern "C" {
//#endif



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************



    /* Provide C++ Compatibility */
//#ifdef __cplusplus
//}
//#endif
#endif /* _ACL_H */

/* *****************************************************************************
 End of File
 */
