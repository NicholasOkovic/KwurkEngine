#pragma once

#include "Event.h"

namespace KwurkEngine
{
	using ListenerId = std::size_t;
	using EventCallBack = std::function<void(const Event&)>;

	class EventManager final
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static EventManager* Get();
		static void Broadcast(const Event& e);

		EventManager() = default;
		~EventManager();

		void Initialize();
		void Terminate();

		ListenerId AddListerner(EventType eventType, const EventCallBack& cb);
		void RemoveListener(EventType eventType, ListenerId listenerId);

	private:
		void BroadcastPrivate(const Event& e);

		using EventListeners = std::unordered_map<EventType, std::unordered_map<ListenerId, EventCallBack>>;
		EventListeners mEventListeners;
		ListenerId mNextListenerId = 0;

	};
}