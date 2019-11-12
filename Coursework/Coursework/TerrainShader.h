#ifndef _TERRAINSHADER_H_
#define _TERRAINSHADER_H_

#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;


class TerrainShader : public BaseShader
{

public:

	TerrainShader(ID3D11Device* device, HWND hwnd);
	~TerrainShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
};

#endif