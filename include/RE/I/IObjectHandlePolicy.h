#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class TESForm;

	namespace BSScript
	{
		struct IObjectHandlePolicy
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IObjectHandlePolicy;

			virtual ~IObjectHandlePolicy();  // 00

			// add
			[[nodiscard]] virtual bool     HandleIsType(VMTypeID a_typeID, VMHandle a_handle) const = 0;                 // 01
			[[nodiscard]] virtual bool     IsHandleObjectAvailable(VMHandle a_handle) const = 0;                         // 02
			[[nodiscard]] virtual VMHandle EmptyHandle() const = 0;                                                      // 03
			virtual VMHandle GetHandleForObject(VMTypeID a_typeID, const void* a_srcData) const = 0;       // 04
			[[nodiscard]] virtual bool     HasParent(VMHandle a_handle) const = 0;                                       // 05
			[[nodiscard]] virtual VMHandle GetParentHandle(VMHandle a_handle) const = 0;                                 // 06
			[[nodiscard]] virtual VMHandle GetHandleScriptsMovedFrom(VMHandle a_handle) const = 0;                       // 07
			[[nodiscard]] virtual void*    GetObjectForHandle(VMTypeID a_typeID, VMHandle a_handle) const = 0;           // 08
			virtual void     PersistHandle(VMHandle a_handle) = 0;                                         // 09
			virtual void     ReleaseHandle(VMHandle a_handle) = 0;                                         // 0A
			virtual void     ConvertHandleToString(VMHandle a_handle, BSFixedString& a_strOut) const = 0;  // 0B

			bool     HandleIsType(FormType a_typeID, VMHandle a_handle);
			VMHandle GetHandleForObject(FormType a_typeID, const TESForm* a_srcData);
			TESForm* GetObjectForHandle(FormType a_typeID, VMHandle a_handle);
		};
		static_assert(sizeof(IObjectHandlePolicy) == 0x8);
	}
}
