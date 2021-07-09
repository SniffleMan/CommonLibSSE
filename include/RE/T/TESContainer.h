#pragma once

#include "RE/B/BaseFormComponent.h"
#include "RE/C/ContainerItemExtra.h"

namespace RE
{
	class TESBoundObject;

	struct ContainerObject
	{
	public:
		// members
		std::int32_t        count;      // 00 - CNTO~
		std::uint32_t       pad04;      // 04
		TESBoundObject*     obj;        // 08 - ~CNTO
		ContainerItemExtra* itemExtra;  // 10 - COED
	};
	static_assert(sizeof(ContainerObject) == 0x18);

	class TESContainer : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESContainer;

		~TESContainer() override;  // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;                // 01 - { return; }
		void ClearDataComponent() override;                     // 02
		void CopyComponent(BaseFormComponent* a_rhs) override;  // 03

		inline void ForEachContainerObject(std::function<bool(ContainerObject&)> a_fn) const
		{
			for (std::uint32_t i = 0; i < numContainerObjects; ++i) {
				auto entry = containerObjects[i];
				if (entry) {
					if (!a_fn(*entry)) {
						break;
					}
				}
			}
		}

		[[nodiscard]] std::optional<ContainerObject*> GetContainerObjectAt(std::uint32_t a_idx) const;
		std::int32_t                    CountObjectsInContainer(TESBoundObject* a_object) const;

		// members
		ContainerObject** containerObjects;     // 08
		std::uint32_t     numContainerObjects;  // 10
		std::uint32_t     pad14;                // 14
	};
	static_assert(sizeof(TESContainer) == 0x18);
}
