#ifndef OTP_H
#define OTP_H

#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

class OTP
{
private: // data
	
	// Information about the Wii U's OTP was taken from here:
	// http://wiiubrew.org/wiki/Hardware/OTP

	struct
	{
		struct
		{
			char bootSHA1[0x14];     // 0x00, Size: 0x14
			char commonKey[0x10];    // 0x14, Size: 0x10
			char NG_ID[0x4];         // 0x24, Size: 0x4
			char privNGKey[0x1C]; 	 // 0x28, Size: 0x1C
			char NAND_HMAC[0x14];    // 0x44, Size: 0x14
			char keyNAND[0x10];      // 0x58, Size: 0x10
			char keyRNG[0x10];       // 0x68, Size: 0x10
			char unknown[0x08];		 // 0x78, Size: 0x08
		} BK0; // Wii Bank

		char BK1[0x80]; // Wii U Bank (Part 1)
		char BK2[0x80]; // Wii U Bank (Part 2)
		char BK3[0x80]; // Wii U Bank (Part 3)
		char BK4[0x80]; // Wii U NG Bank
		char BK5[0x80]; // Wii U Certificate Bank

		struct
		{
			char rootMS_ID[0x4];         // 0x300, Size: 0x4
			char rootCA_ID[0x4];         // 0x304, Size: 0x4
			char rootKeyNG_ID[0x4];      // 0x308, Size: 0x4
			char rootSignNG[0x3C];       // 0x30C, Size: 0x3C
			char keyKorean[0x10];        // 0x348, Size: 0x10
			char Unknown[0x8];           // 0x358, Size: 0x8
			char privKeyDeviceNSS[0x20]; // 0x360, Size: 0x20
		} BK6; // Wii Certificate Bank

		char BK7[0x80]; // Misc Bank

	} otpBin;

private: // functions
	string hexToHexString(char request[], uint8_t size, bool includeSpace = true);
	void formatData(ostream &streamOutput, int setWidth, string filename, string hexString);

public: // enumerator
	enum bankType {BK0 = 1, BK1 = 2, BK2 = 4,
				   BK3 = 8, BK4 = 16, BK5 = 32,
				   BK6 = 64, BK7 = 128};
	enum fileType {BootMii = 0, Text = 1};

public: // functions
	OTP(string filename = "otp.bin");

	void genFile(int fileType = 0, string filename = "");
	void printData(ostream &streamOutput, uint8_t requestedBanks);
};

#endif