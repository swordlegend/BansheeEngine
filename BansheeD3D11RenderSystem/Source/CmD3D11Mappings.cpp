#include "CmD3D11Mappings.h"
#include "CmDebug.h"
#include "CmException.h"

namespace BansheeEngine
{
	D3D11_TEXTURE_ADDRESS_MODE D3D11Mappings::get(TextureAddressingMode tam)
	{
		switch( tam )
		{
		case TAM_WRAP:
			return D3D11_TEXTURE_ADDRESS_WRAP;
		case TAM_MIRROR:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case TAM_CLAMP:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		case TAM_BORDER:
			return D3D11_TEXTURE_ADDRESS_BORDER;
		}
		return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
	}

	D3D11_BLEND D3D11Mappings::get(BlendFactor sbf)
	{
		switch( sbf )
		{
		case BF_ONE:
			return D3D11_BLEND_ONE;
		case BF_ZERO:
			return D3D11_BLEND_ZERO;
		case BF_DEST_COLOR:
			return D3D11_BLEND_DEST_COLOR;
		case BF_SOURCE_COLOR:
			return D3D11_BLEND_SRC_COLOR;
		case BF_INV_DEST_COLOR:
			return D3D11_BLEND_INV_DEST_COLOR;
		case BF_INV_SOURCE_COLOR:
			return D3D11_BLEND_INV_SRC_COLOR;
		case BF_DEST_ALPHA:
			return D3D11_BLEND_DEST_ALPHA;
		case BF_SOURCE_ALPHA:
			return D3D11_BLEND_SRC_ALPHA;
		case BF_INV_DEST_ALPHA:
			return D3D11_BLEND_INV_DEST_ALPHA;
		case BF_INV_SOURCE_ALPHA:
			return D3D11_BLEND_INV_SRC_ALPHA;
		}
		return D3D11_BLEND_ZERO;
	}

	D3D11_BLEND_OP D3D11Mappings::get(BlendOperation sbo)
	{
		switch( sbo )
		{
		case BO_ADD:
			return D3D11_BLEND_OP_ADD;
		case BO_SUBTRACT:
			return D3D11_BLEND_OP_SUBTRACT;
		case BO_REVERSE_SUBTRACT:
			return D3D11_BLEND_OP_REV_SUBTRACT;
		case BO_MIN:
			return D3D11_BLEND_OP_MIN;
		case BO_MAX:
			return D3D11_BLEND_OP_MAX;
		}
		return D3D11_BLEND_OP_ADD;
	}

	D3D11_COMPARISON_FUNC D3D11Mappings::get(CompareFunction cf)
	{
		switch( cf )
		{
		case CMPF_ALWAYS_FAIL:
			return D3D11_COMPARISON_NEVER;
		case CMPF_ALWAYS_PASS:
			return D3D11_COMPARISON_ALWAYS;
		case CMPF_LESS:
			return D3D11_COMPARISON_LESS;
		case CMPF_LESS_EQUAL:
			return D3D11_COMPARISON_LESS_EQUAL;
		case CMPF_EQUAL:
			return D3D11_COMPARISON_EQUAL;
		case CMPF_NOT_EQUAL:
			return D3D11_COMPARISON_NOT_EQUAL;
		case CMPF_GREATER_EQUAL:
			return D3D11_COMPARISON_GREATER_EQUAL;
		case CMPF_GREATER:
			return D3D11_COMPARISON_GREATER;
		};
		return D3D11_COMPARISON_ALWAYS;
	}

	D3D11_CULL_MODE D3D11Mappings::get(CullingMode cm)
	{
		switch( cm )
		{
		case CULL_NONE:
			return D3D11_CULL_NONE;
		case CULL_CLOCKWISE:
			return D3D11_CULL_FRONT;
		case CULL_COUNTERCLOCKWISE:
			return D3D11_CULL_BACK;
		}
		return D3D11_CULL_NONE;
	}

	D3D11_FILL_MODE D3D11Mappings::get(PolygonMode level)
	{
		switch(level)
		{
		case PM_WIREFRAME:
			return D3D11_FILL_WIREFRAME;
		case PM_SOLID:
			return D3D11_FILL_SOLID;
		}
		return D3D11_FILL_SOLID;
	}

