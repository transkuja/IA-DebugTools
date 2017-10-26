/***************************************************/
/* Nom:	AITools.h
/* Description: AITools
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __AITools_H_
#define __AITools_H_

#include "Core\Scene.h"
using namespace crea;

class AITools
{
	GameManager*	m_pGM;

	// Selection
	Vector2f positionOnClic;
	bool mouseButtonWasPressedLastFrame = false;

	FloatRect* selectionRect;
	RectangleShape* selectionRectShape;
	Color* blankColor = new Color();
	Color* magenta = new Color();
	int fpsNeedRefresh = 0;

	// Command

	// Diagnostics
	float fps;
	double timeBeforeFPSPrint;

public:
	AITools();
	virtual ~AITools();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
