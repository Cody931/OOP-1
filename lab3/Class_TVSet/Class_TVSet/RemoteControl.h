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
	bool SelectedChannel(unsigned channel);
	void GetInfo();
	bool CRemoteControl::SelectedPreviouseChannel();
};
