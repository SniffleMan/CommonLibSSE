#pragma once

namespace RE
{
	namespace BSScript
	{
		class ObjectTypeInfo;

		class TypeInfo
		{
		public:
			enum class RawType : std::size_t
			{
				kNone = 0,
				kObject = 1,
				kString = 2,
				kInt = 3,
				kFloat = 4,
				kBool = 5,

				kNoneArray = 10,
				kObjectArray = 11,
				kStringArray = 12,
				kIntArray = 13,
				kFloatArray = 14,
				kBoolArray = 15,

				kArraysEnd

				// the type id for classes IS their class ptr
				// an object is an array if its first bit is set
			};

			TypeInfo();
			explicit TypeInfo(RawType a_type);
			TypeInfo(const TypeInfo& a_rhs);
			TypeInfo(TypeInfo&& a_rhs);

			TypeInfo& operator=(const TypeInfo& a_rhs);
			TypeInfo& operator=(TypeInfo&& a_rhs);
			TypeInfo& operator=(RawType a_rhs);

			friend bool operator==(const TypeInfo& a_lhs, const TypeInfo& a_rhs);
			friend bool operator!=(const TypeInfo& a_lhs, const TypeInfo& a_rhs);
			friend bool operator<(const TypeInfo& a_lhs, const TypeInfo& a_rhs);
			friend bool operator<=(const TypeInfo& a_lhs, const TypeInfo& a_rhs);
			friend bool operator>(const TypeInfo& a_lhs, const TypeInfo& a_rhs);
			friend bool operator>=(const TypeInfo& a_lhs, const TypeInfo& a_rhs);

			[[nodiscard]] RawType         GetRawType() const;
			[[nodiscard]] ObjectTypeInfo* GetTypeInfo() const;
			[[nodiscard]] RawType         GetUnmangledRawType() const;
			[[nodiscard]] bool            IsArray() const;
			[[nodiscard]] bool            IsBool() const;
			[[nodiscard]] bool            IsFloat() const;
			[[nodiscard]] bool            IsInt() const;
			[[nodiscard]] bool            IsLiteralArray() const;
			[[nodiscard]] bool            IsNoneArray() const;
			[[nodiscard]] bool            IsNoneObject() const;
			[[nodiscard]] bool            IsObject() const;
			[[nodiscard]] bool            IsObjectArray() const;
			[[nodiscard]] bool            IsString() const;
			void            SetType(RawType a_type);

		protected:
			// members
			stl::enumeration<RawType, std::size_t> _rawType;  // 00
		};
		static_assert(sizeof(TypeInfo) == 0x8);
	}
}
