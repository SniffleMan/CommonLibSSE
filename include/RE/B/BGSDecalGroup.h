#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSTextureSet;
	class NiAVObject;
	class NiNode;
	class TESObjectCELL;

	struct DECAL_CREATION_DATA
	{
	public:
		// members
		NiPoint3			  origin{ 0.0F, 0.0F, 0.0F };										 // 00
		NiPoint3			  direction{ 0.0F, 0.0F, 0.0F };									 // 0C
		NiPoint3			  surfaceNormal{ 0.0F, 0.0F, 0.0F };								 // 18
		ObjectRefHandle		  objectRefHandle{};												 // 24
		NiPointer<NiAVObject> avObject{ nullptr };												 // 28
		NiNode*				  clone{ nullptr };													 // 30
		BGSTextureSet*		  textureSet{ nullptr };											 // 38
		BGSTextureSet*		  textureSet2{ nullptr };											 // 40
		std::int32_t		  unk48{ -1 };														 // 48
		float				  width{ 0.0F };													 // 4C
		float				  height{ 0.0F };													 // 50
		float				  depth{ 0.0F };													 // 54
		NiMatrix3			  rotation{ 1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F };	 // 58
		TESObjectCELL*		  parentCell{ nullptr };											 // 80
		float				  parallaxScale{ 0.0F };											 // 88
		std::uint64_t		  unk90{ 0U };														 // 90
		float				  shininess{ 4.0F };												 // 98
		float				  angleThreshold{ 15.0F };											 // 9C
		float				  placementRadius{ 16.0F };											 // A0
		NiColor				  color{ 1.0F, 1.0F, 1.0F };										 // A4
		std::uint32_t		  unkB0{ 0U };														 // B0
		std::int8_t			  subtextureIndex{ 0U };											 // B4
		bool				  permanent{ 0U };													 // B5
		std::uint8_t		  unkB6{ 1U };														 // B6
		bool				  parallax{ false };												 // B7
		bool				  alphaTesting{ true };												 // B8
		bool				  alphaBlending{ false };											 // B9
		std::uint8_t		  parallaxPasses{ 0U };												 // BA
		std::uint8_t		  unkBB{ 0U };														 // BB
		std::uint8_t		  unkBC{ 0U };														 // BC
		bool				  twoSided{ false };												 // BD
		std::uint8_t		  unkBE{ 0U };														 // BE
		std::uint8_t		  unkBF{ 0U };														 // BF
		std::uint32_t		  unkC0{ 0U };														 // C0
	};
	static_assert(sizeof(DECAL_CREATION_DATA) == 0xC8);

	struct BGSDecalGroup
	{
	public:
		// members
		bool						   permanentGroup;	// 00
		bool						   manualSaveLoad;	// 01
		std::uint16_t				   pad02;			// 02
		std::uint32_t				   pad04;			// 04
		BSTArray<std::uint32_t>		   decalGroups;		// 08
		BSTArray<DECAL_CREATION_DATA*> pendingDecals;	// 20
	};
	static_assert(sizeof(BGSDecalGroup) == 0x38);
}
