#pragma once

#include "RE/F/FormTypes.h"

namespace RE
{
	template <class T, FormType>
	class ConcreteFormFactory;

	enum class OBJECT_TYPE
	{
	};

	enum class OBJECT_CATEGORY_TYPE
	{
	};

	class IFormFactory
	{
	public:
		inline static constexpr auto RTTI = RTTI_IFormFactory;

		virtual ~IFormFactory();  // 00

	protected:
		// add
		virtual TESForm* CreateImpl() = 0;  // 01

	public:
		[[nodiscard]] virtual const char*          GetFormName() const = 0;    // 02
		[[nodiscard]] virtual FormType             GetFormType() const = 0;    // 03
		[[nodiscard]] virtual const char*          GetObjectName() const;      // 04 - { return 0; }
		[[nodiscard]] virtual OBJECT_TYPE          GetObjectType() const;      // 05 - { return 106; }
		[[nodiscard]] virtual OBJECT_CATEGORY_TYPE GetObjectCategory() const;  // 06 - { return 9; }

		static std::pair<IFormFactory**, bool> GetFormFactories();
		static IFormFactory*                   GetFormFactoryByType(FormType a_formType);

		template <class T>
		static ConcreteFormFactory<T, T::FORMTYPE>* GetConcreteFormFactoryByType();

		TESForm* Create();
	};
	static_assert(sizeof(IFormFactory) == 0x8);
}
