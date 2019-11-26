#ifndef _NORMALSHADER_H_
#define _NORMALSHADER_H_

#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;


class NormalShader : public BaseShader
{

public:

	NormalShader(ID3D11Device* device, HWND hwnd);
	~NormalShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext,
		const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		ID3D11ShaderResourceView* texture);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11Buffer * heightBuffer;

	struct HeightBufferType
	{
		XMFLOAT4 scale;
		XMFLOAT4 heightOffset;
	};
};

#endif