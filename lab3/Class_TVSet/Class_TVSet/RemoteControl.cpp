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
		unsigned channel;
		strm >> channel;
		SelectedChannel(channel);
	}
	else if (action == "Info")
	{
		GetInfo();
	}
	else if (action == "SelectPreviousChannel")
	{
		SelectedPreviouseChannel();
	}
	else
	{
		return false;
	}
	return true;
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

bool CRemoteControl::SelectedChannel(unsigned channel)
{
	return m_tv.SelectChannel(channel);
}

void CRemoteControl::GetInfo()
{
	cout << m_tv.GetChannel() << endl;
}

bool CRemoteControl::SelectedPreviouseChannel()
{
	return m_tv.SelectPreviousChannel();
}