#include "stdafx.h"
#include "TVSet.h"
#include <iostream>
#include <string>

using namespace std;


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
	return m_selectedChannel;
}

bool CTVSet::SelectChannel(unsigned channel)
{
	bool isAviableChannel = (channel >= 1) && (channel <= 99);
	if (m_isOn && isAviableChannel)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SelectChannel(string const& nameChannel)
{
	if (nameChannel.size() && m_isOn)
	{
		for (auto it : m_tvChannels)
		{
			if (it.second == nameChannel)
			{
				m_prevChannel = m_selectedChannel;
				m_selectedChannel = it.first;
				return true;
			}
		}
	}
	return true;
}

unsigned CTVSet::GetInfo()const
{
	for (auto it : m_tvChannels)
	{
		cout << it.first << " - " << it.second << endl;
	}
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

bool CTVSet::SetChannelName(unsigned channel, string const& nameChannel)
{
	bool isAviableChannel = (channel >= 1) && (channel <= 99);
	if (m_isOn && isAviableChannel && nameChannel.size())
	{
		cout << channel << " - " << nameChannel << endl;
		if (m_tvChannels.find(channel) != m_tvChannels.end())
		{
			m_tvChannels[channel] = nameChannel;
			return true;
		}
		m_tvChannels.insert(pair<int, string>(channel, nameChannel));
		return true;
	}
	return false;
}

bool CTVSet::DeleteChannelName(string const& nameChannel)
{
	for (map<unsigned, string>::iterator it = m_tvChannels.begin(); it != m_tvChannels.end(); )
	{
		if (it->second == nameChannel)
		{
			m_tvChannels.erase(it++);
		}
		else
			++it;
	}
	return true;
}

string CTVSet::GetChannelName(unsigned channel)const
{
	string nameChannel;
	auto it = m_tvChannels.find(channel);
	if (it != m_tvChannels.end())
	{
		nameChannel = it->second;
	}
	return nameChannel;
}

unsigned CTVSet::GetChannelByName(string const& nameChannel)const
{
	for (auto it : m_tvChannels)
	{
		if (it.second == nameChannel)
		{
			return it.first;
		}
	}
	return 0;
}