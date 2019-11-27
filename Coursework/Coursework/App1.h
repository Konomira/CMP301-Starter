// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "../DXFramework/PlaneMesh.h"
#include "TerrainShader.h"
#include "WaterShader.h"
#include "NormalShader.h"
#include "TextureShader.h"
class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void renderToTexture();
	void gui();
	void GenerateHeightmap();

private:
	Light* sun;
	RenderTexture* shadowMap;

	// Main terrain mesh
	PlaneMesh* terrain;
	
	// Sea level
	PlaneMesh* water;

	// Shaders
	TerrainShader* terrainShader;
	NormalShader* normalShader;
	WaterShader* waterShader;
	TextureShader* textureShader;

	// Loaded textures / maps
	RenderTexture* heightmap;

	// GUI
	bool normalToggle;

	OrthoMesh* pip;
};

#endif