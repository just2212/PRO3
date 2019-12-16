////////////////////////////////////////////////////////////
//
// Source file	: ADXL345.cpp
// Author				: Nikolaj
// Date 				: 4 Dec 2019
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#include "ADXL345.h"


ADXL345::ADXL345 (unsigned short bus, unsigned short address ):
I2C(I2CBus, I2CAddress)
{
	this->I2CAddress = I2CAddress;
	this->I2CBus = I2CBus;
	this->accelX = 0;
	this->accelY = 0;
	this->accelZ = 0;
	this->registers = NULL;
	this->range = ADXL345::PLUSMINUS_16_G;
	this->resolution = ADXL345::HIGH;
	this->baud = ADXL345::BANDWITH_1600_Hz;
	this->writeRegister(BW_RATE, 0x0f);
	this->updateRegisters();

}

ADXL345::~ADXL345 ( )
{
	// TODO Auto-generated destructor stub
}

/**
 * Method to combine two 8-bit registers into a single short, which is 16-bits on the BBB. It shifts
 * the MSB 8-bits to the left and then ORs the result with the LSB.
 * @param msb an unsigned character that contains the most significant byte
 * @param lsb an unsigned character that contains the least significant byte
 */
short ADXL345::combineRegisters(unsigned char msb, unsigned char lsb){
   //shift the MSB left by 8 bits and OR with LSB
   return ((short)msb<<8)|(short)lsb;
}
/**
 * Method used to update the DATA_FORMAT register and any other registers that might be added
 * in the future.
 * @return 0 if the register is updated successfully
 */
int ADXL345::updateRegisters(){
   //update the DATA_FORMAT register
   char data_format = 0x00;  //+/- 2g with normal resolution
   //Full_resolution is the 3rd LSB
   data_format = data_format|((this->resolution)<<3);
   data_format = data_format|this->range; // 1st and 2nd LSB therefore no shift
   return this->writeRegister(DATA_FORMAT, data_format);
}

int ADXL345::setRange(ADXL345::RANGE range)
{
	this->range = range;
	if(updateRegisters() == 1) {
		perror("ADXL345: Failed write Range to register\n");
		return 1;
	}
	return 0;
}

int ADXL345::setResolution(ADXL345::RESOLUTION resulution)
{
	this->resolution = resulution;
	if(updateRegisters() == 1) {
		perror("ADXL345: Failed write resulotion to register\n");
		return 1;
	}
	return 0;
}

int ADXL345::setBWrate(ADXL345::BAUD baud)
{
	this->baud = baud;
	if(this->writeRegister(BW_RATE,baud) == 1) {
		perror("ADXL345: Failed write Baud rate to register\n");
		return 1;
	}
	return 0;

}
/**
 * Read the sensor state. This method checks that the device is being correctly
 * read by using the device ID of the ADXL345 sensor. It will read in the accelerometer registers
 * and pass them to the combineRegisters() method to be processed.
 * @return 0 if the registers are successfully read and -1 if the device ID is incorrect.
 */
int ADXL345::readSensorState(){
	this->registers = this->readRegisters(BUFFER_SIZE, 0x00);
	if(*this->registers!=0xe5){
		perror("ADXL345: Failure Condition - Sensor ID not Verified");
		return -1;
	}
	this->accelX = this->combineRegisters(*(registers+DATAX1), *(registers+DATAX0));
	this->accelY = this->combineRegisters(*(registers+DATAY1), *(registers+DATAY0));
	this->accelZ = this->combineRegisters(*(registers+DATAZ1), *(registers+DATAZ0));
	this->resolution = (ADXL345::RESOLUTION) (((*(registers+DATA_FORMAT))&0x08)>>3);
	this->range = (ADXL345::RANGE) ((*(registers+DATA_FORMAT))&0x03);
	return 0;
}
