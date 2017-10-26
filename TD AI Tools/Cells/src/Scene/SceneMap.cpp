#include "stdafx.h"

#include "Scene\SceneMap.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"


SceneMap::SceneMap()
{
	// AI Tools
	m_bUseAITools = true;
	m_pAITools = new AITools;
}

SceneMap::~SceneMap()
{
	// AI Tools
	delete m_pAITools;
}
	
bool SceneMap::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Load Map
	m_pEntity3 = m_pGM->getEntity("map0");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map0.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onInit();
	}
	return true;
}

bool SceneMap::onUpdate()
{
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setScene(new SceneMenu());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num2))
	{
		m_pGM->setScene(new SceneGame());
		return true;
	}

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onUpdate();
	}

	return true;
}

bool SceneMap::onDraw()
{
	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onDraw();
	}

	return true;
}

bool SceneMap::onQuit()
{
	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onQuit();
	}

	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

