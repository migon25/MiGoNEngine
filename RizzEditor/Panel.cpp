#include "Panel.h"

Panel::Panel(){}
Panel::	~Panel(){}

void Panel::Activate(bool enabled)
{
	active = enabled;
}

void Panel::SwitchActive()
{
	active = !active;
}

bool Panel::IsActive()
{
	return active;
}