	D3D11_STENCIL_OP D3D11Mappings::get(StencilOperation op, bool invert)
	{
		switch(op)
		{
		case SOP_KEEP:
			return D3D11_STENCIL_OP_KEEP;
		case SOP_ZERO:
			return D3D11_STENCIL_OP_ZERO;
		case SOP_REPLACE:
			return D3D11_STENCIL_OP_REPLACE;
		case SOP_INCREMENT:
			return invert? D3D11_STENCIL_OP_DECR_SAT : D3D11_STENCIL_OP_INCR_SAT;
		case SOP_DECREMENT:
			return invert? D3D11_STENCIL_OP_INCR_SAT : D3D11_STENCIL_OP_DECR_SAT;
		case SOP_INCREMENT_WRAP:
			return invert? D3D11_STENCIL_OP_DECR : D3D11_STENCIL_OP_INCR;
		case SOP_DECREMENT_WRAP:
			return invert? D3D11_STENCIL_OP_INCR : D3D11_STENCIL_OP_DECR;
		case SOP_INVERT:
			return D3D11_STENCIL_OP_INVERT;
		}
		return D3D11_STENCIL_OP_KEEP;
	}

	DWORD D3D11Mappings::get(FilterType ft)
	{
		switch (ft)
		{
		case FT_MIN:
			return D3D11_MIN_FILTER_SHIFT;
			break;
		case FT_MAG:
			return D3D11_MAG_FILTER_SHIFT;
			break;
		case FT_MIP:
			return D3D11_MIP_FILTER_SHIFT;
			break;
		}

		// to keep compiler happy
		return D3D11_MIP_FILTER_SHIFT;
	}
	//---------------------------------------------------------------------
	D3D11_FILTER D3D11Mappings::get(const FilterOptions min, const FilterOptions mag, const FilterOptions mip, const bool comparison)
	{

		D3D11_FILTER res;
#define MERGE_FOR_SWITCH(_comparison_, _min_ , _mag_, _mip_ ) ((_comparison_ << 16) | (_min_ << 8) | (_mag_ << 4) | (_mip_))

		switch((MERGE_FOR_SWITCH(comparison, min, mag, mip)))
		{
		case MERGE_FOR_SWITCH(true, FO_POINT, FO_POINT, FO_POINT):
			res = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(true, FO_POINT, FO_POINT, FO_LINEAR):
			res = D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
			break;
		case MERGE_FOR_SWITCH(true, FO_POINT, FO_LINEAR, FO_POINT):
			res = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(true, FO_POINT, FO_LINEAR, FO_LINEAR):
			res = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
			break;
		case MERGE_FOR_SWITCH(true, FO_LINEAR, FO_POINT, FO_POINT):
			res = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(true, FO_LINEAR, FO_POINT, FO_LINEAR):
			res = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			break;		
		case MERGE_FOR_SWITCH(true, FO_LINEAR, FO_LINEAR, FO_POINT):
			res = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(true, FO_LINEAR, FO_LINEAR, FO_LINEAR):
			res = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
			break;
		case MERGE_FOR_SWITCH(true, FO_ANISOTROPIC, FO_ANISOTROPIC, FO_ANISOTROPIC):
			res = D3D11_FILTER_COMPARISON_ANISOTROPIC;
			break;

		case MERGE_FOR_SWITCH(false, FO_POINT, FO_POINT, FO_POINT):
			res = D3D11_FILTER_MIN_MAG_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(false, FO_POINT, FO_POINT, FO_LINEAR):
			res = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
			break;
		case MERGE_FOR_SWITCH(false, FO_POINT, FO_LINEAR, FO_POINT):
			res = D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(false, FO_POINT, FO_LINEAR, FO_LINEAR):
			res = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
			break;
		case MERGE_FOR_SWITCH(false, FO_LINEAR, FO_POINT, FO_POINT):
			res = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(false, FO_LINEAR, FO_POINT, FO_LINEAR):
			res = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
			break;		
		case MERGE_FOR_SWITCH(false, FO_LINEAR, FO_LINEAR, FO_POINT):
			res = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			break;
		case MERGE_FOR_SWITCH(false, FO_LINEAR, FO_LINEAR, FO_LINEAR):
			res = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			break;
		case MERGE_FOR_SWITCH(false, FO_ANISOTROPIC, FO_ANISOTROPIC, FO_ANISOTROPIC):
			res = D3D11_FILTER_ANISOTROPIC;
			break;
		default:
			res = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		}	

#undef MERGE_FOR_SWITCH
		
		return res;
	}

