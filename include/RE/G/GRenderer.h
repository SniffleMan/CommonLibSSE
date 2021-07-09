#pragma once

#include "RE/G/GColor.h"
#include "RE/G/GMatrix2D.h"
#include "RE/G/GPoint.h"
#include "RE/G/GRect.h"
#include "RE/G/GRefCountBase.h"
#include "RE/G/GRendererEventHandler.h"
#include "RE/G/GTexture.h"

namespace RE
{
	class GImageBase;
	class GMatrix3D;
	class GRenderTarget;
	class GViewport;

	class GRenderer : public GRefCountBase<GRenderer, GStatRenderer::kMem>
	{
	public:
		using Handle = void*;
		using Matrix = GMatrix2D;
		using Point = GPointF;
		using Rect = GRectF;

		enum class BlendType
		{
			kNone = 0,
			kNormal = 1,
			kLayer = 2,
			kMultiply = 3,
			kScreen = 4,
			kLighten = 5,
			kDarken = 6,
			kDifference = 7,
			kAdd = 8,
			kSubtract = 9,
			kInvert = 10,
			kAlpha = 11,
			kErase = 12,
			kOverlay = 13,
			kHardLight = 14
		};

		enum class ResizeImageType
		{
			kRGBToRGB,
			kRGBAToRGBA,
			kRGBToRGBA,
			kGray
		};

		enum class VertexFormat
		{
			kNone = 0,
			kXY16i = 1 << 1,
			kXY32f = 1 << 2,
			kXY16iC32 = 1 << 3,
			kXY16iCF32 = 1 << 4
		};

		enum class IndexFormat
		{
			kNone = 0,
			k16 = 1,
			k32 = 2
		};

		enum class RenderCapBits
		{
			kNone = 0,

			kCacheDataUse = 1 << 0,

			kIndex16 = 1 << 2,
			kIndex32 = 1 << 3,
			kRenderStats = 1 << 4,
			kRenderTargets = 1 << 5,
			kRenderTargetPrePass = 1 << 6,
			kRenderTargetNonPow2 = 1 << 7,
			kFillGouraud = 1 << 8,
			kFillGouraudTex = 1 << 9,

			kCxformAdd = 1 << 12,
			kNestedMasks = 1 << 13,
			kTexNonPower2 = 1 << 14,
			kTexNonPower2Wrap = 1 << 15,
			kCanLoseData = 1 << 16,
			kKeepVertexData = 1 << 17,
			kNoTexOverwrite = 1 << 18,
			kTexNonPower2Mip = 1 << 19,
			kThreadedTextureCreation = 1 << 20,
			kRenderTargetMip = 1 << 21,
			kFilter_Blurs = 1 << 22,
			kFilter_ColorMatrix = 1 << 23,
		};

		enum class StereoDisplay
		{
			kStereoCenter,
			kStereoLeft,
			kStereoRight
		};

		enum class CachedDataType
		{
			kVertex = 1,
			kIndex = 2,
			kBitmapList = 3
		};

		enum class UserDataPropertyFlag
		{
			kNone,
			kHasString,
			kHasFloat,
			kHasMatrix
		};

		enum class BitmapWrapMode
		{
			kRepeat,
			kClamp
		};

		enum class BitmapSampleMode
		{
			kPoint,
			kLinear
		};

		enum class GouraudFillType
		{
			kColor,
			k1Texture,
			k1TextureColor,
			k2Texture,
			k2TextureColor,
			k3Texture
		};

		enum class SubmitMaskMode
		{
			kClear,
			kIncrement,
			kDecrement
		};

		enum class FilterModes
		{
			kBlur = 1 << 0,
			kShadow = 1 << 1,
			kHighlight = 1 << 2,

			Filter_Knockout = 1 << 8,
			Filter_Inner = 1 << 9,
			Filter_HideObject = 1 << 10,

			Filter_UserModes = 0xFFFF,
			Filter_SkipLastPass = 1 << 16,
			Filter_LastPassOnly = 1 << 17
		};

		enum class FilterSupport
		{
			kNone = 0,
			kOk = 1 << 0,
			kMultipass = 1 << 1,
			kSlow = 1 << 2,
		};

		class Stats
		{
		public:
			Stats();

			void Clear();

