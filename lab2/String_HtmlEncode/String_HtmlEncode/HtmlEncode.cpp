#include "stdafx.h"
#include "HtmlEncode.h"
#include <algorithm>
#include <boost/range/algorithm/transform.hpp>


string ReadInputText()
{
	string text;
	getline(cin, text);
	return text;
}

void HtmlTextEncode(string & text)
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
		text = encodeText;
	}
}

void PrintText(string const& text)
{
	cout << text << endl;
}