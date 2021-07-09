#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class BSIInputDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSIInputDevice;

		virtual ~BSIInputDevice();  // 00

		// add
		virtual void          Initialize() = 0;                                                  // 01
		virtual void          Process(float a_arg1) = 0;                                         // 02
		virtual void          Unk_03(void) = 0;                                                  // 03
		virtual bool          GetKeyMapping(std::uint32_t a_key, BSFixedString& a_mapping) = 0;  // 04
		virtual std::uint32_t GetMappingKey(BSFixedString a_mapping) = 0;                        // 05
		virtual void          Unk_06(void) = 0;                                                  // 06
		[[nodiscard]] virtual bool          IsEnabled() const = 0;                                             // 07
		virtual void          Reset() = 0;                                                       // 08
	};
	static_assert(sizeof(BSIInputDevice) == 0x8);
}
