#pragma once

#include "RE/G/GFxMovieView.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IVirtualMachine.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/V/VirtualMachine.h"

#include "SKSE/Impl/Stubs.h"
#include "SKSE/Version.h"

namespace SKSE
{
	struct PluginInfo;

	class QueryInterface
	{
	public:
		[[nodiscard]] std::uint32_t EditorVersion() const;
		[[nodiscard]] bool          IsEditor() const;
		[[nodiscard]] REL::Version  RuntimeVersion() const;
		[[nodiscard]] std::uint32_t SKSEVersion() const;

	protected:
		[[nodiscard]] const detail::SKSEInterface* GetProxy() const;
	};

	class LoadInterface : public QueryInterface
	{
	public:
		enum : std::uint32_t
		{
			kInvalid = 0,
			kScaleform,
			kPapyrus,
			kSerialization,
			kTask,
			kMessaging,
			kObject,
			kTrampoline,
			kTotal
		};

		[[nodiscard]] PluginHandle      GetPluginHandle() const;
		const PluginInfo* GetPluginInfo(const char* a_name) const;
		[[nodiscard]] std::uint32_t     GetReleaseIndex() const;
		[[nodiscard]] void*             QueryInterface(std::uint32_t a_id) const;
	};

	class ScaleformInterface
	{
	public:
		using RegCallback = bool(RE::GFxMovieView* a_view, RE::GFxValue* a_root);
		using RegInvCallback = void(RE::GFxMovieView* a_view, RE::GFxValue* a_object, RE::InventoryEntryData* a_item);

		enum
		{
			kVersion = 2
		};

		[[nodiscard]] std::uint32_t Version() const;

		bool Register(RegCallback* a_callback, const char* a_name) const;
		void Register(RegInvCallback* a_callback) const;

	protected:
		[[nodiscard]] const detail::SKSEScaleformInterface* GetProxy() const;
	};

	class SerializationInterface
	{
	public:
		using EventCallback = void(SerializationInterface* a_intfc);
		using FormDeleteCallback = void(RE::VMHandle a_handle);

		enum
		{
			kVersion = 4
		};

		[[nodiscard]] std::uint32_t Version() const;

		void SetUniqueID(std::uint32_t a_uid) const;

		void SetFormDeleteCallback(FormDeleteCallback* a_callback) const;
		void SetLoadCallback(EventCallback* a_callback) const;
		void SetRevertCallback(EventCallback* a_callback) const;
		void SetSaveCallback(EventCallback* a_callback) const;

		bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const void* a_buf, std::uint32_t a_length) const;

