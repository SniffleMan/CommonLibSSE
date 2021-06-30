#pragma once

#include "RE/B/BSISoundOutputModel.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class BGSSoundOutput :
		public TESForm,             // 00
		public BSISoundOutputModel  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSoundOutput;
		inline static constexpr auto FORMTYPE = FormType::SoundOutputModel;

		enum class Type  // MNAM
		{
			kUsesHRTF = 0,
			kDefinedSpeakerOutput = 1
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Data  // NAM1
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kAttenuatesWithDistance = 1 << 0,
				kAllowsRumble = 1 << 1
			};

			// members
			stl::enumeration<Flag, std::uint8_t> flags;          // 0
			std::uint8_t                         unk1;           // 1
			std::uint8_t                         unk2;           // 2
			std::uint8_t                         reverbSendPct;  // 3
		};
		static_assert(sizeof(Data) == 0x4);

		struct DynamicAttenuationCharacteristics : public BSIAttenuationCharacteristics
		{
		public:
			struct DataType
			{
			public:
				// members
				float         minDistance;  // 00
				float         maxDistance;  // 04
				std::uint8_t  curve[5];     // 08
				std::uint8_t  pad15;        // 0D
				std::uint16_t pad16;        // 0E
			};
			static_assert(sizeof(DataType) == 0x10);

			~DynamicAttenuationCharacteristics() override;  // 00

			// override (BSIAttenuationCharacteristics)
			float        GetMaxDistance() const override;                    // 01 - { return data.maxDistance; }
			float        GetMinDistance() const override;                    // 02 - { return data.minDistance; }
			std::uint8_t GetCurveValue(std::uint32_t a_idx) const override;  // 03 - { return a_idx >= 5 ? 0 : data.curve[a_idx]; }

			// members
			DataType data;  // 00
		};
		static_assert(sizeof(DynamicAttenuationCharacteristics) == 0x18);

		struct SpeakerArrays  // ONAM
		{
		public:
			struct Channel
			{
			public:
				// members
				std::uint8_t l;    // 0
				std::uint8_t r;    // 1
				std::uint8_t c;    // 2
				std::uint8_t lfe;  // 3
				std::uint8_t rl;   // 4
				std::uint8_t rr;   // 5
				std::uint8_t bl;   // 6
				std::uint8_t br;   // 7
			};
			static_assert(sizeof(Channel) == 0x8);

			// members
			Channel channels[3];
		};
		static_assert(sizeof(SpeakerArrays) == 0x18);

		~BGSSoundOutput() override;  // 00

		// override (TESForm)
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// override (BSISoundOutputModel)
		bool                                 DoGetUsesHRTF() const override;                                                                   // 01 - { return type == kUsesHRTF; }
		bool                                 DoGetHasSpeakerBias() const override;                                                             // 02 - { return type == kDefinedSpeakerOutput; }
		bool                                 DoGetSpeakerBias(std::uint32_t a_arg1, std::uint32_t a_arg2, float (&a_arg3)[8]) const override;  // 03
		bool                                 DoGetAttenuatesWithDistance() const override;                                                     // 04 - { return data.flags & 1; }
		bool                                 DoGetAudibility(float a_distance) const override;                                                 // 05 - { float maxDistance = attenuationValues ? attenuationValues->GetMaxDistance() : 3.4028235e38; return a_distance > maxDistance; }
		std::uint32_t                        DoGetSupportedInputChannels() const override;                                                     // 06 - { return 2; }
		const BSIAttenuationCharacteristics* DoGetAttenuation() const override;                                                                // 07 - { return attenuationValues; }
		float                                DoGetReverbSendLevel() const override;                                                            // 08 - { return data.reverbSendPct * 0.0099999998; }
		[[nodiscard]] bool                                 DoGetSupportsMonitor(std::uint32_t a_arg1) const override;                                        // 09

		// members
		Data                                  data;            // 28 - NAM1
		stl::enumeration<Type, std::uint32_t> type;            // 2C - MNAM
		DynamicAttenuationCharacteristics*    attenuation;     // 30 - ANAM
		SpeakerArrays*                        speakerOutputs;  // 38 - ONAM
	};
	static_assert(sizeof(BGSSoundOutput) == 0x40);
}
