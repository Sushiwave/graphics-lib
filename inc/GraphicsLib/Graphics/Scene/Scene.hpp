#pragma once
#include <GraphicsLib/Graphics/DrawableObject/DrawableObject.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/DirectionalLight.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/PointLight.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/SpotLight.hpp>
#include <list>




namespace cg
{
	class Scene
	{
	public:
		class Group
			: public cpp::Observer
		{
		public:
			using OperationPerObject = std::function<void(std::shared_ptr<DrawableObject>)>;
			using OperationPerObjectPart = std::function<void(const Geometry::Part&)>;
			using DrawableObjectDict = std::unordered_map<ID::Type, std::shared_ptr<DrawableObject>>;
		private:
			using RenderingGroup = std::shared_ptr<DrawableObjectDict>;
			using RenderingGroupDictSearchWithRenderPipelineName = std::unordered_map<std::string, RenderingGroup>;
			using RenderingGroupDictSearchWithObjectID = std::unordered_map<ID::Type, RenderingGroup>;
		private:
			std::string m_name;

			RenderingGroupDictSearchWithRenderPipelineName m_renderingGroupDictSearchWithRenderPipelineName;
			RenderingGroupDictSearchWithObjectID m_renderingGroupDictSearchWithObjectID;
			DrawableObjectDict m_objectDict;
		private:
			[[nodiscard]] bool m_renderingGroupExists(const std::string& groupName) const noexcept;

			void update(cpp::Subject* pSubject) override;
		public:
			Group(const std::string& name);
			virtual ~Group() = default;



			[[nodiscard]] std::string name() const noexcept;



			[[nodiscard]] bool objectExists(const cg::ID& objectID) const noexcept;



			void add(std::shared_ptr<DrawableObject> objectRef);
			void remove(const cg::ID& objectID);
			void removeAll();


			DrawableObjectDict makeObjectDict() const;


			void draw(const std::string& renderingGroupName, const OperationPerObject& operationPerObject, const OperationPerObjectPart& operationPerObjectPart) const;
		};
	public:
		using GroupNameList = std::vector<std::string>;

		using GroupDict = std::unordered_map<std::string, std::shared_ptr<Scene::Group>>;

		using LightDict = std::unordered_map<std::string, std::shared_ptr<Light>>;
		using LightGroup = std::unordered_map<std::string, std::shared_ptr<Light>>;
	private:
		using LightGroupDictSearchWithType = std::unordered_map<Light::Type, std::shared_ptr<LightGroup>>;
		using LightGroupDictSearchWithName = std::unordered_map<std::string, std::shared_ptr<LightGroup>>;
	private:
		GroupDict m_groupDict;

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



		[[nodiscard]] bool groupExists(const std::string& name) const noexcept;
		void addGroup(const std::shared_ptr<Scene::Group>& group);
		void removeGroup(const std::string& groupName);
		void removeAllGroups();

		GroupNameList makeGroupNameList() const;
		std::shared_ptr<Scene::Group> getGroup(const std::string& groupName) const;



		[[nodiscard]] bool lightExists(const std::string& name) const noexcept;
		void addLight(const std::shared_ptr<Light>& light);
		void removeLight(const std::string& name);
		void removeAllLights();
		
		[[nodiscard]] LightDict makeLightDict() const;
		[[nodiscard]] LightGroup getLights(const Light::Type& type) const;
		template <typename Light_>
		[[nodiscard]] std::shared_ptr<Light_> getLight(const std::string& name) const
		{
			return std::dynamic_pointer_cast<Light_>(m_lightDict.at(name));
		}



		void draw(const std::string renderingGroupName, const Scene::Group::OperationPerObject& operationPerObject, const Scene::Group::OperationPerObjectPart& operationPerObjectPart) const;
	};
}
