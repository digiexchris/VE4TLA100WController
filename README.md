# VE4TLA Amp Controller

This is intended to control the MRF101AN evaluation boards provided by RfPowerTools.com for the MRF101AN LDMOS device. It is designed around the ESP32 and FreeRTOS, and taking advantage of the dual core multi-threading capability of the ESP32 in order to provided dedicated safety features.

It is likely this could be used for most amplifier control schemes where:
- the LPF takes BCD input
- the bias-off signal is a high signal rather than a low signal (though it's easy to invert this)
- the T/R switch is high for transmit (though it's easy to invert this)
- the SWR bridge outputs a compatible voltage range (I may make this configurable)

Features:
- DS18B20 i2c temp sensor
- 20x4 HD44780 style LCD with an i2c backpack
- High side voltage and current (with a 0.2 ohm resistor and a simple voltage divider)
- Input from the RFPowerTools T/R switch board for Power and SWR
- Controlls the RFPowerTools T/R switch board
- Controls the RFPowerTools low pass filter board
- Band up/down buttons
- Standby button
- Reset button (for resetting an error condition such as high swr)

Planned Features:
- automatic band decoding via rig decoding
- automatic band decoding using a frequency counter

See includes/pins.h for pins that are needed to be connected.

