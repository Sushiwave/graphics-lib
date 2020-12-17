#include <CPPLib/DesignPattern/Observer/Observer.hpp>
#include <CPPLib/DesignPattern/Observer/Subject.hpp>
#include <CPPLib/Log/Log.hpp>





namespace cpp
{
	void Observer::addSelfToSubject(Subject* pSubject)
	{
		if (pSubject == nullptr) { return; }
		pSubject->addObserver(m_id, shared_from_this());
	}

	void Observer::removeSelfFromSubject(Subject* pSubject)
	{
		if (pSubject == nullptr) { return; }
		pSubject->removeObserver(m_id);
	}
}
