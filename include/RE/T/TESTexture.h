#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	class TESTexture : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESTexture;

		~TESTexture() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		virtual std::uint32_t GetMaxAllowedSize();                     // 04 - { return 0; }
		virtual const char*   GetAsNormalFile(BSString& a_out) const;  // 05
		[[nodiscard]] virtual const char*   GetDefaultPath() const;                  // 06 - { return "Textures\\"; }

		// members
		BSFixedString textureName;  // 08 - ICON
	};
	static_assert(sizeof(TESTexture) == 0x10);
}
