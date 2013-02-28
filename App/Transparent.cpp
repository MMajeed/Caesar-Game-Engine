#include "DX11ObjectManager.h"
#include "App.h"
#include "DX11App.h"
#include "DX11Helper.h"
#include "Helper.h"
#include "cBuffer.h"
#include "VertexBuffer.h"
#include "Transparent.h"
#include <sstream>

void Transparent::DrawObject()
{
	ID3D11DeviceContext* pImmediateContext = ((DX11App*)App::getInstance())->direct3d.pImmediateContext;
		
	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	pImmediateContext->OMSetBlendState(this->pTransparent.second, blendFactor, 0xffffffff);

	PlyFile::DrawObject();

	pImmediateContext->OMSetBlendState(0, blendFactor, 0xffffffff);
}
void Transparent::Init()
{
	PlyFile::Init();

	ID3D11Device* device = (dynamic_cast<DX11App*>(App::getInstance()))->direct3d.pd3dDevice;

	this->LoadTransparency(device);

	if(!DX11ObjectManager::getInstance()->BelnderState.Get(this->pTransparent.first, this->pTransparent.second)){ throw std::exception("Transparent blender not found"); }
}
void Transparent::LoadTransparency(ID3D11Device* device)
{
	if(!DX11ObjectManager::getInstance()->BelnderState.Exists(this->pTransparent.first))
	{
		std::wstring error;
		if(!DX11Helper::LoadTransparent(device, &(this->pTransparent.second), error))
		{
			throw std::exception(Helper::WStringtoString(error).c_str());
		}
		DX11ObjectManager::getInstance()->BelnderState.Add(this->pTransparent.first , this->pTransparent.second);
	}
}
Transparent::Transparent()
{
	this->pTransparent.first = "Transparent";
}
Transparent::Transparent(PlyFile base)
	: PlyFile(base)
{

}
Transparent* Transparent::Spawn(std::map<std::string, std::string> info)
{
	PlyFile* plyObject = PlyFile::Spawn(info);
	Transparent* newTransparent = new Transparent(*plyObject);
	delete plyObject;
	return newTransparent;
}