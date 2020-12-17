#pragma once
#include "Observer.hpp"

#include <unordered_map>
#include <string>





namespace cpp
{
	class Subject
	{
	private:
		friend class Observer;
	private:
		std::unordered_map<Observer::ID::Type, std::weak_ptr<Observer>> m_observerDict;
	private:
		void addObserver(const Observer::ID& id, std::shared_ptr<Observer> observer);
		void removeObserver(const Observer::ID& id);
		[[nodiscard]] bool exists(const Observer::ID& id);
	protected:
		void notify() const;
	public:
		virtual ~Subject() = default;
	};
}
