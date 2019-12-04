// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "../DXFramework/PlaneMesh.h"
#include "TerrainShader.h"
#include "WaterShader.h"
#include "NormalShader.h"
#include "DepthShader.h"
#include "OrthoShader.h"
#include "LightShader.h"
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
	void GenerateHeightmap();
	void depthPass();
	void lightPass();
	float sWidth, sHeight;

private:
	// Main terrain mesh
	PlaneMesh* terrain;
	bool normalToggle;
	// Sea level
	PlaneMesh* water;

	TerrainShader* terrainShader;
	NormalShader* normalShader;
	WaterShader* waterShader;
	DepthShader* depthShader;
	OrthoShader* orthoShader;
	LightShader* lightShader;


	RenderTexture* depthMap;
	RenderTexture* heightMap;
	OrthoMesh* orthoMesh;

	Light* light;

	int lod[2];
};

#endif