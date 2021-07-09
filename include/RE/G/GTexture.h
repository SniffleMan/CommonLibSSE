#pragma once

#include "RE/G/GAtomic.h"
#include "RE/G/GImage.h"
#include "RE/G/GNewOverrideBase.h"
#include "RE/G/GPoint.h"
#include "RE/G/GRect.h"

namespace RE
{
	class GImageBase;
	class GRenderer;

	class GTexture : public GNewOverrideBase<GStatRenderer::kMem>
	{
	public:
		using Handle = void*;

		enum class MapFlags
		{
			kNone = 0,
			kKeepOld = 1
		};

		enum class ImageTexUsage
		{
			kWrap = 1 << 0,
			kUpdate = 1 << 4,
			kMap = 1 << 5,
			kRenderTarget = 1 << 6
		};

		struct UpdateRect
		{
		public:
			// members
			GPoint<std::int32_t> dest;  // 00
			GRect<std::int32_t>  src;   // 08
		};
		static_assert(sizeof(UpdateRect) == 0x18);

		struct MapRect
		{
		public:
			// members
			std::uint32_t width;   // 00
			std::uint32_t height;  // 04
			std::uint8_t* data;    // 08
			std::uint32_t pitch;   // 10
			std::uint32_t pad14;   // 14
		};
		static_assert(sizeof(MapRect) == 0x18);

		class ChangeHandler
		{
		public:
			enum class EventType
			{
				kDataChange,
				kDataLost,
				kRendererReleased
			};

			virtual ~ChangeHandler() = default;  // 00

			// add
			virtual void OnChange(GRenderer* a_renderer, EventType a_changeType);  // 01
			virtual bool Recreate(GRenderer* a_renderer);                          // 02
		};
		static_assert(sizeof(ChangeHandler) == 0x8);

		virtual ~GTexture() = default;  // 00

		// add
		virtual bool         InitTexture(GImageBase* a_im, ImageTexUsage a_usage = ImageTexUsage::kWrap) = 0;                                                                   // 01
		virtual bool         InitDynamicTexture(std::int32_t a_width, std::int32_t a_height, GImage::ImageFormat a_format, std::int32_t a_mipmaps, ImageTexUsage a_usage) = 0;  // 02
		virtual void         Update(std::int32_t a_level, std::int32_t a_num, const UpdateRect* a_rects, const GImageBase* a_im) = 0;                                           // 03
		virtual std::int32_t Map(std::int32_t a_level, std::int32_t a_num, MapRect* a_maps, MapFlags a_flags = MapFlags::kNone) = 0;                                            // 04
		virtual bool         Unmap(std::int32_t a_level, std::int32_t a_num, MapRect* a_maps, MapFlags a_flags = MapFlags::kNone) = 0;                                          // 05
		[[nodiscard]] virtual GRenderer*   GetRenderer() const = 0;                                                                                                                           // 06
		[[nodiscard]] virtual bool         IsDataValid() const = 0;                                                                                                                           // 07
		[[nodiscard]] virtual Handle       GetUserData() const = 0;                                                                                                                           // 08
		virtual void         SetUserData(Handle a_data) = 0;                                                                                                                    // 09
		virtual void         AddChangeHandler(ChangeHandler* a_handler) = 0;                                                                                                    // 0A
		virtual void         RemoveChangeHandler(ChangeHandler* a_handler) = 0;                                                                                                 // 0B

		// members
		GAtomicInt<std::int32_t> refCount;  // 08
	};
}