			// members
			std::uint32_t triangles;   // 00
			std::uint32_t lines;       // 04
			std::uint32_t primitives;  // 08
			std::uint32_t masks;       // 0C
			std::uint32_t filters;     // 10
		};
		static_assert(sizeof(Stats) == 0x14);

		class CachedData
		{
		public:
			CachedData();
			~CachedData();

			[[nodiscard]] GRenderer* GetRenderer() const;
			[[nodiscard]] Handle     GetRendererData() const;
			void       SetRendererData(Handle a_handle);
			void       ReleaseData(CachedDataType a_type);
			void       ReleaseDataByRenderer();

			// members
			GRenderer* renderer;  // 00
			Handle     data;      // 08
		};
		static_assert(sizeof(CachedData) == 0x10);

		class CacheProvider
		{
		public:
			CacheProvider(CachedData* a_cache);
			~CacheProvider() = default;

			CachedData* GetCachedData(GRenderer* a_renderer);
			CachedData* CreateCachedData(CachedDataType a_type, GRenderer* a_renderer, bool a_keepSharedData = true);
			bool        CanDiscardData();

			// members
			CachedData*   data;               // 00
			bool          discardSharedData;  // 10
			std::uint8_t  pad11;              // 11
			std::uint16_t pad12;              // 12
			std::uint32_t pad14;              // 14
		};
		static_assert(sizeof(CacheProvider) == 0x10);

		class Cxform
		{
		public:
			enum
			{
				kR,
				kG,
				kB,
				kA,
				kRGBA
			};

			enum
			{
				kMult,
				kAdd,
				kMultAdd
			};

			Cxform();

			bool operator==(const Cxform& a_rhs) const;

			// members
			float matrix[kRGBA][kMultAdd];  // 00
		};
		static_assert(sizeof(Cxform) == 0x20);

		struct StereoParams
		{
		public:
			StereoParams();

			// members
			float displayWidthCm;      // 00
			float distortion;          // 04
			float displayDiagInches;   // 08
			float displayAspectRatio;  // 0C
			float eyeSeparationCm;     // 10
		};
		static_assert(sizeof(StereoParams) == 0x14);

		struct RenderCaps
		{
		public:
			// members
			stl::enumeration<RenderCapBits, std::uint32_t> capBits;         // 00
			std::uint32_t                                  vertexFormats;   // 04
			std::uint32_t                                  blendModes;      // 08
			std::uint32_t                                  maxTextureSize;  // 0C
		};
		static_assert(sizeof(RenderCaps) == 0x10);

		struct UserData
		{
		public:
			UserData();

			// members
			const char*                                          string;      // 00
			float*                                               flt;         // 08
			float*                                               matrix;      // 10
			std::uint32_t                                        matrixSize;  // 18
			stl::enumeration<UserDataPropertyFlag, std::uint8_t> propFlags;   // 1C
			std::uint8_t                                         pad1D;       // 1D
			std::uint16_t                                        pad1E;       // 1E
		};
		static_assert(sizeof(UserData) == 0x20);

		struct FillTexture
		{
		public:
			// members
			GTexture*                                         texture;        // 00
			Matrix                                            textureMatrix;  // 08
			stl::enumeration<BitmapWrapMode, std::uint32_t>   wrapMode;       // 20
			stl::enumeration<BitmapSampleMode, std::uint32_t> sampleMode;     // 24
		};
		static_assert(sizeof(FillTexture) == 0x28);

		struct VertexXY16i
		{
		public:
			// members
			std::int16_t x;  // 0
			std::int16_t y;  // 2
		};
		static_assert(sizeof(VertexXY16i) == 0x4);

		struct VertexXY16iC32
		{
		public:
			enum
			{
				kVFormat = static_cast<std::underlying_type_t<VertexFormat>>(VertexFormat::kXY16iC32)
			};

			// members
			std::int16_t  x;      // 0
			std::int16_t  y;      // 2
			std::uint32_t color;  // 4
		};
		static_assert(sizeof(VertexXY16iC32) == 0x8);

		struct VertexXY16iCF32
		{
		public:
			enum
			{
				kVFormat = static_cast<std::underlying_type_t<VertexFormat>>(VertexFormat::kXY16iCF32)
			};

			// members
			std::int16_t  x;        // 0
			std::int16_t  y;        // 2
			std::uint32_t color;    // 4
			std::uint32_t factors;  // 8
		};
		static_assert(sizeof(VertexXY16iCF32) == 0xC);

