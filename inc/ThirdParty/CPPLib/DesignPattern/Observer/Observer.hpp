#pragma once
#include <ThirdParty/CPPLib/ID/SimpleStringID.hpp>
#include <ThirdParty/CPPLib/C++/multiple_inheritable_enable_shared_from_this.hpp>

#include <memory>

namespace cpp
{
	class Subject;
}





namespace cpp
{
	class Observer
		: public multiple_inheritable_enable_shared_from_this<Observer>
	{
	private:
		friend class Subject;
	public:
		DEFINE_SIMPLE_STRING_ID(ID, 5);
	private:
		ID m_id;
	private:
		virtual void update(Subject* pSubject) = 0;
	protected:
		void addSelfToSubject(Subject* pSubject);
		void removeSelfFromSubject(Subject* pSubject);
	public:
		virtual ~Observer() = default;
	};
}