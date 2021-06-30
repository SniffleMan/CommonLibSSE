#pragma once

namespace RE
{
	template <class T>
	struct IBSTCreator
	{
	public:
		virtual ~IBSTCreator();  // 00

	protected:
		// add
		[[nodiscard]] virtual T* CreateImpl() const = 0;  // 01

	public:
		virtual void Destroy(const T* a_val) const = 0;  // 02

		[[nodiscard]] inline T* Create() const
		{
			return CreateImpl();
		}
	};
	static_assert(sizeof(IBSTCreator<void*>) == 0x8);
}
