#pragma once

#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GRefCountBase.h"

namespace RE
{
	class GFxFunctionHandler;
	class GFxMovieDef;
	class GFxValue;

	class GFxMovie : public GRefCountBase<GFxMovie, GFxStatMovieViews::kGFxStatMV_Other_Mem>
	{
	public:
		// PlayState describes the play state of the movie clip. When set on a Movie, affects only the root movie clip.
		enum class PlayState
		{
			kPlaying,  // The movie is playing
			kStopped   // The movie is stopped at its current clip. Child clips may still be playing
		};

		// SetVarType describes the delayed assignment queuing behavior of SetVariable and SetVariableDouble functions; the use of this flag allows developers to control the type of effect the variable assignment will have on target objects that have not yet been created at the time of SetVariable call
		enum class SetVarType
		{
			kNormal,    // Sets variable only if target movie clip containing the variable is found
			kSticky,    // Sets variable if target clip is found, otherwise queues a set until the clip is created at path. When the target clip is created, value will be lost
			kPermanent  // Sets variable applied to this and all future clips at given path
		};

		// SetArrayType sets the type of array.
		enum class SetArrayType
		{
			kInt,      // Array of 'Int'
			kDouble,   // Array of 'Double' in memory
			kFloat,    // Array of 'Float' in memory
			kString,   // Array of 'const char*'. (Deprecated; use kValue)
			kStringW,  // Array of 'const wchar_t*'. (Deprecated; use kValue)
			kValue     // Array of Value
		};

		// add
		[[nodiscard]] virtual GFxMovieDef*  GetMovieDef() const;                                                                                                                                                                 // 01 - pure - Obtains the movie definition that created this instance.
		[[nodiscard]] virtual std::uint32_t GetCurrentFrame() const;                                                                                                                                                             // 02 - pure - Obtains the currently active frame of the movie, starting with 0.
		[[nodiscard]] virtual bool          HasLooped() const;                                                                                                                                                                   // 03 - pure - Determines whether the movie clip has looped past its last frame.
		virtual void          GotoFrame(std::uint32_t a_frameNumber);                                                                                                                                              // 04 - pure - Moves a playhead to a specified frame.
		virtual bool          GotoLabeledFrame(const char* a_label, std::int32_t a_offset = 0);                                                                                                                    // 05 - pure - Moves a playhead to a specified frame identified by a label.
		virtual void          SetPlayState(PlayState a_state);                                                                                                                                                     // 06 - pure - Changes playback state of the movie, allowing animation to be paused and resumed.
		[[nodiscard]] virtual PlayState     GetPlayState() const;                                                                                                                                                                // 07 - pure - Obtains the play state of the movie clip, currently either Playing or Stopped.
		virtual void          SetVisible(bool a_visible);                                                                                                                                                          // 08 - pure - Sets the visibility state of a movie clip.
		[[nodiscard]] virtual bool          GetVisible() const;                                                                                                                                                                  // 09 - pure - Obtains the visibility state of a movie clip.
		virtual bool          IsAvailable(const char* a_pathToVar) const;                                                                                                                                          // 0A - pure - Checks for availability of a field, method, or nested clip.
		virtual void          CreateString(GFxValue* a_value, const char* a_string);                                                                                                                               // 0B - pure - Creates strings that are managed by ActionScript runtime.
		virtual void          CreateStringW(GFxValue* a_value, const wchar_t* a_string);                                                                                                                           // 0C - pure - Creates wide character strings that are managed by ActionScript runtime.
		virtual void          CreateObject(GFxValue* a_value, const char* a_className = 0, const GFxValue* a_args = 0, std::uint32_t a_numArgs = 0);                                                               // 0D - pure - Creates an instance of an ActionScript Object.
		virtual void          CreateArray(GFxValue* a_value);                                                                                                                                                      // 0E - pure - Creates an instance of an ActionScript Array object.
		virtual void          CreateFunction(GFxValue* a_value, GFxFunctionHandler* a_fc, void* a_userData = 0);                                                                                                   // 0F - pure - Creates a function object that wraps a C++ function.
		virtual bool          SetVariable(const char* a_pathToVar, const GFxValue& a_value, SetVarType a_setType = SetVarType::kSticky);                                                                           // 10 - pure - Sets a variable identified by a path to a new value, specified in UTF-8 encoding.
		virtual bool          GetVariable(GFxValue* a_val, const char* a_pathToVar) const;                                                                                                                         // 11 - pure - Obtains the value of an ActionScript variable based on its path.
		virtual bool          SetVariableArray(SetArrayType a_type, const char* a_pathToVar, std::uint32_t a_index, const void* a_data, std::uint32_t a_count, SetVarType a_setType = SetVarType::kSticky) const;  // 12 - pure - Sets array elements in specified range to data items of specified type.
		virtual bool          SetVariableArraySize(const char* a_pathToVar, std::uint32_t a_count, SetVarType a_setType = SetVarType::kSticky);                                                                    // 13 - pure - Sets the size of the array.
		virtual std::uint32_t GetVariableArraySize(const char* a_pathToVar);                                                                                                                                       // 14 - pure - Returns the size of array buffer necessary for GetVariableArray.
		virtual bool          GetVariableArray(SetArrayType a_type, const char* a_pathToVar, std::uint32_t a_index, void* a_data, std::uint32_t a_count);                                                          // 15 - pure - Populates a buffer with results from an ActionScript array.
		virtual bool          InvokeFmt(const char* a_methodName, GFxValue* a_result, const char* a_argFmt, ...);                                                                                                  // 16 - pure - Calls an ActionScript method on the movie clip.
		virtual bool          Invoke(const char* a_methodName, GFxValue* a_result, const GFxValue* a_args, std::uint32_t a_numArgs);                                                                               // 17 - pure - Calls an ActionScript method on the movie clip.
		virtual bool          InvokeArgs(const char* a_methodName, GFxValue* a_result, const char* a_argFmt, std::va_list a_args);                                                                                 // 18 - pure - Invokes an ActionScript method on the movie clip using a format string followed by a variable argument list.

		static float GetRenderPixelScale();

		[[nodiscard]] std::uint32_t GetFrameCount() const;
		[[nodiscard]] float         GetFrameRate() const;
		bool          SetVariable(const char* a_pathToVar, const char* a_value, SetVarType a_setType = SetVarType::kSticky);
		bool          SetVariable(const char* a_pathToVar, const wchar_t* a_value, SetVarType a_setType = SetVarType::kSticky);
		bool          SetVariableDouble(const char* a_pathToVar, double a_value, SetVarType a_setType = SetVarType::kSticky);
		double        GetVariableDouble(const char* a_pathToVar) const;
		bool          SetVariableArray(const char* a_pathToVar, std::uint32_t a_index, const GFxValue* a_data, std::uint32_t a_count, SetVarType a_setType = SetVarType::kSticky);
		bool          GetVariableArray(const char* a_pathToVar, std::uint32_t a_index, GFxValue* a_data, std::uint32_t a_count);
	};
	static_assert(sizeof(GFxMovie) == 0x10);
}
