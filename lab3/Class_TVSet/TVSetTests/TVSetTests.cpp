#include "stdafx.h"
#include "../Class_TVSet/TVSet.h"

struct TVSetFixture
{
	CTVSet tv;
};

BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)

	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}
	BOOST_AUTO_TEST_CASE(can_not_select_channel_when_TV_is_turned_off)
	{
		BOOST_CHECK(!tv.SelectChannel(33));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}
	BOOST_AUTO_TEST_CASE(can_turn_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}
	BOOST_AUTO_TEST_CASE(channel_0_is_the_default_when_TV_turned_off)
	{
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
		BOOST_AUTO_TEST_CASE(can_select_some_channel)
		{
			BOOST_CHECK(tv.SelectChannel(25));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 25);

			BOOST_CHECK(!tv.SelectChannel(100));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 25);
		}
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.IsTurnedOn());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_turned_off_ : when_turned_on_
	{
		when_turned_off_()
		{
			tv.TurnOn();
			tv.TurnOff();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_turned_off, when_turned_off_)
		BOOST_AUTO_TEST_CASE(can_not_select_channel)
		{
			BOOST_CHECK(!tv.SelectChannel(1));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 0);

			BOOST_CHECK(!tv.SelectChannel(47));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 0);

			BOOST_CHECK(!tv.SelectChannel(99));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
		}
		BOOST_AUTO_TEST_CASE(can_turned_on)
		{
			tv.TurnOn();
			BOOST_CHECK(tv.IsTurnedOn());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_subsequent_turning_on_ : when_turned_off_
	{
		after_subsequent_turning_on_()
		{
			tv.TurnOn();
			tv.SelectChannel(33);
			tv.TurnOff();
			tv.TurnOn();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
		BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_set_names_for_several_channels_ : after_subsequent_turning_on_
	{
		after_set_names_for_several_channels_()
		{
			tv.SetChannelName(48, "BBC");
			tv.SetChannelName(32, "A-One");
			tv.SetChannelName(16, "Live");
			tv.SetChannelName(1, "1 channel");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_set_names_for_several_channels, after_set_names_for_several_channels_)
		BOOST_AUTO_TEST_CASE(some_channel_have_name)
		{
			BOOST_CHECK_EQUAL(tv.GetChannelName(48), "BBC");
		}
		BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
		{
			BOOST_CHECK(tv.SelectChannel("BBC"));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 48);

			BOOST_CHECK(tv.SelectChannel("Live"));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 16);
		}
		BOOST_AUTO_TEST_CASE(can_delete_name_of_some_channel)
		{
			BOOST_CHECK(tv.DeleteChannelName("1 channel"));
			BOOST_CHECK(!tv.GetChannelByName("1 channel"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_select_another_channel_by_name_ : after_set_names_for_several_channels_
	{
		after_select_another_channel_by_name_()
		{
			tv.SelectChannel("A-One");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_select_another_channel_by_name, after_select_another_channel_by_name_)
		BOOST_AUTO_TEST_CASE(can_select_previous_channel)
		{
			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 33);

			BOOST_CHECK(tv.SelectPreviousChannel());
			BOOST_CHECK_EQUAL(tv.GetChannel(), 32);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()