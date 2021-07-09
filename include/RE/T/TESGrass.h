#pragma once

#include "RE/F/FormTypes.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESModel.h"

namespace RE
{
	class TESGrass :
		public TESBoundObject,  // 00
		public TESModel         // 30
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESGrass;
		inline static constexpr auto FORMTYPE = FormType::Grass;

		enum class GRASS_WATER_STATE
		{
			kAboveOnlyAtLeast = 0,
			kAboveOnlyAtMost = 1,
			kBelowOnlyAtLeast = 2,
			kBelowOnlyAtMost = 3,
			kBothAtLeast = 4,
			kBothAtMost = 5,
			kBothAtMostAbove = 6,
			kBothAtMostBelow = 7
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct GRASS_DATA  // DATA
		{
			enum class Flag
			{
				kNone = 0,
				kVertexLighting = 1 << 0,
				kUniformScale = 1 << 1,
				kFitSlope = 1 << 2
			};

			std::int8_t                                        density;                 // 00
			std::int8_t                                        minSlopeDegrees;         // 01
			std::int8_t                                        maxSlopeDegrees;         // 02
			std::uint8_t                                       pad03;                   // 03
			std::uint16_t                                      distanceFromWaterLevel;  // 04
			std::uint16_t                                      pad06;                   // 06
			stl::enumeration<GRASS_WATER_STATE, std::uint32_t> underwater;              // 08
			float                                              positionRange;           // 0C
			float                                              heightRange;             // 10
			float                                              colorRange;              // 14
			float                                              wavePeriod;              // 18
			stl::enumeration<Flag, std::uint8_t>               flags;                   // 1C
			std::uint8_t                                       pad1D;                   // 1D
			std::uint16_t                                      pad1E;                   // 1E
		};
		static_assert(sizeof(GRASS_DATA) == 0x20);

		~TESGrass() override;  // 00

		// override (TESBoundObject)
		void InitializeData() override;      // 04
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// add
		[[nodiscard]] virtual std::uint8_t      GetDensity() const;                                         // 53 - { return data.density; }
		virtual bool              SetDensity(std::uint8_t a_density);                         // 54 - { if (a_density > 100) return false; data.density = a_density; return true; }
		[[nodiscard]] virtual std::uint8_t      GetMinSlopeDegrees() const;                                 // 55 - { return data.minSlope; }
		virtual bool              SetMinSlopeDegrees(std::uint8_t a_minSlope);                // 56 - { if (a_minSlope > 90 || a_minSlope > data.maxSlopeDegrees) return false; data.minSlopeDegrees = a_minSlope; return true; }
		[[nodiscard]] virtual std::uint8_t      GetMaxSlopeDegrees() const;                                 // 57 - { return data.maxSlope; }
		virtual bool              SetMaxSlopeDegrees(std::uint8_t a_maxSlope);                // 58 - { if (a_maxSlope > 90 || a_maxSlope < data.minSlopeDegrees) return false; data.maxSlopeDegrees = a_maxSlope; return true; }
		[[nodiscard]] virtual float             GetMinSlope() const;                                        // 59 - { return data.minSlopeDegrees * 1deg; }
		[[nodiscard]] virtual float             GetMaxSlope() const;                                        // 5A - { return data.maxSlopeDegrees * 1deg; }
		[[nodiscard]] virtual std::uint16_t     GetDistanceFromWaterLevel() const;                          // 5B - { return data.distanceFromWaterLevel; }
		virtual void              SetDistanceFromWaterLevel(std::uint16_t a_unitsFromWater);  // 5C - { data.distanceFromWaterLevel = a_unitsFromWater; }
		[[nodiscard]] virtual GRASS_WATER_STATE GetUnderwaterState() const;                                 // 5D - { return data.underwater; }
		virtual void              SetUnderwaterState(GRASS_WATER_STATE a_waterState);         // 5E - { data.underwater = a_waterState; }
		[[nodiscard]] virtual float             GetPositionRange() const;                                   // 5F - { return data.positionRange; }
		virtual bool              SetPositionRange(float a_positionRange);                    // 60 - { if (a_positionRange < 0.0 || a_positionRange > 512.0) return false; data.positionRange = a_positionRange; return true; }
		[[nodiscard]] virtual float             GetHeightRange() const;                                     // 61 - { return data.heightRange; }
		virtual bool              SetHeightRange(float a_heightRange);                        // 62 - { if (a_heightRange < 0.0 || a_heightRange > 1.0) return false; data.heightRange = a_heightRange; return true; }
		[[nodiscard]] virtual float             GetColorRange() const;                                      // 63 - { return data.colorRange; }
		virtual bool              SetColorRange(float a_colorRange);                          // 64 - { if (a_colorRange < 0.0 || a_colorRange > 1.0) return false; data.colorRange = a_colorRange; return true; }
		[[nodiscard]] virtual float             GetWavePeriod() const;                                      // 65 - { return data.wavePeriod; }
		virtual bool              SetWavePeriod(float a_wavePeriod);                          // 66 - { if (a_wavePeriod <= 0.0) return false; data.wavePeriod = a_wavePeriod; return true; }
		[[nodiscard]] virtual bool              GetVertexLighting() const;                                  // 67 - { return data.flags & 1; }
		virtual void              SetVertexLighting(bool a_set);                              // 68 - { if (a_set) data.flags |= 0x1; else data.flags &= 0xFE; }
		[[nodiscard]] virtual bool              GetUniformScaling() const;                                  // 69 - { return (data.flags >> 1) & 1; }
		virtual void              SetUniformScaling(bool a_set);                              // 6A - { if (a_set) data.flags |= 0x2; else data.flags &= 0xFD; }
		[[nodiscard]] virtual bool              GetFitToSlope() const;                                      // 6B - { return (data.flags >> 2) & 1; }
		virtual void              SetFitToSlope(bool a_set);                                  // 6C - { if (a_set) data.flags |= 0x4; else data.flags &= 0xFB; }

		// members
		GRASS_DATA data;  // 58 - DATA
	};
	static_assert(sizeof(TESGrass) == 0x78);
}
