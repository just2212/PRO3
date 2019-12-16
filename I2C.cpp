////////////////////////////////////////////////////////////
//
// Source file	: I2C.cpp
// Author				: Nikolaj
// Date 				: 3 Dec 2019
// Version 			: 1
//
// Description  : a I2C basedriver for BBB
//
////////////////////////////////////////////////////////////
#include "I2C.h"

using namespace std;

//#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)


/**
 * Constructor for the I2C class. It requires the I2C number and device Id. The constructor
 * opens a file handle to the I2C device.
 * @param bus The bus number. Usually 0 or 1 on the BBB
 * @param device The device ID on the bus.
 */
I2C::I2C (unsigned int bus, unsigned int address)
{
	this->address = address;
	this->bus = bus;
	this->file = -1;
	this->open();
}

/**
 * Closes the file on destruction, provided that it has not already been closed.
 */
I2C::~I2C ( )
{
	if(file!=-1)
		this->close();
}
/**
 * Connects to an I2C device
 * @return 1 on failure to connec to bus or address, 0 on success.
 */
int I2C::open()
{
	string I2Cname;
	if(this->bus == 0) {
		I2Cname = BBB_I2C_0;
	}
	else if(this->bus == 1) {
		I2Cname = BBB_I2C_1;
	}
	else if(this->bus == 2) {
		I2Cname = BBB_I2C_2;
	}
  if((this->file=::open(I2Cname.c_str(), O_RDWR)) < 0){
     perror("I2C: failed to open the bus\n");
	  return 1;
  }
  if(ioctl(this->file, I2C_SLAVE, this->address) < 0){
     perror("I2C: Failed to connect to the address\n");
	  return 1;
  }
	return 0;
}


int I2C::writeRegister(unsigned int registerAddress, unsigned char value){
   unsigned char buffer[2];
   buffer[0] = registerAddress;
   buffer[1] = value;
   if(::write(this->file, buffer, 2)!=2){
      perror("I2C: Failed write to the device\n");
      return 1;
   }
   return 0;
}

/**
 * Method to read a number of registers from a single device.
 * The from address is the starting address to read from, which
 * defaults to 0x00.
 * @param number the number of registers to read from the device
 * @param fromAddress the starting address to read from
 * @return a pointer of type unsigned char* that points to the first element in the block of registers
 */
unsigned char * I2C::readRegisters(unsigned int length, unsigned int FromAddress)
{
	unsigned buffer[1];
	buffer[0] = FromAddress;
	if(::write(this->file,buffer,1) != 1) {
		perror("I2C: Failed write to the device\n");
		return NULL;
	}
	unsigned char * data = new unsigned char[length];
	if(::read(this->file, data, length)!=(int)length){
	       perror("IC2: Failed to read in the full buffer.\n");
		   return NULL;
	}
	return data;
}

/**
 * Close the file handles and sets a temporary state to -1.
 */
void I2C::close(){
	::close(this->file);
	this->file = -1;
}

