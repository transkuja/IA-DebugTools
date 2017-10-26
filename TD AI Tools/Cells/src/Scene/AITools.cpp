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
	blankColor->setValues(0, 0, 0, 0);
	magenta->setValues(255, 0, 255, 255);

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

	fpsNeedRefresh++;
	// Command
	//m_rCommandWindow.contains(vMousePosition)
	//cout << m_pGM->getSelectedEntities()->size() << endl;

	return true;
}

bool AITools::onDraw()
{
	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
		selectionRectShape->draw();

	// Commands

	// Diagnostics
	// TODO: remove this shit
	if (fpsNeedRefresh > 100)
	{
		fps = 1 / TimeManager::getSingleton()->getFrameTime().asSeconds();
		fpsNeedRefresh = 0;
	}

	Text fpsText;
	fpsText.setCharacterSize(20);
	fpsText.setFont(m_pGM->getFont("arial.ttf"));
	fpsText.setPosition(900.0f, 10.0f);
	fpsText.setString(to_string((int)fps) + " fps");
	fpsText.setColor(magenta);
	fpsText.draw();
	

	ListEntity* entities = m_pGM->getSelectedEntities();
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{
		Text unitName;
		unitName.setCharacterSize(20);
		unitName.setFont(m_pGM->getFont("arial.ttf"));
		unitName.setPosition((*it)->getPosition().getX(), (*it)->getPosition().getY() - 30.0f);
		unitName.setString((*it)->getName());
		unitName.setColor(magenta);
		unitName.draw();

		Agent* pAgent = (*it)->getComponent<Agent>();
		if (pAgent != nullptr)
		{
			Text unitStats;
			unitStats.setCharacterSize(18);
			unitStats.setFont(m_pGM->getFont("arial.ttf"));
			unitStats.setPosition((*it)->getPosition().getX(), (*it)->getPosition().getY() - 10.0f);
			string textString = "Dexterity:" + to_string(pAgent->getDexterity())
				+ " Health:" + to_string(pAgent->getHealth())
				+ " Strength:" + to_string(pAgent->getStrength())
				+ " Int:" + to_string(pAgent->getIntelligence());
			unitStats.setString(textString);
			unitStats.setColor(magenta);
			unitStats.draw();
		}
	}

	return true;
}

bool AITools::onQuit()
{

	return true;
}

