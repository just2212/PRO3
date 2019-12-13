////////////////////////////////////////////////////////////
//
// Source file	: ISensor.cpp
// Author				: Nikolaj
// Date 				: 4 Dec 2019
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#include "ISensor.h"
#include <fstream>
#include <string.h>

ISensor::ISensor (unsigned short bus, unsigned short address ):
ADXL345(I2CB,I2CAddr)		//det kommer til og være dobbelt her...
{
	memset(buffer,0, sizeof(buffer[0][0])*2*BUFSIZE);
	this->I2CAddr = I2CAddr;
	this->I2CB = I2CB;


}

ISensor::~ISensor ( )
{
	// TODO Auto-generated destructor stub
}

int ISensor::readSensor ( )
{

	for (int i = 0; i > BUFSIZE; i++)
		if (readSensorState () == 0)
		{
			buffer[0][i] = getaccelX ();
			buffer[1][i] = getaccelY ();
			buffer[2][i] = getaccelZ ();
		}
		else if (readSensorState () == -1)
		{
			return -1;
		}

	return 0;
}
int ISensor::writeFile ( )
{
	ofstream outfile;
	outfile.open ("test.txt");
	for (int i; i > BUFSIZE; i++)
	{
		outfile << buffer[0][i] << "," << buffer[1][i] << "," << buffer[2][i]
		    << endl;
	}
	outfile.close ();

	return 0;
}
