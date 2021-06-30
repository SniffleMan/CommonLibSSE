#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BaseFormComponent.h"

namespace RE
{
	namespace BSResource
	{
		struct ID;
	}

	class TESModelTextureSwap;

	class TESModel : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESModel;

		~TESModel() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		// add
		[[nodiscard]] virtual const char*          GetModel() const;               // 04 - { return model.c_str(); }
		virtual void                 SetModel(const char* a_model);  // 05 - { model = a_model; }
		virtual TESModelTextureSwap* GetAsModelTextureSwap();        // 06 - { return 0; }

		// members
		BSFixedString   model;        // 08 - MODL
		BSResource::ID* textures;     // 10 - MODT
		std::uint32_t*  addons;       // 18
		std::uint16_t   numTextures;  // 20
		std::uint16_t   numAddons;    // 22
		std::uint32_t   pad24;        // 24
	};
	static_assert(sizeof(TESModel) == 0x28);
}
