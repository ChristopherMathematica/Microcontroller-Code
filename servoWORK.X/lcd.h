#define LCDDATA 1       // RS = 1 ; access data register 
#define LCDCMD 0        // RS = 0 ; access command register 
#define PMDATA PMDIN   // PMP data buffer   
#define busyLCD() readLCD( LCDCMD)  &  0x80 
#define addrLCD() readLCD( LCDCMD)  &  0x7F 
#define getLCD() readLCD( LCDDATA)
#define putLCD( d)  writeLCD( LCDDATA, (d))     
#define cmdLCD( c)  writeLCD( LCDCMD, (c))     
#define homeLCD()   writeLCD( LCDCMD, 2)     
#define clrLCD()    writeLCD( LCDCMD, 1)  
void initLCD(void);
char readLCD( int addr);
void writeLCD( int addr, char c);
void putsLCD( char *s);
void secondLine(void);
