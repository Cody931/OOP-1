#include "stdafx.h"
#include "RemoteControl.h"

using namespace std;

CRemoteControl::CRemoteControl(CTVSet & tv, istream & input, ostream & output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);
	string action;
	strm >> action;

	if (action == "TurnOn")
	{
		TurnedOn();
	}
	else if (action == "TurnOff")
	{
		TurnedOff();
	}
	else if (action == "SelectChannel")
	{
		SelectedChannel(strm);
	}
	else if (action == "Info")
	{
		GetInfo();
	}
	else if (action == "SelectPreviousChannel")
	{
		m_tv.SelectPreviousChannel();
	}
	else if (action == "SetChannelName")
	{
		SetChannelName(strm);
	}
	else if (action == "DeleteChannelName")
	{
		DeletedChannelName(strm);
	}
	else if (action == "GetChannelName")
	{
		GetChannelName(strm);
	}
	else if (action == "GetChannelByName")
	{
		GetChannelByName(strm);
	}
	else
	{
		return false;
	}
}

bool CRemoteControl::TurnedOn()
{
	if (m_tv.IsTurnedOn())
	{
		return false;
	}
	m_tv.TurnOn();
	cout << "TV is turned ON" << endl;
	return true;
}

bool CRemoteControl::TurnedOff()
{
	if (!m_tv.IsTurnedOn())
	{
		return false;
	}
	m_tv.TurnOff();
	cout << "TV is turned OFF" << endl;
	return true;
}

bool CRemoteControl::SetChannelName(istringstream & strm)
{
	unsigned channel;
	strm >> channel;
	string buf, nameChannel;
	while (strm >> buf)
	{
		nameChannel += (nameChannel.size() ? (' ' + buf) : buf);
	}
	return m_tv.SetChannelName(channel, nameChannel);
}

bool CRemoteControl::SelectedChannel(istringstream & strm)
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

void CRemoteControl::GetInfo()const
{
	m_tv.GetInfo() == 0 ? (cout << "TV is OFF.\n") : (cout << "Selected channel : " << m_tv.GetChannel() << endl);
}

void CRemoteControl::DeletedChannelName(istringstream & strm)
{
	string channelName;
	strm >> channelName;
	m_tv.DeleteChannelName(channelName);
}

void CRemoteControl::GetChannelName(istringstream & strm)const
{
	unsigned channel;
	strm >> channel;
	string channelName = m_tv.GetChannelName(channel);
	cout << (channelName.size() ? channelName : "Channel name doesn't set!") << endl;
}

void CRemoteControl::GetChannelByName(istringstream & strm)const
{
	string channelName;
	strm >> channelName;
	unsigned channel = m_tv.GetChannelByName(channelName);
	if (channel != 0)
	{
		cout << channel << endl;
	}
	else
	{
		"There is no channel with the same name!\n";
	}
}