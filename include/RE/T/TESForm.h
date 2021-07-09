#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BaseFormComponent.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class TESBoundObject;
	class TESFile;
	struct FORM;
	struct FORM_GROUP;

	class TESFileArray : public BSStaticArray<TESFile*>
	{
	public:
	};
	static_assert(sizeof(TESFileArray) == 0x10);

	class TESFileContainer
	{
	public:
		// members
		TESFileArray* array;  // 0
	};
	static_assert(sizeof(TESFileContainer) == 0x8);

	class TESForm : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESForm;
		inline static constexpr auto FORMTYPE = FormType::None;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kCreated = 0,
				kFlags = 1 << 0
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDestructible = 1 << 0,
				kMaster = 1 << 0,
				kUnlocked = 1 << 0,

				kAltered = 1 << 1,
				kPlayable = 1 << 2,
				kInitialized = 1 << 3,
				kNonOccluder = 1 << 4,
				kDeleted = 1 << 5,

				kBorderRegion = 1 << 6,
				kGlobalConstant = 1 << 6,
				kHasSpokenFlag = 1 << 6,
				kKnown = 1 << 6,
				kInPlaceableWater = 1 << 6,

				kFireOff = 1 << 7,
				kMustUpdate = 1 << 8,
				kOnLocalMap = 1 << 9,
				kPersistent = 1 << 10,

				kDisabled = 1 << 11,
				kUsedAsMovingPlatform = 1 << 11,

				kIgnored = 1 << 12,

				kEmpty = 1 << 13,
				kResetDestruction = 1 << 13,

				kTemporary = 1 << 14,
				kMustBeVisibleDistant = 1 << 15,
				kRandomAnim = 1 << 16,
				kDangerous = 1 << 17,
				kHasCurrents = 1 << 19,
				kIgnoreFriendlyHits = 1 << 20,
				kStillLoading = 1 << 21,
				kFormRetainsID = 1 << 22,
				kDestroyed = 1 << 23,

				kNoAIAcquire = 1 << 25,
				kObstacle = 1 << 25,

				kVATSTargetOverride = 1 << 26,
				kDisableFade = 1 << 27,

				kReflectedByAutoWater = 1 << 28,
				kShowOnWorldMap = 1 << 28,

				kChildCanUse = 1 << 29
			};
		};

		enum class InGameFormFlag
		{
			kNone = 0,
			kWantsDelete = 1 << 0,
			kForcedPersistent = 1 << 1,
			kNoFavorAllowed = 1 << 4,
			kIsSkyObject = 1 << 5,
			kRefOriginalPersistent = 1 << 6,
			kRefPermanentlyDeleted = 1 << 7
		};

		~TESForm() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { return; }
		void ClearDataComponent() override;                     // 02 - { SetEditorID(""); }
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual void                 InitializeData();                                                                                                                                // 04 - { return; }
		virtual void                 ClearData();                                                                                                                                     // 05 - { return; }
		virtual bool                 Load(TESFile* a_mod);                                                                                                                            // 06 - { return true; }
		virtual bool                 LoadPartial(TESFile* a_mod);                                                                                                                     // 07 - { return true; }
		virtual bool                 LoadEdit(TESFile* a_mod);                                                                                                                        // 08 - { return Load(a_mod); }
		virtual TESForm*             CreateDuplicateForm(bool a_createEditorID, void* a_arg2);                                                                                        // 09
		virtual bool                 AddChange(std::uint32_t a_changeFlags);                                                                                                          // 0A
		virtual void                 RemoveChange(std::uint32_t a_changeFlags);                                                                                                       // 0B
		virtual bool                 FindInFileFast(TESFile* a_mod);                                                                                                                  // 0C - { return false; }
		virtual bool                 CheckSaveGame(BGSSaveFormBuffer* a_buf);                                                                                                         // 0D - { return true; }
		virtual void                 SaveGame(BGSSaveFormBuffer* a_buf);                                                                                                              // 0E
		virtual void                 LoadGame(BGSLoadFormBuffer* a_buf);                                                                                                              // 0F
		virtual void                 InitLoadGame(BGSLoadFormBuffer* a_buf);                                                                                                          // 10 - { return; }
		virtual void                 FinishLoadGame(BGSLoadFormBuffer* a_buf);                                                                                                        // 11 - { return; }
		virtual void                 Revert(BGSLoadFormBuffer* a_buf);                                                                                                                // 12 - { return; }
		virtual void                 InitItemImpl();                                                                                                                                  // 13 - { return; }
		[[nodiscard]] virtual TESFile*             GetDescriptionOwnerFile() const;                                                                                                                 // 14 - returns the file that last modified this form
		[[nodiscard]] virtual FormType             GetSavedFormType() const;                                                                                                                        // 15 - { return formType; }
		virtual void                 GetFormDetailedString(char* a_buf, std::uint32_t a_bufLen);                                                                                      // 16 - { return std::sprintf_s(a_buf, a_bufLen, "%s Form '%s' (%08X)", g_formStrings[3 * formID], "", formID); }
		[[nodiscard]] virtual bool                 GetKnown() const;                                                                                                                                // 17 - { return (flags >> 6 ) & 1; }
		[[nodiscard]] virtual bool                 GetRandomAnim() const;                                                                                                                           // 18 - { return (flags >> 16) & 1; }
		[[nodiscard]] virtual bool                 GetPlayable() const;                                                                                                                             // 19 - { return (flags >> 2) & 1; }
		[[nodiscard]] virtual bool                 IsHeadingMarker() const;                                                                                                                         // 1A - { return false; }
		[[nodiscard]] virtual bool                 GetDangerous() const;                                                                                                                            // 1B - { return (flags >> 17) & 1; }
		[[nodiscard]] virtual bool                 QHasCurrents() const;                                                                                                                            // 1C - { return (flags >> 19) & 1; }
		[[nodiscard]] virtual bool                 GetObstacle() const;                                                                                                                             // 1D - { return (flags >> 25) & 1; }
		[[nodiscard]] virtual bool                 QIsLODLandObject() const;                                                                                                                        // 1E - { return false; }
		[[nodiscard]] virtual bool                 GetOnLocalMap() const;                                                                                                                           // 1F - { return (flags >> 9) & 1; }
		[[nodiscard]] virtual bool                 GetMustUpdate() const;                                                                                                                           // 20 - { return (flags >> 8) & 1; }
		virtual void                 SetOnLocalMap(bool a_set);                                                                                                                       // 21 - { if (a_set) flags &= 0xFFFFFDFF; else flags |= 0x200; }
		[[nodiscard]] virtual bool                 GetIgnoredBySandbox() const;                                                                                                                     // 22 - { return false; }
		virtual void                 SetDelete(bool a_set);                                                                                                                           // 23 - { bool result = (flags >> 5) & 1; if (result != a_set) { if (a_set) flags |= 0x20; else flags &= 0xFFFFFFDF; AddChange(1); return result; }
		virtual void                 SetAltered(bool a_set);                                                                                                                          // 24
		virtual void                 SaveObjectBound();                                                                                                                               // 25 - { return; }
		virtual void                 LoadObjectBound(TESFile* a_mod);                                                                                                                 // 26 - { return; }
		[[nodiscard]] virtual bool                 IsBoundObject() const;                                                                                                                           // 27 - { return false; }
		[[nodiscard]] virtual bool                 IsObject() const;                                                                                                                                // 28 - { return false; }
		[[nodiscard]] virtual bool                 IsMagicItem() const;                                                                                                                             // 29 - { return false; }
		[[nodiscard]] virtual bool                 IsWater() const;                                                                                                                                 // 2A - { return false; }
		virtual TESObjectREFR*       AsReference1();                                                                                                                                  // 2B - { return 0; }
		[[nodiscard]] virtual const TESObjectREFR* AsReference2() const;                                                                                                                            // 2C - { return 0; }
		[[nodiscard]] virtual std::uint32_t        GetRefCount() const;                                                                                                                             // 2D - { return 0; }
		[[nodiscard]] virtual const char*          GetTextForParsedSubTag(const BSFixedString& a_tag) const;                                                                                        // 2E
		virtual void                 Copy(TESForm* a_srcForm);                                                                                                                        // 2F - { return; }
		virtual bool                 BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly);                                                                      // 30
		virtual void                 CreateGroupData(FORM* a_form, FORM_GROUP* a_group);                                                                                              // 31
		[[nodiscard]] virtual const char*          GetFormEditorID() const;                                                                                                                         // 32 - { return ""; }
		virtual bool                 SetFormEditorID(const char* a_str);                                                                                                              // 33 - { return true; }
		virtual bool                 IsParentForm();                                                                                                                                  // 34 - { return false; }
		virtual bool                 IsParentFormTree();                                                                                                                              // 35 - { return false; }
		virtual bool                 IsFormTypeChild(FormType a_type);                                                                                                                // 36 - { return false; }
		virtual bool                 Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, std::uint8_t a_arg3, TESBoundObject* a_object, std::int32_t a_targetCount);  // 37 - { return false; }
		virtual void                 SetFormID(FormID a_id, bool a_updateFile);                                                                                                       // 38
		[[nodiscard]] virtual const char*          GetObjectTypeName() const;                                                                                                                       // 39 - { return ""; }
		[[nodiscard]] virtual bool                 QAvailableInGame() const;                                                                                                                        // 3A - { return true; }

		static void AddCompileIndex(FormID& a_id, TESFile* a_file)
		{
			using func_t = decltype(&TESForm::AddCompileIndex);
			REL::Relocation<func_t> func{ REL::ID(14509) };
			return func(a_id, a_file);
		}

		[[nodiscard]] static auto GetAllForms()
			-> std::pair<
				BSTHashMap<FormID, TESForm*>*,
				std::reference_wrapper<BSReadWriteLock>>
		{
			REL::Relocation<BSTHashMap<FormID, TESForm*>**> allForms{ REL::ID(514351) };
			REL::Relocation<BSReadWriteLock*>               allFormsMapLock{ REL::ID(514360) };
			return { *allForms, std::ref(*allFormsMapLock) };
		}

		[[nodiscard]] static auto GetAllFormsByEditorID()
			-> std::pair<
				BSTHashMap<BSFixedString, TESForm*>*,
				std::reference_wrapper<BSReadWriteLock>>
		{
			REL::Relocation<BSTHashMap<BSFixedString, TESForm*>**> allFormsByEditorID{ REL::ID(514352) };
			REL::Relocation<BSReadWriteLock*>                      allFormsEditorIDMapLock{ REL::ID(514361) };
			return { *allFormsByEditorID, std::ref(*allFormsEditorIDMapLock) };
		}

		[[nodiscard]] static TESForm* LookupByID(FormID a_formID)
		{
			const auto& [map, lock] = GetAllForms();
			const BSReadWriteLock l{ lock };
			if (map) {
				const auto it = map->find(a_formID);
				return it != map->end() ? it->second : nullptr;
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] static T* LookupByID(FormID a_formID)
		{
			const auto form = LookupByID(a_formID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] static TESForm* LookupByEditorID(const std::string_view& a_editorID)
		{
			const auto& [map, lock] = GetAllFormsByEditorID();
			const BSReadWriteLock l{ lock };
			if (map) {
				const auto it = map->find(a_editorID);
				return it != map->end() ? it->second : nullptr;
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] static T* LookupByEditorID(const std::string_view& a_editorID)
		{
			const auto form = LookupByEditorID(a_editorID);
			return form ? form->As<T>() : nullptr;
		}

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] T* As() noexcept;

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] const T* As() const noexcept;

		[[nodiscard]] TESObjectREFR*       AsReference() { return AsReference1(); }
		[[nodiscard]] const TESObjectREFR* AsReference() const { return AsReference2(); }

		[[nodiscard]] TESFile* GetFile(std::int32_t a_idx = -1) const
		{
			const auto array = sourceFiles.array;
			if (!array || array->empty()) {
				return nullptr;
			}

			if (a_idx < 0 || static_cast<std::uint32_t>(a_idx) >= array->size()) {
				return array->back();
			} else {
				return (*array)[a_idx];
			}
		}

		[[nodiscard]] std::uint32_t GetFormFlags() const noexcept { return formFlags; }
		[[nodiscard]] FormID        GetFormID() const noexcept { return formID; }
		[[nodiscard]] FormType      GetFormType() const noexcept { return *formType; }
		[[nodiscard]] std::int32_t  GetGoldValue() const;
		[[nodiscard]] const char*   GetName() const;
		[[nodiscard]] float         GetWeight() const;
		[[nodiscard]] bool          HasVMAD() const;
		[[nodiscard]] bool          HasWorldModel() const noexcept;
		void                        InitItem() { InitItemImpl(); }

		[[nodiscard]] bool Is(FormType a_type) const noexcept { return GetFormType() == a_type; }

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept  //
			requires(std::same_as<Args, FormType>&&...)
		{
			return (Is(a_args) || ...);
		}

		[[nodiscard]] bool IsAmmo() const noexcept { return Is(FormType::Ammo); }
		[[nodiscard]] bool IsArmor() const noexcept { return Is(FormType::Armor); }
		[[nodiscard]] bool IsBook() const noexcept { return Is(FormType::Book); }
		[[nodiscard]] bool IsDeleted() const noexcept { return (GetFormFlags() & RecordFlags::kDeleted) != 0; }
		[[nodiscard]] bool IsDynamicForm() const noexcept { return GetFormID() >= 0xFF000000; }
		[[nodiscard]] bool IsGold() const noexcept { return GetFormID() == 0x0000000F; }
		[[nodiscard]] bool IsIgnored() const noexcept { return (GetFormFlags() & RecordFlags::kIgnored) != 0; }
		[[nodiscard]] bool IsInitialized() const noexcept { return (GetFormFlags() & RecordFlags::kInitialized) != 0; }
		[[nodiscard]] bool IsKey() const noexcept { return Is(FormType::KeyMaster); }
		[[nodiscard]] bool IsLockpick() const noexcept { return GetFormID() == 0x0000000A; }

		[[nodiscard]] bool IsNot(FormType a_type) const noexcept { return !Is(a_type); }

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept  //
			requires(std::same_as<Args, FormType>&&...)
		{
			return (IsNot(a_args) && ...);
		}

		[[nodiscard]] bool IsNote() const noexcept { return Is(FormType::Note); }
		[[nodiscard]] bool IsPlayer() const noexcept { return GetFormID() == 0x00000007; }
		[[nodiscard]] bool IsPlayerRef() const noexcept { return GetFormID() == 0x00000014; }
		[[nodiscard]] bool IsSoulGem() const noexcept { return Is(FormType::SoulGem); }
		[[nodiscard]] bool IsWeapon() const noexcept { return Is(FormType::Weapon); }

		// members
		TESFileContainer                                sourceFiles;      // 08
		std::uint32_t                                   formFlags;        // 10
		FormID                                          formID;           // 14
		stl::enumeration<InGameFormFlag, std::uint16_t> inGameFormFlags;  // 18
		stl::enumeration<FormType, std::uint8_t>        formType;         // 1A
		std::uint8_t                                    pad1B;            // 1B
		std::uint32_t                                   pad1C;            // 1C
	};
	static_assert(sizeof(TESForm) == 0x20);
}
