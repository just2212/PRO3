////////////////////////////////////////////////////////////
//
// Source file	: ISensor.h
// Author				: Nikolaj
// Date 				: 4 Dec 2019
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef ISENSOR_H_
#define ISENSOR_H_

#include "ADXL345.h"

#define BUFSIZE 32000

using namespace std;

class ISensor: protected ADXL345
{
	public:
		ISensor ( unsigned short bus, unsigned short address);
		virtual ~ISensor ( );
		virtual int readSensor();
		virtual int writeFile();
	private:
		char buffer[2][BUFSIZE];
		unsigned short I2CAddr,I2CB;
};

#endif /* ISENSOR_H_ */
