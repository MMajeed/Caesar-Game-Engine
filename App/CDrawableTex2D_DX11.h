#ifndef _CDrawableTex2D_DX11_HG_
#define _CDrawableTex2D_DX11_HG_

#include <D3D11.h>
#include <D3DX11core.h>
#include <xnamath.h>

class CDrawableTex2D_DX11
{
public:
	CDrawableTex2D_DX11();
	~CDrawableTex2D_DX11();

	void init(ID3D11Device* device, ID3D11DeviceContext* contextDevice, UINT width, UINT height, bool hasColorMap, DXGI_FORMAT colorFormat);

	ID3D11ShaderResourceView* colorMap();
	ID3D11ShaderResourceView* depthMap();

	void begin();
	void end();

	CDrawableTex2D_DX11(const CDrawableTex2D_DX11& rhs);
	CDrawableTex2D_DX11& operator = (const CDrawableTex2D_DX11& rhs);
	void buildDepthMap();
	void buildColorMap();

	
private:
	UINT mWidth;
	UINT mHeight;
	DXGI_FORMAT mColorMapFormat;

	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dDeviceContext;

	ID3D11ShaderResourceView* mColorMapSRV;
	ID3D11RenderTargetView* mColorMapRTV;
	
	ID3D11ShaderResourceView* mDepthMapSRV;
	ID3D11DepthStencilView* mDepthMapDSV;

	D3D11_VIEWPORT mViewport;
};
#endif