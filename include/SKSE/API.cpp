#include "SKSE/API.h"

#include "SKSE/Logger.h"

namespace SKSE
{
	namespace detail
	{
		struct APIStorage
		{
		public:
			[[nodiscard]] static APIStorage& get() noexcept
			{
				static APIStorage singleton;
				return singleton;
			}

			PluginHandle  pluginHandle{ static_cast<PluginHandle>(-1) };
			std::uint32_t releaseIndex{ 0 };

			ScaleformInterface*     scaleformInterface{ nullptr };
			PapyrusInterface*       papyrusInterface{ nullptr };
			SerializationInterface* serializationInterface{ nullptr };
			TaskInterface*          taskInterface{ nullptr };
			TrampolineInterface*    trampolineInterface{ nullptr };

			MessagingInterface*                    messagingInterface{ nullptr };
			RE::BSTEventSource<ModCallbackEvent>*  modCallbackEventSource{ nullptr };
			RE::BSTEventSource<CameraEvent>*       cameraEventSource{ nullptr };
			RE::BSTEventSource<CrosshairRefEvent>* crosshairRefEventSource{ nullptr };
			RE::BSTEventSource<ActionEvent>*       actionEventSource{ nullptr };
			RE::BSTEventSource<NiNodeUpdateEvent>* niNodeUpdateEventSource{ nullptr };

			ObjectInterface*             objectInterface{ nullptr };
			SKSEDelayFunctorManager*     delayFunctorManager{ nullptr };
			SKSEObjectRegistry*          objectRegistry{ nullptr };
			SKSEPersistentObjectStorage* persistentObjectStorage{ nullptr };

			std::mutex                         apiLock;
			std::vector<std::function<void()>> apiInitRegs;
			bool                               apiInit{ false };

			template <class T>
			[[nodiscard]] RE::BSTEventSource<T>* GetEventDispatcher(MessagingInterface::Dispatcher a_id) const
			{
				assert(messagingInterface);
				return static_cast<RE::BSTEventSource<T>*>(messagingInterface->GetEventDispatcher(a_id));
			}

		private:
			APIStorage() noexcept = default;
			APIStorage(const APIStorage&) = delete;
			APIStorage(APIStorage&&) = delete;

			~APIStorage() noexcept = default;

			APIStorage& operator=(const APIStorage&) = delete;
			APIStorage& operator=(APIStorage&&) = delete;
		};

		template <class T>
		T* QueryInterface(const LoadInterface* a_intfc, std::uint32_t a_id)
		{
			auto result = static_cast<T*>(a_intfc->QueryInterface(a_id));
			if (result && result->Version() > T::kVersion) {
				log::warn("interface definition is out of date"sv);
			}
			return result;
		}
	}

	void Init(const LoadInterface* a_intfc) noexcept
	{
		if (!a_intfc) {
			stl::report_and_fail("interface is null"sv);
		}

		(void)REL::Module::get();
		(void)REL::IDDatabase::get();

		auto&       storage = detail::APIStorage::get();
		const auto& intfc = *a_intfc;

		const std::scoped_lock l(storage.apiLock);
		if (!storage.apiInit) {
			storage.pluginHandle = intfc.GetPluginHandle();
			storage.releaseIndex = intfc.GetReleaseIndex();

			storage.scaleformInterface = detail::QueryInterface<ScaleformInterface>(a_intfc, LoadInterface::kScaleform);
			storage.papyrusInterface = detail::QueryInterface<PapyrusInterface>(a_intfc, LoadInterface::kPapyrus);
			storage.serializationInterface = detail::QueryInterface<SerializationInterface>(a_intfc, LoadInterface::kSerialization);
			storage.taskInterface = detail::QueryInterface<TaskInterface>(a_intfc, LoadInterface::kTask);
			storage.trampolineInterface = detail::QueryInterface<TrampolineInterface>(a_intfc, LoadInterface::kTrampoline);

			storage.messagingInterface = detail::QueryInterface<MessagingInterface>(a_intfc, LoadInterface::kMessaging);
			if (storage.messagingInterface) {
				storage.modCallbackEventSource = storage.GetEventDispatcher<ModCallbackEvent>(MessagingInterface::Dispatcher::kModEvent);
				storage.cameraEventSource = storage.GetEventDispatcher<CameraEvent>(MessagingInterface::Dispatcher::kCameraEvent);
				storage.crosshairRefEventSource = storage.GetEventDispatcher<CrosshairRefEvent>(MessagingInterface::Dispatcher::kCrosshairEvent);
				storage.actionEventSource = storage.GetEventDispatcher<ActionEvent>(MessagingInterface::Dispatcher::kActionEvent);
				storage.niNodeUpdateEventSource = storage.GetEventDispatcher<NiNodeUpdateEvent>(MessagingInterface::Dispatcher::kNiNodeUpdateEvent);
			}

			storage.objectInterface = detail::QueryInterface<ObjectInterface>(a_intfc, LoadInterface::kObject);
			if (storage.objectInterface) {
				const auto& objectInterface = *storage.objectInterface;
				storage.delayFunctorManager = std::addressof(objectInterface.GetDelayFunctorManager());
				storage.objectRegistry = std::addressof(objectInterface.GetObjectRegistry());
				storage.persistentObjectStorage = std::addressof(objectInterface.GetPersistentObjectStorage());
			}

			storage.apiInit = true;
			auto& regs = storage.apiInitRegs;
			for (const auto& reg : regs) {
				reg();
			}
			regs.clear();
			regs.shrink_to_fit();
		}
	}

