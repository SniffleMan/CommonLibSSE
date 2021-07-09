#pragma once

#include "RE/G/GFxStateBag.h"
#include "RE/G/GPtr.h"

namespace RE
{
	class GFxFileOpenerBase;
	class GFxJpegSupportBase;
	class GFxZlibSupportBase;
	class GFxLoaderImpl;
	class GFxMovieDef;
	class GFxMovieInfo;
	class GFxResourceLib;

	class GFxLoader : public GFxStateBag
	{
	public:
		enum LoadConstants : std::uint32_t
		{
			kLoadAll = 0,
			kLoadWaitCompletion = 1 << 0,
			kLoadWaitFrame1 = 1 << 1,
			kLoadOrdered = 1 << 4,
			kLoadThreadedBinding = 1 << 5,
			kLoadOnThread = 1 << 6,
			kLoadKeepBindData = 1 << 7,
			kLoadImageFiles = 1 << 16,
			kLoadDisableSWF = 1 << 19,
			kLoadDisableImports = 1 << 20,
			kLoadQuietOpen = 1 << 21,
			kLoadDebugHeap = 1 << 28
		};

		struct LoaderConfig
		{
			std::uint32_t            defLoadFlags;
			GPtr<GFxFileOpenerBase>  fileOpener;
			GPtr<GFxZlibSupportBase> zLibSupport;
			GPtr<GFxJpegSupportBase> jpegSupport;
		};

		// override (GFxStateBag)
		GFxStateBag* GetStateBagImpl() const override;  // 00

		~GFxLoader() override;  // 01

		// add
		[[nodiscard]] virtual bool CheckTagLoader(std::int32_t a_tagType) const;  // 05

		GFxMovieDef*   CreateMovie(const char* a_filename, LoadConstants a_loadConstants = LoadConstants::kLoadAll, UPInt a_memoryArena = 0);
		[[nodiscard]] GFxLoaderImpl* GetLoaderImpl() const;

		// members
		GFxLoaderImpl*  impl;               // 08
		GFxResourceLib* strongResourceLib;  // 10
		std::uint32_t   defLoadFlags;       // 18
		std::uint32_t   pad1C;              // 1C
	};
	static_assert(sizeof(GFxLoader) == 0x20);
}
