#include "OTP.h"
using namespace std;

// 
// I plan to make use of the args feature later.
// 

int main(int argc, char *argv[])
{
	cout << "ShowMiiVWiiKeys " << "0.01 by CuriousTommy (Thomas A.)" << endl << endl;
	cout << "The program is currently hardcoded to expect a otp.bin file in the "
	     << "same location at the application. It will also create a keys.bin and "
	     << "keys.txt file. Please don't share these files as they contain personal "
	     << "information about your Wii U." << endl << endl << endl;

	try
	{
		OTP mainOperation;

		mainOperation.printData(cout, OTP::BK0 | OTP::BK6);
		mainOperation.genFile(OTP::BootMii);
		mainOperation.genFile(OTP::Text);
	}

	catch (const char *exception)
	{
		cout << exception << endl;
	}
}