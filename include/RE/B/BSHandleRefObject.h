#pragma once

#include "RE/N/NiRefObject.h"

namespace RE
{
	class BSHandleRefObject : public NiRefObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSHandleRefObject;

		enum
		{
			kRefCountMask = 0x3FF,
			kHandleValid = 1 << 10
		};

		~BSHandleRefObject() override;  // 00

		void          DecRefCount();
		void          IncRefCount();
		[[nodiscard]] bool          IsHandleValid() const;
		[[nodiscard]] std::uint32_t QRefCount() const;
	};
	static_assert(sizeof(BSHandleRefObject) == 0x10);
}
