#include "App1.h"

App1::App1()
{

}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);
	textureMgr->loadTexture(L"heightmap", L"res/height.png");
	lod[0] = 8;
	lod[1] = 8;
	terrainShader = new TerrainShader(renderer->getDevice(), hwnd);
	normalShader = new NormalShader(renderer->getDevice(), hwnd);
	depthShader = new DepthShader(renderer->getDevice(), hwnd);
	orthoShader = new OrthoShader(renderer->getDevice(), hwnd);
	lightShader = new LightShader(renderer->getDevice(), hwnd);

	light = new Light();
	light->setPosition(0, 10, 50);
	light->setDirection(50 - light->getPosition().x, 10 - light->getPosition().y, 50 - light->getPosition().z);
	light->setAmbientColour(0.3, 0.3, 0.3, 1);
	light->setDiffuseColour(0.6, 0.6, 0.3, 1);
	light->generateOrthoMatrix(screenWidth/10, screenHeight/30, 1.0f, 150.0f);
	light->generateViewMatrix();

	sWidth = screenWidth;
	sHeight = screenHeight;

	// Initalise scene variables.
	terrain = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 100 * lod[0]);
	water = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 100);
	//heightMap = new RenderTexture(renderer->getDevice(), 1024, 1024, SCREEN_NEAR, SCREEN_DEPTH);
	depthMap = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	orthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), 
		screenWidth / 4, screenHeight / 4,
		-(screenWidth / 2) + 160 , (screenHeight / 2) -160);
}


App1::~App1()
{

	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	
}



bool App1::frame()
{
	bool result;
	if (lod[0] != lod[1])
	{
		terrain = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 100 * lod[0]);
		lod[1] = lod[0];
	}


	float s = sin(XMConvertToRadians(0.1f));
	float c = cos(XMConvertToRadians(0.1f));

	XMFLOAT3 position = light->getPosition();

	position.x -= 50;
	position.z -= 50;

	float xNew = position.x * c - position.z * s;
	float zNew = position.x * s + position.z * c;

	light->setPosition(xNew + 50, position.y, zNew + 50);

	light->setDirection(50 - light->getPosition().x, 0 - light->getPosition().y, 50 - light->getPosition().z);
	light->generateOrthoMatrix(sWidth / 8, sHeight / 12, 0.1f, 141.0f);
	light->generateViewMatrix();
	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

void App1::GenerateHeightmap()
{
	ID3D11Texture2D* renderTargetTextureMap;
	ID3D11RenderTargetView* renderTargetViewMap;
	ID3D11ShaderResourceView* shaderResourceViewMap;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

}

void App1::depthPass()
{
	depthMap->setRenderTarget(renderer->getDeviceContext());
	depthMap->clearRenderTarget(renderer->getDeviceContext(), 1, 0, 0, 1);
	camera->update();

	XMMATRIX world = renderer->getWorldMatrix();
	XMMATRIX view = light->getViewMatrix();
	XMMATRIX projection = light->getOrthoMatrix();

	world = XMMatrixScaling(1.0f / (float)lod[0], 1.0, 1.0f / (float)lod[0]);
	terrain->sendData(renderer->getDeviceContext());
	depthShader->setShaderParameters(renderer->getDeviceContext(), 
		world, view, projection, 
		textureMgr->getTexture(L"heightmap"),
		light->getPosition());
	depthShader->render(renderer->getDeviceContext(), terrain->getIndexCount());

	renderer->setBackBufferRenderTarget();
}

void App1::lightPass()
{

}

bool App1::render()
{

	depthPass();
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();
	worldMatrix = XMMatrixScaling(1.0f / (float)lod[0], 1.0f, 1.0f / (float)lod[0]);
	terrain->sendData(renderer->getDeviceContext());
	terrainShader->setShaderParameters(renderer->getDeviceContext(),
		worldMatrix, viewMatrix, projectionMatrix,
		depthMap->getShaderResourceView(),textureMgr->getTexture(L"heightmap"),
		camera->getPosition(),light);
	terrainShader->render(renderer->getDeviceContext(), terrain->getIndexCount());

	if (normalToggle)
	{
		terrain->sendData(renderer->getDeviceContext());
		normalShader->setShaderParameters(renderer->getDeviceContext(), 
			worldMatrix, viewMatrix, projectionMatrix, 
			textureMgr->getTexture(L"heightmap"));
		normalShader->render(renderer->getDeviceContext(), terrain->getIndexCount());
	}
	//water->sendData(renderer->getDeviceContext());
	worldMatrix = renderer->getWorldMatrix();
	XMMATRIX orthoView = camera->getOrthoViewMatrix();
	XMMATRIX orthoMatrix = renderer->getOrthoMatrix();

	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	orthoShader->setShaderParameters(renderer->getDeviceContext(),
		worldMatrix, orthoView, orthoMatrix,
		depthMap->getShaderResourceView());
	orthoShader->render(renderer->getDeviceContext(),orthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Render GUI
	gui();

	// Present the rendered scene to the screen.
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);
	ImGui::Checkbox("Show normals", &normalToggle);
	ImGui::SliderInt("LOD", &lod[0], 1, 8);


	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

