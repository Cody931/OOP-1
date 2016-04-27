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
		it->second(strm);
	}
	else
	{
		return false;
	}
}

bool CRemoteControl::SelectedPreviousChannel(std::istream & args)
{
	return m_tv.SelectPreviousChannel();
}

bool CRemoteControl::TurnedOn(std::istream & args)
{
	if (m_tv.IsTurnedOn())
	{
		return false;
	}
	m_tv.TurnOn();
	m_output << "TV is turned ON\n";
	return true;
}

bool CRemoteControl::TurnedOff(std::istream & args)
{
	if (!m_tv.IsTurnedOn())
	{
		return false;
	}
	m_tv.TurnOff();
	m_output << "TV is turned OFF" << endl;
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
	m_tv.PrintNamesOfChannels();
	m_tv.GetInfo() == 0 ? (m_output << "TV is OFF.\n") : (m_output << "Selected channel : " << m_tv.GetChannel() << endl);
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
	string channelName = m_tv.GetChannelName(channel);
	m_output << (channelName.size() ? channelName : "Channel name doesn't set!") << endl;
	return true;
}

bool CRemoteControl::GetChannelByName(istream & strm)const
{
	string channelName;
	strm >> channelName;
	unsigned channel = m_tv.GetChannelByName(channelName);
	if (channel != 0)
	{
		m_output << channel << endl;
		return true;
	}
	else
	{
		m_output << "There is no channel with the same name!\n";
	}
	return false;
}