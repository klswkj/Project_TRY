#pragma once
#include "Bindable.h"
#include "BindableCodex.h"
#include "GraphicsThrowMacros.h"

namespace Bind
{
	class Stencil : public Bindable
	{
	public:
		enum class Mode
		{
			Off,
			Write,
			Mask,
			DepthOff,
			DepthReversed
		};
		Stencil( Graphics& gfx,Mode mode )
			:
			mode( mode )
		{
			// D3D11_DEPTH_STENCIL_DESC dsDesc = CD3D11_DEPTH_STENCIL_DESC{ CD3D11_DEFAULT{} };
			D3D12_GRAPHICS_PIPELINE_STATE_DESC PSODescriptor = {};

			if( mode == Mode::Write )
			{
				PSODescriptor.DepthStencilState.DepthEnable = FALSE;
				PSODescriptor.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
				PSODescriptor.DepthStencilState.StencilEnable = TRUE;
				PSODescriptor.DepthStencilState.StencilWriteMask = 0xFF;
				PSODescriptor.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
				PSODescriptor.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_REPLACE;
			}
			else if( mode == Mode::Mask )
			{
				PSODescriptor.DepthStencilState.DepthEnable = FALSE;
				PSODescriptor.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
				PSODescriptor.DepthStencilState.StencilEnable = TRUE;
				PSODescriptor.DepthStencilState.StencilWriteMask = 0xFF;
				PSODescriptor.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NOT_EQUAL;
				PSODescriptor.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			}
			else if( mode == Mode::DepthOff )
			{
				PSODescriptor.DepthStencilState.DepthEnable = FALSE;
				PSODescriptor.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
			}
			else if( mode == Mode::DepthReversed )
			{
				PSODescriptor.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_GREATER;
			}

			GetDevice( gfx )->CreateGraphicsPipelineState( &PSODescriptor, IID_PPV_ARGS(&pStencil) );
		}
		void Bind( Graphics& gfx ) noxnd override
		{
			INFOMAN_NOHR( gfx );
			GFX_THROW_INFO_ONLY( GetCommandList( gfx )->OMSetDepthStencilState( pStencil.Get(),0xFF ) );
		}
		static std::shared_ptr<Stencil> Resolve( Graphics& gfx,Mode mode )
		{
			return Codex::Resolve<Stencil>( gfx,mode );
		}
		static std::string GenerateUID( Mode mode )
		{
			using namespace std::string_literals;
			const auto modeName = [mode]() {
				switch( mode ) {
				case Mode::Off:
					return "off"s;
				case Mode::Write:
					return "write"s;
				case Mode::Mask:
					return "mask"s;
				case Mode::DepthOff:
					return "depth-off"s;
				case Mode::DepthReversed:
					return "depth-reversed"s;
				}
				return "ERROR"s;
			};
			return typeid(Stencil).name() + "#"s + modeName();
		}
		std::string GetUID() const noexcept override
		{
			return GenerateUID( mode );
		}
	private:
		Mode mode;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pStencil;
	};
}
