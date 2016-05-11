#include "stdafx.h"
#include "../Class_TVSet/RemoteControl.h"
#include "../Class_TVSet/TVSet.h"
#include <boost/optional/optional_io.hpp>


using namespace std;
using boost::optional;
using boost::none;


struct RemoteControlDependencies
{
	CTVSet tv;
	stringstream input;
	ostringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const optional<unsigned> & expectedChannel, const string& expectedOutput)
	{
		input << command;
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
	void VerifyCommandWithNamesHandling(const string& command, const optional<unsigned> & channel, const optional<string> & channelName, const string& expectedOutput)
	{
		input << command;
		BOOST_CHECK(tv.IsTurnedOn());
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.GetChannelName((*channel)), channelName);
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

	BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
	{
		VerifyCommandHandling("TurnOn", 1, "TV is turned ON");
	}

	BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("TurnOff", none, "TV is turned OFF");
	}

	BOOST_AUTO_TEST_CASE(can_show_info_when_tv_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("Info", 1, "Selected channel : 1");
	}

	BOOST_AUTO_TEST_CASE(can_show_info_when_tv_is_off)
	{
		tv.TurnOff();
		VerifyCommandHandling("Info", none, "TV is OFF.");
	}

	BOOST_AUTO_TEST_CASE(can_select_channel_when_tv_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SelectChannel 22", 22, "");
	}

	BOOST_AUTO_TEST_CASE(can_set_name_of_some_channel_when_tv_is_on)
	{
		tv.TurnOn();
		boost::optional <string> nameChannel = "bbc";
		VerifyCommandWithNamesHandling("SetChannelName 23 bbc", 23, nameChannel , "");
	}

BOOST_AUTO_TEST_SUITE_END()

struct _after_set_names_of_some_channels : RemoteControlFixture
{
	_after_set_names_of_some_channels()
	{
		tv.TurnOn();
		tv.SetChannelName(45, "bbc rus");
		tv.SetChannelName(32, "1_channel");
		tv.SelectChannel(20);
	}
};
BOOST_FIXTURE_TEST_SUITE(_after_set_names_of_some_channels_, _after_set_names_of_some_channels)

	BOOST_AUTO_TEST_CASE(can_get_name_of_some_channel_when_tv_is_on)
	{
		boost::optional <string> nameChannel = "1_channel";
		VerifyCommandWithNamesHandling("GetChannelName 32", 32, nameChannel, "1_channel");
	}
	BOOST_AUTO_TEST_CASE(can_delete_name_of_some_channel_when_tv_is_on)
	{
		VerifyCommandWithNamesHandling("DeleteChannelName bbc rus", 45, none, "");
	}
	BOOST_AUTO_TEST_CASE(can_select_channel_by_channel_name)
	{
		VerifyCommandHandling("SelectChannel bbc rus", 45, "");
	}
	BOOST_AUTO_TEST_CASE(can_get_channel_by_channel_name)
	{
		boost::optional<string> channelName = "1_channel";
		VerifyCommandWithNamesHandling("GetChannelByName 1_channel", 32, channelName, "32");
	}
	BOOST_AUTO_TEST_CASE(can_select_previous_channel)
	{
		VerifyCommandHandling("SelectPreviousChannel", 1, "");
	}

BOOST_AUTO_TEST_SUITE_END()

struct _after_TV_is_off : _after_set_names_of_some_channels
{
	_after_TV_is_off()
	{
		tv.TurnOff();
	}
	void VerifyCommandWithNamesHandlingWhenTurnedOff(const string& command, const optional<unsigned> & channel, const optional<string> & channelName, const string& expectedOutput)
	{
		input << command;
		BOOST_CHECK(tv.IsTurnedOn() == false);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.GetChannelName((*channel)), channelName);
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(_after_TV_is_off_, _after_TV_is_off)
	BOOST_AUTO_TEST_CASE(can_not_get_name_of_some_channel)
	{
		VerifyCommandWithNamesHandlingWhenTurnedOff("GetChannelName 32", 32, none, "");
	}
	BOOST_AUTO_TEST_CASE(can_not_delete_name_of_some_channel_when_tv_is_on)
	{
		VerifyCommandWithNamesHandlingWhenTurnedOff("DeleteChannelName bbc rus", 45, none, "");
	}
	BOOST_AUTO_TEST_CASE(can_not_select_channel_by_channel_name)
	{
		VerifyCommandHandling("SelectChannel bbc rus", none, "");
	}
	BOOST_AUTO_TEST_CASE(can_not_select_channel)
	{
		VerifyCommandHandling("SelectChannel 45", none, "");
	}
	BOOST_AUTO_TEST_CASE(can_not_get_channel_by_channel_name)
	{
		VerifyCommandWithNamesHandlingWhenTurnedOff("GetChannelByName 1_channel", 32, none, "");
	}
	BOOST_AUTO_TEST_CASE(can_not_get_channel_name_by_channel_number)
	{
		VerifyCommandWithNamesHandlingWhenTurnedOff("GetChannelName 32", 32, none, "");
	}
	BOOST_AUTO_TEST_CASE(can_not_select_previous_channel)
	{
		VerifyCommandHandling("SelectPreviousChannel", none, "");
	}
BOOST_AUTO_TEST_SUITE_END()