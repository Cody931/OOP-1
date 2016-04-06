#include "stdafx.h"
#include "TVSet.h"
#include <iostream>

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

unsigned CTVSet::GetChannel()const
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