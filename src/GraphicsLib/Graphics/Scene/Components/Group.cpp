#include <GraphicsLib/Graphics/Scene/Components/DrawableObjectGroup.hpp>
#include <GraphicsLib/API/API.hpp>

#include <tuple>





namespace cg
{
	DrawableObjectGroup::DrawableObjectGroup(const std::string& name)
		: m_name(name)
	{
	}


	std::string DrawableObjectGroup::name() const noexcept
	{
		return m_name;
	}


	bool DrawableObjectGroup::m_renderingGroupExists(const std::string& groupName) const noexcept
	{
		return m_renderingGroupDictSearchWithRenderPipelineName.count(groupName) == 1;
	}
	void DrawableObjectGroup::update(cpp::Subject* pSubject)
	{
		const auto pObject = static_cast<DrawableObject*>(pSubject);

		const auto& objectID = pObject->getID();
		if (objectExists(objectID) == false) { return; }

		const auto objectIDSTR = objectID.get();
		const auto renderingGroup = m_renderingGroupDictSearchWithObjectID.at(objectIDSTR);
		const auto managedObject = renderingGroup->at(objectIDSTR);
		renderingGroup->erase(objectIDSTR);
		add(managedObject.lock());
	}
	bool DrawableObjectGroup::objectExists(const cg::ID& objectID) const noexcept
	{
		return m_renderingGroupDictSearchWithObjectID.count(objectID.get()) == 1;
	}



	void DrawableObjectGroup::add(const std::shared_ptr<DrawableObject>& objectRef)
	{
		if (objectRef == nullptr) { return; }

		const auto objectID = objectRef->getID();
		const auto objectIDSTR = objectID.get();

		if (objectExists(objectID)) 
		{
			LogEX("An object \"ID: %s\" already exists.", objectIDSTR.c_str());
			return; 
		}

		const auto& groupName = objectRef->whichRenderingGroupBelongTo();
		if (m_renderingGroupExists(groupName) == false)
		{
			m_renderingGroupDictSearchWithRenderPipelineName.emplace(groupName, std::make_shared<DrawableObjectDict>());
		}

		m_renderingGroupDictSearchWithRenderPipelineName.at(groupName)->emplace(objectIDSTR, objectRef);
		m_renderingGroupDictSearchWithObjectID.emplace(objectIDSTR, m_renderingGroupDictSearchWithRenderPipelineName.at(groupName));
		m_objectDict.emplace(objectIDSTR, objectRef);
		addSelfToSubject(objectRef.get());
	}
	void DrawableObjectGroup::remove(const cg::ID& objectID)
	{
		auto objectIDSTR = objectID.get().c_str();
		if (objectExists(objectID) == false) 
		{
			LogEX("An object \"ID: %s\" does not exist.", objectIDSTR);
			return; 
		}

		const auto& renderingGroup = m_renderingGroupDictSearchWithObjectID.at(objectIDSTR);

		removeSelfFromSubject(renderingGroup->at(objectIDSTR).lock().get());

		m_renderingGroupDictSearchWithObjectID.erase(objectIDSTR);
		renderingGroup->erase(objectIDSTR);
		m_objectDict.erase(objectIDSTR);
	}
	void DrawableObjectGroup::removeAll()
	{
		for (auto& pair : m_renderingGroupDictSearchWithRenderPipelineName)
		{
			auto& renderingGroup = *pair.second;
			for (auto& managedObject : renderingGroup)
			{
				removeSelfFromSubject(managedObject.second.lock().get());
			}
		}

		m_renderingGroupDictSearchWithObjectID.clear();
		m_renderingGroupDictSearchWithRenderPipelineName.clear();
		m_objectDict.clear();
	}

	DrawableObjectGroup::DrawableObjectDict DrawableObjectGroup::getObjectDict() const
	{
		return m_objectDict;
	}




	void DrawableObjectGroup::draw(const std::string& renderingGroupName, const OperationPerObject& operationPerObject, const OperationPerObjectPart operationPerObjectPart) const
	{
		if (m_renderingGroupExists(renderingGroupName) == false) { return; }
		const auto& group = *m_renderingGroupDictSearchWithRenderPipelineName.at(renderingGroupName);
		if (group.empty()) { return; }

		for (auto objectWeak : group)
		{
			const auto object = objectWeak.second.lock();
			if (object == nullptr) { continue; }

			operationPerObject(object);

			for (const auto& pair : object->parts)
			{
				const auto& part = pair.second;
				const auto geometryBuffer = part.getGeometryBuffer();

				operationPerObjectPart(part);

				geometryBuffer->draw(object->primitiveTopology, object->instanceCount);
			}
		}
	}
}
