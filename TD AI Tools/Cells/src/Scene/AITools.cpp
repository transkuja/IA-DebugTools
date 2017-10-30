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
	vertCacaDOie->setValues(121, 137, 51, 255);
	fuschia->setValues(219, 0, 115, 255);

	selectionRectShape = new RectangleShape();
	selectionRectShape->setSize(0.0f, 0.0f);

	selectionRectShape->setOutlineThickness(2.0f);
	selectionRectShape->setColor(blankColor);
	selectionRectShape->setOutlineColor(fuschia);

	// Commands
	commandSprite = m_pGM->getSprite("Commands");
	commandSprite->setTexture(m_pGM->getTexture("debug/Commands.png"));
	commandSprite->setPosition(m_pGM->getWindowRect().getWidth() + 256.0f, m_pGM->getWindowRect().getHeight() + 256.0f);

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
		selectionRect->m_fH = m_pGM->getMousePosition().getY() - positionOnClic.getY();
		selectionRect->m_fW = m_pGM->getMousePosition().getX() - positionOnClic.getX();
		selectionRect->m_fX = positionOnClic.getX();
		selectionRect->m_fY = positionOnClic.getY();

		selectionRectShape->setSize(selectionRect->m_fW, selectionRect->m_fH);
	}

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
	fps = 1 / TimeManager::getSingleton()->getFrameTime().asSeconds();

	Text fpsText;
	fpsText.setCharacterSize(20);
	fpsText.setFont(m_pGM->getFont("arial.ttf"));
	fpsText.setPosition(900.0f, 10.0f);
	fpsText.setString(to_string((int)fps) + " fps");
	fpsText.setColor(magenta);
	fpsText.draw();
	

	ListEntity* entitties = m_pGM->getSelectedEntities();
	for (std::list<Entity*>::iterator it = entitties->begin(); it != entitties->end(); it++)
	{
		Text unitName;
		unitName.setCharacterSize(20);
		unitName.setFont(m_pGM->getFont("arial.ttf"));
		unitName.setPosition((*it)->getPosition().getX(), (*it)->getPosition().getY() - 30.0f);	
		unitName.setString((*it)->getName());
		unitName.setColor(vertCacaDOie);
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
			unitStats.setColor(vertCacaDOie);
			unitStats.draw();
		}
	}

	// Draw grid
	RectangleShape* gridRectangle = new RectangleShape();
	gridRectangle->setSize(gridUnitSize, gridUnitSize);
	gridRectangle->setOutlineThickness(.5f);
	gridRectangle->setColor(blankColor);
	gridRectangle->setOutlineColor(magenta);

	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			gridRectangle->setPosition(j * gridUnitSize, i * gridUnitSize);
			gridRectangle->draw();
		}
	}

	commandSprite->draw();
	return true;
}

bool AITools::onQuit()
{

	return true;
}

