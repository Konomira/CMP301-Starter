// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "../DXFramework/PlaneMesh.h"
#include "TerrainShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	// Main terrain mesh
	PlaneMesh* terrain;

	// Sea level
	PlaneMesh* water;

	TerrainShader* shader;
};

#endif