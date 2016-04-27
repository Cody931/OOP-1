#include "stdafx.h"
#include "../Class_TVSet/RemoteControl.h"
#include "../Class_TVSet/TVSet.h"


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
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
{
	VerifyCommandHandling("TurnOn", 1, "TV is turned ON\n");
}

BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("TurnOff", none, "TV is turned OFF\n");
}

BOOST_AUTO_TEST_CASE(can_show_info_when_tv_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("Info", 1, "Selected channel : 1\n");
}

BOOST_AUTO_TEST_CASE(can_show_info_when_tv_is_off)
{
	tv.TurnOff();
	VerifyCommandHandling("Info", none, "TV is OFF.\n");
}

BOOST_AUTO_TEST_CASE(can_get_name_of_some_channel_when_tv_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("GetChannelName", 1, "Channel name doesn't set!\n");
}

BOOST_AUTO_TEST_SUITE_END()
