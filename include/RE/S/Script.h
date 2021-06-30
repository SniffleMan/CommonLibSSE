#pragma once

#include "RE/C/CommandTable.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"

namespace RE
{
	enum class COMPILER_NAME
	{
		kDefaultCompiler,
		kSystemWindowCompiler,
		kDialogueCompiler
	};

	class ScriptCompiler
	{
	public:
	};
	static_assert(sizeof(ScriptCompiler) == 0x1);

	class Script : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_Script;
		inline static constexpr auto FORMTYPE = FormType::Script;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
			};
		};

		~Script() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		void        ClearCommand();
		void        CompileAndRun(TESObjectREFR* a_targetRef, COMPILER_NAME a_name = COMPILER_NAME::kSystemWindowCompiler);
		void        CompileAndRun(ScriptCompiler* a_compiler, TESObjectREFR* a_targetRef, COMPILER_NAME a_name = COMPILER_NAME::kSystemWindowCompiler);
		[[nodiscard]] std::string GetCommand() const;
		void        SetCommand(std::string_view a_command);

		// members
		SCRIPT_HEADER                           header;                       // 20
		std::uint32_t                           pad34;                        // 34
		char*                                   text;                         // 38
		SCRIPT_FUNCTION::ScriptData*            data;                         // 40
		float                                   profilerTimer;                // 48
		float                                   questScriptDelay;             // 4C
		float                                   questScriptGetSecondsBuffer;  // 50
		std::uint32_t                           pad54;                        // 54
		TESQuest*                               parentQuest;                  // 58
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> refObjects;                   // 60
		BSSimpleList<ScriptVariable*>           variables;                    // 70

	private:
		void CompileAndRun_Impl(ScriptCompiler* a_compiler, COMPILER_NAME a_type, TESObjectREFR* a_targetRef);
	};
	static_assert(sizeof(Script) == 0x80);
}
