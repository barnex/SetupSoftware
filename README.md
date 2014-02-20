SetupSoftware
=============

List of available software/firmware:
------------------------------------
The following software is present:
- Controller: presents an interface to the STM32 based piezo/magnet controller with 8-channel, 16-bit bipolar ADC input;
- CurrentSense: an interface to a STM32 based current sensor (current through fast photodiode)
- FFTGrabber: when requested, it will record a number of samples from a soundcard and returns the FFT of this
- HPInterface: interfaces both with a Prologix or Arduino based GPIB controller hooked up to the HP 8672A signal generator
- STM32F-workarea: contains two projects: Controller firmware and CurrentSense firmware
- Example: contains a simple example of how to communicate with one of the servers
- GUI: unfinished

The "Libraries" folder contains certain functions and definitions that are common to all servers and even firmware. It is strongly recommended to use these, and not code your own.

Protocol definition:
--------------------
Each server will be run by regular user, using a port specified at runtime. Use SSH tunneling for authentication and
security.

Commands given to a server are always in ASCII, always capital letters. When (multiple) arguments are given, they are seperated by comma's.
For example, the set the position of the piezo stage halfway in each direction, the command will be (given to "Controller"):
SET,POSITION,0.5,0.5,0.5,0.0

(The magnet will be powered off)

Each server will always reply with two int32_t values. The first holds the exit code, 1/SUCCESS if al went well. The second holds the number of bytes that will 
be returned to the user. If something went wrong, the resulting error code can be looked up in "Libraries/errors.h".
If you do not read all bytes present, they may be present in the input buffer when you read at a later point in time.

*Note: for list of command and parameters, please consult the source of the corresponding server
