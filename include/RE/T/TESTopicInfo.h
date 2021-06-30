#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/D/DialogueItem.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MemoryManager.h"
#include "RE/T/TESCondition.h"
#include "RE/T/TESForm.h"

namespace RE
{
	struct TOPIC_INFO_DATA  // ENAM
	{
		enum class TOPIC_INFO_FLAGS
		{
			kNone = 0,
			kStartSceneOnEnd = 1 << 0,
			kRandom = 1 << 1,
			kSayOnce = 1 << 2,
			kRequiresPlayerActivation = 1 << 3,
			kInfoRefusal = 1 << 4,
			kRandomEnd = 1 << 5,
			kEndRunningScene = 1 << 6,
			kIsForceGreet = 1 << 7,
			kPlayerAddress = 1 << 8,
			kForceSubtitle = 1 << 9,
			kCanMoveWhileGreeting = 1 << 10,
			kNoLIPFile = 1 << 11,
			kPostProcess = 1 << 12,
			kCustomSoundOutput = 1 << 13,
			kSpendsFavorPoints = 1 << 14
		};

		[[nodiscard]] float GetResetHours() const;

		stl::enumeration<TOPIC_INFO_FLAGS, std::uint16_t> flags;           // 0
		std::uint16_t                                     timeUntilReset;  // 2 - reset hours as a std::uint16_t
	};
	static_assert(sizeof(TOPIC_INFO_DATA) == 0x4);

	class TESTopicInfo : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESTopicInfo;
		inline static constexpr auto FORMTYPE = FormType::Info;

		enum class FavorLevel  // CNAM
		{
			kNone = 0,
			kSmall = 1,
			kMedium = 2,
			kLarge = 3
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kSaidOnce = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct ResponseData  // TRDT
		{
			enum class EmotionType
			{
				kNeutral = 0,
				kAnger = 1,
				kDisgust = 2,
				kFear = 3,
				kSad = 4,
				kHappy = 5,
				kSurprise = 6,
				kPuzzled = 7
			};

			enum class Flag
			{
				kNone = 0,
				kUseEmotionAnimation = 1 << 0
			};

			~ResponseData();
			void PopulateResponseText(TESFile* a_file);

			TES_HEAP_REDEFINE_NEW();

			// members
			stl::enumeration<EmotionType, std::uint32_t> emotionType;     // 00
			std::uint32_t                                emotionValue;    // 04
			TESTopic*                                    unk08;           // 08
			std::uint8_t                                 responseNumber;  // 10
			std::uint8_t                                 pad11;           // 11
			std::uint16_t                                pad12;           // 12
			std::uint32_t                                pad14;           // 14
			BGSSoundDescriptorForm*                      sound;           // 18
			stl::enumeration<Flag, std::uint8_t>         flags;           // 20
			std::uint8_t                                 pad21;           // 21
			std::uint16_t                                pad22;           // 22
			std::uint32_t                                pad24;           // 24
			BSFixedString                                responseText;    // 28 - NAM1
			TESIdleForm*                                 speakerIdle;     // 30
			TESIdleForm*                                 listenerIdle;    // 38
			ResponseData*                                next;            // 40
		};
		static_assert(sizeof(ResponseData) == 0x48);

		~TESTopicInfo() override;  // 00

		// override (TESForm)
		void InitializeData() override;                                                            // 04
		void ClearData() override;                                                                 // 05
		bool Load(TESFile* a_mod) override;                                                        // 06
		void LoadGame(BGSLoadFormBuffer* a_buf) override;                                          // 0F
		void Revert(BGSLoadFormBuffer* a_buf) override;                                            // 12
		void InitItemImpl() override;                                                              // 13
		void GetFormDetailedString(char* a_buf, std::uint32_t a_bufLen) override;                  // 16 - { return; }
		void SetAltered(bool a_set) override;                                                      // 24
		bool BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;  // 30
		void CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;                          // 31

		DialogueItem GetDialogueData(Actor* a_speaker);

		// members
		TESTopic*                                  parentTopic;    // 20
		TESTopicInfo*                              dataInfo;       // 28 - PNAM
		TESCondition                               objConditions;  // 30 - CTDA
		std::uint16_t                              infoIndex;      // 38 - index in infoTopics array of parent topic
		bool                                       saidOnce;       // 3A
		stl::enumeration<FavorLevel, std::uint8_t> favorLevel;     // 3B - CNAM
		TOPIC_INFO_DATA                            data;           // 3C - ENAM
		std::uint32_t                              fileOffset;     // 40
		std::uint32_t                              pad44;          // 44
	};
	static_assert(sizeof(TESTopicInfo) == 0x48);
}
