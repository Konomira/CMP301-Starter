#ifndef _WATERSHADER_H_
#define _WATERSHADER_H_

#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;


class WaterShader : public BaseShader
{

public:

	WaterShader(ID3D11Device* device, HWND hwnd);
	~WaterShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext,
		const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		ID3D11ShaderResourceView* texture);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
};

#endif