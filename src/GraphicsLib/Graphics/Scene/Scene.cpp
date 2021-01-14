#include <GraphicsLib/Graphics/Scene/Scene.hpp>





namespace cg
{
	Scene::Scene(const std::string& name)
		: m_name(name)
	{
	}

	std::string Scene::getName() const noexcept
	{
		return m_name;
	}

	bool Scene::groupExists(const std::string& name) const noexcept
	{
		return m_groupDict.count(name) == 1;
	}

	void Scene::addGroup(const std::shared_ptr<Scene::Group>& group)
	{
		const auto& name = group->name();
		if (groupExists(name)) 
		{
			LogEX("A group named \"%s\" already exists.", name.c_str());
			return; 
		}

		m_groupDict.emplace(name, group);
	}
	void Scene::removeGroup(const std::string& groupName)
	{
		if (groupExists(groupName) == false)
		{
			LogEX("A group named \"%s\" does not exist.", groupName.c_str());
			return; 
		}

		m_groupDict.erase(groupName);
	}
	void Scene::removeAllGroups()
	{
		m_groupDict.clear();
	}

	Scene::GroupNameList Scene::makeGroupNameList() const
	{
		GroupNameList list;
		for (auto pair : m_groupDict)
		{
			list.emplace_back(pair.first);
		}
		return list;
	}

	std::shared_ptr<Scene::Group> Scene::getGroup(const std::string& groupName) const
	{
		return m_groupDict.at(groupName);
	}

	void Scene::addLight(const std::shared_ptr<Light>& light)
	{
		auto lightName = light->getName();
		if (lightExists(lightName))
		{
			LogEX("A light named \"%s\" already exists.", lightName.c_str());
			return;
		}

		auto lightType = light->getType();
		if (m_lightGroupDictSearchWithType.count(lightType) == 0)
		{
			m_lightGroupDictSearchWithType.emplace(lightType, std::make_shared<LightGroup>());
		}
		auto group = m_lightGroupDictSearchWithType.at(lightType);
		group->emplace(lightName, light);
		m_lightDict.emplace(lightName, light);
		m_lightGroupDictSearchWithName.emplace(lightName, group);
	}

	void Scene::removeLight(const std::string& name)
	{
		if (lightExists(name) == 0)
		{
			LogEX("A light named \"%s\" does not exist.", name.c_str());
			return;
		}

		auto group = m_lightGroupDictSearchWithName.at(name);
		if (group->size() == 1)
		{
			m_lightGroupDictSearchWithType.erase(group->at(name)->getType());
		}
		else
		{
			group->erase(name);
		}

		m_lightDict.erase(name);
		m_lightGroupDictSearchWithName.erase(name);
	}

	void Scene::removeAllLights()
	{
		m_lightDict.clear();
		m_lightGroupDictSearchWithName.clear();
		m_lightGroupDictSearchWithType.clear();
	}

	Scene::LightDict Scene::makeLightDict() const
	{
		return m_lightDict;
	}

	Scene::LightGroup Scene::getLights(const Light::Type& type) const
	{
		if(m_lightGroupDictSearchWithType.count(type) == 0)
		{
			return Scene::LightGroup();
		}
		return *m_lightGroupDictSearchWithType.at(type);
	}

	bool Scene::lightExists(const std::string& name) const noexcept
	{
		return m_lightGroupDictSearchWithName.count(name) == 1;
	}

	void Scene::draw(const std::string renderingGroupName, const Scene::Group::OperationPerObject& operationPerObject, const Scene::Group::OperationPerObjectPart& operationPerObjectPart) const
	{
		for (const auto& pair : m_groupDict)
		{
			pair.second->draw(renderingGroupName, operationPerObject, operationPerObjectPart);
		}
	}









	Scene::Group::Group(const std::string& name)
		: m_name(name)
	{
	}


	std::string Scene::Group::name() const noexcept
	{
		return m_name;
	}


