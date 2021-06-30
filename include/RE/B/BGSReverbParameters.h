#pragma once

#include "RE/B/BSIReverbType.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSReverbParameters :
		public TESForm,       // 00
		public BSIReverbType  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSReverbParameters;
		inline static constexpr auto FORMTYPE = FormType::ReverbParam;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct ReverbParams  // DATA
		{
			std::uint16_t decayTime;        // 00 - in ms
			std::uint16_t hfReference;      // 02 - in Hz
			std::int8_t   roomFilter;       // 04
			std::int8_t   roomHFFilter;     // 05
			std::int8_t   reflections;      // 06
			std::int8_t   reverb;           // 07
			std::int8_t   decayHFRatio;     // 08
			std::int8_t   reflectionDelay;  // 09 - in ms
			std::int8_t   reverbDelay;      // 0A - in ms
			std::int8_t   diffusionPct;     // 0B
			std::int8_t   densityPct;       // 0C
			std::uint8_t  pad0D;            // 0D
		};
		static_assert(sizeof(ReverbParams) == 0xE);

		~BGSReverbParameters() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		bool Load(TESFile* a_mod) override;  // 06

		// override (BSIReverbType)
		std::int32_t DoGetRoomLevel() const override;        // 00 - { return data.roomFilter * 100; }
		std::int32_t DoGetRoomHFLevel() const override;      // 01 - { return data.roomHFFilter * 100; }
		float        DoGetDecayTime() const override;        // 02 - { return data.decayTime * 0.001; }
		float        DoGetDecayHFRatio() const override;     // 03 - { return data.decayHFRatio * 0.0099999998; }
		std::int32_t DoGetReflectionLevel() const override;  // 04 - { return data.reflections * 100; }
		float        DoGetReflectionDelay() const override;  // 05 - { return data.reflectDelay * 0.0012000001; }
		std::int32_t DoGetReverbLevel() const override;      // 06 - { return data.reverb * 100; }
		float        DoGetReverbDelay() const override;      // 07 - { return data.reverbDelay * 0.001; }
		float        DoGetDiffusion() const override;        // 08 - { return data.diffusionPct; }
		float        DoGetDensity() const override;          // 09 - { return data.densityPct; }
		[[nodiscard]] float        DoGetHFReference() const override;      // 0A - { return data.hfReference; }

		// members
		ReverbParams  data;   // 28 - DATA
		std::uint16_t pad36;  // 36
	};
	static_assert(sizeof(BGSReverbParameters) == 0x38);
}