	void RegisterForAPIInitEvent(std::function<void()> a_fn)
	{
		{
			auto&                  storage = detail::APIStorage::get();
			const std::scoped_lock l(storage.apiLock);
			if (!storage.apiInit) {
				storage.apiInitRegs.push_back(a_fn);
				return;
			}
		}

		a_fn();
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return detail::APIStorage::get().pluginHandle;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return detail::APIStorage::get().releaseIndex;
	}

	const ScaleformInterface* GetScaleformInterface() noexcept
	{
		return detail::APIStorage::get().scaleformInterface;
	}

	const PapyrusInterface* GetPapyrusInterface() noexcept
	{
		return detail::APIStorage::get().papyrusInterface;
	}

	const SerializationInterface* GetSerializationInterface() noexcept
	{
		return detail::APIStorage::get().serializationInterface;
	}

	const TaskInterface* GetTaskInterface() noexcept
	{
		return detail::APIStorage::get().taskInterface;
	}

	const TrampolineInterface* GetTrampolineInterface() noexcept
	{
		return detail::APIStorage::get().trampolineInterface;
	}

	const MessagingInterface* GetMessagingInterface() noexcept
	{
		return detail::APIStorage::get().messagingInterface;
	}

	RE::BSTEventSource<ModCallbackEvent>* GetModCallbackEventSource() noexcept
	{
		return detail::APIStorage::get().modCallbackEventSource;
	}

	RE::BSTEventSource<CameraEvent>* GetCameraEventSource() noexcept
	{
		return detail::APIStorage::get().cameraEventSource;
	}

	RE::BSTEventSource<CrosshairRefEvent>* GetCrosshairRefEventSource() noexcept
	{
		return detail::APIStorage::get().crosshairRefEventSource;
	}

	RE::BSTEventSource<ActionEvent>* GetActionEventSource() noexcept
	{
		return detail::APIStorage::get().actionEventSource;
	}

	RE::BSTEventSource<NiNodeUpdateEvent>* GetNiNodeUpdateEventSource() noexcept
	{
		return detail::APIStorage::get().niNodeUpdateEventSource;
	}

	const ObjectInterface* GetObjectInterface() noexcept
	{
		return detail::APIStorage::get().objectInterface;
	}

	const SKSEDelayFunctorManager* GetDelayFunctorManager() noexcept
	{
		return detail::APIStorage::get().delayFunctorManager;
	}

	const SKSEObjectRegistry* GetObjectRegistry() noexcept
	{
		return detail::APIStorage::get().objectRegistry;
	}

	const SKSEPersistentObjectStorage* GetPersistentObjectStorage() noexcept
	{
		return detail::APIStorage::get().persistentObjectStorage;
	}

	Trampoline& GetTrampoline()
	{
		static Trampoline trampoline;
		return trampoline;
	}

	void AllocTrampoline(std::size_t a_size, bool a_trySKSEReserve)
	{
		auto& trampoline = GetTrampoline();
		if (auto intfc = GetTrampolineInterface();
			intfc && a_trySKSEReserve) {
			auto memory = intfc->AllocateFromBranchPool(a_size);
			if (memory) {
				trampoline.set_trampoline(memory, a_size);
				return;
			}
		}

		trampoline.create(a_size);
	}
}
