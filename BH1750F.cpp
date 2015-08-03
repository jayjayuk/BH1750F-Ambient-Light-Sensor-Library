#include "BH1750F.h"
#include <Wire.h>


BH1750F::BH1750F(uint8_t i2cAddr)
{
	_resolution = ONE_H_RES_MODE;		// Default resolution 		= ONE_H_RES_MODE
	_sensitivity = 69;					// Default sensitivity		= 69
	_powerSave	= true;					// Default powerSaveMode   	= Enabled

		if(i2cAddr == 1)
		_i2cAddr = BH1750F_ADDR_L;		// Default address #1 		- HW addr pin low
		else if(i2cAddr == 2)
		_i2cAddr = BH1750F_ADDR_H;		// Alternate address #2 	- HW addr pin high
}

float BH1750F::readAmbientLight(void)
{
	uint16_t ambientLightI;					// read from sensor as an int
	float ambientLightF;					// conversion/return float

		if(_powerSave)						// if power save mode is enabled
		{
		writeRegister(BH1750F_POWER_ON);	// turn sensor on
		writeRegister(BH1750F_RESET);		// reset sensor registers
		setResolution(getResolution());		// set sensor resolution
		}
	
	Wire.beginTransmission(_i2cAddr);		// begin data transmission to sensor
	Wire.requestFrom(_i2cAddr, 2);			// request two bytes of data from sensor
	ambientLightI = Wire.read() << 8;		// store 1st byte as int MSB
	ambientLightI |= Wire.read();			// store 2nd byte as int LSB
	Wire.endTransmission();					// end data transmission to sensor
	ambientLightF = ambientLightI/1.2;		// calculate ambient light level

		if(_sensitivity != 69)				// check if sensitivity has been changed
		ambientLightF = ambientLightF*69/(float)_sensitivity; // re-calculate

		if(_resolution == CONT_H_RES_MODE_2 || _resolution == ONE_H_RES_MODE_2)
		ambientLightF = ambientLightF / 2;	// resolution is set to highest

	return ambientLightF;					// return ambient light level as float
}

void BH1750F::setResolution(uint8_t resolution)
{
		if(resolution == 1) 				// set resolution LOW
		_resolution = _powerSave ? ONE_L_RES_MODE : CONT_L_RES_MODE;
		else if(resolution == 2) 			// set resolution HIGH
		_resolution = _powerSave ? ONE_H_RES_MODE : CONT_H_RES_MODE;
		else if(resolution == 3) 			// set resolution HIGH_2
		_resolution = _powerSave ? ONE_H_RES_MODE_2 : CONT_H_RES_MODE_2;
	
	writeRegister(_resolution); 			// write resolution to sensor
	delay(24); 								// minimum delay for resolution LOW

		if(_resolution != ONE_L_RES_MODE && _resolution != CONT_L_RES_MODE)
		delay(120); 						// extra delay for resolution HIGH & HIGH_2

		if(_sensitivity > 69)
		{
			if(_resolution == CONT_L_RES_MODE || _resolution == ONE_L_RES_MODE)
			delay(_sensitivity/7); 			// varying delay for sensitivity LOW res
			else
			delay((_sensitivity*2)/1.5);	// varying delay for sensitivity HIGH res
		}
}

uint8_t BH1750F::getResolution()
{
	if(_resolution == ONE_L_RES_MODE || _resolution == CONT_L_RES_MODE || _resolution == 1)
	return 1; 								// return 1 for LOW resolution modes
	if(_resolution == ONE_H_RES_MODE || _resolution == CONT_H_RES_MODE || _resolution == 2)
	return 2; 								// return 2 for HIGH resolution modes
	if(_resolution == ONE_H_RES_MODE_2 || _resolution == CONT_H_RES_MODE_2 || _resolution == 3)
	return 3; 								// return 3 for HIGH_2 resolution modes
}

void BH1750F::setSensitivity(uint8_t sensitivity)
{
	if(sensitivity > 30 && sensitivity < 255) // min/max range for sensitivity
	{
	uint8_t highByte = 0x40;          		// highByte start bits for sensitivity
	uint8_t lowByte = 0x60;           		// lowByte start bits for sensitivity
	highByte |= sensitivity >> 5;     		// shift sensitivity 5 bits and use as mask
	lowByte |= sensitivity & 0x1F;    		// mask the 5 LSB's from sensitivity 
	writeRegister(highByte);				// write highByte to sensor
	writeRegister(lowByte);					// write lowByte to sensor
	_sensitivity = sensitivity;				// save the new sensor sensitivity
	}
}

uint8_t BH1750F::getSensitivity()
{
	return _sensitivity; 					// return current sensitivity
}

void BH1750F::setPowerSaveMode(uint8_t powerSave)
{
	if(powerSave)
	{
	_powerSave = true;						// save power state
	writeRegister(BH1750F_POWER_DOWN);		// turn sensor off
	}
	else
	{
	_powerSave = false;						// save power state
	writeRegister(BH1750F_POWER_ON);		// turn sensor on
	writeRegister(BH1750F_RESET);			// reset sensor registers
	setResolution(getResolution());			// set current resolution
	}
}

uint8_t BH1750F::getPowerSaveMode()
{
	return _powerSave;						// return current power save mode state
}

void BH1750F::writeRegister(uint8_t reg)
{
    Wire.beginTransmission(_i2cAddr);		// begin data transmission to sensor
    Wire.write(reg);						// write operation code to sensor
    Wire.endTransmission();					// send/end transmission to sensor
}
