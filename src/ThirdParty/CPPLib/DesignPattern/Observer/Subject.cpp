#include <ThirdParty/CPPLib/DesignPattern/Observer/Subject.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>





namespace cpp
{
	void Subject::addObserver(const Observer::ID& id, std::shared_ptr<Observer> observer)
	{
		if (exists(id))
		{
			LogEX("An observer \"ID: %s\" already exist.", id.get().c_str());
			return;
		}

		m_observerDict.emplace(id.get(), observer);
	}

	void Subject::removeObserver(const Observer::ID& id)
	{
		if (exists(id) == false) 
		{
			LogEX("An observer \"ID: %s\" does not exist.", id.get().c_str());
			return;
		}

		m_observerDict.erase(id.get());
	}

	bool Subject::exists(const Observer::ID& id)
	{
		return m_observerDict.count(id.get()) == 1;
	}

	void Subject::notify() const
	{
		for (auto observer : m_observerDict)
		{
			if(const auto safeObserver = observer.second.lock())
			{
				safeObserver->update(const_cast<Subject*>(this));
			}
		}
	}
}
