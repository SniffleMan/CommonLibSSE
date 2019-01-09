#pragma once

#include "RE/BGSBipedObjectForm.h"  // BGSBipedObjectForm
#include "RE/BSTArray.h"  // BSTArray
#include "RE/FormTypes.h"  // FormType
#include "RE/TESObject.h"  // TESObject
#include "RE/TESRaceForm.h"  // TESRaceForm


namespace RE
{
	class TESObjectARMA :
		public TESObject,			// 00
		public TESRaceForm,			// 20
		public BGSBipedObjectForm	// 30
	{
	public:
		enum { kTypeID = FormType::ARMA };


		struct Data	// DATA
		{
			enum class WeightSlider : UInt8
			{
				kNone = 0,
				kEnabled = 1 << 1
			};


			UInt8			malePriority;			// 00
			UInt8			femalePriority;			// 01
			WeightSlider	maleWeightSlider;		// 02
			WeightSlider	femaleWeightSlider;		// 03
			UInt16			unk04;					// 04
			UInt8			detectionSoundValue;	// 06
			UInt8			unk07;					// 07
			float			weaponAdjust;			// 08
			UInt32			pad0C;					// 0C
		};
		STATIC_ASSERT(sizeof(Data) == 0x10);


		bool	isValidRace(TESRace* a_sourceRace) const;
		void	GetNodeName(char* a_dstBuff, TESObjectREFR* a_refr, TESObjectARMO* a_armor, float a_weightOverride);


		// members
		Data						data;						// 040
		TESModelTextureSwap			maleWorldModel;				// 050
		TESModelTextureSwap			femaleWorldModel;			// 088
		TESModelTextureSwap			maleFirstPerson;			// 0C0
		TESModelTextureSwap			femaleFirstPerson;			// 0F8
		BGSTextureSet*				maleSkinTexture;			// 130 - NAM0
		BGSTextureSet*				femaleSkinTexture;			// 138 - NAM1
		BGSTextureSet*				maleSkinTextureSwapList;	// 140 - NAM2
		BGSTextureSet*				femaleSkinTextureSwapList;	// 148 - NAM3
		BSTArray<TESRace*>			additionalRaces;			// 150
		BGSFootstepSet*				footstepSound;				// 168 - SNDD
		BGSArtObject*				artObject;					// 170 - ONAM
	};
	STATIC_ASSERT(sizeof(TESObjectARMA) == 0x178);
}