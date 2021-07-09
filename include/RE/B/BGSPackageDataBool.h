#pragma once

#include "RE/B/BGSNamedPackageData.h"
#include "RE/I/IPackageData.h"

namespace RE
{
	class BGSPackageDataBool : public BGSNamedPackageData<IPackageData>
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSPackageDataBool;

		~BGSPackageDataBool() override;  // 00

		// override (BGSNamedPackageData<IPackageData>)
		void                 LoadPackage(TESFile* a_mod) override;              // 02
		void                 Assign(IPackageData* a_other) override;            // 03
		bool                 IsNotEqual(IPackageData* a_other) const override;  // 04
		void                 Unk_05(void) override;                             // 05 - { return 1; }
		void                 Unk_07(void) override;                             // 07
		void                 LoadBuffer(BGSLoadFormBuffer* a_buf) override;     // 08
		void                 Unk_09(void) override;                             // 09 - { return; }
		bool                 GetDataAsString(BSString* a_dst) const override;   // 0A - { return *a_dst->set_cstr(((data >> 1) & 1) ? "True" : "False"); }
		[[nodiscard]] const BSFixedString& GetTypeName() const override;                      // 0B - { return "Bool"; }
	};
	static_assert(offsetof(BGSPackageDataBool, data) == 0x08);
	static_assert(sizeof(BGSPackageDataBool) == 0x10);
}
