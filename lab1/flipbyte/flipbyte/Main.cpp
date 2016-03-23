#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <mbstring.h>

using namespace std;

const int NUMBER_OF_BITS = 8;

bool IsDigit(const char *line)
{
	bool digit = true;
	for (int i = 0; i < strlen(line); i++)
	{
		if (!isdigit(line[i]))
			digit = false;
	}
	return digit;
}

void ConvertToBin(unsigned int inputNumb, vector<unsigned> &bytes, int &i)
{
	if (inputNumb)
	{
		bytes[i++] = (inputNumb & 1);
		ConvertToBin(inputNumb >> 1, bytes, i);
	}
}

int InterpretationToDec(vector<unsigned int> bytes)
{
	int dec = 0;
	int exp = 0;
	for (int i = 7; i >= 0; i--) 
	{
		dec += bytes[i] * (int)pow(2, exp++);
	}
	return dec;
}

int FlipByte(unsigned int inputNumb)
{
	int i = 0;
	vector<unsigned> bytes(NUMBER_OF_BITS, 0);
	ConvertToBin(inputNumb, bytes, i);
	return InterpretationToDec(bytes);
}

int main(int argc, char * argv[])
{
	if ((argc < 2) || (argc > 2))
	{
		cout << "Error input!\nExample input: flipbyte.exe <input byte>\n";
	}
	else if (!IsDigit(argv[1]))// && ((unsigned)argv[1] > 255))
	{
		cout << "The input data are not correct!\nYou should enter a unsigned number not letters!\n";
	}
	else if (atoi(argv[1]) > 255)
	{
		cout << "The input data are not correct!\nYou should enter a unsigned number greater than 0 and less than 255!\n";
	}
	else
	{
		unsigned int inputNumber = atoi(argv[1]);
		cout << "Input byte: " << inputNumber << endl;
		cout << "Inverted byte: " << FlipByte(inputNumber) << endl;
	}
	system("pause");
	return 0;
}