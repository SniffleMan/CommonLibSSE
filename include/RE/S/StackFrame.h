#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/V/Variable.h"

namespace RE
{
	namespace BSScript
	{
		class IFunction;
		class ObjectTypeInfo;
		class Stack;

		class StackFrame
		{
		public:
			[[nodiscard]] std::uint32_t GetPageForFrame() const;
			[[nodiscard]] Variable&     GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const;

			// members
			Stack*                          parent;              // 00
			StackFrame*                     previousFrame;       // 08
			BSTSmartPointer<IFunction>      owningFunction;      // 10
			BSTSmartPointer<ObjectTypeInfo> owningObjectType;    // 18
			std::uint32_t                   instructionPointer;  // 20
			std::uint32_t                   pad24;               // 24
			Variable                        self;                // 28
			std::uint32_t                   size;                // 38
			bool                            instructionsValid;   // 3C
			std::uint8_t                    pad3D;               // 3D
			std::uint16_t                   pad3E;               // 3E

			//Variable args[4];	40 - minimum space for 4 args is allocated
		};
		static_assert(sizeof(StackFrame) == 0x40);  // frames can be larger
	}
}