		struct BitmapDesc
		{
		public:
			// members
			Rect   Coords;         // 00
			Rect   TextureCoords;  // 10
			GColor Color;          // 20
		};
		static_assert(sizeof(BitmapDesc) == 0x24);

		struct DistanceFieldParams
		{
		public:
			// members
			float   width;         // 00
			float   shadowWidth;   // 04
			GColor  shadowColor;   // 08
			GPointF shadowOffset;  // 0C
			GColor  glowColor;     // 14
			float   glowSize[2];   // 18
		};
		static_assert(sizeof(DistanceFieldParams) == 0x20);

		struct BlurFilterParams
		{
		public:
			// members
			std::uint32_t mode;      // 00
			float         blurX;     // 04
			float         blurY;     // 08
			std::uint32_t passes;    // 0C
			GPointF       offset;    // 10
			GColor        color;     // 18
			GColor        color2;    // 1C
			float         strength;  // 20
			Cxform        cxform;    // 24
		};
		static_assert(sizeof(BlurFilterParams) == 0x44);

		~GRenderer() override;  // 00

		// add
		virtual bool           GetRenderCaps(RenderCaps* a_caps) = 0;                                                                                                                                                                                                             // 01
		virtual GTexture*      CreateTexture() = 0;                                                                                                                                                                                                                               // 02
		virtual GTexture*      CreateTextureYUV() = 0;                                                                                                                                                                                                                            // 03
		virtual void           BeginFrame();                                                                                                                                                                                                                                      // 04
		virtual void           EndFrame();                                                                                                                                                                                                                                        // 05
		virtual GRenderTarget* CreateRenderTarget() = 0;                                                                                                                                                                                                                          // 06
		virtual void           SetDisplayRenderTarget(GRenderTarget* a_renderTarget, bool a_setstate = true) = 0;                                                                                                                                                                 // 07
		virtual void           PushRenderTarget(const GRectF& a_frameRect, GRenderTarget* a_renderTarget) = 0;                                                                                                                                                                    // 08
		virtual void           PopRenderTarget() = 0;                                                                                                                                                                                                                             // 09
		virtual GTexture*      PushTempRenderTarget(const GRectF& a_frameRect, std::uint32_t a_targetW, std::uint32_t a_targetH) = 0;                                                                                                                                             // 0A
		virtual void           ReleaseTempRenderTargets(std::uint32_t a_keepArea);                                                                                                                                                                                                // 0B
		virtual void           BeginDisplay(GColor a_backgroundColor, const GViewport& a_viewport, float a_x0, float a_x1, float a_y0, float a_y1) = 0;                                                                                                                           // 0C
		virtual void           EndDisplay() = 0;                                                                                                                                                                                                                                  // 0D
		virtual void           SetMatrix(const Matrix& a_matrix) = 0;                                                                                                                                                                                                             // 0E
		virtual void           SetUserMatrix(const Matrix& a_matrix) = 0;                                                                                                                                                                                                         // 0F
		virtual void           SetCxform(const Cxform& a_cxForm) = 0;                                                                                                                                                                                                             // 10
		virtual void           PushBlendMode(BlendType a_mode) = 0;                                                                                                                                                                                                               // 11
		virtual void           PopBlendMode() = 0;                                                                                                                                                                                                                                // 12
		virtual bool           PushUserData(UserData* a_data);                                                                                                                                                                                                                    // 13
		virtual void           PopUserData();                                                                                                                                                                                                                                     // 14
		virtual void           SetPerspective3D(const GMatrix3D& a_projMatIn) = 0;                                                                                                                                                                                                // 15
		virtual void           SetView3D(const GMatrix3D& a_viewMatIn) = 0;                                                                                                                                                                                                       // 16
		virtual void           SetWorld3D(const GMatrix3D* a_worldMatIn) = 0;                                                                                                                                                                                                     // 17
		virtual void           MakeViewAndPersp3D(const GRectF& a_visFrameRectInTwips, GMatrix3D& a_matView, GMatrix3D& a_matPersp, float a_perspFOV, bool a_InvertY = false);                                                                                                    // 18
		virtual void           SetStereoParams(StereoParams a_params);                                                                                                                                                                                                            // 19
		virtual void           SetStereoDisplay(StereoDisplay a_display, bool a_setstate = false);                                                                                                                                                                                // 1A
		virtual void           SetVertexData(const void* a_vertices, std::int32_t a_numVertices, VertexFormat a_vtxFmt, CacheProvider* a_cache = 0) = 0;                                                                                                                          // 1B
		virtual void           SetIndexData(const void* a_indices, std::int32_t a_numIndices, IndexFormat a_idxFmt, CacheProvider* a_cache = 0) = 0;                                                                                                                              // 1C
		virtual void           ReleaseCachedData(CachedData* a_data, CachedDataType a_type) = 0;                                                                                                                                                                                  // 1D
		virtual void           DrawIndexedTriList(std::int32_t a_baseVertexIndex, std::int32_t a_minVertexIndex, std::int32_t a_numVertices, std::int32_t a_startIndex, std::int32_t a_triangleCount) = 0;                                                                        // 1E
		virtual void           DrawLineStrip(std::int32_t a_baseVertexIndex, std::int32_t a_lineCount) = 0;                                                                                                                                                                       // 1F
		virtual void           LineStyleDisable() = 0;                                                                                                                                                                                                                            // 20
		virtual void           LineStyleColor(GColor a_color) = 0;                                                                                                                                                                                                                // 21
		virtual void           FillStyleDisable() = 0;                                                                                                                                                                                                                            // 22
		virtual void           FillStyleColor(GColor a_color) = 0;                                                                                                                                                                                                                // 23
		virtual void           FillStyleBitmap(const FillTexture* a_fill) = 0;                                                                                                                                                                                                    // 24
		virtual void           FillStyleGouraud(GouraudFillType a_fillType, const FillTexture* a_texture0 = 0, const FillTexture* a_texture1 = 0, const FillTexture* a_texture2 = 0) = 0;                                                                                         // 25
		virtual void           DrawBitmaps(BitmapDesc* a_bitmapList, std::int32_t a_listSize, std::int32_t a_startIndex, std::int32_t a_count, const GTexture* a_texture, const Matrix& a_matrix, CacheProvider* a_cache = 0) = 0;                                                // 26
		virtual void           DrawDistanceFieldBitmaps(BitmapDesc* a_bitmapList, std::int32_t a_listSize, std::int32_t a_startIndex, std::int32_t a_count, const GTexture* a_texture, const Matrix& a_matrix, const DistanceFieldParams& a_params, CacheProvider* a_cache = 0);  // 27
		virtual void           BeginSubmitMask(SubmitMaskMode a_maskMode = SubmitMaskMode::kClear) = 0;                                                                                                                                                                           // 28
		virtual void           EndSubmitMask() = 0;                                                                                                                                                                                                                               // 29
		virtual void           DisableMask() = 0;                                                                                                                                                                                                                                 // 2A
		virtual std::uint32_t  CheckFilterSupport(const BlurFilterParams& a_params) = 0;                                                                                                                                                                                          // 2B
		virtual void           DrawBlurRect(GTexture* a_srcIn, const GRectF& a_inSrcRect, const GRectF& a_inDstRect, const BlurFilterParams& a_params) = 0;                                                                                                                       // 2C
		virtual void           DrawColorMatrixRect(GTexture* a_srcIn, const GRectF& a_inSrcRect, const GRectF& a_dstRect, const float* a_matrix) = 0;                                                                                                                             // 2D
		virtual void           GetRenderStats(Stats* a_stats, bool a_resetStats = 0) = 0;                                                                                                                                                                                         // 2E
		virtual void           GetStats(GStatBag* a_bag, bool a_reset = true) = 0;                                                                                                                                                                                                // 2F
		virtual void           ReleaseResources() = 0;                                                                                                                                                                                                                            // 30
		virtual bool           AddEventHandler(GRendererEventHandler* a_handler);                                                                                                                                                                                                 // 31
		virtual void           RemoveEventHandler(GRendererEventHandler* a_handler);                                                                                                                                                                                              // 32

		void FillStyleBitmap(GTexture* a_texture, const Matrix& a_matrix, BitmapWrapMode a_wrapMode, BitmapSampleMode a_sampleMode);

		// members
		GList<GRendererEventHandler>                   handlers;    // 10
		StereoParams                                   s3DParams;   // 20
		stl::enumeration<StereoDisplay, std::uint32_t> s3DDisplay;  // 34
	};
	static_assert(sizeof(GRenderer) == 0x38);
}
