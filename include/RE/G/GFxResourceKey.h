#pragma once

namespace RE
{
	class GFxResourceKey
	{
	public:
		using KeyHandle = void*;

		enum class KeyType
		{
			kNone,
			kUnique,
			kFile,
			kGradient,
			kSubImage
		};

		class KeyInterface
		{
		public:
			virtual ~KeyInterface();  // 00

			// add
			virtual void        AddRef(KeyHandle a_data) = 0;                                    // 01
			virtual void        Release(KeyHandle a_data) = 0;                                   // 02
			virtual KeyType     GetKeyType(KeyHandle a_data) const = 0;                          // 03
			virtual UPInt       GetHashCode(KeyHandle a_data) const = 0;                         // 04
			virtual bool        KeyEquals(KeyHandle a_data, const GFxResourceKey& a_other) = 0;  // 05
			virtual const char* GetFileURL(KeyHandle a_data) const;                              // 06
		};

		class HashOp
		{
		public:
			UPInt operator()(const GFxResourceKey& a_key)
			{
				return a_key._keyInterface ? a_key._keyInterface->GetHashCode(a_key._keyData) : 0;
			}
		};

		GFxResourceKey();
		GFxResourceKey(KeyInterface* a_keyIntfc, KeyHandle a_keyHandle);
		GFxResourceKey(const GFxResourceKey& a_rhs);
		~GFxResourceKey();

		GFxResourceKey& operator=(const GFxResourceKey& a_rhs);
		bool            operator==(const GFxResourceKey& a_other) const;
		[[nodiscard]] KeyType         GetKeyType() const;
		[[nodiscard]] const char*     GetFileURL() const;
		[[nodiscard]] KeyInterface*   GetKeyInterface() const;
		[[nodiscard]] KeyHandle       GetKeyData() const;

	protected:
		// members
		KeyInterface* _keyInterface;  // 00
		KeyHandle     _keyData;       // 08
	};
	static_assert(sizeof(GFxResourceKey) == 0x10);
}
