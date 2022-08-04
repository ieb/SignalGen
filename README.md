# Signal Generator

Need a signal generator which can produce a clean narrow spectrum at a single frequency for testing LC networks and mixing with RF signals. Aim to build a fixed frequency RF reciever for Navtex (490KHz + 512KHz LSB FSK with FEC).

## First Attempt Si5351

see main.cpp-Si5351 which works, is very precise. At 15Mhz the output looks like a sine wave but has multiple frequencies in the spectrum. At 500Hz the output is vry square wave and hence not suitable due to the wide spectrum.

### Wiring

standard i2c, using a 3V pro mini from the default SCL/SDA pins.

## Second attepmt AD9850

Initially I thought the chip was a AD9833 which has a different register set causing very odd results. With the correct library (https://github.com/f4goj/AD9850SPI) this produces clean sine wave output at 500Khz with no other frequencies in the spectrum.  The SPI interface is quite odd as it seems to accept a single stream of bits to configure containg all the information packed into workds. There is no MISO signal from the chip only a MOSI signal from the MCU clocked by the SCK signal.

Spectrums can be drawn very accurately and cleanly using a Picoscope 2204A below 10Mhz by sweeping the frequency in suitably small steps (eg 100Hz) through the range, (eg 400 - 600 KHz). The Picosope is setup to capture the spectrum using peak hold which draws a precise line at the peak response seen in the LC curcuit driven through a suitably high resistor (eg 220K) to make the non resonant response minimal.

Static outputs are stable and precise with almost no side spread in the spectrum. Probably very suitable for RF mixing.


### Wiring

Like I said a bit odd, it is SPI, but it doesnt feel like it and most AD9850 modules dont label the SPI pins as you would expect.  The AD9850 module I had didnt work well on 3v so I used an Uno on 5v.

		MCU   -> Module
		D13 (SCK) -> W_CLK
		D11 (MOSI) -> DATA/D7
		D9 -> RESET
		D8 -> FQ_UD

## Next ?

Thats it for the moment. Probably wont build the reciever as life its too short.



