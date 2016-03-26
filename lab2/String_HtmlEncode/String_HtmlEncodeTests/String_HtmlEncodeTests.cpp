#include "stdafx.h"
#include "../String_HtmlEncode/HtmlEncode.h"

BOOST_AUTO_TEST_SUITE(Html_Encode)

	BOOST_AUTO_TEST_CASE(should_encode_empty_string)
	{
		string checkedString = "";
		HtmlTextEncode(checkedString);
		BOOST_CHECK(checkedString.empty());
	}

	BOOST_AUTO_TEST_CASE(should_encode_not_emty_string)
	{
		string checkedString = "Hel&lo, 'world' <\"< or >>";
		string rightString = "Hel&amp;lo, &apos;world&apos; &lt;&quot;&lt; or &gt;&gt;";
		HtmlTextEncode(checkedString);
		BOOST_CHECK_EQUAL(checkedString, rightString);
	}
BOOST_AUTO_TEST_SUITE_END()