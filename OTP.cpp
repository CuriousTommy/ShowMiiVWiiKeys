#include "OTP.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;




OTP::OTP(string filename)
{
	ifstream input;
	input.open(filename, ios::binary);
	if (!input) throw "The Wii U OTP file could not be found!";


	input.read(reinterpret_cast<char *>(&otpBin), sizeof(otpBin));
	input.close();
}




void OTP::genFile(int fileType, string filename)
{
	ofstream output;

	switch (fileType)
	{
		case BootMii:
		{
			string stringConsoleID;
			if (filename == "") filename = "keys.bin";
			output.open(filename, ios::binary);
			if (!output) throw "Could not create BootMii file";
			

			// Information of the keys.bin file are taken from:
			// https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/ec_wii.h
			// https://wiibrew.org/wiki/Bootmii/NAND_dump_format
			// http://wiibrew.org/wiki/BootMii#Console_Keys_and_keys.bin
			// http://wiibrew.org/wiki/Hardware/OTP
			// http://wiibrew.org/wiki/Hardware/SEEPROM

			struct
			{
				char humanInfo[0x100];			// 0x0

				// ec_wii.h states that privNGKey should be 0x1E
				// but remember that  privNGKey and NAND_HMAC overlaps
				// each other by two bytes. So this should be okay.
				struct
				{
					char bootSHA1[0x14];		// 0x100
					char commonKey[0x10];		// 0x114
					char consoleID[0x4];		// 0x124
					char privNGKey[0x1C];		// 0x128
					char NAND_HMAC[0x14];		// 0x144
					char keyNAND[0x10];      	// 0x158
					char keyRNG[0x10];			// 0x168
					char Unknown[0x08];			// 0x178

				} OTP;

				char postPadOTP[0x80]; 			// 0x180

				// Note, there is a structure for both counters,
				// but since the Wii U's OTP does not provide info
				// for these counter, I am going to be lazy and have
				// a char array represent the whole counter.
				struct
				{
					char rootMS_ID[0x4];         	// 0x200
					char rootCA_ID[0x4];         	// 0x204
					char rootKeyNG_ID[0x4];      	// 0x208
					char rootSignNG[0x3C];       	// 0x20C
					char boot2Counter[0x14];	 	// 0x248
					char nandCounter[0x18];	 		// 0x25c	
					char keyKorean[0x10];        	// 0x274
					char postKorPad[0x74];	 		// 0x284
					char PRNG_Seed[0x4];			// 0x2F8
					char postPRNG_Pad[0x4];			// 0x2FC
				} SEEPROM;

				char postPadSEEPROM[0x100];
			} bootMiiKeys;

			cout << "Generating " << filename << endl;

			// Lets fill the entire structure with zero
			fill_n(reinterpret_cast<char *>(&bootMiiKeys), sizeof(bootMiiKeys), 0);

			// Fill the humanInfo section
			strcpy(bootMiiKeys.humanInfo, "BackupMii v1, ConsoleID: ");
			stringConsoleID = hexToHexString(otpBin.BK0.NG_ID, sizeof(otpBin.BK0.NG_ID), false);
			strcpy(bootMiiKeys.humanInfo + 0x19, stringConsoleID.c_str()); // 0x19 == sizeof("BackupMii ...")
			bootMiiKeys.humanInfo[0x21] = 0x0A; 

			// Fill the OTP section
			memcpy(&bootMiiKeys.OTP, &otpBin.BK0, sizeof(bootMiiKeys.OTP));
			
			// Fill the SEEPROM section
			memcpy(&bootMiiKeys.SEEPROM, &otpBin.BK6, 0x4 + 0x4 + 0x4 + 0x3C); // rootMS_ID + rootCA_ID + rootKeyNG_ID + rootSignNG
			memcpy(&bootMiiKeys.SEEPROM.keyKorean, &otpBin.BK6.keyKorean, sizeof(bootMiiKeys.SEEPROM.keyKorean));

			// Write the entire the structure in file
			output.write(reinterpret_cast<char *>(&bootMiiKeys), sizeof(bootMiiKeys));
			output.close();

			cout << filename << " has be successfully created" << endl;
			cout << endl;

			break;
		}


		case Text:
		{
			if (filename == "") filename = "keys.txt";
			output.open(filename);
			if (!output) throw "Could not create text file";

			cout << "Generating " << filename << endl;

			// The stream from printData will be stored into output.
			printData(output, BK0 | BK6);
			output.close();
			
			cout << filename << " has be successfully created" << endl;
			cout << endl;

			break;
		}


		default:
			throw "Invalid Request";
	}
}




