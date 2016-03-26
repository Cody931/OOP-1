#include "stdafx.h"
#include <string>
#include <iostream>
#include "HtmlEncode.h"


using namespace std;

int _tmain()
{
	string text;
	text = ReadInpitText();
	HtmlTextEncode(text);
	PrintText(text);
    return 0;
}

