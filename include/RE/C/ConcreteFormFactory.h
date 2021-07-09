#pragma once

#include "RE/I/IFormFactory.h"
#include "RE/T/TESForm.h"

namespace RE
{
	template <class T, FormType FORM_TYPE>
	class ConcreteFormFactory : public IFormFactory
	{
	public:
		~ConcreteFormFactory() override;  // 00

	protected:
		// override (IFormFactory)
		TESForm* CreateImpl() override;  // 01

	public:
		const char* GetFormName() const override;  // 02 - { return _name; }
		[[nodiscard]] FormType    GetFormType() const override;  // 03 - { return FORM_TYPE; }

		inline T* Create()
		{
			return static_cast<T*>(CreateImpl());
		}

	protected:
		// members
		const char* _name;  // 08
	};
	static_assert(sizeof(ConcreteFormFactory<TESForm, FormType::None>) == 0x10);

	template <class T>
	inline ConcreteFormFactory<T, T::FORMTYPE>* IFormFactory::GetConcreteFormFactoryByType()
	{
		return static_cast<ConcreteFormFactory<T, T::FORMTYPE>*>(GetFormFactoryByType(T::FORMTYPE));
	}
}