		template <
			class T,
			std::enable_if_t<
				std::negation_v<
					std::is_pointer<T>>,
				int> = 0>
		inline std::uint32_t WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T& a_buf) const
		{
			return WriteRecord(a_type, a_version, std::addressof(a_buf), sizeof(T));
		}

		template <
			class T,
			std::size_t N,
			std::enable_if_t<
				std::is_array_v<T>,
				int> = 0>
		inline std::uint32_t WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const T (&a_buf)[N]) const
		{
			return WriteRecord(a_type, a_version, std::addressof(a_buf), sizeof(T) * N);
		}

		[[nodiscard]] bool OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const;

		bool WriteRecordData(const void* a_buf, std::uint32_t a_length) const;

		template <
			class T,
			std::enable_if_t<
				std::negation_v<
					std::is_pointer<T>>,
				int> = 0>
		inline std::uint32_t WriteRecordData(const T& a_buf) const
		{
			return WriteRecordData(std::addressof(a_buf), sizeof(T));
		}

		template <
			class T,
			std::size_t N,
			std::enable_if_t<
				std::is_array_v<T>,
				int> = 0>
		inline std::uint32_t WriteRecordData(const T (&a_buf)[N]) const
		{
			return WriteRecordData(std::addressof(a_buf), sizeof(T) * N);
		}

		bool GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, std::uint32_t& a_length) const;

		std::uint32_t ReadRecordData(void* a_buf, std::uint32_t a_length) const;

		template <
			class T,
			std::enable_if_t<
				std::negation_v<
					std::is_pointer<T>>,
				int> = 0>
		inline std::uint32_t ReadRecordData(T& a_buf) const
		{
			return ReadRecordData(std::addressof(a_buf), sizeof(T));
		}

		template <
			class T,
			std::size_t N,
			std::enable_if_t<
				std::is_array_v<T>,
				int> = 0>
		inline std::uint32_t ReadRecordData(T (&a_buf)[N]) const
		{
			return ReadRecordData(std::addressof(a_buf), sizeof(T) * N);
		}

		bool ResolveFormID(RE::FormID a_oldFormID, RE::FormID& a_newFormID) const;
		bool ResolveHandle(RE::VMHandle a_oldHandle, RE::VMHandle& a_newHandle) const;

	protected:
		[[nodiscard]] const detail::SKSESerializationInterface* GetProxy() const;
	};

	class TaskInterface
	{
	public:
		using TaskFn = std::function<void()>;

		enum
		{
			kVersion = 2
		};

		[[nodiscard]] std::uint32_t Version() const;

		void AddTask(TaskFn a_task) const;
		void AddTask(TaskDelegate* a_task) const;
		void AddUITask(TaskFn a_task) const;
		void AddUITask(UIDelegate_v1* a_task) const;

	protected:
		class Task : public detail::TaskDelegate
		{
		public:
			Task(TaskFn&& a_fn);

			void Run() override;
			void Dispose() override;

		private:
			TaskFn _fn;
		};

		class UITask : public detail::UIDelegate_v1
		{
		public:
			UITask(TaskFn&& a_fn);

			void Run() override;
			void Dispose() override;

		private:
			TaskFn _fn;
		};

		[[nodiscard]] const detail::SKSETaskInterface* GetProxy() const;
	};

	class PapyrusInterface
	{
	public:
		using RegFunction1 = bool(RE::BSScript::Internal::VirtualMachine* a_vm);
		using RegFunction2 = bool(RE::BSScript::IVirtualMachine* a_vm);

		enum
		{
			kVersion = 1
		};

		[[nodiscard]] std::uint32_t Version() const;

		template <class Last>
		bool Register(Last a_last) const
		{
			return Register_Impl(a_last);
		}

		template <class First, class... Rest>
		bool Register(First a_first, Rest... a_rest) const
		{
			return Register_Impl(a_first) && Register(a_rest...);
		}

	protected:
		[[nodiscard]] const detail::SKSEPapyrusInterface* GetProxy() const;

	private:
		bool Register_Impl(RegFunction1* a_fn) const;
		bool Register_Impl(RegFunction2* a_fn) const;
	};

	class MessagingInterface
	{
	public:
		struct Message
		{
			const char*   sender;
			std::uint32_t type;
			std::uint32_t dataLen;
			void*         data;
		};

		using EventCallback = void(Message* a_msg);

		enum
		{
			kVersion = 2
		};

		enum : std::uint32_t
		{
			kPostLoad,
			kPostPostLoad,
			kPreLoadGame,
			kPostLoadGame,
			kSaveGame,
			kDeleteGame,
			kInputLoaded,
			kNewGame,
			kDataLoaded,

			kTotal
		};

		enum class Dispatcher : std::uint32_t
		{
			kModEvent = 0,
			kCameraEvent,
			kCrosshairEvent,
			kActionEvent,
			kNiNodeUpdateEvent,

			kTotal
		};

		[[nodiscard]] std::uint32_t Version() const;

		bool  Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const;
		[[nodiscard]] void* GetEventDispatcher(Dispatcher a_dispatcherID) const;
		bool  RegisterListener(EventCallback* a_callback) const;
		bool  RegisterListener(const char* a_sender, EventCallback* a_callback) const;

	protected:
		[[nodiscard]] const detail::SKSEMessagingInterface* GetProxy() const;
	};

	class ObjectInterface
	{
	public:
		enum
		{
			kVersion = 1
		};

		[[nodiscard]] std::uint32_t Version() const;

		[[nodiscard]] SKSEDelayFunctorManager&     GetDelayFunctorManager() const;
		[[nodiscard]] SKSEObjectRegistry&          GetObjectRegistry() const;
		[[nodiscard]] SKSEPersistentObjectStorage& GetPersistentObjectStorage() const;

	private:
		[[nodiscard]] const detail::SKSEObjectInterface* GetProxy() const;
	};

	class TrampolineInterface
	{
	public:
		enum
		{
			kVersion = 1
		};

		[[nodiscard]] std::uint32_t Version() const;

		[[nodiscard]] void* AllocateFromBranchPool(std::size_t a_size) const;
		[[nodiscard]] void* AllocateFromLocalPool(std::size_t a_size) const;

	private:
		[[nodiscard]] const detail::SKSETrampolineInterface* GetProxy() const;
	};

	struct PluginInfo
	{
		enum
		{
			kVersion = 1
		};

		std::uint32_t infoVersion;
		const char*   name;
		std::uint32_t version;
	};
}
