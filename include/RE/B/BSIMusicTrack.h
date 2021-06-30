#pragma once

namespace RE
{
	class BSIMusicTrack
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSIMusicTrack;

		enum class TrackType : std::uint32_t
		{
			kSilentTrack = 0xA1A9C4D5,
			kSingleTrack = 0x6ED7E048,
			kPalette = 0x23F678C3
		};

		enum class MUSIC_STATUS
		{
			kInactive = 0,
			kPlaying = 1,
			kPaused = 2,
			kFinishing = 3,
			kFinished = 4
		};

		virtual ~BSIMusicTrack();  // 00

		// add
		virtual void         DoUpdate() = 0;                                    // 01
		virtual void         DoPlay() = 0;                                      // 02
		virtual void         DoPause() = 0;                                     // 03
		virtual void         DoFinish(bool a_immediate, float a_fadeTime) = 0;  // 04
		[[nodiscard]] virtual float        GetDurationImpl() const = 0;                       // 05
		[[nodiscard]] virtual TrackType    GetType() const = 0;                               // 06 - CRC32 hash of class name
		[[nodiscard]] virtual bool         TestCanPlay() const;                               // 07 - { return true; }
		[[nodiscard]] virtual MUSIC_STATUS GetMusicStatus() const;                            // 08 - { return trackStatus; }
		virtual void         DoSetDuckingAttenuation(std::uint16_t a_ducking);  // 09 - { return; }
		virtual void         DoClearDucking();                                  // 0A - { return; }

		// members
		stl::enumeration<MUSIC_STATUS, std::uint32_t> trackStatus;  // 08
		std::uint32_t                                 pad0C;        // 0C
	};
	static_assert(sizeof(BSIMusicTrack) == 0x10);
}