	bool Scene::Group::m_renderingGroupExists(const std::string& groupName) const noexcept
	{
		return m_renderingGroupDictSearchWithRenderPipelineName.count(groupName) == 1;
	}
	void Scene::Group::update(cpp::Subject* pSubject)
	{
		const auto pObject = static_cast<DrawableObject*>(pSubject);

		const auto& objectID = pObject->getID();
		if (objectExists(objectID) == false) { return; }

		const auto objectIDSTR = objectID.get();
		const auto renderingGroup = m_renderingGroupDictSearchWithObjectID.at(objectIDSTR);
		const auto managedObject = renderingGroup->at(objectIDSTR);
		renderingGroup->erase(objectIDSTR);
		add(managedObject);
	}
	bool Scene::Group::objectExists(const cg::ID& objectID) const noexcept
	{
		return m_renderingGroupDictSearchWithObjectID.count(objectID.get()) == 1;
	}



	void Scene::Group::add(std::shared_ptr<DrawableObject> objectRef)
	{
		if (objectRef == nullptr) { return; }

		const auto objectID = objectRef->getID();
		const auto objectIDSTR = objectID.get();

		if (objectExists(objectID))
		{
			LogEX("An object \"ID: %s\" already exists.", objectIDSTR.c_str());
			return;
		}

		const auto& groupName = objectRef->getNameOfRenderingGroupToWhichThisBelongs();
		if (m_renderingGroupExists(groupName) == false)
		{
			m_renderingGroupDictSearchWithRenderPipelineName.emplace(groupName, std::make_shared<DrawableObjectDict>());
		}

		m_renderingGroupDictSearchWithRenderPipelineName.at(groupName)->emplace(objectIDSTR, objectRef);
		m_renderingGroupDictSearchWithObjectID.emplace(objectIDSTR, m_renderingGroupDictSearchWithRenderPipelineName.at(groupName));
		m_objectDict.emplace(objectIDSTR, objectRef);
		addSelfToSubject(objectRef.get());
	}
	void Scene::Group::remove(const cg::ID& objectID)
	{
		auto objectIDString = objectID.get();
		auto objectIDCSTR = objectIDString.c_str();
		if (objectExists(objectID) == false)
		{
			LogEX("An object \"ID: %s\" does not exist.", objectIDSTR);
			return;
		}

		const auto& renderingGroup = m_renderingGroupDictSearchWithObjectID.at(objectIDCSTR);

		removeSelfFromSubject(renderingGroup->at(objectIDCSTR).get());

		m_renderingGroupDictSearchWithObjectID.erase(objectIDCSTR);
		renderingGroup->erase(objectIDCSTR);
		m_objectDict.erase(objectIDCSTR);
	}
	void Scene::Group::removeAll()
	{
		for (auto& pair : m_renderingGroupDictSearchWithRenderPipelineName)
		{
			auto& renderingGroup = *pair.second;
			for (auto& managedObject : renderingGroup)
			{
				removeSelfFromSubject(managedObject.second.get());
			}
		}

		m_renderingGroupDictSearchWithObjectID.clear();
		m_renderingGroupDictSearchWithRenderPipelineName.clear();
		m_objectDict.clear();
	}

	Scene::Group::DrawableObjectDict Scene::Group::makeObjectDict() const
	{
		return m_objectDict;
	}




	void Scene::Group::draw(const std::string& renderingGroupName, const OperationPerObject& operationPerObject, const OperationPerObjectPart& operationPerObjectPart) const
	{
		if (m_renderingGroupExists(renderingGroupName) == false) { return; }
		const auto& group = *m_renderingGroupDictSearchWithRenderPipelineName.at(renderingGroupName);
		if (group.empty()) { return; }

		for (auto pair : group)
		{
			auto object = pair.second;
			if (object == nullptr) { continue; }

			operationPerObject(object);

			const auto partNameList = object->geometry.parts.makePartNameList();
			for (const auto& name : partNameList)
			{
				const auto& part = object->geometry.parts.get(name);;
				const auto geometryBuffer = part.getGeometryBuffer();

				operationPerObjectPart(part);

				geometryBuffer->draw(part.primitiveTopology, object->instanceCount);
			}
		}
	}
}
