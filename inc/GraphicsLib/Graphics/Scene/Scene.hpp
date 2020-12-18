#pragma once
#include <GraphicsLib/Graphics/Scene/Components/DrawableObjectGroup.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/DirectionalLight.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/PointLight.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/SpotLight.hpp>
#include <list>




namespace cg
{
	class Scene
	{
	public:
		using ManagedObjectGroupNameList = std::vector<std::string>;

		using DrawableObjectGroupDict = std::unordered_map<std::string, std::shared_ptr<DrawableObjectGroup>>;

		using LightDict = std::unordered_map<std::string, std::shared_ptr<Light>>;
		using LightGroup = std::unordered_map<std::string, std::shared_ptr<Light>>;
	private:
		using LightGroupDictSearchWithType = std::unordered_map<Light::Type, std::shared_ptr<LightGroup>>;
		using LightGroupDictSearchWithName = std::unordered_map<std::string, std::shared_ptr<LightGroup>>;
	private:
		DrawableObjectGroupDict m_objectGroupDict;

		LightDict m_lightDict;
		LightGroupDictSearchWithType m_lightGroupDictSearchWithType;
		LightGroupDictSearchWithName m_lightGroupDictSearchWithName;

		std::string m_name;
	public:
		Camera camera;
	public:
		Scene(const std::string& name);
		virtual ~Scene() = default;

		[[nodiscard]] std::string getName() const noexcept;



		[[nodiscard]] bool objectGroupExists(const std::string& name) const noexcept;
		void addObjectGroup(const std::shared_ptr<DrawableObjectGroup>& group);
		void removeObjectGroup(const std::string& groupName);
		void removeAllObjectGroups();

		ManagedObjectGroupNameList createManagedObjectGroupNameList() const;
		std::shared_ptr<DrawableObjectGroup> getObjectGroup(const std::string& groupName) const;



		[[nodiscard]] bool lightExists(const std::string& name) const noexcept;
		void addLight(const std::shared_ptr<Light>& light);
		void removeLight(const std::string& name);
		void removeAllLights();
		
		[[nodiscard]] LightDict createLightDict() const;
		[[nodiscard]] LightGroup getLights(const Light::Type& type) const;
		template <typename Light_>
		[[nodiscard]] std::shared_ptr<Light_> getLight(const std::string& name) const
		{
			return std::dynamic_pointer_cast<Light_>(m_lightDict.at(name));
		}



		void draw(const std::string renderingGroupName, const DrawableObjectGroup::OperationPerObject& operationPerObject, const DrawableObjectGroup::OperationPerObjectPart& operationPerObjectPart) const;
	};
}
