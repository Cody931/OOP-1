#pragma once
#include <map>
#include <string>

using namespace std;


class CTVSet
{
public:
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(unsigned channel);
	bool SelectChannel(string const& nameChannel);
	unsigned GetInfo()const;
	unsigned GetChannel()const;
	bool SelectPreviousChannel();
	bool SetChannelName(unsigned channel, string const& nameChannel);
	bool DeleteChannelName(string const& nameChannel);
	string GetChannelName(unsigned channel)const;
	unsigned GetChannelByName(string const& nameChannel)const;
private:
	bool m_isOn = false;
	unsigned m_selectedChannel = 1;
	unsigned m_prevChannel = 0;
	map<unsigned, string> m_tvChannels;
};

