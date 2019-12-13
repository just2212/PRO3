////////////////////////////////////////////////////////////
//
// Source file	: ADXL345.h
// Author				: Nikolaj
// Date 				: 4 Dec 2019
// Version 			:
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef ADXL345_H_
#define ADXL345_H_

//includes
#include"I2C.h"

//defines
#define BUFFER_SIZE 0x40

//ADXL345 register defines
#define DEVID          0x00   //Device ID
#define THRESH_TAP     0x1D   //Tap Threshold
#define OFSX           0x1E   //X-axis Offset
#define OFSY           0x1F   //Y-axis Offset
#define OFSZ           0x20   //Z-axis Offset
#define DUR            0x21   //Tap duration
#define LATENT         0x22   //Tap latency
#define WINDOW         0x23   //Tap window
#define THRESH_ACT     0x24   //Activity threshold
#define THRESH_INACT   0x25   //Threshold inactivity
#define TIME_INACT     0x26   //Inactivity time
#define ACT_INACT_CTL  0x27   //Axis enable control for activity and inactivity detection
#define THRESH_FF      0x28   //Free-fall threshold
#define TIME_FF        0x29   //Free-fall time
#define TAP_AXES       0x2A   //Axis control for single tap/double tap
#define ACT_TAP_STATUS 0x2B   //Source of single tap/double tap
#define BW_RATE        0x2C   //Data rate and power mode control
#define POWER_CTL      0x2D   //Power-saving features control
#define INT_ENABLE     0x2E   //Interrupt enable control
#define INT_MAP        0x2F   //Interrupt mapping control
#define INT_SOURCE     0x30   //Source of interrupts
#define DATA_FORMAT    0x31   //Data format control
#define DATAX0         0x32   //X-axis Data 0
#define DATAX1         0x33   //X-axis Data 1
#define DATAY0         0x34   //Y-axis Data 0
#define DATAY1         0x35   //Y-axis Data 1
#define DATAZ0         0x36   //Z-axis Data 0
#define DATAZ1         0x37   //Z-axis Data 1
#define FIFO_CTL       0x38   //FIFO control
#define FIFO_STATUS    0x39   //FIFO status

using namespace std;


class ADXL345:protected I2C
{
	public:
		/// An enumeration to define the gravity range of the sensor
		enum RANGE {
			PLUSMINUS_2_G 		= 0,//!< plus/minus 2g
			PLUSMINUS_4_G 		= 1,//!< plus/minus 4g
			PLUSMINUS_8_G 		= 2,//!< plus/minus 8g
			PLUSMINUS_16_G 		= 3 //!< plus/minus 16g
		};
		/// The resolution of the sensor. High is only available in +/- 16g range.
		enum RESOLUTION {
			NORMAL = 0,//!< NORMAL 10-bit resolution
			HIGH = 1   //!< HIGH 13-bit resolution
		};

		ADXL345 (unsigned short bus, unsigned short address=0x53 );
		virtual ADXL345::RANGE getRange() { return this->range; };
		virtual ADXL345::RESOLUTION getResolution() {return this->resolution;};
		virtual void setRange(ADXL345::RANGE range);
		virtual void setResulotion(ADXL345::RESOLUTION resolution);
		virtual int updateRegisters();
		virtual ~ADXL345 ( );
		virtual int readSensorState();
		virtual short getaccelX() { return this->accelX; };
		virtual short getaccelY() { return this->accelY; };
		virtual short getaccelZ() { return this->accelZ; };

	private:
		short combineRegisters(unsigned char msb, unsigned char lsb);
		short accelX,accelY,accelZ;
		unsigned short I2CAddress,I2CBus;
		unsigned char * registers;
		ADXL345::RANGE range;
		ADXL345::RESOLUTION resolution;






};

#endif /* ADXL345_H_ */
