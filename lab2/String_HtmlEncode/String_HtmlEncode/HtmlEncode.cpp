#include "stdafx.h"
#include "HtmlEncode.h"

string ReadInputText()
{
	string text;
	cout << "Enter the text to encode (Enter \"no\", if input should fihished!): ";
	while (getline(cin, text))
	return text;
}

string HtmlTextEncode(string const& text)
{
	string encodeText;
	if (text.length() != 0)
	{
		for (auto letter : text)
		{
			if (letter == '\"')
				encodeText.append("&quot;");
			else if (letter == '\'')
				encodeText.append("&apos;");
			else if (letter == '<')
				encodeText.append("&lt;");
			else if (letter == '>')
				encodeText.append("&gt;");
			else if (letter == '&')
				encodeText.append("&amp;");
			else
				encodeText += letter;
		}
	}
	return encodeText;
}

void PrintText(string const& text)
{
	cout << text << endl;
}