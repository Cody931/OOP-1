#include "stdafx.h"
#include "TVSet.h"
#include <iostream>

using namespace std;

namespace
{
	const unsigned MAX_CHANNEL_COUNT = 99;
	const unsigned MIN_CHANNEL_COUNT = 1;
}


bool CTVSet::IsTurnedOn()const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

unsigned CTVSet::GetChannel()const
{
	return IsTurnedOn() ? m_selectedChannel : 0;
}

bool CTVSet::SelectChannel(unsigned channel)
{
	bool isAvailableChannel = (channel >= MIN_CHANNEL_COUNT) && (channel <= MAX_CHANNEL_COUNT);
	if (m_isOn && isAvailableChannel)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SelectChannel(string const& channelName)
{
	if (channelName.size() && m_isOn)
	{
		boost::optional <unsigned> channel = GetChannelByName(channelName);
		if (channel)
		{
			m_prevChannel = m_selectedChannel;
			m_selectedChannel = *channel;
			return true;
		}
	}
	return false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn && (m_prevChannel != 0))
	{
		swap(m_prevChannel, m_selectedChannel);
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(unsigned channel, string const& channelName)
{
	bool isAviableChannel = (channel >= MIN_CHANNEL_COUNT) && (channel <= MAX_CHANNEL_COUNT);
	if (m_isOn && isAviableChannel && channelName.size())
	{
		if (m_tvChannelsNumbers.find(channel) != m_tvChannelsNumbers.end())
		{
			m_tvChannelsNumbers[channel] = channelName;
			m_tvChannelsName[channelName] = channel;
			return true;
		}
		m_tvChannelsNumbers.insert(pair<int, string>(channel, channelName));
		m_tvChannelsName.insert(pair<string, unsigned>(channelName, channel));
		return true;
	}
	return false;
}

bool CTVSet::DeleteChannelName(string const& channelName)
{
	if (m_isOn)
	{
		auto it = m_tvChannelsName.find(channelName);
		if (it != m_tvChannelsName.end())
		{
			unsigned channel = it->second;
			m_tvChannelsName.erase(it++);
			m_tvChannelsNumbers.erase(m_tvChannelsNumbers.find(channel));
			return true;
		}
	}
	return false;
}

boost::optional <string> CTVSet::GetChannelName(unsigned channel)const
{
	boost::optional<string> channelName;
	if (m_isOn)
	{
		auto it = m_tvChannelsNumbers.find(channel);
		if (it != m_tvChannelsNumbers.end())
		{
			channelName = it->second;
		}
	}
	return channelName;
}

boost::optional <unsigned> CTVSet::GetChannelByName(string const& channelName)const
{
	boost::optional <unsigned> channel;
	if (m_isOn)
	{
		auto it = m_tvChannelsName.find(channelName);
		if (it != m_tvChannelsName.end())
		{
			channel = it->second;
		}
	}
	return channel;
}