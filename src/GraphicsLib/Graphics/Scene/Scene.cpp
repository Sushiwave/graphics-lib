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

	bool Scene::objectGroupExists(const std::string& name) const noexcept
	{
		return m_objectGroupDict.count(name) == 1;
	}

	void Scene::addObjectGroup(const std::shared_ptr<DrawableObjectGroup>& group)
	{
		const auto& name = group->name();
		if (objectGroupExists(name)) 
		{
			LogEX("A group named \"%s\" already exists.", name.c_str());
			return; 
		}

		m_objectGroupDict.emplace(name, group);
	}
	void Scene::removeObjectGroup(const std::string& groupName)
	{
		if (objectGroupExists(groupName) == false)
		{
			LogEX("A group named \"%s\" does not exist.", groupName.c_str());
			return; 
		}

		m_objectGroupDict.erase(groupName);
	}
	void Scene::removeAllObjectGroups()
	{
		m_objectGroupDict.clear();
	}

	Scene::ManagedObjectGroupNameList Scene::createManagedObjectGroupNameList() const
	{
		ManagedObjectGroupNameList list;
		for (auto pair : m_objectGroupDict)
		{
			list.emplace_back(pair.first);
		}
		return list;
	}

	std::shared_ptr<DrawableObjectGroup> Scene::getObjectGroup(const std::string& groupName) const
	{
		return m_objectGroupDict.at(groupName);
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

	Scene::LightDict Scene::createLightDict() const
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

	void Scene::draw(const std::string renderingGroupName, const DrawableObjectGroup::OperationPerObject& operationPerObject, const DrawableObjectGroup::OperationPerObjectPart& operationPerObjectPart) const
	{
		for (const auto& pair : m_objectGroupDict)
		{
			pair.second->draw(renderingGroupName, operationPerObject, operationPerObjectPart);
		}
	}
}
