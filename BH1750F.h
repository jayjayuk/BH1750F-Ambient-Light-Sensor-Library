#ifndef __BH1750F_H__
#define __BH1750F_H__

#include "Arduino.h"

#define BH1750F_ADDR_L      0x23    // ADDR pin voltage less than 0.3Vcc (Default)
#define BH1750F_ADDR_H      0x5C    // ADDR pin voltage greater than 0.7Vcc
#define BH1750F_POWER_DOWN  0x00    // Turn sensor off
#define BH1750F_POWER_ON    0x01    // Waiting for measurement command
#define BH1750F_RESET       0x07    // Reset data register value

#define CONT_H_RES_MODE     0x10    // Start measurement at 1lx resolution
#define CONT_H_RES_MODE_2   0x11    // Start measurement at 0.5lx resolution
#define CONT_L_RES_MODE     0x13    // Start measurement at 4lx resolution
#define ONE_H_RES_MODE      0x20    // Start measurement at 1lx resolution
#define ONE_H_RES_MODE_2    0x21    // Start measurement at 0.5lx resolution
#define ONE_L_RES_MODE      0x23    // Start measurement at 5lx resolution

class BH1750F
{
	public:
			BH1750F(uint8_t i2cAddr);
			/* Main Function */
			float readAmbientLight(void);

			/* Resolution Functions */
			void setResolution(uint8_t resolution);
			uint8_t getResolution();

			/* Sensitivity Functions */
			void setSensitivity(uint8_t sensitivity);
			uint8_t getSensitivity();

			/* Power Save Functions */
			void setPowerSaveMode(uint8_t powerSave);
			uint8_t getPowerSaveMode();

	private:
			void writeRegister(uint8_t reg);
			
			uint8_t _i2cAddr;
			uint8_t _resolution;
			uint8_t _sensitivity;
			uint8_t _powerSave;
};

#endif