#pragma once

#include "RE/T/TESForm.h"

namespace RE
{
	class NiAVObject;
	class TESObjectREFR;

	class TESObject : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESObject;

		struct ChangeFlags
		{
			enum ChangeFlag : std::uint32_t
			{
				kObjectValue = 1 << 1,
				kObjectFullName = 1 << 2
			};
		};

		~TESObject() override;  // 00

		// override (TESForm)
		bool          IsObject() const override;     // 28 - { return true; }
		[[nodiscard]] std::uint32_t GetRefCount() const override;  // 2D - { return 0; }

		// add
		virtual void          Unk_3B(void);                                // 3B - { return 0; }
		virtual bool          IsBoundAnimObject();                         // 3C - { return false; }
		[[nodiscard]] virtual TESWaterForm* GetWaterType() const;                        // 3D - { return 0; }
		[[nodiscard]] virtual bool          IsAutoCalc() const;                          // 3E - { return false; }
		virtual void          SetAutoCalc(bool a_autoCalc);                // 3F - { return; }
		virtual NiAVObject*   Clone3D(TESObjectREFR* a_ref, bool a_arg3);  // 40 - { return 0; }
		virtual void          UnClone3D(TESObjectREFR* a_ref);             // 41
		virtual bool          IsMarker();                                  // 42
		virtual bool          IsOcclusionMarker();                         // 43 - { return formType == FormType::Static && this == Plane/Room/PortalMarker; }
		virtual bool          ReplaceModel();                              // 44
		virtual std::uint32_t IncRef();                                    // 45 - { return 0; }
		virtual std::uint32_t DecRef();                                    // 46 - { return 0; }
		virtual NiAVObject*   LoadGraphics(TESObjectREFR* a_ref);          // 47
	};
	static_assert(sizeof(TESObject) == 0x20);
}
