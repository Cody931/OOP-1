#include "stdafx.h"
#include <string>
#include <iostream>
#include "HtmlEncode.h"


using namespace std;

int _tmain()
{
	string text;
	cout << "Enter the text to encode: ";
	text = ReadInputText();
	HtmlTextEncode(text);
	PrintText(text);
    return 0;
}

