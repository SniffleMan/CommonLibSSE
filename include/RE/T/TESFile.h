#pragma once

#include "RE/B/BSString.h"
#include "RE/B/BSTList.h"
#include "RE/F/FORM.h"
#include "RE/F/FormTypes.h"

namespace RE
{
	class BSFile;
	struct TESBitArrayFile;

	class TESFile
	{
	public:
		enum class Error
		{
			kNone = 0,
			kNotFound = 1,
			kNoFile = 2,
			kNoForm = 3,
			kNoChunk = 4,
			kNoID = 5,
			kBadFile = 6,
			kBadID = 7,
			kFormOpen = 8,
			kFileOpen = 9,
			kWriteFailure = 10,
			kInvalidFile = 11,
			kFileInUse = 12,
			kCreateFailure = 13
		};

		enum class RecordFlag
		{
			kNone = 0,
			kMaster = 1 << 0,
			kAltered = 1 << 1,
			kChecked = 1 << 2,
			kActive = 1 << 3,
			kOptimizedFile = 1 << 4,
			kTempIDOwner = 1 << 5,
			kDelocalized = 1 << 7,
			kPrecalcDataOnly = 1 << 8,
			kSmallFile = 1 << 9
		};

		TESFile*                Duplicate(std::uint32_t a_cacheSize = 0x4000);
		std::uint32_t           GetCurrentSubRecordType();
		[[nodiscard]] constexpr std::uint32_t GetCurrentSubRecordSize() const noexcept { return actualChunkSize; }
		[[nodiscard]] constexpr std::uint32_t GetCurrentChunkID() const noexcept { return currentchunkID; }
		FormType                GetFormType();
		[[nodiscard]] constexpr std::uint32_t GetPartialIndex() const noexcept { return !IsLight() ? compileIndex : (0xFE000 | smallFileCompileIndex); };
		[[nodiscard]] constexpr bool          IsLight() const noexcept { return recordFlags.all(RecordFlag::kSmallFile); };
		[[nodiscard]] constexpr bool          IsLocalized() const noexcept { return recordFlags.all(RecordFlag::kDelocalized); }
		void                    ReadData(void* a_buf, std::uint32_t a_size);
		bool                    Seek(std::uint32_t a_offset);
		bool                    SeekNextSubrecord();

		// members
		stl::enumeration<Error, std::uint32_t>      lastError;                        // 000
		std::uint32_t                               pad004;                           // 004
		TESFile*                                    threadSafeParent;                 // 008
		void*                                       threadSafeFileMap;                // 010 - NiTPointerMap<std::uint32_t, TESFile*>* - size == 0x20
		std::uint64_t                               unk018;                           // 018
		std::uint64_t                               unk020;                           // 020
		std::uint8_t                                unk028;                           // 028
		std::uint8_t                                unk029;                           // 029
		std::uint16_t                               pad02A;                           // 02A
		std::uint32_t                               pad02C;                           // 02C
		BSFile*                                     lockedFile;                       // 030
		BSFile*                                     file;                             // 038
		TESBitArrayFile*                            formUserDataBitArray;             // 040
		TESBitArrayFile*                            formVersionBitArray;              // 048
		TESBitArrayFile*                            formIDBitArray;                   // 050
		char                                        fileName[WinAPI::MAX_PATH];       // 058
		char                                        path[WinAPI::MAX_PATH];           // 15C
		char*                                       buffer;                           // 260
		std::uint32_t                               bufferAllocSize;                  // 268
		std::uint32_t                               firstCellOffset;                  // 26C
		std::uint32_t                               currCellOffset;                   // 270
		std::uint32_t                               unk274;                           // 274
		TESObjectCELL*                              currCell;                         // 278
		std::uint32_t                               currRefOffset;                    // 280
		FORM                                        currentform;                      // 284
		std::uint32_t                               currentchunkID;                   // 29C
		std::uint32_t                               actualChunkSize;                  // 2A0
		std::uint32_t                               filesize;                         // 2A4
		std::uint32_t                               fileOffset;                       // 2A8
		std::uint32_t                               formoffset;                       // 2AC
		std::uint32_t                               chunkoffset;                      // 2B0
		FORM                                        saveform;                         // 2B4
		std::uint32_t                               saveFormOffset;                   // 2CC
		std::uint64_t                               saveChunkOffset;                  // 2D0
		std::uint64_t                               unk2D8;                           // 2D8
		std::uint64_t                               unk2E0;                           // 2E0
		std::uint8_t                                unk2E8;                           // 2E8
		bool                                        isBigEndian;                      // 2E9
		std::uint8_t                                unk2EA;                           // 2EA
		std::uint8_t                                pad2EB;                           // 2EB
		WinAPI::WIN32_FIND_DATAA                    fileData;                         // 2EC
		float                                       unk42C;                           // 42C
		std::uint32_t                               unk430;                           // 430
		std::uint32_t                               flags;                            // 434
		stl::enumeration<RecordFlag, std::uint32_t> recordFlags;                      // 438
		std::uint32_t                               pad43C;                           // 43C
		BSSimpleList<const char*>                   masters;                          // 440
		BSSimpleList<std::uint64_t*>                mastersData;                      // 450
		std::uint32_t                               masterCount;                      // 460
		std::uint32_t                               pad464;                           // 464
		TESFile**                                   masterPtrs;                       // 468
		WinAPI::FILETIME                            deletedFormTime;                  // 470
		std::uint8_t                                compileIndex;                     // 478
		std::uint8_t                                pad479;                           // 479
		std::uint16_t                               smallFileCompileIndex;            // 47A
		std::uint32_t                               pad47C;                           // 47C
		BSString                                    createdBy;                        // 480
		BSString                                    summary;                          // 490
		char*                                       decompressedFormBuffer;           // 4A0
		std::uint32_t                               decompressedFormBufferSize;       // 4A8
		std::uint32_t                               pad4AC;                           // 4AC
		void*                                       reservedDecompressionBuffer;      // 4B0
		std::uint32_t                               reservedDecompressionBufferSize;  // 4B8
		std::uint32_t                               pad4BC;                           // 4BC
		void*                                       unk4C0;                           // 4C0
	};
	static_assert(sizeof(TESFile) == 0x4C8);
}
