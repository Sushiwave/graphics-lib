#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>
#include <GraphicsLib/Graphics/DrawableObject/DrawableObject.hpp>
#include <GraphicsLib/Graphics/GPUResource/MaterialConstantBuffer/MaterialConstantBuffer.hpp>
#include <ThirdParty/CPPLib/DesignPattern/Observer/Observer.hpp>





namespace cg
{
	class DrawableObjectGroup
		: public cpp::Observer
	{
	public:
		using OperationPerObject = std::function<void(std::shared_ptr<DrawableObject>)>;
		using OperationPerObjectPart = std::function<void(const DrawableObject::Part&)>;
		using DrawableObjectDict = std::unordered_map<ID::Type, std::weak_ptr<DrawableObject>>;
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
		DrawableObjectGroup(const std::string& name);
		virtual ~DrawableObjectGroup() = default;



		[[nodiscard]] std::string name() const noexcept;



		[[nodiscard]] bool objectExists(const cg::ID& objectID) const noexcept;



		void add(std::shared_ptr<DrawableObject> objectRef);
		void remove(const cg::ID& objectID);
		void removeAll();


		DrawableObjectDict getObjectDict() const;


		void draw(const std::string& renderingGroupName, const OperationPerObject& operationPerObject, const OperationPerObjectPart operationPerObjectPart) const;
	};
}
