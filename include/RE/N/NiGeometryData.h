#pragma once

#include "RE/N/NiBound.h"
#include "RE/N/NiObject.h"

namespace RE
{
	class NiAdditionalGeometryData;
	class NiColorA;
	class NiPoint2;
	class NiPoint3;
	class NiTriShapeData;
	class NiTriStripsData;

	class NiGeometryData : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiGeometryData;
		inline static constexpr auto Ni_RTTI = NiRTTI_NiGeometryData;

		enum class DataFlag
		{
			kNone = 0x0000,
			kNDL = 1 << 12,
			kMax = 1 << 13,
			kATI = kNDL | kMax,
		};

		enum class DirtyFlag
		{
			kVertex = 1 << 0,
			kNormal = 1 << 1,
			kColor = 1 << 2,
			kTexture = 1 << 3,

			kMutable = 0,
			kStatic = 1 << 14,
			kVolatile = 1 << 15
		};

		enum class KeepFlag
		{
			kXYZ = 1 << 0,
			kNorm = 1 << 1,
			kColor = 1 << 2,
			kUV = 1 << 3,
			kIndices = 1 << 4,
			kBonedata = 1 << 5,

			kAll = kXYZ | kNorm | kColor | kUV | kIndices | kBonedata
		};

		enum class CompressFlag
		{
			kNorm = 1 << 0,
			kColor = 1 << 1,
			kUV = 1 << 2,
			kWeight = 1 << 3,
			kPosition = 1 << 4,

			kAll = kNorm | kColor | kUV | kWeight | kPosition
		};

		~NiGeometryData() override;  // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;                          // 02
		void          LoadBinary(NiStream& a_stream) override;           // 18
		void          LinkObject(NiStream& a_stream) override;           // 19
		bool          RegisterStreamables(NiStream& a_stream) override;  // 1A
		void          SaveBinary(NiStream& a_stream) override;           // 1B
		bool          IsEqual(NiObject* a_object) override;              // 1C

		// add
		virtual void             SetActiveVertexCount(std::uint16_t a_count);  // 25 - { return; }
		[[nodiscard]] virtual std::uint16_t    GetActiveVertexCount() const;                 // 26 - { return vertices; }
		virtual NiTriStripsData* AsTriStripsData();                            // 27 - { return 0; }
		virtual NiTriShapeData*  AsTriShapeData();                             // 28 - { return 0; }
		virtual void             Unk_29(void) = 0;                             // 29

		// members
		std::uint16_t                                vertices;            // 10
		std::uint16_t                                id;                  // 12
		stl::enumeration<DirtyFlag, std::uint16_t>   dirtyFlags;          // 14
		stl::enumeration<DataFlag, std::uint16_t>    dataFlags;           // 16
		NiBound                                      bound;               // 18
		NiPoint3*                                    vertex;              // 28
		NiPoint3*                                    normal;              // 30
		NiColorA*                                    color;               // 38
		NiPoint2*                                    texture;             // 40
		std::uint32_t                                unk48;               // 48
		std::uint32_t                                unk4C;               // 4C
		std::uint32_t                                unk50;               // 50
		std::uint32_t                                unk54;               // 54
		NiPointer<NiAdditionalGeometryData>          additionalGeomData;  // 58
		stl::enumeration<KeepFlag, std::uint8_t>     keepFlags;           // 60
		stl::enumeration<CompressFlag, std::uint8_t> compressFlags;       // 61
		std::uint8_t                                 unk62;               // 62
		std::uint8_t                                 unk63;               // 63
		std::uint8_t                                 unk64;               // 64
		std::uint8_t                                 unk65;               // 65
		bool                                         hasGeoData;          // 66
		std::uint8_t                                 unk67;               // 67
	};
	static_assert(sizeof(NiGeometryData) == 0x68);
}
