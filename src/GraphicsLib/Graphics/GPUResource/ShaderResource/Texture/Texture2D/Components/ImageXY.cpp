#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/ImageXY.hpp>





namespace cg
{
    ImageXY::Pixel ImageXY::get(int x, int y) const
    {
        return m_pixels.at(x).at(y);
    }
    cpp::Vector2D<int> ImageXY::getSize() const
    {
        return m_size;
    }
}
