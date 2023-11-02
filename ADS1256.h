/*
        ADS1256.h 24bit ADC 
        @v1, 02.Nov. 2023
*/

#ifndef __ADS1256_h__
#define __ADS1256_h__

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
	// Define PORT
	#define PORT_DRDY PORTB // Pin 9 on Arduino UNO
	#define PIN_DRDY PINB
	#define PINDEX_DRDY PB1
	#define DDR_DRDY DDRB

	#define PORT_CS PORTB // Pin 10 on Arduino UNO
	#define PIN_CS PINB
	#define PINDEX_CS PB2
	#define DDR_CS DDRB

	#define PORT_RESET PORTB // PIN 8 on Arduino UNO
	#define PIN_REST PINB
	#define PINDEX_RESET PB0
	#define DDR_RESET DDRB

#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	// Define PORT
	#define PORT_DRDY PORTL // Pin 49 on Arduino Mega
	#define PIN_DRDY PINL
	#define PINDEX_DRDY PL0
	#define DDR_DRDY DDRL

	#define PORT_CS PORTB // Pin 53 on Arduino Mega
	#define PIN_CS PINB
	#define PINDEX_CS PB0
	#define DDR_CS DDRB

	#define PORT_RESET PORTL // PIN 48 on Arduino Mega
	#define PIN_REST PINL
	#define PINDEX_RESET PL1
	#define DDR_RESET DDRL
	
	// Contributions are welcome
#elif   defined(ARDUINO_ARCH_ESP32)
	#error "Oops! ESP32 architecture not supported yet"	
	// Contributions are welcome
#else 
	// Contributions are welcome
	#error "Oops! Your board architecture is not supported yet'"
#endif
// ADS1256 Register
#define STATUS 0x00
#define MUX 0x01
#define ADCON 0x02
#define DRATE 0x03
#define IO 0x04
#define OFC0 0x05
#define OFC1 0x06
#define OFC2 0x07
#define FSC0 0x08
#define FSC1 0x09
#define FSC2 0x0A

// ADS1256 Command
#define WAKEUP 0x00
#define RDATA 0x01
#define RDATAC 0x03
#define SDATAC 0x0f
#define RREG 0x10
#define WREG 0x50
#define SELFCAL 0xF0
#define SELFOCAL 0xF1
#define SELFGCAL 0xF2
#define SYSOCAL 0xF3
#define SYSGCAL 0xF4
#define SYNC 0xFC
#define STANDBY 0xFD
#define RESET 0xFE

// define multiplexer codes
#define ADS1256_MUXP_AIN0 0x00
#define ADS1256_MUXP_AIN1 0x10
#define ADS1256_MUXP_AIN2 0x20
#define ADS1256_MUXP_AIN3 0x30
#define ADS1256_MUXP_AIN4 0x40
#define ADS1256_MUXP_AIN5 0x50
#define ADS1256_MUXP_AIN6 0x60
#define ADS1256_MUXP_AIN7 0x70
#define ADS1256_MUXP_AINCOM 0x80

#define ADS1256_MUXN_AIN0 0x00
#define ADS1256_MUXN_AIN1 0x01
#define ADS1256_MUXN_AIN2 0x02
#define ADS1256_MUXN_AIN3 0x03
#define ADS1256_MUXN_AIN4 0x04
#define ADS1256_MUXN_AIN5 0x05
#define ADS1256_MUXN_AIN6 0x06
#define ADS1256_MUXN_AIN7 0x07
#define ADS1256_MUXN_AINCOM 0x08

/* 
definitions of Programmable Gain Amplifier
*/
#define ADS1256_GAIN_1 0x00   ///< +/-5V range = Gain 1
#define ADS1256_GAIN_2 0x01   ///< +/-2.5V range = Gain 2
#define ADS1256_GAIN_4 0x02   ///< +/-1.25V range = Gain 4
#define ADS1256_GAIN_8 0x03   ///< +/-0.625V range = Gain 8
#define ADS1256_GAIN_16 0x04  ///< +/-312.5mV range = Gain 16
#define ADS1256_GAIN_32 0x05  ///< +/-156.26mV range = Gain 32
#define ADS1256_GAIN_64 0x06  ///< +/-78.125mV range = Gain 64

// Data Rates 
/*
  F_CLKIN= 7.68Mhz, datasheet
*/

#define RATE_ADS1256_30000SPS 0xF0  /// < 30000 samples per second
#define RATE_ADS1256_15000SPS 0xE0  /// < 15000 samples per second
#define RATE_ADS1256_7500SPS 0xD0   /// <  7500 samples per second
#define RATE_ADS1256_3750SPS 0xC0   /// <  3750 samples per second
#define RATE_ADS1256_2000SPS 0xB0   /// <  2000 samples per second
#define RATE_ADS1256_1000SPS 0xA1   /// <  1000 samples per second
#define RATE_ADS1256_500SPS 0x92    /// <  500 samples per second
#define RATE_ADS1256_100SPS 0x82    /// <  100 samples per second
#define RATE_ADS1256_60SPS 0x72     /// <   60 samples per second
#define RATE_ADS1256_50SPS 0x63     /// <   50 samples per second
#define RATE_ADS1256_30SPS 0x53     /// <   30 samples per second
#define RATE_ADS1256_25SPS 0x43     /// <   25 samples per second
#define RATE_ADS1256_15SPS 0x33     /// <   15 samples per second
#define RATE_ADS1256_10SPS 0x23     /// <   10 samples per second
#define RATE_ADS1256_5SPS 0x13      /// <    5 samples per second
#define RATE_ADS1256_2_5SPS 0x03    /// <    2.5 samples per second

#include "Arduino.h"
#include "SPI.h"

class ADS1256 {
 public:
  ADS1256(float clockspdMhz, float vref, bool useresetpin);
  void writeRegister(unsigned char reg, unsigned char wdata);
  unsigned char readRegister(unsigned char reg);
  void sendCommand(unsigned char cmd);
  float readCurrentChannel();
  void setConversionFactor(float val);
  void setChannel(byte channel);
  void setChannel(byte AIP, byte AIN);
  void begin(unsigned char drate, unsigned char gain, bool bufferenable);
  void waitDRDY();
  void setGain(uint8_t gain);
  void readTest();

 private:
  void CSON();
  void CSOFF();
  unsigned long read_uint24();
  long read_int32();
  float read_float32();
  byte _pga;
  float _VREF;
  float _conversionFactor;
};

#endif
