#include "App1.h"

App1::App1()
{

}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);
	textureMgr->loadTexture(L"heightmap", L"res/height.png");

	terrainShader = new TerrainShader(renderer->getDevice(), hwnd);

	// Initalise scene variables.
	terrain = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 100);
	water = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 100);
	heightmap = new RenderTexture(renderer->getDevice(), 1024, 1024, SCREEN_NEAR, SCREEN_DEPTH);

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

bool App1::render()
{
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	terrain->sendData(renderer->getDeviceContext());
	terrainShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"heightmap"));
	terrainShader->render(renderer->getDeviceContext(), terrain->getIndexCount());

	water->sendData(renderer->getDeviceContext());
	

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

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

