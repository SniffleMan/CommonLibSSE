#pragma once

#include "RE/G/GRefCountBase.h"
#include "RE/G/GStats.h"

namespace RE
{
	class GFxState : public GRefCountBase<GFxState, GStatGroups::kGStat_Default_Mem>
	{
	public:
		inline static constexpr auto RTTI = RTTI_GFxState;

		// An enumeration type defining the type of a State object, such as kRenderConfig, kFSCommandHandler, State_Log, etc. Only one State object of each type can be set on the loader or a movie.
		enum class StateType
		{
			kNone,  // An undefined state value

			// Instance related states
			kRenderConfig,
			kRenderStats,
			kTranslator,  // An international language translator of dynamic text fields
			kLog,         // A log object which generates log messages and is used for debugging
			kImageLoader,
			kActionControl,      // An object that controls the verbosity of output generated during ActionScript execution
			kUserEventHandler,   // A user-installable interface to handle events fired from the player
			kFSCommandHandler,   // A handler gets called when Action Script executes the fscommand() statement
			kExternalInterface,  // A callback method for ActionScript to invoke

			// Loading related states
			kFileOpener,       // A callback interface that is used for opening files
			kURLBuilder,       // The object responsible for building a filename path used for loading objects
			kImageCreator,     // An interface used to create Image objects applied during rendering
			kParseControl,     // An object that is used to determine which SWF/GFx file parsing messages will be generated
			kProgressHandler,  // A user-defined handler to receive SWF/GFx load progress
			kImportVisitor,    // An object which is called during loading (import binding state) of a movie after each import is resolved
			kMeshCacheManager,
			kFontPackParams,  // FontPackParams state, which enables static text cache and provides texture size and pack configuration settings
			kFontCacheManager,
			kFontLib,       // FontLib state, which maintains a list of movies that can be used as font sources
			kFontProvider,  // FontProvider derived state, such as FontProviderWin32 that provides support for system fonts
			kFontMap,       // FontMap state, which maintains a set of font name mappings for internationalization
			kGradientParams,
			kTaskManager,  // An object that executes tasks added to the task queue
			kClipboard,    // An object used for storing plain and rich texts in a text clipboard
			kTextKeyMap,   // TextKeyMap state which contains mappings of keystrokes to text field operation
			kPreprocessParams,
			kIMEManager,  // An object which supports IME implementation on the loader
			kXMLSupport,  // XML::Support state which is responsible for providing XML support
			kJpegSupport,
			kZlibSupport,          // ZlibSupport state that provides ZLib support to the loader
			kFontCompactorParams,  // FontCompactorParams state, which provides configuration options for generating glyphs
			kImagePackerParams,    // ImagePackParamsBase state, which provides the texture configuration options to pack images in textures
			kPNGSupport,
			kAudio,  // Audio state, used to initialize the sound system for playing SWF sound files
			kVideo,  // Video state, used to initialize video playbacks
			kTestStream,
			kSharedObject,  // SharedObjectManagerBase state for handling shared objects
			kLocSupport
		};

		// State constructor, only invoked from derived classes. The constructor takes a StateType as an argument, which defines the state type; this value cannot be changed after object creation
		GFxState(StateType a_st = StateType::kNone);
		~GFxState() override = default;  // 00

		// GetStateType obtains the StateType of this state. The state type of a given object never changes after construction
		[[nodiscard]] StateType GetStateType() const;

	protected:
		StateType     stateType;  // 10
		std::uint32_t pad14;      // 14
	};
	static_assert(sizeof(GFxState) == 0x18);
}
