#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	namespace BSScript
	{
		class Object;

		struct IVMObjectBindInterface
		{
		public:
			inline static constexpr auto RTTI = RTTI_BSScript__IVMObjectBindInterface;

			virtual ~IVMObjectBindInterface();  // 00

			// add
			[[nodiscard]] virtual VMHandle GetBoundHandle(const BSTSmartPointer<Object>& a_objPtr) const = 0;                                                                   // 01
			virtual bool     TypeCanBeBound(const BSFixedString& a_className, VMHandle a_handle) = 0;                                                             // 02
			virtual void     BindObject(BSTSmartPointer<Object>& a_objPtr, VMHandle a_handle, bool a_conditional) = 0;                                            // 03
			virtual void     HandleLoadedBinding(BSTSmartPointer<Object>& a_objPtr, VMHandle a_handle, bool a_conditional) = 0;                                   // 04
			virtual void     RemoveAllBoundObjects(VMHandle a_handle) = 0;                                                                                        // 05
			virtual void     RemoveAllDiskLoadedBoundObjects(VMHandle a_handle) = 0;                                                                              // 06
			virtual void     HandleCObjectDeletion(VMHandle a_handle) = 0;                                                                                        // 07
			virtual void     UnbindObject(const BSTSmartPointer<Object>& a_objPtr) = 0;                                                                           // 08
			virtual bool     CreateObjectWithProperties(const BSFixedString& a_className, std::uint32_t a_numProperties, BSTSmartPointer<Object>& a_objPtr) = 0;  // 09
			virtual bool     InitObjectProperties(BSTSmartPointer<Object>& a_objPtr, void* a_property, bool a_arg3) = 0;                                          // 0A
		};
		static_assert(sizeof(IVMObjectBindInterface) == 0x8);
	}
}
