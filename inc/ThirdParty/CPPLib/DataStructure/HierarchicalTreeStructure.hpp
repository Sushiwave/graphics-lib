#pragma once
#include <unordered_map>
#include <memory>
#include <ThirdParty/CPPLib/ID/SimpleStringID.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>
#include <ThirdParty/CPPLib/ID/IDGenerator/StringIDGenerator.hpp>
#include <ThirdParty/CPPLib/C++/multiple_inheritable_enable_shared_from_this.hpp>





namespace cpp
{
	//T must inherit IIDHolder.
	template <typename T>
	class HierarchicalTreeStructure
		: public multiple_inheritable_enable_shared_from_this<HierarchicalTreeStructure<T>>
	{
	public:
		DEFINE_SIMPLE_STRING_ID(ID, 5);
	public:
		using Children = std::unordered_map<std::string, std::shared_ptr<T>>;
	protected:
		ID m_id;

		std::shared_ptr<T> m_parent;
		Children m_children;
	public:
		virtual ~HierarchicalTreeStructure() = default;


		[[nodiscard]] bool childExists(const ID& id) const
		{
			return m_children.count(id.get());
		}
		[[nodiscard]] Children getChildren() const
		{
			return m_children;
		}
		[[nodiscard]] T getParent() const
		{
			return *m_parent;
		}
		[[nodiscard]] bool isLeafNode() const
		{
			return m_children.empty();
		}
		[[nodiscard]] bool isRootNode() const
		{
			return m_parent == nullptr;
		}



		void addChild(std::shared_ptr<T> child)
		{
			auto childID = child->getID();
			if (childExists(childID))
			{
				LogEX("A child  \"ID: %s\" already exist.", childID.get().c_str());
				return;
			}

			if (child->m_parent)
			{
				child->m_parent->removeChild(childID);
			}
			child->m_parent = this->downcasted_shared_from_this<T>();
			m_children.emplace(childID.get(), child);
		}

		void removeChild(const ID& id)
		{
			if (childExists(id)) 
			{
				LogEX("A child \"ID: %s\" does not exist.", id.get().c_str());
				return; 
			}
			m_children[id.get()]->m_parent = nullptr;
			m_children.erase(id.get());
		}

		void removeAllChildren()
		{
			for (const auto& pair : m_children)
			{
				removeChild(pair.first);
			}
		}
	};
}
