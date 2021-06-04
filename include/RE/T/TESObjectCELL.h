#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSBitField.h"
#include "RE/B/BSMultiBoundNode.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/C/Color.h"
#include "RE/E/ExtraDataList.h"
#include "RE/F/FormTypes.h"
#include "RE/I/InteriorData.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTMap.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESFullName.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class bhkWorld;
	class BSTempEffectParticle;
	class NavMesh;
	class NiAVObject;
	class NiNode;
	class NiPoint3;

	class BGSTerrainVisibilityData
	{
	public:
		// members
		BSBitField<>* visData;	// 0
	};
	static_assert(sizeof(BGSTerrainVisibilityData) == 0x8);

	struct EXTERIOR_DATA  // XCLC
	{
	public:
		enum class LandHideFlag
		{
			kNone = 0,
			kQuad1 = 1 << 0,
			kQuad2 = 1 << 1,
			kQuad3 = 1 << 2,
			kQuad4 = 1 << 3
		};

		// members
		std::int32_t								 cellX;			 // 00
		std::int32_t								 cellY;			 // 04
		char*										 maxHeightData;	 // 08
		BGSTerrainVisibilityData*					 lodVisData;	 // 10
		float										 worldX;		 // 18
		float										 worldY;		 // 1C
		stl::enumeration<LandHideFlag, std::uint8_t> landHideFlags;	 // 20
		std::uint8_t								 pad21;			 // 21
		std::uint16_t								 pad22;			 // 22
		std::uint32_t								 pad24;			 // 24
	};
	static_assert(sizeof(EXTERIOR_DATA) == 0x28);

	class NavMeshArray
	{
	public:
		// members
		BSTArray<BSTSmartPointer<NavMesh>> navMeshes;  // 00
	};
	static_assert(sizeof(NavMeshArray) == 0x18);

	struct LOADED_CELL_DATA
	{
	public:
		// members
		void*												 unk000;				// 000 - smart ptr
		NiPointer<NiNode>									 cell3D;				// 008
		void*												 unk010;				// 010 - smart ptr
		void*												 unk018;				// 018 - smart ptr
		void*												 unk020;				// 020 - smart ptr
		std::uint64_t										 unk028;				// 028
		std::uint64_t										 unk030;				// 030
		std::uint64_t										 unk038;				// 038
		BSTArray<void*>										 unk040;				// 040
		BSTArray<void*>										 unk058;				// 058
		NiTMap<TESForm*, ObjectRefHandle>					 unk070;				// 070
		NiTMap<ObjectRefHandle, NiNode*>					 emittanceLightRefMap;	// 090
		NiTMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>> multiboundRefMap;		// 0B0
		NiTMap<BSMultiBoundNode*, ObjectRefHandle>			 refMultiboundMap;		// 0D0
		BSSimpleList<ObjectRefHandle>						 activatingRefs;		// 0F0
		BSSimpleList<ObjectRefHandle>						 unk100;				// 100
		std::uint64_t										 unk110;				// 110
		BSTArray<void*>										 unk118;				// 118
		BSTArray<void*>										 unk130;				// 130
		BSTArray<void*>										 unk148;				// 148
		BGSEncounterZone*									 encounterZone;			// 160
		std::uint64_t										 unk168;				// 168
		std::uint64_t										 unk170;				// 170
		std::uint64_t										 unk178;				// 178
	};
	static_assert(sizeof(LOADED_CELL_DATA) == 0x180);

	class TESObjectCELL :
		public TESForm,		// 000
		public TESFullName	// 020
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObjectCELL;
		inline static constexpr auto FORMTYPE = FormType::Cell;

		enum class Flag	 // DATA
		{
			kNone = 0,
			kIsInteriorCell = 1 << 0,
			kHasWater = 1 << 1,
			kCanTravelFromHere = 1 << 2,
			kNoLODWater = 1 << 3,
			kHasTempData = 1 << 4,
			kPublicArea = 1 << 5,
			kHandChanged = 1 << 6,
			kShowSky = 1 << 7,
			kUseSkyLighting = 1 << 8
		};

		enum class CellState
		{
			kAttached = 7
		};

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kFlags = 1 << 1,
				kFullName = 1 << 2,
				kOwnership = 1 << 3,
				kExteriorShort = 1 << 28,
				kExteriorChar = 1 << 29,
				kDetachTime = 1 << 30,
				kSeendData = (std::uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kPersistent = 1 << 10,
				kIgnored = 1 << 12,
				kOffLimits = 1 << 17,
				kCompressed = 1 << 18,
				kCantWait = 1 << 19
			};
		};

		union CellData
		{
			EXTERIOR_DATA* exterior;  // XCLC
			INTERIOR_DATA* interior;  // XCLL
		};
		static_assert(sizeof(CellData) == 0x8);

		virtual ~TESObjectCELL();  // 00

		// override (TESForm)
		virtual void		ClearData() override;																  // 05
		virtual bool		Load(TESFile* a_mod) override;														  // 06
		virtual TESForm*	CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;					  // 09 - { return 0; }
		virtual bool		FindInFileFast(TESFile* a_mod) override;											  // 0C
		virtual void		SaveGame(BGSSaveFormBuffer* a_buf) override;										  // 0E
		virtual void		LoadGame(BGSLoadFormBuffer* a_buf) override;										  // 0F
		virtual void		Revert(BGSLoadFormBuffer* a_buf) override;											  // 12
		virtual void		InitItemImpl() override;															  // 13
		virtual void		GetFormDetailedString(char* a_buf, std::uint32_t a_bufLen) override;				  // 16
		virtual void		SetAltered(bool a_set) override;													  // 24
		virtual bool		BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;  // 30
		virtual void		CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;						  // 31
		virtual const char* GetFormEditorID() const override;													  // 32
		virtual bool		SetFormEditorID(const char* a_str) override;										  // 33
		virtual bool		IsParentForm() override;															  // 34 - { return true; }
		virtual bool		IsFormTypeChild(FormType a_type) override;											  // 36

		TESNPC* GetActorOwner();

		inline bhkWorld* GetbhkWorld() const
		{
			using func_t = decltype(&TESObjectCELL::GetbhkWorld);
			REL::Relocation<func_t> func{ REL::ID(18536) };
			return func(this);
		}

		void		   ForEachReference(std::function<bool(TESObjectREFR&)> a_callback) const;
		void		   ForEachReferenceInRange(const NiPoint3& a_origin, float a_radius, std::function<bool(TESObjectREFR&)> a_callback) const;
		EXTERIOR_DATA* GetCoordinates();
		TESFaction*	   GetFactionOwner();
		INTERIOR_DATA* GetLighting();
		float		   GetNorthRotation();
		TESForm*	   GetOwner();
		bool		   IsAttached() const;
		bool		   IsExteriorCell() const;
		bool		   IsInteriorCell() const;
		void		   SetActorOwner(TESNPC* a_owner);
		void		   SetFactionOwner(TESFaction* a_owner);
		void		   SetFogColor(Color a_near, Color a_far);
		void		   SetFogPlanes(float a_near, float a_far);
		void		   SetFogPower(float a_power);
		void		   SetHandChanged(bool a_changed);
		void		   SetOwner(TESForm* a_owner);
		void		   SetPublic(bool a_public);
		bool		   UsesSkyLighting() const;

		BSTempEffectParticle* PlaceTempEffectParticle(std::uint64_t a_unused, const char* a_model, NiPoint3* a_normal, NiPoint3* a_position, float a_scale = 1.0F, std::uint32_t a_flags = 7U, NiAVObject* a_target = nullptr)
		{
			using func_t = decltype(&TESObjectCELL::PlaceTempEffectParticle);
			REL::Relocation<func_t> func{ REL::ID(29218) };
			return func(this, a_unused, a_model, a_normal, a_position, a_scale, a_flags, a_target);
		}

		// members
		mutable BSSpinLock						  grassCreateLock;	 // 030
		mutable BSSpinLock						  grassTaskLock;	 // 038
		stl::enumeration<Flag, std::uint16_t>	  cellFlags;		 // 040
		std::uint16_t							  cellGameFlags;	 // 042
		stl::enumeration<CellState, std::uint8_t> cellState;		 // 044
		bool									  autoWaterLoaded;	 // 045
		bool									  cellDetached;		 // 046
		std::uint8_t							  pad047;			 // 047
		ExtraDataList							  extraList;		 // 048
		CellData								  cellData;			 // 060 - XCLL if interior, XCLC if exterior
		TESObjectLAND*							  cellLand;			 // 068
		float									  waterHeight;		 // 070 - XCLW
		NavMeshArray*							  navMeshes;		 // 078
		BSTSet<NiPointer<TESObjectREFR>>		  references;		 // 080
		TESForm*								  unk0B0;			 // 0B0 - REFR owner of cell?
		BSTArray<TESObjectREFR*>				  objectList;		 // 0B8 - persistent
		BSTArray<void*>							  unk0D0;			 // 0D0
		BSTArray<void*>							  unk0E8;			 // 0E8
		BSTArray<void*>							  unk100;			 // 100
		mutable BSSpinLock						  spinLock;			 // 118
		TESWorldSpace*							  worldSpace;		 // 120
		LOADED_CELL_DATA*						  loadedData;		 // 128
		BGSLightingTemplate*					  lightingTemplate;	 // 130 - LTMP
		std::uint64_t							  unk138;			 // 138
	};
	static_assert(sizeof(TESObjectCELL) == 0x140);
}
