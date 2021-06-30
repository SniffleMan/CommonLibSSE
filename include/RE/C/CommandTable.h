#pragma once

#include "RE/B/BSString.h"
#include "RE/B/BSTList.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class ScriptLocals;
	struct ACTION_OBJECT;
	struct ConditionCheckParams;
	struct ScriptCompileData;
	struct ScriptLineBuffer;
	struct ScriptVariable;
	struct SCRIPT_EFFECT_DATA;
	struct SCRIPT_HEADER;
	struct SCRIPT_LINE;
	struct SCRIPT_LOCAL;
	struct SCRIPT_PARAMETER;
	struct SCRIPT_REFERENCED_OBJECT;

	enum class SCRIPT_PARAM_TYPE
	{
		kChar = 0x0,
		kInt = 0x1,
		kFloat = 0x2,
		kInventoryObject = 0x3,
		kObjectRef = 0x4,
		kActorValue = 0x5,
		kActor = 0x6,
		kSpellItem = 0x7,
		kAxis = 0x8,
		kCell = 0x9,
		kAnimGroup = 0x0A,
		kMagicItem = 0x0B,
		kSound = 0x0C,
		kTopic = 0x0D,
		kQuest = 0x0E,
		kRace = 0x0F,
		kClass = 0x10,
		kFaction = 0x11,
		kSex = 0x12,
		kGlobal = 0x13,
		kFurnitureOrFormList = 0x14,
		kObject = 0x15,
		kScriptVar = 0x16,
		kStage = 0x17,
		kMapMarker = 0x18,
		kActorBase = 0x19,
		kCoontainerRef = 0x1A,
		kWorldOrList = 0x1B,
		kCrimeType = 0x1C,
		kPackage = 0x1D,
		kCombatStyle = 0x1E,
		kMagicEffect = 0x1F,
		kFormType = 0x20,
		kWeather = 0x21,
		kNPC = 0x22,
		kOwner = 0x23,
		kShaderEffect = 0x24,
		kFormList = 0x25,
		kMenuIcon = 0x26,
		kPerk = 0x27,
		kNote = 0x28,
		kMiscStat = 0x29,
		kImagespaceMod = 0x2A,
		kImagespace = 0x2B,
		kVATSValue = 0x2C,
		kVATSValueData = 0x2D,
		kEventFunction = 0x2E,
		kEventFunctionMember = 0x2F,
		kEventFunctionData = 0x30,
		kVoiceType = 0x31,
		kEncounterZone = 0x32,
		kIdleForm = 0x33,
		kMessage = 0x34,
		kInvObjectOrFormList = 0x35,
		kAlignment = 0x36,
		kEquipType = 0x37,
		kObjectOrFormList = 0x38,
		kMusic = 0x39,
		kCritStage = 0x3A,
		kKeyword = 0x3B,
		kRefType = 0x3C,
		kLocation = 0x3D,
		kForm = 0x3E,
		kAlias = 0x3F,
		kShout = 0x40,
		kWordOfPower = 0x41,
		kRelationshipRank = 0x42,
		kBGSScene = 0x43,
		kCastingSource = 0x44,
		kAssociationType = 0x45,
		kWardState = 0x46,
		kPackageDataCanBeNull = 0x47,
		kPackageDataNumeric = 0x48,
		kFurnitureAnimType = 0x49,
		kFurnitureEntryType = 0x4A,
		kVMScriptVar = 0x4C,
		kReferenceEffect = 0x4D,
		kPackageData = 0x4E,
		kSoundCategory = 0x50,
		kKnowableForm = 0x51,
		kRegion = 0x52
	};

	// basically the unique id for the function, there's ~5000 of these
	enum class SCRIPT_OUTPUT
	{
	};

	enum class SCRIPT_ERROR
	{
	};

	struct SCRIPT_HEADER
	{
	public:
		// members
		std::uint32_t variableCount;        // 00
		std::uint32_t refObjectCount;       // 04
		std::uint32_t dataSize;             // 08
		std::uint32_t lastID;               // 0C
		bool          isQuestScript;        // 10
		bool          isMagicEffectScript;  // 11
		bool          isCompiled;           // 12
		std::uint8_t  pad13;                // 13
	};
	static_assert(sizeof(SCRIPT_HEADER) == 0x14);

	struct SCRIPT_PARAMETER
	{
	public:
		// members
		const char*                                        paramName;  // 00
		stl::enumeration<SCRIPT_PARAM_TYPE, std::uint32_t> paramType;  // 08
		bool                                               optional;   // 0C
		std::uint8_t                                       pad0D;      // 0D
		std::uint16_t                                      pad0E;      // 0E
	};
	static_assert(sizeof(SCRIPT_PARAMETER) == 0x10);

	struct SCRIPT_REFERENCED_OBJECT
	{
	public:
		// members
		BSString      editorID;    // 00
		TESForm*      form;        // 10
		std::uint32_t variableID;  // 18
		std::uint32_t pad1C;       // 1C
	};
	static_assert(sizeof(SCRIPT_REFERENCED_OBJECT) == 0x20);

	struct ACTION_OBJECT
	{
	public:
		// members
		TESForm*      form;   // 00
		std::uint32_t flags;  // 08
		std::uint32_t pad0C;  // 0C
	};
	static_assert(sizeof(ACTION_OBJECT) == 0x10);

	struct SCRIPT_LOCAL
	{
	public:
		// members
		std::uint32_t id;         // 0
		float         value;      // 4
		bool          isInteger;  // 8
		std::uint8_t  pad9;       // 9
		std::uint16_t padA;       // A
	};
	static_assert(sizeof(SCRIPT_LOCAL) == 0xC);

	struct SCRIPT_EFFECT_DATA
	{
	public:
		// members
		bool          scriptEffectStart;   // 00
		bool          scriptEffectFinish;  // 01
		std::uint16_t pad02;               // 02
		float         secondsElapsed;      // 04
	};
	static_assert(sizeof(SCRIPT_EFFECT_DATA) == 0x8);

	class ScriptLocals
	{
	public:
		// members
		Script*                       masterScript;      // 00
		char                          flags;             // 08
		std::uint8_t                  pad09;             // 09
		std::uint16_t                 pad0A;             // 0A
		std::uint32_t                 pad0C;             // 0C
		BSSimpleList<ACTION_OBJECT*>* actionList;        // 10
		BSSimpleList<SCRIPT_LOCAL*>*  localList;         // 18
		SCRIPT_EFFECT_DATA*           scriptEffectData;  // 20
	};
	static_assert(sizeof(ScriptLocals) == 0x28);

	struct ScriptVariable
	{
	public:
		// members
		SCRIPT_LOCAL  data;   // 00
		std::uint32_t pad0C;  // 0C
		BSString      name;   // 10
	};
	static_assert(sizeof(ScriptVariable) == 0x20);

	struct SCRIPT_LINE
	{
	public:
		// members
		std::uint32_t                                  lineNumber;      // 000
		char                                           line[512];       // 004
		std::uint32_t                                  size;            // 204
		std::uint32_t                                  offset;          // 208
		char                                           output[512];     // 20C
		std::uint32_t                                  outputSize;      // 40C
		stl::enumeration<SCRIPT_OUTPUT, std::uint32_t> expression;      // 410
		std::uint32_t                                  refObjectIndex;  // 414
		stl::enumeration<SCRIPT_ERROR, std::uint32_t>  scriptError;     // 418
	};
	static_assert(sizeof(SCRIPT_LINE) == 0x41C);

	struct SCRIPT_FUNCTION
	{
		struct Commands
		{
			enum : std::uint32_t
			{
				kConsoleCommandsEnd = 0x01B4,
				kConsoleOpBase = 0x0100,

				kScriptCommandsEnd = 0x02E0,
				kScriptOpBase = 0x1000
			};
		};

		struct StringChunk;
		struct IntegerChunk;

		struct Chunk
		{
		public:
			StringChunk*  AsString();
			IntegerChunk* AsInteger();
		};

		struct StringChunk : public Chunk
		{
		public:
			[[nodiscard]] std::string GetString() const;
			Chunk*      GetNext();

			// members
			std::uint16_t length;  // 00
			char          str[0];  // 02
		};
		static_assert(sizeof(StringChunk) == 0x2);

#pragma pack(push, 1)
		struct IntegerChunk : public Chunk
		{
		public:
			[[nodiscard]] int    GetInteger() const;
			Chunk* GetNext();

			// members
			char         magic;  // 00
			std::int32_t value;  // 01
		};
		static_assert(offsetof(IntegerChunk, value) == 0x1);
		static_assert(sizeof(IntegerChunk) == 0x5);
#pragma pack(pop)

		struct ScriptData
		{
		public:
			Chunk*        GetChunk();
			StringChunk*  GetStringChunk();
			IntegerChunk* GetIntegerChunk();

			// members
			std::uint16_t opcode;     // 00
			std::uint16_t chunkSize;  // 02
			std::uint16_t numParams;  // 04
		};
		static_assert(sizeof(ScriptData) == 0x6);

		using Execute_t = bool(const SCRIPT_PARAMETER* a_paramInfo, ScriptData* a_scriptData, TESObjectREFR* a_thisObj, TESObjectREFR* a_containingObj, Script* a_scriptObj, ScriptLocals* a_locals, double& a_result, std::uint32_t& a_opcodeOffsetPtr);
		using Compile_t = bool(std::uint16_t a_numParams, const SCRIPT_PARAMETER* a_paramInfo, SCRIPT_LINE* a_lineBuf, ScriptCompileData* a_scriptBuf);
		using Condition_t = bool(TESObjectREFR* a_thisObj, void* a_param1, void* a_param2, double& a_result);

		static SCRIPT_FUNCTION* GetFirstScriptCommand();
		static SCRIPT_FUNCTION* LocateScriptCommand(const char* a_longName);

		static SCRIPT_FUNCTION* GetFirstConsoleCommand();
		static SCRIPT_FUNCTION* LocateConsoleCommand(const char* a_longName);

		template <std::uint16_t SIZE>
		inline void SetParameters(SCRIPT_PARAMETER (&a_params)[SIZE])
		{
			numParams = SIZE;
			params = a_params;
		}

		void SetParameters();

		// members
		const char*       functionName;         // 00
		const char*       shortName;            // 08
		SCRIPT_OUTPUT     output;               // 10
		std::uint32_t     pad14;                // 14
		const char*       helpString;           // 18
		bool              referenceFunction;    // 20
		std::uint8_t      pad21;                // 21
		std::uint16_t     numParams;            // 22
		std::uint32_t     pad24;                // 24
		SCRIPT_PARAMETER* params;               // 28
		Execute_t*        executeFunction;      // 30
		Compile_t*        compileFunction;      // 38
		Condition_t*      conditionFunction;    // 40
		bool              editorFilter;         // 48
		bool              invalidatesCellList;  // 49
		std::uint16_t     pad4A;                // 4A
		std::uint32_t     pad4C;                // 4C
	};
	static_assert(sizeof(SCRIPT_FUNCTION) == 0x50);
}
