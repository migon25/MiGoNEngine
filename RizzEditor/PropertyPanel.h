#ifndef PROPERTY_PANEL_H
#define PROPERTY_PANEL_H

#include "Panel.h"
#include "..\RiZzEngine\RizzEngine.h"
class PropertyPanel : public Panel
{
public:
	PropertyPanel(std::vector<GameObject*>& model, Camera& camera);
	virtual ~PropertyPanel();

	void Render() override;
	void ObjectSelection();
	void TransformationPanel();

	int objectSelected = 0;
	bool objectIsSelected = false;

	Camera& camera;
private:
	std::vector<GameObject*>& Model;

};

#endif //PROPERTY_PANEL_H