void OTP::printData(ostream &streamOutput, uint8_t requestedBanks)
{
	if (requestedBanks & BK0)
	{
		int size = 24;

		streamOutput << "BANK 0:" << endl;
		formatData(streamOutput, size, "Wii Boot1 SHA-1 Hash",
				   hexToHexString(otpBin.BK0.bootSHA1, sizeof(otpBin.BK0.bootSHA1)));

		formatData(streamOutput, size, "Wii Common Key",
				   hexToHexString(otpBin.BK0.commonKey, sizeof(otpBin.BK0.commonKey)));

		formatData(streamOutput, size, "Wii NG ID",
				   hexToHexString(otpBin.BK0.NG_ID, sizeof(otpBin.BK0.NG_ID)));

		formatData(streamOutput, size, "Wii NG Private Key",
				   hexToHexString(otpBin.BK0.privNGKey, sizeof(otpBin.BK0.privNGKey)));

		formatData(streamOutput, size, "Wii NAND HMAC",
				   hexToHexString(otpBin.BK0.NAND_HMAC, sizeof(otpBin.BK0.NAND_HMAC)));

		formatData(streamOutput, size, "Wii NAND key",
				   hexToHexString(otpBin.BK0.keyNAND, sizeof(otpBin.BK0.keyNAND)));

		formatData(streamOutput, size, "Wii RNG key",
				   hexToHexString(otpBin.BK0.keyRNG, sizeof(otpBin.BK0.keyRNG)));
		streamOutput << endl;
	}

	if (requestedBanks & BK6)
	{
		int size = 38;

		streamOutput << "BANK 6:" << endl;
		formatData(streamOutput, size, "Wii Root Certificate MS ID",
				   hexToHexString(otpBin.BK6.rootMS_ID, sizeof(otpBin.BK6.rootMS_ID)));

		formatData(streamOutput, size, "Wii Root Certificate CA ID",
				   hexToHexString(otpBin.BK6.rootCA_ID, sizeof(otpBin.BK6.rootCA_ID)));

		formatData(streamOutput, size, "Wii Root Certificate NG Key ID",
				   hexToHexString(otpBin.BK6.rootKeyNG_ID, sizeof(otpBin.BK6.rootKeyNG_ID)));

		formatData(streamOutput, size, "Wii Root Certificate NG Singature",
				   hexToHexString(otpBin.BK6.rootSignNG, sizeof(otpBin.BK6.rootSignNG)));

		formatData(streamOutput, size, "Wii Korean Key",
				   hexToHexString(otpBin.BK6.keyKorean, sizeof(otpBin.BK6.keyKorean)));

		formatData(streamOutput, size, "Unknown (unused)",
				   hexToHexString(otpBin.BK6.Unknown, sizeof(otpBin.BK6.Unknown)));

		formatData(streamOutput, size, "NSS Device Certificate Private Key",
				   hexToHexString(otpBin.BK6.privKeyDeviceNSS, sizeof(otpBin.BK6.privKeyDeviceNSS)));
		streamOutput << endl;
	}
}




string OTP::hexToHexString(char request[], uint8_t size, bool includeSpace)
{
	stringstream value;

	for (int i = 0; i < size; i++)
	{
		value << setw(2) << setfill('0');
		value << hex << static_cast<unsigned>((static_cast<uint8_t>(request[i])));
		includeSpace ? (value << " ") : (value << "");
	}

	return value.str();
}




void OTP::formatData(ostream &streamOutput, int setWidth, string filename, string hexString)
{
	// For the sake of convenience, I will be using stringstream
	// to store the hex string. hexSize is used to state the max
	// amount of hexes each row can hold.
	stringstream value(hexString);
	string eightBitHex;
	int hexSize = 20;


	// This is the very first row, the name of the key will be
	// printed follow by first 20 hex values.
	// For Example: Key ~~~setw(space)~~~ : AA BB CC DD EE FF
	streamOutput << left << setw(setWidth - 3) << filename;
	streamOutput << right << " : ";
	for (int i = 0; i < hexSize && value; i++)
	{
		if (value >> eightBitHex) streamOutput << eightBitHex << " ";
		else break;
	}
	streamOutput << endl;


	// If there happens to be additional hex values they will be printed
	// in a new line.
	while (value)
	{
		streamOutput << setw(setWidth) << " ";
		for (int i = 0; i < hexSize && value; i++)
		{
			if (value >> eightBitHex) streamOutput << eightBitHex << " ";
			else break;
		}
		streamOutput << endl;
	}
}