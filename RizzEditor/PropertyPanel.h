#ifndef PROPERTY_PANEL_H
#define PROPERTY_PANEL_H

#include "Panel.h"
#include "..\RiZzEngine\RizzEngine.h"
class PropertyPanel : public Panel
{
public:
	PropertyPanel(std::vector<GameObject*>& model);
	virtual ~PropertyPanel();

	void Render() override;
	void ObjectSelection();

	int objectSelected = 0;

private:
	std::vector<GameObject*>& Model;

};

#endif //PROPERTY_PANEL_H