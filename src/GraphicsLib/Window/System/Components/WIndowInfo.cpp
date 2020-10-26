#include <GraphicsLib/Window/System/Components/WindowInfo.hpp>





namespace cg
{
	WindowInfo::WindowInfo(int width, int height, bool fullScreen, const std::string& title) noexcept
		: m_size({ width, height }),
		  m_fullScreen(fullScreen),
		  m_title(title)
	{
	}

	cpp::Vector2D<int> WindowInfo::getSize() const noexcept
	{
		return m_size;
	}

	int WindowInfo::getWidth() const noexcept
	{
		return m_size.x;
	}

	int WindowInfo::getHeight() const noexcept
	{
		return m_size.y;
	}

	float WindowInfo::calcAspect() const noexcept
	{
		return m_size.x/float(m_size.y);
	}

	std::string WindowInfo::getTitle() const noexcept
	{
		return m_title;
	}

	bool WindowInfo::fullScreen() const noexcept
	{
		return m_fullScreen;
	}
}
