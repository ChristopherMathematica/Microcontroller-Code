/*adc.h
 
 initADC --- for ADC initialization
 readADC --- read ADC data
 

 */

void initADC(void);
int readADC (void);
void delay(int a);
void initU4(void);
int putU4 (int c);
char getU4 (void);
int putsU4(char *s);
int string_number(char *s);
char *getsU4(char *s, int len);