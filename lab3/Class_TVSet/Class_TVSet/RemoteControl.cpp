#include "stdafx.h"
#include "RemoteControl.h"

using namespace std::placeholders;
using namespace std;

CRemoteControl::CRemoteControl(CTVSet & tv, istream & input, ostream & output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "TurnOn", bind(&CRemoteControl::TurnedOn, this, _1) },
		{ "TurnOff", bind(&CRemoteControl::TurnedOff, this, _1) },
		{ "SelectChannel", bind(&CRemoteControl::SelectedChannel, this, _1) },
		{ "Info", bind(&CRemoteControl::GetInfo, this, _1) },
		{ "SelectPreviousChannel", bind(&CRemoteControl::SelectedPreviousChannel, this, _1) },
		{ "SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1) },
		{ "DeleteChannelName", bind(&CRemoteControl::DeletedChannelName, this, _1) },
		{ "GetChannelName", bind(&CRemoteControl::GetChannelName, this, _1) },
		{ "GetChannelByName", bind(&CRemoteControl::GetChannelByName, this, _1) },
	})
{}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);
	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		cout << ((!it->second(strm)) ? "Operation can't be executed!\n" : "\n");
		return true;
	}
	else
	{
		return false;
	}
}

bool CRemoteControl::SelectedPreviousChannel(std::istream & args)
{
	return ((m_tv.SelectPreviousChannel() ? true : false));
}

bool CRemoteControl::TurnedOn(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		return false;
	}
	m_tv.TurnOn();
	m_output << "TV is turned ON";
	return true;
}

bool CRemoteControl::TurnedOff(std::istream & args)
{
	if (!m_tv.IsTurnedOn())
	{
		return false;
	}
	m_tv.TurnOff();
	m_output << "TV is turned OFF";
	return true;
}

bool CRemoteControl::SetChannelName(istream & strm)
{
	unsigned channel;
	strm >> channel;
	string buf, channelName;
	while (strm >> buf)
	{
		channelName += (channelName.size() ? (' ' + buf) : buf);
	}
	return m_tv.SetChannelName(channel, channelName);
}

bool CRemoteControl::SelectedChannel(istream & strm)
{
	string value;
	strm >> value;
	unsigned channel = atoi(value.c_str());
	if ((channel > 0) && (channel < 100))
	{ 
		return m_tv.SelectChannel(channel);
	}
	return m_tv.SelectChannel(value);
}

bool CRemoteControl::GetInfo(istream & args)const
{
	if (m_tv.IsTurnedOn())
	{
		for (auto it : m_tv.m_tvChannelsNumbers)
		{
			cout << it.first << " - " << it.second << endl;
		}
	}
	m_tv.GetChannel() == 0 ? (m_output << "TV is OFF.") : (m_output << "Selected channel : " << m_tv.GetChannel());
	return true;
}

bool CRemoteControl::DeletedChannelName(istream & strm)
{
	string channelName;
	strm >> channelName;
	return m_tv.DeleteChannelName(channelName);
}

bool CRemoteControl::GetChannelName(istream & strm)const
{
	unsigned channel;
	strm >> channel;
	if (m_tv.IsTurnedOn())
	{
		boost::optional <string> channelName = m_tv.GetChannelName(channel);
		m_output << (channelName ? *channelName : "Channel name doesn't set!");
		return true;
	}
	return false;
}

bool CRemoteControl::GetChannelByName(istream & strm)const
{
	string channelName;
	strm >> channelName;
	boost::optional <unsigned> channel = m_tv.GetChannelByName(channelName);
	if (m_tv.IsTurnedOn())
	{
		if (channel)
		{
			m_output << (*channel);
		}
		else
		{
			m_output << "There is no channel with the same name!";
		}
		return true;
	}
	return false;
}