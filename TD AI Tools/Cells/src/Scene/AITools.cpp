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
	delete selectionRect;
	delete selectionRectShape;
	delete blankColor;
	delete magenta;
	delete vertCacaDOie;
	delete fuschia;
	delete m_rCommandWindow;
	delete commandText;
	delete gridRectangle;
	delete fpsText;
}
	
bool AITools::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Selection
	blankColor->setValues(0, 0, 0, 0);
	magenta->setValues(255, 0, 255, 255);
	vertCacaDOie->setValues(121, 137, 51, 255);
	fuschia->setValues(219, 0, 115, 255);

	selectionRectShape->setSize(0.0f, 0.0f);
	selectionRectShape->setOutlineThickness(2.0f);
	selectionRectShape->setColor(blankColor);
	selectionRectShape->setOutlineColor(fuschia);

	// Commands
	m_rCommandWindow = new FloatRect(m_pGM->getWindowRect().getWidth() + 256.0f, m_pGM->getWindowRect().getHeight() + 256.0f, 5 * 46.0f, 2 * 38.0f);

	commandSprite = m_pGM->getSprite("Commands");
	commandSprite->setTexture(m_pGM->getTexture("debug/Commands.png"));
	commandSprite->setPosition(m_pGM->getWindowRect().getWidth() + 256.0f, m_pGM->getWindowRect().getHeight() + 256.0f);

	commandText->setFont(m_pGM->getFont("arial.ttf"));
	commandText->setPosition(900, 120);
	commandText->setString("Last command: None");
	commandText->setCharacterSize(15.0f);
	commandText->setColor(magenta);

	commands[0] = "Reset";
	commands[1] = "Kill";
	commands[2] = "Stop";
	commands[3] = "GoToHQ";
	commands[4] = "GoTo (bad practice)";
	commands[5] = "Build";
	commands[6] = "Mine";
	commands[7] = "Harvest";
	commands[8] = "Suicide";
	commands[9] = "Boost";

	// Diagnostics
	gridRectangle->setSize(gridUnitSize, gridUnitSize);
	gridRectangle->setOutlineThickness(.5f);
	gridRectangle->setColor(blankColor);
	gridRectangle->setOutlineColor(magenta);

	fpsText->setCharacterSize(20);
	fpsText->setFont(m_pGM->getFont("arial.ttf"));
	fpsText->setPosition(900.0f, 10.0f);
	fpsText->setString(" fps");
	fpsText->setColor(magenta);

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
	if (m_pGM->isMouseButtonPressed(Button::MouseRight))
	{
		Vector2f mousePos = Vector2f(m_pGM->getMousePosition().getX() - m_rCommandWindow->m_fX, m_pGM->getMousePosition().getY() - m_rCommandWindow->m_fY);
		if (m_rCommandWindow->contains(m_pGM->getMousePosition()))
			commandText->setString("Last command: " + commands[(int)(mousePos.getX() / 46.0f) + ((int)(mousePos.getY() / 38.0f) * 5)]);
	}

	return true;
}

bool AITools::onDraw()
{
	// Draw grid
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			gridRectangle->setPosition(j * gridUnitSize, i * gridUnitSize);
			gridRectangle->draw();
		}
	}


	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
		selectionRectShape->draw();

	// Diagnostics
	fpsText->setString(to_string((int)(1 / TimeManager::getSingleton()->getFrameTime().asSeconds())) + " fps");
	fpsText->draw();
	

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

	// Commands
	commandSprite->draw();
	commandText->draw();
	return true;
}

bool AITools::onQuit()
{

	return true;
}

