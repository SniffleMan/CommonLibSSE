#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/A/ActiveEffect.h"
#include "RE/A/ActorState.h"
#include "RE/A/ActorValueOwner.h"
#include "RE/A/ActorValues.h"
#include "RE/B/BGSEntryPointPerkEntry.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSPointerHandleSmartPointer.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTTuple.h"
#include "RE/D/DetectionPriorities.h"
#include "RE/F/FormTypes.h"
#include "RE/I/IPostAnimationChannelUpdateFunctor.h"
#include "RE/M/MagicSystem.h"
#include "RE/M/MagicTarget.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESNPC.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class ActorMagicCaster;
	class ActorMover;
	class AIProcess;
	class bhkCharacterController;
	class bhkCharacterMoveFinishEvent;
	class BipedAnim;
	class BSTransformDeltaEvent;
	class CombatController;
	class CombatGroup;
	class ExtraDataList;
	class InventoryEntryData;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class NiRefObject;
	class PackageLocation;
	class PerkEntryVisitor;
	struct ActorMotionFeedbackData;
	struct ActorMotionFeedbackOutput;

	enum class ACTOR_CRITICAL_STAGE
	{
		kNone = 0,
		kGooStart = 1,
		kGooEnd = 2,
		kDisintegrateStart = 3,
		kDisintegrateEnd = 4,

		kTotal
	};

	struct Modifiers
	{
	public:
		// members
		float modifiers[ACTOR_VALUE_MODIFIERS::kTotal];	 // 0
	};
	static_assert(sizeof(Modifiers) == 0xC);

	struct ActorValueStorage
	{
	public:
		template <class T>
		struct LocalMap
		{
		public:
			T* operator[](ActorValue a_actorValue)
			{
				return GetAt(static_cast<char>(a_actorValue));
			}

			const T* operator[](ActorValue a_actorValue) const
			{
				return GetAt(static_cast<char>(a_actorValue));
			}

			// members
			BSFixedString actorValues;	// 00
			T*			  entries;		// 08

		private:
			T* GetAt(char a_actorValue) const
			{
				auto akVals = actorValues.data();
				if (akVals && entries) {
					std::uint32_t idx = 0;
					while (akVals[idx] != '\0') {
						if (akVals[idx] == a_actorValue) {
							break;
						}
						++idx;
					}

					if (akVals[idx] != '\0') {
						return std::addressof(entries[idx]);
					}
				}
				return 0;
			}
		};
		static_assert(sizeof(LocalMap<float>) == 0x10);

		// members
		LocalMap<float>		baseValues;	 // 00
		LocalMap<Modifiers> modifiers;	 // 10
	};
	static_assert(sizeof(ActorValueStorage) == 0x20);

	NiSmartPointer(Actor);

	class Actor :
		public TESObjectREFR,							   // 000
		public MagicTarget,								   // 098
		public ActorValueOwner,							   // 0B0
		public ActorState,								   // 0B8
		public BSTEventSink<BSTransformDeltaEvent>,		   // 0C8
		public BSTEventSink<bhkCharacterMoveFinishEvent>,  // 0D0
		public IPostAnimationChannelUpdateFunctor		   // 0D8
	{
	private:
		using EntryPoint = BGSEntryPointPerkEntry::EntryPoint;

	public:
		inline static constexpr auto RTTI = RTTI_Actor;
		inline static constexpr auto FORMTYPE = FormType::ActorCharacter;

		struct SlotTypes
		{
			enum
			{
				kLeftHand = 0,
				kRightHand,
				kUnknown,
				kPowerOrShout,

				kTotal
			};
		};

		enum class BOOL_BITS
		{
			kNone = 0,
			kDelayUpdateScenegraph = 1 << 0,
			kProcessMe = 1 << 1,
			kMurderAlarm = 1 << 2,
			kHasSceneExtra = 1 << 3,
			kHeadingFixed = 1 << 4,
			kSpeakingDone = 1 << 5,
			kIgnoreChangeAnimationCall = 1 << 6,
			kSoundFileDone = 1 << 7,
			kVoiceFileDone = 1 << 8,
			kInTempChangeList = 1 << 9,
			kDoNotRunSayToCallback = 1 << 10,
			kDead = 1 << 11,
			kForceGreetingPlayer = 1 << 12,
			kForceUpdateQuestTarget = 1 << 13,
			kSearchingInCombat = 1 << 14,
			kAttackOnNextTheft = 1 << 15,
			kEvpBuffered = 1 << 16,
			kResetAI = 1 << 17,
			kInWater = 1 << 18,
			kSwimming = 1 << 19,
			kVoicePausedByScript = 1 << 20,
			kWasInFrustrum = 1 << 21,
			kShouldRotateToTrack = 1 << 22,
			kSetOnDeath = 1 << 23,
			kDoNotPadVoice = 1 << 24,
			kFootIKInRange = 1 << 25,
			kPlayerTeammate = 1 << 26,
			kGivePlayerXP = 1 << 27,
			kSoundCallbackSuccess = 1 << 28,
			kUseEmotion = 1 << 29,
			kGuard = 1 << 30,
			kParalyzed = 1 << 31
		};

		enum class BOOL_FLAGS
		{
			kNone = 0,
			kScenePackage = 1 << 0,
			kIsAMount = 1 << 1,
			kMountPointClear = 1 << 2,
			kGettingOnOffMount = 1 << 3,
			kInRandomScene = 1 << 4,
			kNoBleedoutRecovery = 1 << 5,
			kInBleedoutAnimation = 1 << 6,
			kCanDoFavor = 1 << 7,
			kShouldAnimGraphUpdate = 1 << 8,
			kCanSpeakToEssentialDown = 1 << 9,
			kBribedByPlayer = 1 << 10,
			kAngryWithPlayer = 1 << 11,
			kIsTrespassing = 1 << 12,
			kCanSpeak = 1 << 13,
			kIsInKillMove = 1 << 14,
			kAttackOnSight = 1 << 15,
			kIsCommandedActor = 1 << 16,
			kForceOneAnimgraphUpdate = 1 << 17,
			kEssential = 1 << 18,
			kProtected = 1 << 19,
			kAttackingDisabled = 1 << 20,
			kCastingDisabled = 1 << 21,
			kSceneHeadTrackRotation = 1 << 22,
			kForceIncMinBoneUpdate = 1 << 23,
			kCrimeSearch = 1 << 24,
			kMovingIntoLoadedArea = 1 << 25,
			kDoNotShowOnStealthMeter = 1 << 26,
			kMovementBlocked = 1 << 27,
			kAllowInstantFurniturePopInPlayerCell = 1 << 28,
			kForceAnimGraphUpdate = 1 << 29,
			kCheckAddEffectDualCast = 1 << 30,
			kUnderwater = 1 << 31
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kLifeState = 1 << 10,
				kPackageExtraData = 1 << 11,
				kMerchantContainer = 1 << 12,
				kDismemberedLimbs = 1 << 17,
				kLeveledActor = 1 << 18,
				kDispModifiers = 1 << 19,
				kTempModifiers = 1 << 20,
				kDamageModifiers = 1 << 21,
				kOverrideModifiers = 1 << 22,
				kPermanentModifiers = 1 << 23,
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kStartsDead = 1 << 9,
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,
				kNoAIAcquire = 1 << 25,
				kDontHavokSettle = 1 << 29
			};
		};

		virtual ~Actor();  // 000

		// override (TESObjectREFR)
		virtual void					SaveGame(BGSSaveFormBuffer* a_buf) override;																																										  // 00E
		virtual void					LoadGame(BGSLoadFormBuffer* a_buf) override;																																										  // 00F
		virtual void					InitLoadGame(BGSLoadFormBuffer* a_buf) override;																																									  // 010
		virtual void					FinishLoadGame(BGSLoadFormBuffer* a_buf) override;																																									  // 011
		virtual void					Revert(BGSLoadFormBuffer* a_buf) override;																																											  // 012
		virtual void					InitItemImpl() override;																																															  // 013
		virtual void					SetDelete(bool a_set) override;																																														  // 023
		virtual void					Predestroy() override;																																																  // 03B
		virtual BGSLocation*			GetEditorLocation1() const override;																																												  // 03C - { return editorLocation; }
		virtual bool					GetEditorLocation2(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback) override;																							  // 03D
		virtual void					ForceEditorLocation(BGSLocation* a_location) override;																																								  // 03E - { editorLocation = a_location; }
		virtual void					Update3DPosition(bool a_warp) override;																																												  // 03F
		virtual void					UpdateSoundCallBack(bool a_endSceneAction) override;																																								  // 040
		virtual bool					SetDialogueWithPlayer(bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic) override;																																  // 041
		virtual BGSAnimationSequencer*	GetSequencer(void) const override;																																													  // 045 - { return currentProcess->high->animSequencer; }
		virtual bool					HasKeywordHelper(const BGSKeyword* a_keyword) const override;																																						  // 048
		virtual TESPackage*				CheckForCurrentAliasPackage() override;																																												  // 049 - { return 0; }
		virtual BGSScene*				GetCurrentScene() const override;																																													  // 04A
		virtual void					SetCurrentScene(BGSScene* a_scene) override;																																										  // 04B
		virtual bool					UpdateInDialogue(DialogueResponse* a_response, bool a_unused) override;																																				  // 04C
		virtual BGSDialogueBranch*		GetExclusiveBranch() const override;																																												  // 04D - { return exclusiveBranch; }
		virtual void					SetExclusiveBranch(BGSDialogueBranch* a_branch) override;																																							  // 04E - { exclusiveBranch = a_arg1; }
		virtual void					PauseCurrentDialogue(void) override;																																												  // 04F
		virtual NiPoint3				GetStartingAngle() const override;																																													  // 052
		virtual NiPoint3				GetStartingLocation() const override;																																												  // 053
		virtual ObjectRefHandle			RemoveItem(TESBoundObject* a_item, std::int32_t a_count, ITEM_REMOVE_REASON a_reason, ExtraDataList* a_extraList, TESObjectREFR* a_moveToRef, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0) override;  // 056
		virtual bool					AddWornItem(TESBoundObject* a_item, std::int32_t a_count, bool a_forceEquip, std::uint32_t a_arg4, std::uint32_t a_arg5) override;																					  // 057
		virtual void					DoTrap1(TrapData& a_data) override;																																													  // 058
		virtual void					DoTrap2(TrapEntry* a_trap, TargetEntry* a_target) override;																																							  // 059
		virtual void					AddObjectToContainer(TESBoundObject* a_object, ExtraDataList* a_extraList, std::int32_t a_count, TESObjectREFR* a_fromRefr) override;																				  // 05A
		virtual NiPoint3				GetLookingAtLocation() const override;																																												  // 05B
		virtual MagicCaster*			GetMagicCaster(MagicSystem::CastingSource a_source) override;																																						  // 05C
		virtual MagicTarget*			GetMagicTarget() override;																																															  // 05D - { return static_cast<MagicTarget*>(this); }
		virtual bool					IsChild() const override;																																															  // 05E - { return false; }
		virtual BSFaceGenAnimationData* GetFaceGenAnimationData() override;																																													  // 063
		virtual bool					DetachHavok(NiAVObject* a_obj3D) override;																																											  // 065
		virtual void					InitHavok() override;																																																  // 066
		virtual void					Unk_67(void) override;																																																  // 067 - related to vampire lord cape
		virtual void					Unk_68(void) override;																																																  // 068
		virtual void					Unk_69(void) override;																																																  // 069
		virtual NiAVObject*				Load3D(bool a_arg1) override;																																														  // 06A
		virtual void					Set3D(NiAVObject* a_object, bool a_queue3DTasks = true) override;																																					  // 06C
		virtual bool					PopulateGraphProjectsToLoad(void) const override;																																									  // 072
		virtual NiPoint3				GetBoundMin() const override;																																														  // 073
		virtual NiPoint3				GetBoundMax() const override;																																														  // 074
		virtual void					Unk_75(void) override;																																																  // 075 - "ActorValue GetWeaponSkill()"? really weird call, only works for right hand, and defaults to 1
		virtual void					Unk_78(void) override;																																																  // 078
		virtual void					ModifyAnimationUpdateData(BSAnimationUpdateData& a_data) override;																																					  // 079
		virtual bool					ShouldSaveAnimationOnUnloading() const override;																																									  // 07A - { return false; }
		virtual bool					ShouldSaveAnimationOnSaving() const override;																																										  // 07B
		virtual bool					ShouldPerformRevert() const override;																																												  // 07C
		virtual void					UpdateAnimation(float a_delta) override;																																											  // 07D
		virtual void					Unk_82(void) override;																																																  // 082
		virtual void					SetObjectReference(TESBoundObject* a_object) override;																																								  // 084
		virtual void					MoveHavok(bool a_forceRec) override;																																												  // 085
		virtual void					GetLinearVelocity(NiPoint3& a_velocity) const override;																																								  // 086
		virtual void					SetActionComplete(bool a_set) override;																																												  // 087
		virtual void					Disable() override;																																																	  // 089
		virtual void					ResetInventory(bool a_leveledOnly) override;																																										  // 08A
		virtual void					Unk_8B(void) override;																																																  // 08B
		virtual void					Unk_8C(void) override;																																																  // 08C
		virtual bool					OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;																																				  // 090
		virtual void					DoMoveToHigh() override;																																															  // 091
		virtual void					TryMoveToMiddleLow() override;																																														  // 092
		virtual bool					TryChangeSkyCellActorsProcessLevel() override;																																										  // 093
		virtual void					Unk_95(void) override;																																																  // 095
		virtual void					Unk_96(void) override;																																																  // 096
		virtual void					SetParentCell(TESObjectCELL* a_cell) override;																																										  // 098
		virtual bool					IsDead(bool a_notEssential = true) const override;																																									  // 099
		virtual void					Unk_9C(void) override;																																																  // 09C
		virtual void					Unk_9D(void) override;																																																  // 09D
		virtual TESAmmo*				GetCurrentAmmo() const override;																																													  // 09E
		virtual void					UnequipItem(std::uint64_t a_arg1, TESBoundObject* a_object) override;																																				  // 0A1

		// override (MagicTarget)
		virtual Actor*						 GetTargetStatsObject() override;	   // 002 - { return this; }
		virtual bool						 MagicTargetIsActor() const override;  // 003 - { return true; }
		virtual BSSimpleList<ActiveEffect*>* GetActiveEffectList() override;	   // 007

		// add
		virtual void				 Unk_A2(void);																																									  // 0A2
		virtual void				 PlayPickUpSound(TESBoundObject* a_object, bool a_pickup, bool a_use);																											  // 0A3
		virtual float				 GetHeading(bool a_ignoreRaceSettings) const;																																	  // 0A4
		virtual void				 SetAvoidanceDisabled(bool a_set);																																				  // 0A5 - { return; }
		virtual void				 DrawWeaponMagicHands(bool a_draw);																																				  // 0A6
		virtual void				 Unk_A7(void);																																									  // 0A7
		virtual void				 Unk_A8(void);																																									  // 0A8
		virtual void				 SetPosition(const NiPoint3& a_pos, bool a_updateCharController);																												  // 0A9
		virtual void				 KillDying();																																									  // 0AA
		virtual void				 Resurrect(bool a_resetInventory, bool a_attach3D);																																  // 0AB
		virtual bool				 PutActorOnMountQuick();																																						  // 0AC
		virtual void				 Update(float a_delta);																																							  // 0AD
		virtual void				 UpdateNoAI(float a_delta);																																						  // 0AE - { return UpdateActor3DPosition(); }
		virtual void				 UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_controller);																								  // 0AF
		virtual void				 PotentiallyFixRagdollState();																																					  // 0B0
		virtual void				 UpdateNonRenderSafe(float a_delta);																																			  // 0B1
		virtual void				 OnItemEquipped(bool a_playAnim);																																				  // 0B2
		virtual void				 Unk_B3(void);																																									  // 0B3 - { return 1; }
		virtual void				 Unk_B4(void);																																									  // 0B4
		virtual void				 SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_amount);																								  // 0B5
		virtual void				 ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_amount);																								  // 0B6
		virtual void				 RemoveCrimeGoldValue(TESFaction* a_faction, std::int32_t a_amount, bool a_violent);																							  // 0B7
		virtual std::uint32_t		 GetCrimeGoldValue(const TESFaction* a_faction) const;																															  // 0B8
		virtual void				 GoToPrison(TESFaction* a_faction, bool a_removeInventory, bool a_realJail);																									  // 0B9 - { return; }
		virtual void				 ServePrisonTime();																																								  // 0BA - { return; }
		virtual void				 PayFine(TESFaction* a_faction, bool a_goToJail, bool a_removeStolenItems);																										  // 0BB - { return; }
		virtual bool				 GetCannibal();																																									  // 0BC - { return false; }
		virtual void				 SetCannibal(bool a_set);																																						  // 0BD - { return; }
		virtual bool				 GetVampireFeed();																																								  // 0BE - { return false; }
		virtual void				 SetVampireFeed(bool a_set);																																					  // 0BF - { return; }
		virtual void				 InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);																										  // 0C0 - { return; }
		virtual void				 InitiateCannibalPackage(Actor* a_target);																																		  // 0C1 - { return; }
		virtual void				 GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset);																							  // 0C2
		virtual void				 SetRefraction(bool a_enable, float a_refraction);																																  // 0C3
		virtual void				 Unk_C4(void);																																									  // 0C4 - { return; }
		virtual void				 Unk_C5(void);																																									  // 0C5 - { return 1; }
		virtual void				 Unk_C6(void) = 0;																																								  // 0C6
		virtual float				 GetAcrobatics() const;																																							  // 0C7 - { return 1.0; }
		virtual void				 Unk_C8(void);																																									  // 0C8
		virtual void				 Unk_C9(void);																																									  // 0C9
		virtual void				 OnArmorActorValueChanged();																																					  // 0CA - { return; }
		virtual ObjectRefHandle		 DropObject(const TESBoundObject* a_object, ExtraDataList* a_extraList, std::int32_t a_count, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0);						  // 0CB
		virtual void				 PickUpObject(TESObjectREFR* a_object, std::int32_t a_count, bool a_arg3 = false, bool a_playSound = true);																		  // 0CC
		virtual void				 AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped);																														  // 0CD
		virtual void				 DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped);																														  // 0CE
		virtual bool				 AddShout(TESShout* a_shout);																																					  // 0CF
		virtual void				 Unk_D0(void);																																									  // 0D0 - { return; }
		virtual void				 Unk_D1(void);																																									  // 0D1
		virtual std::uint32_t		 UseAmmo(std::uint32_t a_shotCount);																																			  // 0D2
		virtual bool				 CalculateCachedOwnerIsInCombatantFaction() const;																																  // 0D3
		virtual CombatGroup*		 GetCombatGroup() const;																																						  // 0D4
		virtual void				 SetCombatGroup(CombatGroup* a_group);																																			  // 0D5
		virtual bool				 CheckValidTarget(TESObjectREFR& a_target);																																		  // 0D6
		virtual void				 Unk_D7(void);																																									  // 0D7 - { return 0; }
		virtual void				 InitiateDialogue(Actor* a_target, PackageLocation* a_loc1, PackageLocation* a_loc2);																							  // 0D8
		virtual void				 Unk_D9(void);																																									  // 0D9
		virtual void				 EndDialogue();																																									  // 0DA
		virtual Actor*				 SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_activator);																												  // 0DB
		virtual void				 Unk_DC(void);																																									  // 0DC - { return; }
		virtual void				 InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runOnce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, float a_fleeFromDist, float a_fleeToDist);  // 0DD
		virtual void				 InitiateGetUpPackage();																																						  // 0DE
		virtual void				 PutCreatedPackage(TESPackage* a_package, bool a_tempPackage, bool a_createdPackage, bool a_allowFromFurniture);																  // 0DF
		virtual void				 UpdateAlpha();																																									  // 0E0
		virtual void				 SetAlpha(float a_alpha = 1.0);																																					  // 0E1
		virtual float				 GetAlpha();																																									  // 0E2
		virtual bool				 IsInCombat() const;																																							  // 0E3
		virtual void				 UpdateCombat();																																								  // 0E4
		virtual void				 StopCombat();																																									  // 0E5
		virtual void				 Unk_E6(void);																																									  // 0E6 - { return 0.0; }
		virtual void				 Unk_E7(void);																																									  // 0E7 - { return 0.0; }
		virtual void				 Unk_E8(void);																																									  // 0E8 - { return 0; }
		virtual void				 Unk_E9(void);																																									  // 0E9 - { return 0; }
		virtual void				 Unk_EA(void);																																									  // 0EA - { return 0; }
		virtual void				 Unk_EB(void);																																									  // 0EB
		virtual void				 Unk_EC(void);																																									  // 0EC
		virtual void				 Unk_ED(void);																																									  // 0ED
		virtual void				 Unk_EE(void);																																									  // 0EE
		virtual void				 WeaponSwingCallBack();																																							  // 0EF
		virtual void				 SetActorStartingPosition();																																					  // 0F0
		virtual bool				 MoveToHigh();																																									  // 0F1
		virtual bool				 MovetoLow();																																									  // 0F2
		virtual bool				 MovetoMiddleLow();																																								  // 0F3
		virtual void				 Unk_F4(void);																																									  // 0F4
		virtual bool				 HasBeenAttacked() const;																																						  // 0F5
		virtual void				 SetBeenAttacked(bool a_set);																																					  // 0F6
		virtual void				 UseSkill(ActorValue a_av, float a_points, TESForm* a_arg3);																													  // 0F7 - { return; }
		virtual bool				 IsAtPoint(const NiPoint3& a_point, float a_radius, bool a_expandRadius, bool a_alwaysTestHeight);																				  // 0F8
		virtual bool				 IsInFaction(const TESFaction* faction) const;																																	  // 0F9
		virtual void				 ForEachPerk(PerkEntryVisitor& a_visitor) const;																																  // 0FA
		virtual void				 AddPerk(BGSPerk* a_perk, std::uint32_t a_rank = 0);																															  // 0FB - { return; }
		virtual void				 RemovePerk(BGSPerk* a_perk);																																					  // 0FC - { return; }
		virtual void				 Unk_FD(void);																																									  // 0FD - { return; }
		virtual void				 Unk_FE(void);																																									  // 0FE - { return; }
		virtual bool				 HasPerkEntries(EntryPoint a_entryType) const;																																	  // 0FF
		virtual void				 ForEachPerkEntry(EntryPoint a_entryType, PerkEntryVisitor& a_visitor) const;																									  // 100
		virtual void				 ApplyPerksFromBase();																																							  // 101
		virtual void				 StartPowerAttackCoolDown();																																					  // 102 - { return; }
		virtual bool				 IsPowerAttackCoolingDown() const;																																				  // 103 - { return false; }
		virtual void				 HandleHealthDamage(Actor* a_attacker, float a_damage);																															  // 104
		virtual void				 Unk_105(void);																																									  // 105
		virtual void				 Unk_106(void);																																									  // 106 - { return; }
		virtual bool				 QSpeakingDone() const;																																							  // 107 - { return ~(unk0E0 >> 5) & 1; }
		virtual void				 SetSpeakingDone(bool a_set);																																					  // 108
		virtual void				 CreateMovementController();																																					  // 109
		virtual void				 Unk_10A(void);																																									  // 10A - { return unk16C; }
		virtual void				 Unk_10B(void);																																									  // 10B - { unk16C = a_arg1; }
		virtual void				 Unk_10C(void);																																									  // 10C - { return unk170; }
		virtual void				 Unk_10D(void);																																									  // 10D - { unk170 = a_arg1; }
		virtual void				 KillImpl(Actor* a_attacker, float a_damage, bool a_sendEvent, bool a_ragdollInstant);																							  // 10E
		virtual void				 Unk_10F(void);																																									  // 10F
		virtual bool				 CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason);																						  // 110
		virtual void				 CheckTempModifiers();																																							  // 111 - { return; }
		virtual std::int32_t		 GetCurrentShoutLevel();																																						  // 112 - return -1 on error
		virtual void				 SetLastRiddenMount(ActorHandle a_mount);																																		  // 113 - { return; }
		virtual ActorHandle			 QLastRiddenMount() const;																																						  // 114 - { return {}; }
		virtual bool				 CalculateCachedOwnerIsUndead() const;																																			  // 115
		virtual bool				 CalculateCachedOwnerIsNPC() const;																																				  // 116
		virtual void				 Unk_117(void);																																									  // 117 - { return; }
		virtual void				 Unk_118(void);																																									  // 118
		virtual const BSFixedString& GetResponseString() const;																																						  // 119 - { return "ActorResponse"; }
		virtual void				 Unk_11A(void);																																									  // 11A
		virtual void				 UpdateCombatControllerSettings();																																				  // 11B
		virtual void				 UpdateFadeSettings(bhkCharacterController* a_controller);																														  // 11C
		virtual bool				 ComputeMotionFeedbackSpeedAndDirection(const ActorMotionFeedbackData& a_data, float a_delta, ActorMotionFeedbackOutput& a_output);												  // 11D
		virtual bool				 UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_output);																								  // 11E
		virtual void				 UpdateActor3DPosition();																																						  // 11F
		virtual void				 PrecacheData();																																								  // 120
		virtual void				 WornArmorChanged(void);																																						  // 121
		virtual void				 ProcessTracking(float a_delta, NiAVObject* a_obj3D);																															  // 122
		virtual void				 Unk_123(void);																																									  // 123
		virtual void				 CreateActorMover();																																							  // 124
		virtual void				 DestroyActorMover();																																							  // 125
		virtual bool				 ShouldRespondToActorCollision(const MovementMessageActorCollision& a_msg, const ActorHandlePtr& a_target);																		  // 126
		virtual float				 CheckClampDamageModifier(ActorValue a_av, float a_delta);																														  // 127

		static NiPointer<Actor> LookupByHandle(RefHandle a_refHandle);
		static bool				LookupByHandle(RefHandle a_refHandle, NiPointer<Actor>& a_refrOut);

		bool						 AddSpell(SpellItem* a_spell);
		void						 AllowBleedoutDialogue(bool a_canTalk);
		void						 AllowPCDialogue(bool a_talk);
		bool						 CanFlyHere() const;
		bool						 CanPickpocket() const;
		bool						 CanTalkToPlayer() const;
		void						 ClearArrested();
		void						 ClearExpressionOverride();
		inline void					 ClearExtraArrows() { RemoveExtraArrows3D(); }
		ActorHandle					 CreateRefHandle();
		void						 DispelWornItemEnchantments();
		void						 DoReset3D(bool a_updateWeight);
		void						 EvaluatePackage(bool a_immediate = false, bool a_resetAI = false);
		TESNPC*						 GetActorBase();
		const TESNPC*				 GetActorBase() const;
		InventoryEntryData*			 GetAttackingWeapon();
		const InventoryEntryData*	 GetAttackingWeapon() const;
		bhkCharacterController*		 GetCharController() const;
		ActorHandle					 GetCommandingActor() const;
		TESFaction*					 GetCrimeFaction();
		const TESFaction*			 GetCrimeFaction() const;
		InventoryEntryData*			 GetEquippedEntryData(bool a_leftHand) const;
		TESForm*					 GetEquippedObject(bool a_leftHand) const;
		std::int32_t				 GetGoldAmount();
		ActorHandle					 GetHandle();
		float						 GetHeight();
		std::uint16_t				 GetLevel() const;
		ObjectRefHandle				 GetOccupiedFurniture() const;
		TESRace*					 GetRace() const;
		bool						 HasPerk(BGSPerk* a_perk) const;
		void						 InterruptCast(bool a_restoreMagicka) const;
		bool						 IsAIEnabled() const;
		bool						 IsAMount() const;
		bool						 IsAnimationDriven() const;
		bool						 IsBeingRidden() const;
		bool						 IsCommandedActor() const;
		bool						 IsEssential() const;
		bool						 IsFactionInCrimeGroup(const TESFaction* a_faction) const;
		bool						 IsGhost() const;
		bool						 IsGuard() const;
		bool						 IsHostileToActor(Actor* a_actor);
		[[nodiscard]] constexpr bool IsInKillMove() const noexcept { return boolFlags.all(BOOL_FLAGS::kIsInKillMove); }
		bool						 IsOnMount() const;
		bool						 IsPlayerTeammate() const;
		bool						 IsPowerAttacking() const;
		bool						 IsRunning() const;
		bool						 IsSneaking() const;
		bool                         IsStaggering() const;
		[[nodiscard]] bool			 IsSummoned() const noexcept;
		bool						 IsTrespassing() const;
		void						 RemoveExtraArrows3D();
		bool						 RemoveSpell(SpellItem* a_spell);
		std::int32_t				 RequestDetectionLevel(Actor* a_target, DETECTION_PRIORITY a_priority = DETECTION_PRIORITY::kNormal);
		void						 StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, std::int32_t a_num, std::int32_t a_total, TESForm* a_owner, bool a_allowWarning);
		void						 SwitchRace(TESRace* a_race, bool a_player);
		void						 UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData);
		void						 Update3DModel();
		void						 UpdateHairColor();
		void						 UpdateSkinColor();
		void						 UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand);
		bool						 VisitFactions(std::function<bool(TESFaction* a_faction, std::int8_t a_rank)> a_visitor);
		bool						 WouldBeStealing(const TESObjectREFR* a_target) const;

		// members
		stl::enumeration<BOOL_BITS, std::uint32_t>			  boolBits;							  // 0E0
		float												  updateTargetTimer;				  // 0E4
		stl::enumeration<ACTOR_CRITICAL_STAGE, std::uint32_t> criticalStage;					  // 0E8
		std::uint32_t										  pad0EC;							  // 0EC
		AIProcess*											  currentProcess;					  // 0F0
		ObjectRefHandle										  dialogueItemTarget;				  // 0F8
		ActorHandle											  currentCombatTarget;				  // 0FC
		ActorHandle											  myKiller;							  // 100
		float												  checkMyDeadBodyTimer;				  // 104
		float												  voiceTimer;						  // 108
		float												  underWaterTimer;					  // 10C
		std::int32_t										  thiefCrimeStamp;					  // 110
		std::int32_t										  actionValue;						  // 114
		float												  timerOnAction;					  // 118
		std::uint32_t										  unk11C;							  // 11C
		NiPoint3											  editorLocCoord;					  // 120
		float												  editorLocRot;						  // 12C
		TESForm*											  editorLocForm;					  // 130
		BGSLocation*										  editorLocation;					  // 138
		ActorMover*											  actorMover;						  // 140
		BSTSmartPointer<MovementControllerNPC>				  movementController;				  // 148
		void*												  unk150;							  // 150
		CombatController*									  combatController;					  // 158
		TESFaction*											  vendorFaction;					  // 160
		AITimeStamp											  calculateVendorFactionTimer;		  // 168
		std::uint32_t										  unk16C;							  // 16C
		std::uint32_t										  unk170;							  // 170
		std::uint32_t										  unk174;							  // 174
		std::uint32_t										  unk178;							  // 178
		std::uint32_t										  intimidateBribeDayStamp;			  // 17C
		std::uint64_t										  unk180;							  // 180
		BSTSmallArray<SpellItem*>							  addedSpells;						  // 188
		ActorMagicCaster*									  magicCasters[SlotTypes::kTotal];	  // 1A0
		MagicItem*											  selectedSpells[SlotTypes::kTotal];  // 1C0
		TESForm*											  selectedPower;					  // 1E0
		std::uint32_t										  unk1E8;							  // 1E8
		std::uint32_t										  pad1EC;							  // 1EC
		TESRace*											  race;								  // 1F0
		float												  equippedWeight;					  // 1F8
		stl::enumeration<BOOL_FLAGS, std::uint32_t>			  boolFlags;						  // 1FC
		ActorValueStorage									  avStorage;						  // 200
		BGSDialogueBranch*									  exclusiveBranch;					  // 220
		Modifiers											  healthModifiers;					  // 228
		Modifiers											  magickaModifiers;					  // 234
		Modifiers											  staminaModifiers;					  // 240
		Modifiers											  voicePointsModifiers;				  // 24C
		float												  lastUpdate;						  // 258
		std::uint32_t										  lastSeenTime;						  // 25C
		BSTSmartPointer<BipedAnim>							  biped;							  // 260
		float												  armorRating;						  // 268
		float												  armorBaseFactorSum;				  // 26C
		std::int8_t											  soundCallBackSet;					  // 271
		std::uint8_t										  unk271;							  // 270
		std::uint8_t										  unk272;							  // 272
		std::uint8_t										  unk273;							  // 273
		std::uint32_t										  unk274;							  // 274
		std::uint64_t										  unk278;							  // 278
		std::uint64_t										  unk280;							  // 280
		WinAPI::CRITICAL_SECTION							  unk288;							  // 288 - havok related

	private:
		TESFaction* GetCrimeFactionImpl() const;
	};
	static_assert(sizeof(Actor) == 0x2B0);
}
