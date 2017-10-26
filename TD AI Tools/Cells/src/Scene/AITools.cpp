#include "stdafx.h"

#include "Scene\AITools.h"
#include "Scene\SceneMenu.h"
#include "Core\SceneManager.h"
#include <string>

AITools::AITools()
{

}

AITools::~AITools()
{

}
	
bool AITools::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Selection
	blankColor = new Color();
	blankColor->setValues(0, 0, 0, 0);

	selectionRectShape = new RectangleShape();
	selectionRectShape->setSize(0.0f, 0.0f);

	selectionRectShape->setOutlineThickness(2.0f);
	selectionRectShape->setColor(blankColor);
	// Commands

	// Diagnostics

	return true;
}

bool AITools::onUpdate()
{
	// Selection
	bool mouseButtonPressed = m_pGM->isMouseButtonPressed(Button::MouseLeft);
	if (!mouseButtonWasPressedLastFrame && mouseButtonPressed)
	{
		m_pGM->unselectEntities();
		positionOnClic = m_pGM->getMousePosition();
		selectionRect = new FloatRect();
		
		selectionRectShape->setPosition(positionOnClic.getX(), positionOnClic.getY());
	}

	if (mouseButtonWasPressedLastFrame && !mouseButtonPressed)
		m_pGM->selectEntities(positionOnClic, m_pGM->getMousePosition());

	mouseButtonWasPressedLastFrame = mouseButtonPressed;

	// Show selection rect
	if (mouseButtonPressed)
	{
		// TODO: abs
		selectionRect->m_fH = m_pGM->getMousePosition().getY() - positionOnClic.getY();
		selectionRect->m_fW = m_pGM->getMousePosition().getX() - positionOnClic.getX();
		selectionRect->m_fX = positionOnClic.getX();
		selectionRect->m_fY = positionOnClic.getY();

		selectionRectShape->setSize(selectionRect->m_fW, selectionRect->m_fH);
	}

	// Command
	//m_rCommandWindow.contains(vMousePosition)
	cout << m_pGM->getSelectedEntities()->size() << endl;

	return true;
}

bool AITools::onDraw()
{
	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
		selectionRectShape->draw();

	// Commands

	// Diagnostics
	// Agent* pAgent = pEntity->getComponent<Agent>();

	return true;
}

bool AITools::onQuit()
{

	return true;
}

