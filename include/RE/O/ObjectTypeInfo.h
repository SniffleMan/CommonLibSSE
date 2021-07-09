#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/P/PropertyTypeInfo.h"
#include "RE/T/TypeInfo.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSScript
	{
		class IFunction;

		class ObjectTypeInfo : public BSIntrusiveRefCounted
		{
		public:
			enum class LinkValidState : std::uint32_t
			{
				kNotLinked,
				kCurrentlyLinking,
				kLinkedInvalid,
				kLinkedValid
			};

			struct UnlinkedNativeFunction
			{
			public:
				// members
				UnlinkedNativeFunction*    next;  // 00
				BSTSmartPointer<IFunction> func;  // 08
			};
			static_assert(sizeof(UnlinkedNativeFunction) == 0x10);

			struct UserFlagInfo
			{
			public:
				enum : std::uintptr_t
				{
					kSetOnObject = 1 << 0
				};

				[[nodiscard]] BSFixedString GetUserFlag() const;

				// members
				std::uintptr_t data;  // 0
			};
			static_assert(sizeof(UserFlagInfo) == 0x8);

			struct VariableInfo
			{
			public:
				// members
				BSFixedString name;  // 00
				TypeInfo      type;  // 08
			};
			static_assert(sizeof(VariableInfo) == 0x10);

			struct InitialValueInfo
			{
			public:
				// members
				std::uint32_t variableIndex;  // 00
				std::uint32_t pad04;          // 04
				Variable      initialValue;   // 08
			};
			static_assert(sizeof(InitialValueInfo) == 0x18);

			struct PropertyInfo
			{
			public:
				// members
				BSFixedString    name;  // 00
				PropertyTypeInfo info;  // 08
			};
			static_assert(sizeof(PropertyInfo) == 0x48);

			struct GlobalFuncInfo
			{
			public:
				// members
				BSTSmartPointer<IFunction> func;  // 00
			};
			static_assert(sizeof(GlobalFuncInfo) == 0x8);

			struct MemberFuncInfo
			{
			public:
				// members
				BSTSmartPointer<IFunction> func;  // 00
			};
			static_assert(sizeof(MemberFuncInfo) == 0x8);

			struct NamedStateInfo
			{
			public:
				enum : std::uint32_t
				{
					kFuncCountMask = 0x1FF,
					kFuncOffsetShift = 9
				};

				struct Func
				{
				public:
					// members
					BSTSmartPointer<IFunction> func;  // 00
				};
				static_assert(sizeof(Func) == 0x8);

				[[nodiscard]] constexpr std::uint32_t GetNumFuncs() const noexcept { return memberFunctionCount; }
				Func*                                 GetFuncIter();
				[[nodiscard]] const Func*                           GetFuncIter() const;

				// members
				BSFixedString name;                     // 00
				std::uint32_t memberFunctionCount: 9;   // 08 - 0
				std::uint32_t memberFunctionOffset: 9;  // 09 - 1
				std::uint32_t pad0C;                    // 0C
			};
			static_assert(sizeof(NamedStateInfo) == 0x10);

			~ObjectTypeInfo();

			const char*           GetName() const;
			ObjectTypeInfo*       GetParent();
			const ObjectTypeInfo* GetParent() const;
			TypeInfo::RawType     GetRawType() const;

			[[nodiscard]] constexpr bool IsLinked() const noexcept
			{
				switch (linkedValid) {
				case LinkValidState::kLinkedInvalid:
				case LinkValidState::kLinkedValid:
					return true;
				default:
					return false;
				}
			}

			UnlinkedNativeFunction*       GetUnlinkedFunctionIter();
			const UnlinkedNativeFunction* GetUnlinkedFunctionIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumUserFlags() const noexcept { return userFlagCount; }
			UserFlagInfo*                         GetUserFlagIter();
			const UserFlagInfo*                   GetUserFlagIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumVariables() const noexcept { return variableCount; }
			std::uint32_t                         GetTotalNumVariables() const;
			VariableInfo*                         GetVariableIter();
			const VariableInfo*                   GetVariableIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumInitalValues() const noexcept { return initialValueCount; }
			InitialValueInfo*                     GetInitialValueIter();
			const InitialValueInfo*               GetInitialValueIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumProperties() const noexcept { return propertyCount; }
			PropertyInfo*                         GetPropertyIter();
			const PropertyInfo*                   GetPropertyIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumGlobalFuncs() const noexcept { return staticFunctionCount; }
			GlobalFuncInfo*                       GetGlobalFuncIter();
			const GlobalFuncInfo*                 GetGlobalFuncIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumMemberFuncs() const noexcept { return emptyStateMemberFunctionCount; }
			MemberFuncInfo*                       GetMemberFuncIter();
			const MemberFuncInfo*                 GetMemberFuncIter() const;

			[[nodiscard]] constexpr std::uint32_t GetNumNamedStates() const noexcept { return namedStateCount; }
			NamedStateInfo*                       GetNamedStateIter();
			const NamedStateInfo*                 GetNamedStateIter() const;

			std::uint32_t GetPropertyIndex(const BSFixedString& a_name) const;

			// members
			BSFixedString                   name;                               // 08
			BSTSmartPointer<ObjectTypeInfo> parentTypeInfo;                     // 10
			BSFixedString                   docString;                          // 18
			LinkValidState                  linkedValid: 2;                     // 20 - 00 - 0 or 1 -> data == UnlinkedNativeFunction*, 2 or 3 -> data == normal progression
			std::uint32_t                   userFlagCount: 6;                   // 20 - 02
			std::uint32_t                   variableCount: 10;                  // 20 - 08
			std::uint32_t                   variableUserFlagCount: 6;           // 20 - 18
			std::uint32_t                   pad20_24: 8;                        // 20 - 24
			std::uint32_t                   initialValueCount: 10;              // 24 - 0
			std::uint32_t                   propertyCount: 10;                  // 24 - 10
			std::uint32_t                   staticFunctionCount: 9;             // 24 - 20
			std::uint32_t                   pad24_29: 3;                        // 24 - 29
			std::uint32_t                   emptyStateMemberFunctionCount: 11;  // 28 - 0
			std::uint32_t                   namedStateCount: 7;                 // 28 - 11
			std::uint32_t                   pad28_18: 14;                       // 28 - 18
			void*                           data;                               // 30

		private:
			void ReleaseData();
		};
		static_assert(sizeof(ObjectTypeInfo) == 0x38);
	}
}
