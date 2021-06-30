#pragma once

#include "RE/G/GFxValue.h"

namespace RE
{
	class FxDelegateHandler;
	class FxResponseArgsBase;
	class GFxMovieView;

	class FxDelegateArgs
	{
	public:
		FxDelegateArgs(GFxValue a_responseID, FxDelegateHandler* a_handler, GFxMovieView* a_movie, const GFxValue* a_vals, std::uint32_t a_numArgs);

		void               Respond(FxResponseArgsBase& a_params) const;
		const GFxValue&    operator[](UPInt a_pos) const;
		[[nodiscard]] FxDelegateHandler* GetHandler() const;
		[[nodiscard]] GFxMovieView*      GetMovie() const;
		[[nodiscard]] std::uint32_t      GetArgCount() const;

	protected:
		// members
		GFxValue           _responseID;  // 00
		FxDelegateHandler* _handler;     // 18
		GFxMovieView*      _movieView;   // 20
		const GFxValue*    _args;        // 28
		std::uint32_t      _numArgs;     // 30
		std::uint32_t      _pad34;       // 34
	};
	static_assert(sizeof(FxDelegateArgs) == 0x38);
}