	DWORD D3D11Mappings::get(GpuBufferUsage usage)
	{
		DWORD ret = D3D11_USAGE_DEFAULT;

		if (usage & GBU_DYNAMIC)
		{
			ret = D3D11_USAGE_DYNAMIC;
		}

		return ret;
	}

	D3D11_MAP D3D11Mappings::get(GpuLockOptions options, GpuBufferUsage usage)
	{
		D3D11_MAP ret = D3D11_MAP_READ_WRITE;
		if (options == GBL_WRITE_ONLY_DISCARD)
		{
			// D3D doesn't like discard on non-dynamic buffers
			if (usage & GBU_DYNAMIC)
				ret = D3D11_MAP_WRITE_DISCARD;
			else
				ret = D3D11_MAP_WRITE;
		}
		else if (options == GBL_READ_ONLY)
		{
			ret = D3D11_MAP_READ;
		}
		else if (options == GBL_WRITE_ONLY_NO_OVERWRITE)
		{
			ret = D3D11_MAP_WRITE_NO_OVERWRITE; // Only allowed for vertex/index buffers
		}

		return ret;
	}

	UINT D3D11Mappings::getByteWidth(IndexBuffer::IndexType itype)
	{
		if (itype == IndexBuffer::IT_32BIT)
		{
			return sizeof(UINT32);
		}
		else
		{
			return sizeof(UINT16);
		}
	}

	DXGI_FORMAT D3D11Mappings::get(VertexElementType vType)
	{
		switch (vType)
		{
		case VET_COLOR:
		case VET_COLOR_ABGR:
		case VET_COLOR_ARGB:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		case VET_FLOAT1:
			return DXGI_FORMAT_R32_FLOAT;
			break;
		case VET_FLOAT2:
			return DXGI_FORMAT_R32G32_FLOAT;
			break;
		case VET_FLOAT3:
			return DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case VET_FLOAT4:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		case VET_SHORT2:
			return DXGI_FORMAT_R16G16_SINT;
			break;
		case VET_SHORT4:
			return DXGI_FORMAT_R16G16B16A16_SINT;
			break;
		case VET_UBYTE4:
			return DXGI_FORMAT_R8G8B8A8_UINT;
			break;
		case VET_UINT4:
			return DXGI_FORMAT_R32G32B32A32_UINT;
			break;
		case VET_SINT4:
			return DXGI_FORMAT_R32G32B32A32_SINT;
			break;
		}
		// to keep compiler happy
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}

	VertexElementSemantic D3D11Mappings::get(LPCSTR sem)
	{
		// todo - add to ogre - POSITIONT and PSIZE ("Transformed vertex position" and "Point size")

		if( strcmp(sem, "BLENDINDICES") == 0 )
			return VES_BLEND_INDICES;
		if( strcmp(sem, "BLENDWEIGHT") == 0 )
			return VES_BLEND_WEIGHTS;
		if( strcmp(sem, "COLOR") == 0 )
			return VES_COLOR;
		if( strcmp(sem, "NORMAL") == 0 )
			return VES_NORMAL;
		if( strcmp(sem, "POSITION") == 0 )
			return VES_POSITION;
		if( strcmp(sem, "TEXCOORD") == 0 )
			return VES_TEXCOORD;
		if( strcmp(sem, "BINORMAL") == 0 )
			return VES_BITANGENT;
		if( strcmp(sem, "TANGENT") == 0 )
			return VES_TANGENT;
		if( strcmp(sem, "POSITIONT") == 0 )
			return VES_POSITIONT;
		if( strcmp(sem, "PSIZE") == 0 ) 
			return VES_PSIZE;

		BS_EXCEPT(RenderingAPIException, "Invalid shader semantic: " + String(sem));

		// to keep compiler happy
		return VES_POSITION;
	}

	LPCSTR D3D11Mappings::get(VertexElementSemantic sem)
	{
		switch (sem)	
		{
		case VES_BLEND_INDICES:
			return "BLENDINDICES";
			break;
		case VES_BLEND_WEIGHTS:
			return "BLENDWEIGHT";
			break;
		case VES_COLOR:
			return "COLOR";
			break;
		case VES_NORMAL:
			return "NORMAL";
			break;
		case VES_POSITION:
			return "POSITION";
			break;
		case VES_TEXCOORD:
			return "TEXCOORD";
			break;
		case VES_BITANGENT:
			return "BINORMAL";
			break;
		case VES_TANGENT:
			return "TANGENT";
			break;
		case VES_POSITIONT:
			return "POSITIONT";
			break;
		case VES_PSIZE:
			return "PSIZE";
			break;
		}
		// to keep compiler happy
		return "";
	}

