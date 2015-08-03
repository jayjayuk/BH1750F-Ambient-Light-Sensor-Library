This library was made for the BH1750F ambient light sensor and only tested
on the teensy 3.1 but it should work for Arduino also. The BH1750F is an I2C device
that runs on 3-5v, it has five pins broken out, two for power, two for I2C and one ADDR
pin for changing the address. a maximum of two sensors can be on the same bus.
connecting the sensor is pretty straight forward no extra components are required.
This library takes advantage of all the features this sensor has to offer and is
fairly cheap on ebay to buy on a breakout board with pin headers. The sensor offers
some nice features, to name a few...

: 3 different resolution modes to select from : LOW / HIGH / HIGH_2
: A selectable sensitivity range from 31 -> 254
: Power save mode which will turn off the device after each reading
: 50Hz / 60Hz light noise rejection (only on high resolution modes)

With this library, it is possible to read the ambient light and control the resolution, 
sensitivity and enable power saving. Below is a description of what the resolution
modes do and how the sensitivity range works as well as describing the power save mode.



Resolution:
The resolution can be set to 1 of 3 different modes using the setResolution() function
1 = LOW Resolution Mode
2 = HIGH Resolution Mode
3 = HIGH Resolution Mode 2
Supply 1, 2 or 3 to the function to select the desired resolution.



Sensitivity:
The sensitivity can be set between the range of 31 -> 254 using the setSensitivity()
function. This will alter the sensitivity for the selected resolution mode and will
also increase the time needed to take a measurement. See below for some examples of
the settings that was used and the time it took to return the ambient light level...



LOW resolution + 31 Sensitivity = 7.42-lx		 25 milliseconds	powerSave=enabled
HIGH resolution + 31 Sensitivity = 1.85-lx		145 milliseconds	powerSave=enabled
HIGH_2 resolution + 31 Sensitivity = 0.93-lx	145 milliseconds	powerSave=enabled

LOW resolution + 69 Sensitivity = 3.33-lx		 25 milliseconds	powerSave=enabled
HIGH resolution + 69 Sensitivity = 0.83-lx		145 milliseconds	powerSave=enabled
HIGH_2 resolution + 69 Sensitivity = 0.42-lx	145 milliseconds	powerSave=enabled

LOW resolution + 254 Sensitivity = 0.91-lx		483 milliseconds	powerSave=enabled
HIGH resolution + 254 Sensitivity = 0.23-lx		483 milliseconds	powerSave=enabled
HIGH_2 resolution + 254 Sensitivity = 0.11-lx	483 milliseconds	powerSave=enabled

LOW resolution + 69 Sensitivity = 3.33-lx		399 microseconds	powerSave=disabled
HIGH resolution + 69 Sensitivity = 0.83-lx		407 microseconds	powerSave=disabled
HIGH_2 resolution + 69 Sensitivity = 0.42-lx	408 microseconds	powerSave=disabled

* All powerSave=disabled times are roughly the same



Power Save Mode:
The power save mode can be enabled and the sensor will turn on before the reading is
taken and turn the sensor off when the reading has finished. the process is as follows...

: Power On Sensor											- RUN EVERY TIME
: Reset Sensor Registers									- RUN EVERY TIME
: Set Resolution To Start Measurement						- RUN EVERY TIME
: Delay Until Measurement Is Complete						- RUN EVERY TIME
: Read Measurement From Sensor And Calculate The Result		- RUN EVERY TIME
: Power Down Sensor											- RUN EVERY TIME

This will guarantee a new reading every time a reading is taken from the sensor, but
this method sets the resolution every time before a reading and uses delays until the
reading is ready. This means the higher resolution mode and higher sensitivity will
delay much longer. If the power save mode is disabled, the process is as follows...

: Power On Sensor 											- ONLY RUN ONCE
: Reset Sensor Registers 									- ONLY RUN ONCE
: Set Resolution To Start Measurement 						- ONLY RUN ONCE
: Delay Until Measurement Is Complete 						- ONLY RUN ONCE
: Read Measurement From Sensor And Calculate The Result		- RUN EVERY TIME

When power save mode is disabled, the resolution is set once so the delays only run
once as well, this allows the sensor to be continuously read without any delays, but
the data will always read the same until the required amount of time has passed for
the sensor to take a reading and update its internal data register. This does not use
delays after the resolution has been set once so the program can continue running and
an if statement can check for a change. This also uses more power in continuous mode
(120μA) as the sensor is always powered on. In power save mode (one time reading) it
will turn the device on only to take a reading and then turn it off again after the
reading has been taken. In power down mode the current consumption drops to roughly
(0.01μA) so for power critical projects it is better to use the power save feature
and wait the required amount of time to take a reading and let the sensor turn off
until the next reading is requested.

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////




The library comes with three examples which print information to the serial monitor.
The following gives a brief description of the examples...


Basic_Demo : Print humidity and temperature to the serial monitor while toggling
             the heater on and off periodically.

Functions : This prints a demo of the function use to the serial monitor, showing what
            action to expect, the status/return of the function and the function called.

Timings : Prints information to the serial monitor showing how long each function
          takes to return. The timing is done in microseconds.


In the zip file provided which contains this library will also be a copy of the
datasheet and a text file named (Functions_Info.txt) that has a complete list of
functions and some info on what the function does, what it returns and possible
parameters for certain functions and a short line of extra info.

I hope this library will help someone with their project.

Si7021 Library - DOWNLOAD



