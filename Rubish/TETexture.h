#ifndef TETEXTURE_H
#define TETEXTURE_H

#include <TEColor.h>
#include <memory>

namespace TE
{
	namespace SceneGraph
	{
		class Texture
		{
		public:
			enum
			{
				FILTERMODE_NEAREST,
				FILTERMODE_LINEAR,
				FILTERMODE_COUNT
			};

			enum
			{
				MIPMAPMODE_NEAREST,
				MIPMAPMODE_LINEAR,
				MIPMAPMODE_NEAREST_NEAREST,
				MIPMAPMODE_NEAREST_LINEAR,
				MIPMAPMODE_LINEAR_NEAREST,
				MIPMAPMODE_LINEAR_LINEAR,
				MIPMAPMODE_COUNT
			};

			enum
			{
				COORDMODE_CLAMP,
				COORDMODE_REPEAT,
				COORDMODE_CLAMP_BORDER,
				COORDMODE_CLAMP_EDGE,
				COORDMODE_COUNT
			};

			enum
			{
				TEXTGENMODE_NONE,
				TEXTGENMODE_ENVIRONMENT_MAP,
				TEXTGENMODE_PROJECTED_TEXTURE,
				TEXTGENMODE_COUNT
			};

			enum
			{
				APPLYMODE_REPLACE,
				APPLYMODE_DECAL,
				APPLYMODE_MODULATE,
				APPLYMODE_BLEND,
				APPLYMODE_ADD,
				APPLYMODE_COMBINE,
				APPLYMODE_COUNT
			};

			enum
			{
				APPCOMBINEFN_REPLACE,
				APPCOMBINEFN_MODULATE,
				APPCOMBINEFN_ADD,
				APPCOMBINEFN_ADD_SIGNED,
				APPCOMBINEFN_SUBTRACT,
				APPCOMBINEFN_INTERPOLATE,
				APPCOMBINEFN_DOT3_RGB,
				APPCOMBINEFN_DOT3_RGBA,
				APPCOMBINEFN_COUNT
			};

			enum
			{
				APPCOMBINESRC_TEXTURE,
				APPCOMBINESRC_PRIMARY_COLOR,
				APPCOMBINESRC_CONSTANT,
				APPCOMBINESRC_PREVIOUS,
				APPCOMBINESRC_COUNT
			};

			enum
			{
				APPCOMBINEOP_SRC_COLOR,
				APPCOMBINEOP_ONE_MINUS_SRC_COLOR,
				APPCOMBINEOP_SRC_ALPHA,
				APPCOMBINEOP_ONE_MINUS_SRC_ALPHA,
				APPCOMBINEOP_COUNT
			};

			enum
			{
				APPCOMBINESCALE_ONE,
				APPCOMBINESCALE_TWO,
				APPCOMBINESCALE_FOUR,
				APPCOMBINESCALE_COUNT
			};

			Texture(std::shared_ptr<Image> image)
				:
				m_filterMode(FILTERMODE_LINEAR),
				m_mipmapMode(MIPMAPMODE_LINEAR_LINEAR),
				m_coordmodeU(COORDMODE_CLAMP_EDGE),
				m_coordmodeV(COORDMODE_CLAMP_EDGE),
				m_coordBorderColor(ColorRGBA(0.0,0.0,0.0,0.0)),
				m_textGenMode(TEXTGENMODE_NONE),
				m_applymode(APPLYMODE_REPLACE),
				m_blendColor(ColorRGBA(0.0,0.0,0.0,1.0)),
				m_combineFuncRGB(APPCOMBINEFN_REPLACE),
				m_combineFuncAlpha(APPCOMBINEFN_REPLACE),
				m_combineSrc0RGB(APPCOMBINESRC_TEXTURE),
				m_combineSrc1RGB(APPCOMBINESRC_TEXTURE),
				m_combineSrc2RGB(APPCOMBINESRC_TEXTURE),
				m_combineSrc0Alpha(APPCOMBINESRC_TEXTURE),
				m_combineSrc1Alpha(APPCOMBINESRC_TEXTURE),
				m_combineSrc2Alpha(APPCOMBINESRC_TEXTURE),
				m_combineOp0RGB(APPCOMBINEOP_SRC_COLOR),
				m_combineOp1RGB(APPCOMBINEOP_SRC_COLOR),
				m_combineOp2RGB(APPCOMBINEOP_SRC_COLOR),
				m_combineOp0Alpha(APPCOMBINEOP_SRC_COLOR),
				m_combineOp1Alpha(APPCOMBINEOP_SRC_COLOR),
				m_combineOp2Alpha(APPCOMBINEOP_SRC_COLOR),
				m_combineScaleRGB(APPCOMBINESCALE_ONE),
				m_combineScaleAlpha(APPCOMBINESCALE_ONE)
			{
				m_image = image;
			}

			virtual ~Texture(){}

			void SetImage(std::shared_ptr<Image> image)
			{
				m_image = image;
			}

			std::shared_ptr<Image> GetImage()
			{
				return m_image;
			}
		private:
			std::shared_ptr<Image> m_image;

			int			m_filterMode;
			int			m_mipmapMode;
			int			m_coordmodeU;
			int			m_coordmodeV;
			ColorRGBA	m_coordBorderColor;
			int			m_textGenMode;
			int			m_applymode;
			ColorRGBA	m_blendColor;

			int			m_combineFuncRGB;
			int			m_combineFuncAlpha;
			int			m_combineSrc0RGB;
			int			m_combineSrc1RGB;
			int			m_combineSrc2RGB;
			int			m_combineSrc0Alpha;
			int			m_combineSrc1Alpha;
			int			m_combineSrc2Alpha;
			int			m_combineOp0RGB;
			int			m_combineOp1RGB;
			int			m_combineOp2RGB;
			int			m_combineOp0Alpha;
			int			m_combineOp1Alpha;
			int			m_combineOp2Alpha;
			int			m_combineScaleRGB;
			int			m_combineScaleAlpha;
		};
	}
}

#endif