	VertexElementType D3D11Mappings::getInputType(D3D_REGISTER_COMPONENT_TYPE type)
	{
		switch(type)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			return VET_FLOAT4;
		case D3D_REGISTER_COMPONENT_SINT32:
			return VET_SINT4;
		case D3D_REGISTER_COMPONENT_UINT32:
			return VET_UINT4;
		default:
			return VET_FLOAT4;
		}
	}

	void D3D11Mappings::get(const Color& inColour, float * outColour )
	{
		outColour[0] = inColour.r;
		outColour[1] = inColour.g;
		outColour[2] = inColour.b;
		outColour[3] = inColour.a;	
	}

	D3D11_BOX D3D11Mappings::toDx11Box(const PixelVolume &inBox)
	{
		D3D11_BOX res;
		res.left	= static_cast<UINT>(inBox.left);
		res.top		= static_cast<UINT>(inBox.top);
		res.front	= static_cast<UINT>(inBox.front);
		res.right	= static_cast<UINT>(inBox.right);
		res.bottom	= static_cast<UINT>(inBox.bottom);
		res.back	= static_cast<UINT>(inBox.back);

		return res;
	}

	PixelFormat D3D11Mappings::_getPF(DXGI_FORMAT d3dPF)
	{
		switch(d3dPF)
		{

		case DXGI_FORMAT_UNKNOWN	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32B32A32_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32B32A32_FLOAT	:
			return PF_FLOAT32_RGBA;
		case DXGI_FORMAT_R32G32B32A32_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32B32A32_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32B32_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32B32_FLOAT	:
			return PF_FLOAT32_RGB;
		case DXGI_FORMAT_R32G32B32_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32B32_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16B16A16_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16B16A16_FLOAT	:
			return PF_FLOAT16_RGBA;
		case DXGI_FORMAT_R16G16B16A16_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16B16A16_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16B16A16_SNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16B16A16_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32_FLOAT	:
			return PF_FLOAT32_RG;
		case DXGI_FORMAT_R32G32_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G32_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32G8X24_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT	:
			return PF_D32_S8X24;
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R10G10B10A2_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R10G10B10A2_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R10G10B10A2_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R11G11B10_FLOAT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8B8A8_UNORM	:
			return PF_R8G8B8A8;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8B8A8_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8B8A8_SNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8B8A8_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16_FLOAT	:
			return PF_FLOAT16_RG;
		case DXGI_FORMAT_R16G16_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16_SNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16G16_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_D32_FLOAT	:
			return PF_D32;
		case DXGI_FORMAT_R32_FLOAT	:
			return PF_FLOAT32_R;
		case DXGI_FORMAT_R32_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R32_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R24G8_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_D24_UNORM_S8_UINT	:
			return PF_D24S8;
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8_UNORM	:
			return PF_R8G8;
		case DXGI_FORMAT_R8G8_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8_SNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16_FLOAT	:
			return PF_FLOAT16_R;
		case DXGI_FORMAT_D16_UNORM	:
			return PF_D16;
		case DXGI_FORMAT_R16_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16_SNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R16_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8_UNORM	:
			return PF_R8;
		case DXGI_FORMAT_R8_UINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8_SNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8_SINT	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_A8_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R1_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_R8G8_B8G8_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_G8R8_G8B8_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_BC1_TYPELESS	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_BC1_UNORM	:
			return PF_DXT1;
		case DXGI_FORMAT_BC1_UNORM_SRGB	:
			return PF_DXT1;
		case DXGI_FORMAT_BC2_TYPELESS	:
			return PF_DXT2;
		case DXGI_FORMAT_BC2_UNORM	:
			return PF_DXT2;
		case DXGI_FORMAT_BC2_UNORM_SRGB	:
			return PF_DXT2;
		case DXGI_FORMAT_BC3_TYPELESS	:
			return PF_DXT3;
		case DXGI_FORMAT_BC3_UNORM	:
			return PF_DXT3;
		case DXGI_FORMAT_BC3_UNORM_SRGB	:
			return PF_DXT3;
		case DXGI_FORMAT_BC4_TYPELESS	:
			return PF_DXT4;
		case DXGI_FORMAT_BC4_UNORM	:
			return PF_DXT4;
		case DXGI_FORMAT_BC4_SNORM	:
			return PF_DXT4;
		case DXGI_FORMAT_BC5_TYPELESS	:
			return PF_DXT5;
		case DXGI_FORMAT_BC5_UNORM	:
			return PF_DXT5;
		case DXGI_FORMAT_BC5_SNORM	:
			return PF_DXT5;
		case DXGI_FORMAT_B5G6R5_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_B5G5R5A1_UNORM	:
			return PF_UNKNOWN;
		case DXGI_FORMAT_B8G8R8A8_UNORM	:
			return PF_B8G8R8A8;
		case DXGI_FORMAT_B8G8R8X8_UNORM	:
			return PF_B8G8R8X8;
		default:
			return PF_UNKNOWN;
		}
	}

	DXGI_FORMAT D3D11Mappings::_getPF(PixelFormat enginePF)
	{
		switch(enginePF)
		{
		case PF_R8:
			return DXGI_FORMAT_R8_UNORM;
		case PF_R8G8:
			return DXGI_FORMAT_R8G8_UNORM; 
		case PF_R8G8B8:
			return DXGI_FORMAT_UNKNOWN;
		case PF_A8R8G8B8:
			return DXGI_FORMAT_UNKNOWN;
		case PF_A8B8G8R8:
			return DXGI_FORMAT_UNKNOWN;
		case PF_X8R8G8B8:
			return DXGI_FORMAT_UNKNOWN;
		case PF_X8B8G8R8:
			return DXGI_FORMAT_UNKNOWN;
		case PF_R8G8B8A8:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case PF_B8G8R8A8:
			return DXGI_FORMAT_B8G8R8A8_UNORM;
		case PF_B8G8R8X8:
			return DXGI_FORMAT_B8G8R8X8_UNORM;
		case PF_FLOAT16_R:
			return DXGI_FORMAT_R16_FLOAT;
		case PF_FLOAT16_RG:
			return DXGI_FORMAT_R16G16_FLOAT;
		case PF_FLOAT16_RGB:
			return DXGI_FORMAT_UNKNOWN;
		case PF_FLOAT16_RGBA:
			return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case PF_FLOAT32_R:
			return DXGI_FORMAT_R32_FLOAT;
		case PF_FLOAT32_RG:
			return DXGI_FORMAT_R32G32_FLOAT;
		case PF_FLOAT32_RGB:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case PF_FLOAT32_RGBA:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case PF_DXT1:
			return DXGI_FORMAT_BC1_UNORM;
		case PF_DXT2:
			return DXGI_FORMAT_BC2_UNORM;
		case PF_DXT3:
			return DXGI_FORMAT_BC3_UNORM;
		case PF_DXT4:
			return DXGI_FORMAT_BC4_UNORM;
		case PF_DXT5:
			return DXGI_FORMAT_BC5_UNORM;
		case PF_D32_S8X24:
			return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		case PF_D24S8:
			return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case PF_D32:
			return DXGI_FORMAT_D32_FLOAT;
		case PF_D16:
			return DXGI_FORMAT_D16_UNORM;
		case PF_UNKNOWN:
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	PixelFormat D3D11Mappings::_getClosestSupportedPF(PixelFormat enginePF)
	{
		if (_getPF(enginePF) != DXGI_FORMAT_UNKNOWN)
		{
			return enginePF;
		}
		switch(enginePF)
		{
		case PF_FLOAT16_RGB:
			return PF_FLOAT16_RGBA;
		case PF_R8G8B8:
			return PF_R8G8B8A8;
		case PF_B8G8R8:
			return PF_R8G8B8A8;
		case PF_A8R8G8B8:
			return PF_R8G8B8A8;
		case PF_A8B8G8R8:
			return PF_B8G8R8A8;
		case PF_X8R8G8B8:
			return PF_R8G8B8A8;
		case PF_X8B8G8R8:
			return PF_B8G8R8X8;
		case PF_R8G8B8X8:
			return PF_B8G8R8X8;
		case PF_UNKNOWN:
		default:
			return PF_R8G8B8A8;
		}
	}

	D3D11_USAGE D3D11Mappings::_getUsage(GpuBufferUsage mUsage)
	{
		if (_isDynamic(mUsage))
		{
			return D3D11_USAGE_DYNAMIC;
		}
		else
		{
			return D3D11_USAGE_DEFAULT;
		}
	}

	bool D3D11Mappings::_isDynamic(GpuBufferUsage mUsage)
	{
		switch ( mUsage)
		{
		case GBU_DYNAMIC:
			return true;
		}

		return false;
	}

	bool D3D11Mappings::_isDynamic(int mUsage)
	{
		return _isDynamic(static_cast<GpuBufferUsage>(mUsage));
	}

	bool D3D11Mappings::isMappingWrite(D3D11_MAP map)
	{
		if(map == D3D11_MAP_READ)
			return false;

		return true;

	}

	bool D3D11Mappings::isMappingRead(D3D11_MAP map)
	{
		if(map == D3D11_MAP_READ || map == D3D11_MAP_READ_WRITE)
			return true;

		return false;
	}

	D3D11_USAGE D3D11Mappings::_getUsage(int mUsage)
	{
		return _getUsage(static_cast<GpuBufferUsage>(mUsage));
	}

	UINT D3D11Mappings::_getAccessFlags(int mUsage)
	{
		return _getAccessFlags(static_cast<GpuBufferUsage>(mUsage));
	}

	UINT D3D11Mappings::_getAccessFlags(GpuBufferUsage mUsage)
	{
		if(_isDynamic(mUsage))
			return D3D11_CPU_ACCESS_WRITE;
		else
			return 0;
	}

	TextureType D3D11Mappings::_getTexType(D3D11_SRV_DIMENSION type)
	{
		switch(type)
		{
		case D3D_SRV_DIMENSION_TEXTURE1D:
			return TEX_TYPE_1D;
		case D3D_SRV_DIMENSION_TEXTURE2D:
		case D3D_SRV_DIMENSION_TEXTURE2DMS:
			return TEX_TYPE_2D;
		case D3D_SRV_DIMENSION_TEXTURE3D:
			return TEX_TYPE_3D;
		case D3D_SRV_DIMENSION_TEXTURECUBE:
			return TEX_TYPE_CUBE_MAP;
		default:
			// unknown
			return static_cast<TextureType>(0);
		}
	}

	D3D11_PRIMITIVE_TOPOLOGY D3D11Mappings::getPrimitiveType(DrawOperationType type)
	{
		switch(type)
		{
		case DOT_POINT_LIST:
			return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		case DOT_LINE_LIST:
			return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		case DOT_LINE_STRIP:
			return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
		case DOT_TRIANGLE_LIST:
			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		case DOT_TRIANGLE_STRIP:
			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		case DOT_TRIANGLE_FAN:
			BS_EXCEPT(InvalidParametersException, "D3D11 doesn't support triangle fan primitive type.");
		}

		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}

	//---------------------------------------------------------------------
	UINT32 D3D11Mappings::_getSizeInBytes(PixelFormat pf, UINT32 xcount, UINT32 ycount)
	{
		if(xcount == 0 || ycount == 0)
			return 0;

		if(PixelUtil::isCompressed(pf))
		{
			// D3D wants the width of one row of cells in bytes
			if (pf == PF_DXT1)
			{
				// 64 bits (8 bytes) per 4x4 block
				return std::max<UINT32>(1, xcount / 4) * std::max<UINT32>(1, ycount / 4) * 8;
			}
			else
			{
				// 128 bits (16 bytes) per 4x4 block
				return std::max<UINT32>(1, xcount / 4) * std::max<UINT32>(1, ycount / 4) * 16;
			}
		}
		else
		{
			return xcount * ycount * PixelUtil::getNumElemBytes(pf);
		}
	}

	D3D11_MAP D3D11Mappings::getLockOptions(GpuLockOptions lockOptions)
	{
		switch(lockOptions)
		{
		case GBL_WRITE_ONLY_NO_OVERWRITE:
			return D3D11_MAP_WRITE_NO_OVERWRITE;
			break;
		case GBL_READ_WRITE:
			return D3D11_MAP_READ_WRITE;
			break;
		case GBL_WRITE_ONLY_DISCARD:
			return D3D11_MAP_WRITE_DISCARD;
			break;
		case GBL_READ_ONLY:
			return D3D11_MAP_READ;
			break;
		case GBL_WRITE_ONLY:
			return D3D11_MAP_WRITE;
			break;
		default: 
			break;
		};

		BS_EXCEPT(RenderingAPIException, "Invalid lock option. No DX11 equivalent of: " + toString(lockOptions));
	}
}