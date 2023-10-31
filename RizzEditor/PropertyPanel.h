#ifndef PROPERTY_PANEL_H
#define PROPERTY_PANEL_H

#include "Panel.h"
#include "..\RiZzEngine\RizzEngine.h"
class PropertyPanel : public Panel
{
public:
	PropertyPanel(RizzEngine& engine);
	virtual ~PropertyPanel();

	void Render() override;

private:
	RizzEngine& Engine;
};

#endif //PROPERTY_PANEL_H