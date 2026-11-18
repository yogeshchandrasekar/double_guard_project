	void I2C_INIT(void){
		PINSEL0|=0x50;
		I2SCLL=75;
		I2SCLH=75;
		I2CONCLR=0X6C;
		I2CONSET=(1<<6);
	}
	void I2C_START(void){
		I2CONSET=(1<<5);
		while(((I2CONSET>>3)&1)==0);
		I2CONCLR=(1<<5);
	}
		void I2C_RESTART(void){
		I2CONSET=(1<<5);
		I2CONCLR=(1<<3);
		while(((I2CONSET>>3)&1)==0);
		I2CONCLR=(1<<5);
	}
	void I2C_WRITE(unsigned char dat){
		I2DAT=dat;
		I2CONCLR=(1<<3);
		while(((I2CONSET>>3)&1)==0);
	}
	void I2C_STOP(void){
		I2CONSET=(1<<4);
		I2CONCLR=(1<<3);
	}
	unsigned char I2C_NACK(void){
		I2CONCLR=(1<<2);
		I2CONCLR=(1<<3);
		while(((I2CONSET>>3)&1)==0);
		return I2DAT;
	}
	unsigned char i2c_masterack(void)
{	
	I2CONSET = 0x04; 
  I2CONCLR = (1<<3);
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR = 0x04;
 	return I2DAT;
}	
