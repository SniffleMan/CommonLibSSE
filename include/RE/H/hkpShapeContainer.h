#pragma once

namespace RE
{
	class hkpShapeContainer
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpShapeContainer;

		enum class ReferencePolicy
		{
			kIgnore,
			kIncrement
		};

		virtual ~hkpShapeContainer();  // 00

		// add
		[[nodiscard]] virtual std::int32_t    GetNumChildShapes() const;                                             // 01
		[[nodiscard]] virtual hkpShapeKey     GetFirstKey() const = 0;                                               // 02
		[[nodiscard]] virtual hkpShapeKey     GetNextKey(hkpShapeKey a_oldKey) const = 0;                            // 03
		[[nodiscard]] virtual std::uint32_t   GetCollisionFilterInfo(hkpShapeKey a_key) const;                       // 04 - { return 0; }
		virtual const hkpShape* GetChildShape(hkpShapeKey a_key, hkpShapeBuffer& a_buffer) const = 0;  // 05
		[[nodiscard]] virtual bool            IsWeldingEnabled() const;                                              // 06 - { return true; }
	};
	static_assert(sizeof(hkpShapeContainer) == 0x8);
}
