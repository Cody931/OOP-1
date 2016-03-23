#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void ZFunction(const string zStr, vector<int> &zVector)
{
	size_t len = zStr.length();
	int j, endBlock, startBlock = endBlock = 0;
	zVector[0] = len;

	for (int i = 1; i < len; i++)
	{
		if (i > endBlock)
		{
			j = 0;
			while (((i + j) < len) && (zStr[j] == zStr[i + j]))
			{
				++j;
			}
			zVector[i] = j;
			startBlock = i;
			endBlock = i + j - 1;
		}
		else
		{
			if (zVector[i - startBlock] < (endBlock - i + 1))
				zVector[i] = zVector[i - startBlock];
			else
			{
				j = 0;
				while (((j + endBlock) < len) && (zStr[endBlock + j] == zStr[endBlock - i + j]))
				{
					++j;
				}
				zVector[i] = endBlock - i + j;
				startBlock = i;
				endBlock = endBlock + j - 1;
			}
		}
	}
}

string ReplacementSubstring(const string inputStr, const string searchStr, const string replacementStr)
{
	string outputStr, zStr = searchStr + "#" + inputStr;
	size_t len = zStr.length();
	size_t lenSearchStr = searchStr.length();
	int i;
	vector<int> zVector(len);

	if (lenSearchStr == 0)
		outputStr = inputStr;
	else
	{
		ZFunction(zStr, zVector);
		for (int i = 0; i <= lenSearchStr; i++)
			zVector.erase(zVector.begin());
		i = 0;
		while (i < zVector.size())
		{
			if (zVector[i] == lenSearchStr)
			{
				outputStr += replacementStr;
				i += lenSearchStr;
			}
			else
				outputStr += inputStr[i++];
		}
	}
	zVector.clear();
	return outputStr;
}

bool AreCorrectInputData(int argc, char * argv[], ifstream & inputFile, string nameInputFile)
{
	if (argc != 5)
	{
		cout << "ERROR INPUT! Wrong number of arguments! Try again! \n";
		cout << "Input data: example.exe <input file> <output file> <search string> <replace string>\n";
		cout << "Example: replace.exe input.txt output.txt mama papa\n";
		return false;
	}
	else if (!inputFile.is_open())
	{
		cout << "Error open file! File not found! \n";
		return false;
	}
	else
		return true;
}

void RecordInOutputFile(char * argv[], ifstream & inputFile)
{
	string nameOutputFile = argv[2];
	string searchStr = argv[3];
	string replacementStr = argv[4];
	string inputFileStr;

	ofstream outputFile(nameOutputFile);

	while (getline(inputFile, inputFileStr))
		outputFile << ReplacementSubstring(inputFileStr, searchStr, replacementStr) << endl;
	if (!outputFile.flush())
		cout << "Error record!\n";
	outputFile.close();
}

int main(int argc, char * argv[])
{
	string nameInputFile = argv[1];
	ifstream inputFile(nameInputFile);
	if (AreCorrectInputData(argc, argv, inputFile, nameInputFile))
	{
		RecordInOutputFile(argv, inputFile);
	}
	return 0;
}