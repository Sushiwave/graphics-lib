#pragma once
#include <ThirdParty/CPPLib/ID/IDGenerator/StringIDGenerator.hpp>





#define DEFINE_SIMPLE_STRING_ID(CLASS_NAME_, ID_LENGTH_)\
	class CLASS_NAME_\
	{\
	public:\
		using Type = std::string;\
	private:\
		static inline cpp::StringIDGenerator m_idGenerator = cpp::StringIDGenerator(ID_LENGTH_);\
		Type m_id;\
	public:\
		CLASS_NAME_##() noexcept\
			: m_id(m_idGenerator.generate())\
		{\
		}\
\
		CLASS_NAME_##(const Type& id) noexcept\
			: m_id(id)\
		{\
		}\
\
		bool operator==(const CLASS_NAME_##& id) const\
		{\
			return m_id == id.m_id;\
		}\
\
		bool operator!=(const CLASS_NAME_##& id) const\
		{\
			return m_id != id.m_id;\
		}\
\
		std::string get() const noexcept\
		{\
			return m_id;\
		}\
	}
