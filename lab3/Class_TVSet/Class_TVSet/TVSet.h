#pragma once
#include <map>
#include <string>

class CTVSet
{
public:
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(unsigned channel);
	bool SelectChannel(std::string const& channelName);
	unsigned GetChannel()const;
	bool SelectPreviousChannel();
	bool SetChannelName(unsigned channel, std::string const& channelName);
	bool DeleteChannelName(std::string const& channelName);
	boost::optional <std::string> GetChannelName(unsigned channel)const;
	boost::optional <unsigned> GetChannelByName(std::string const& channelName)const;
private:
	bool m_isOn = false;
	unsigned m_selectedChannel = 1;
	unsigned m_prevChannel = 0;
public:
	std::map<unsigned, std::string> m_tvChannelsNumbers;
	std::map<std::string, unsigned> m_tvChannelsName;
};

