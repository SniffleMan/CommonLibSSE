#pragma once

#include "RE/G/GFxState.h"
#include "RE/G/GPtr.h"
#include "RE/G/GRenderer.h"

namespace RE
{
	class GRenderer;

	class GFxRenderConfig : public GFxState
	{
	public:
		using RenderCapBits = GRenderer::RenderCapBits;
		using VertexFormat = GRenderer::VertexFormat;

		enum class RenderFlag
		{
			kNone = 0,

			kStrokeCorrect = 0,
			kStrokeNormal = 1 << 0,
			kStrokeHairline = 1 << 1,
			kStrokeMask = 0x03,

			kEdgeAA = 1 << 4,
			kOptimizeTriangles = 1 << 5,
			kNoViewCull = 1 << 8
		};

		[[nodiscard]] bool          IsUsingEdgeAA() const;
		[[nodiscard]] bool          IsEdgeAATextured() const;
		[[nodiscard]] bool          IsOptimizingTriangles() const;
		[[nodiscard]] bool          HasCxformAddAlpha() const;
		[[nodiscard]] bool          HasVertexFormat(VertexFormat a_fmt) const;
		[[nodiscard]] RenderFlag    GetStrokeRenderFlags() const;
		[[nodiscard]] RenderCapBits GetRendererCapBits() const;
		[[nodiscard]] GRenderer*    GetRenderer() const;
		void          SetRenderFlags(RenderFlag a_flags);
		[[nodiscard]] RenderFlag    GetRenderFlags() const;
		void          SetMaxCurvePixelError(float a_pixelError);
		[[nodiscard]] float         GetMaxCurvePixelError() const;
		[[nodiscard]] float         GetStrokerAAWidth() const;
		void          SetStrokerAAWidth(float a_aawidth);

		// members
		GPtr<GRenderer>                                renderer;            // 18
		float                                          maxCurvePixelError;  // 20
		stl::enumeration<RenderFlag, std::uint32_t>    renderFlags;         // 24
		float                                          strokerAAWidth;      // 28
		stl::enumeration<RenderCapBits, std::uint32_t> rendererCapBits;     // 2C
		stl::enumeration<VertexFormat, std::uint32_t>  rendererVtxFmts;     // 30
		std::uint32_t                                  pad34;               // 34
	};
	static_assert(sizeof(GFxRenderConfig) == 0x38);
}
