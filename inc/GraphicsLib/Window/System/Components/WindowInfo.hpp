#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>

#include <string>





namespace cg
{
	class WindowInfo
	{
	private:
		cpp::Vector2D<int> m_size;

		std::string m_title;

		bool m_fullScreen;
	public:
		WindowInfo() = default;
		WindowInfo(int width, int height, bool fullScreen, const std::string& title) noexcept;
		virtual ~WindowInfo() = default;

		[[nodiscard]] cpp::Vector2D<int> getSize() const noexcept;
		[[nodiscard]] int getWidth() const noexcept;
		[[nodiscard]] int getHeight() const noexcept;

		[[nodiscard]] std::string getTitle() const noexcept;

		bool fullScreen() const noexcept;
	};
}