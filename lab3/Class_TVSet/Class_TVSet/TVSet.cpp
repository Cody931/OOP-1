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
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
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
		for (auto it : m_tvChannels)
		{
			if (it.second == channelName)
			{
				m_prevChannel = m_selectedChannel;
				m_selectedChannel = it.first;
				return true;
			}
		}
	}
	return true;
}

void CTVSet::PrintNamesOfChannels()const
{
	for (auto it : m_tvChannels)
	{
		cout << it.first << " - " << it.second << endl;
	}
}

unsigned CTVSet::GetInfo()const
{
	return m_isOn ? m_selectedChannel : 0;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn && (m_prevChannel != 0))
	{
		unsigned prevChannel = m_prevChannel;
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = prevChannel;
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(unsigned channel, string const& channelName)
{
	bool isAviableChannel = (channel >= 1) && (channel <= 99);
	if (m_isOn && isAviableChannel && channelName.size())
	{
		if (m_tvChannels.find(channel) != m_tvChannels.end())
		{
			m_tvChannels[channel] = channelName;
			return true;
		}
		m_tvChannels.insert(pair<int, string>(channel, channelName));
		return true;
	}
	return false;
}

bool CTVSet::DeleteChannelName(string const& channelName)
{
	for (auto it = m_tvChannels.begin(); it != m_tvChannels.end(); )
	{
		if (it->second == channelName)
		{
			m_tvChannels.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

string CTVSet::GetChannelName(unsigned channel)const
{
	string channelName;
	auto it = m_tvChannels.find(channel);
	if (it != m_tvChannels.end())
	{
		channelName = it->second;
	}
	return channelName;
}

unsigned CTVSet::GetChannelByName(string const& channelName)const
{
	for (auto it : m_tvChannels)
	{
		if (it.second == channelName)
		{
			return it.first;
		}
	}
	return false;
}