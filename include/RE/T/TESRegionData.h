#pragma once

namespace RE
{
	class TESForm;

	class TESRegionData
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESRegionData;

		enum class Type
		{
			kObjects = 2,
			kWeather = 3,
			kMap = 4,
			kLand = 5,
			kGrass = 6,
			kSound = 7,
			kImposter = 8
		};

		struct DataHeader  // RDAT
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kOverride = 1 << 0
			};

			// members
			stl::enumeration<Flag, std::uint8_t> flags;     // 0
			std::uint8_t                         unk09;     // 1
			std::uint8_t                         priority;  // 2
			std::uint8_t                         unk0B;     // 3
			std::uint32_t                        unk0C;     // 4
		};
		static_assert(sizeof(DataHeader) == 0x8);

		virtual ~TESRegionData();  // 00

		// add
		virtual bool LoadDataHeader(void* a_arg1);                     // 01
		virtual void LoadData(TESForm* a_form);                        // 02 - { return; }
		[[nodiscard]] virtual Type GetType() const = 0;                              // 03
		virtual void ConstructSelf() = 0;                              // 04
		virtual void Unk_05(void) = 0;                                 // 05
		virtual void CopyFrom(TESRegionData* a_src, bool a_copy) = 0;  // 06
		[[nodiscard]] virtual bool IsLoaded() const = 0;                             // 07

		// members
		DataHeader dataHeader;  // 08 - RDAT
	};
	static_assert(sizeof(TESRegionData) == 0x10);
}
