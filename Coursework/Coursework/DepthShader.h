#ifndef _DEPTHSHADER_H_
#define _DEPTHSHADER_H_

#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;


class DepthShader : public BaseShader
{

public:

	DepthShader(ID3D11Device* device, HWND hwnd);
	~DepthShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext,
		const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		ID3D11ShaderResourceView* texture, XMFLOAT3 camPos);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11Buffer * heightBuffer;
	ID3D11Buffer * cameraBuffer;

	struct HeightBufferType
	{
		XMFLOAT4 scale;
		XMFLOAT4 heightOffset;
	};

	struct CameraBufferType
	{
		XMFLOAT3 position;
		float padding;
	};
};

#endif