#pragma once
class CTVSet
{
public:
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(unsigned channel);
	unsigned GetChannel()const;
	bool SelectPreviousChannel();
private:
	bool m_isOn = false;
	unsigned m_selectedChannel = 1;
	unsigned m_prevChannel = 0;
};

