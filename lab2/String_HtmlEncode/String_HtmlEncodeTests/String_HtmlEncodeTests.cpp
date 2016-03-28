#include "stdafx.h"
#include "../String_HtmlEncode/HtmlEncode.h"

BOOST_AUTO_TEST_SUITE(Html_Encode)

	BOOST_AUTO_TEST_CASE(should_encode_empty_string)
	{
		string checkedString = "";
		HtmlTextEncode(checkedString);
		BOOST_CHECK(HtmlTextEncode(checkedString).empty());
	}

	BOOST_AUTO_TEST_CASE(should_encode_not_emty_string)
	{
		string checkedString = "\"Hello!\" said Maggie&Annie >> 'crazy' Adam.";
		string rightString = "&quot;Hello!&quot; said Maggie&amp;Annie &gt;&gt; &apos;crazy&apos; Adam.";
		BOOST_CHECK_EQUAL(HtmlTextEncode(checkedString), rightString);
	}
BOOST_AUTO_TEST_SUITE_END()