#ifndef _TERRAINSHADER_H_
#define _TERRAINSHADER_H_

#include "../DXFramework/BaseShader.h"
#include "Light.h"

using namespace std;
using namespace DirectX;


class TerrainShader : public BaseShader
{

public:

	TerrainShader(ID3D11Device* device, HWND hwnd);
	~TerrainShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, 
		const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		ID3D11ShaderResourceView* depthMap, ID3D11ShaderResourceView* heightMap,
		XMFLOAT3 camPos, Light* light);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11Buffer * heightBuffer;
	ID3D11Buffer * lightBuffer;
	ID3D11SamplerState* depthSamplerState;

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	struct HeightBufferType
	{
		XMFLOAT4 scale;
		XMFLOAT4 heightOffset;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		XMFLOAT3 position;
		XMFLOAT2 padding;
	};
};

#endif