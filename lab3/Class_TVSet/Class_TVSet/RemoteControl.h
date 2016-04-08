#pragma once
#include "TVSet.h"
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <map>


using namespace std;

class CRemoteControl
{
public:
	CRemoteControl(CTVSet & tv, istream & input, ostream & output);
	bool HandleCommand();
private:
	CTVSet & m_tv;
	istream & m_input;
	ostream & m_output;
private:
	bool TurnedOn();
	bool TurnedOff();
	void GetInfo()const;
	bool SelectedChannel(istringstream & strm);
	bool SetChannelName(istringstream & strm);
	void DeletedChannelName(istringstream & strm);
	void GetChannelName(istringstream & strm)const;
	void GetChannelByName(istringstream & strm)const;
};
