#pragma once
#include "Graphics.h"

class Graphics;

class GraphicsResource
{
protected:
	static ID3D12CommandList* GetCommandList( Graphics& gfx ) noexcept;
	static ID3D12Device* GetDevice( Graphics& gfx ) noexcept;
	static DxgiInfoManager& GetInfoManager( Graphics& gfx );
};