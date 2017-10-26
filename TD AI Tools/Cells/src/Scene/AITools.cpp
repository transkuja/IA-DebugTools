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

	// Commands

	// Diagnostics

	return true;
}

bool AITools::onUpdate()
{
	// Selection

	// m_pGM->isMouseButtonPressed(Button::MouseLeft)
	// m_pGM->getMousePosition();
	// m_pGM->unselectEntities();
	// m_pGM->selectEntities( ...);

	// Command
	// m_rCommandWindow.contains(vMousePosition)
	// m_pGM->getSelectedEntities();

	return true;
}

bool AITools::onDraw()
{
	// Selection

	// Commands

	// Diagnostics
	// Agent* pAgent = pEntity->getComponent<Agent>();

	return true;
}

bool AITools::onQuit()
{

	return true;
}

