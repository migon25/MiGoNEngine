#ifndef PANEL_H
#define PANEL_H

class Panel
{
public:
	Panel();
	~Panel();
	void Activate(bool enabled);
	void SwitchActive();
	bool IsActive();

	virtual void Render() = 0;

public:
	bool active = false;
};

#endif //PANEL_H