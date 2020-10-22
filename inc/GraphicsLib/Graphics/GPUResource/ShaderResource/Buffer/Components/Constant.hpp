#pragma once
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/ID/IIDHolder.hpp>

#include <functional>





namespace cg
{
	class Constant
		: public IIDHolder
	{
	private:
		ID m_id;

		std::shared_ptr<void> m_pData;

		std::function<std::shared_ptr<void>()> m_cloneDataPointer;
	protected:
		template <typename Data_>
		void tweak(const std::function<void(Data_&)>& operation)
		{
			return operation(*std::reinterpret_pointer_cast<Data_>(m_pData));
		}
	public:
		Constant();
		template <typename T>
		Constant(std::shared_ptr<T> pData)
			: m_pData(pData)
		{
			m_cloneDataPointer = [&]()->std::shared_ptr<void>
			{
				const auto size = sizeof(T);
				const auto src  = std::reinterpret_pointer_cast<T>(m_pData);
				const auto dest = std::make_shared<T>();

				memcpy_s(dest.get(), size, src.get(), size);

				return dest;
			};
		}
		template <>
		Constant(std::shared_ptr<void> pData)
			: m_pData(pData)
		{
			m_cloneDataPointer = []()->std::shared_ptr<void>{ return nullptr; };
			//Log
		}
		virtual ~Constant() = default;



		[[nodiscard]] ID getID() const noexcept override;


		template <typename Data_>
		[[nodiscard]] Data_ get() const
		{
			return *std::reinterpret_pointer_cast<Data_>(m_pData);
		}
		[[nodiscard]] std::shared_ptr<void> getP() const noexcept;

		[[nodiscard]] Constant clone() const;
	};
}
