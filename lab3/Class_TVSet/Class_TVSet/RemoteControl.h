#pragma once
#include "TVSet.h"


using namespace std;

class CRemoteControl
{
public:
	CRemoteControl(CTVSet & tv, istream & input, ostream & output);
	bool HandleCommand();
private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;
	CTVSet & m_tv;
	istream & m_input;
	ostream & m_output;
	const ActionMap m_actionMap;
private: 
	bool TurnedOn(std::istream & args);
	bool TurnedOff(std::istream & args);
	bool GetInfo(std::istream & args)const;
	bool SelectedPreviousChannel(std::istream & args);
	bool SelectedChannel(std::istream & strm);
	bool SetChannelName(std::istream & strm);
	bool DeletedChannelName(std::istream & strm);
	bool GetChannelName(std::istream & strm)const;
	bool GetChannelByName(std::istream & strm)const;
};
