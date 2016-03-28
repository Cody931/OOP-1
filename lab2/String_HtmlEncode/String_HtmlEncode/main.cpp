#include "stdafx.h"
#include <string>
#include <iostream>
#include "HtmlEncode.h"


using namespace std;

int _tmain()
{
	string inputText, encodeHtmlText;
	inputText = ReadInputText();
	
	while (inputText != "no") 
	{
		encodeHtmlText = HtmlTextEncode(inputText);
		PrintText(encodeHtmlText);
		inputText = ReadInputText();
	}
    return 0;
}

