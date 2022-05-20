#define RS 0x01				 	//RS -> PB0 (0x01)
#define EN 0x04  		 	 	//EN -> PB2 (0x04)

void LCD_Write4bits(unsigned char data, unsigned char control);

void LCD4bits_Data(unsigned char data);

void LCD4bits_Cmd(unsigned char command);

void LCD4bits_Init(void);

void LCD_WriteString(char* str);

void Cursor_Left(int n);

void Cursor_Right(int n);










	
