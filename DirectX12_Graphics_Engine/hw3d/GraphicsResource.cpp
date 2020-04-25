#include "GraphicsResource.h"
#include <stdexcept>


ID3D12CommandList* GraphicsResource::GetCommandList( Graphics& gfx ) noexcept
{
	return gfx.pCommandList.Get();
}

ID3D12Device* GraphicsResource::GetDevice( Graphics& gfx ) noexcept
{
	return gfx.p12Device.Get();
}

DxgiInfoManager& GraphicsResource::GetInfoManager( Graphics& gfx )
{
	#ifndef NDEBUG
	return gfx.infoManager;
	#else
	throw std::logic_error( "YouFuckedUp! (tried to access gfx.infoManager in Release config)" );
	#endif
}
