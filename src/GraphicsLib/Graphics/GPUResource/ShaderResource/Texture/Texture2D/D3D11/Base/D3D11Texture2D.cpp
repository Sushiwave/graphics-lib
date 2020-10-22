#include "D3D11Texture2D.hpp"
#include <iterator>





namespace cg
{
    namespace d3d11
    {
        Texture2D::Texture2D(const std::string& filename, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool forceSRGB)
            : m_texture(filename, cpuAccessFlags, gpuAccessFlags, forceSRGB)
        {
        }
        Texture2D::Texture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, ImageXY* pImage)
            : m_texture(width, height, format, cpuAccessFlags, gpuAccessFlags, pImage)
        {
        }
        Texture2D::Texture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage)
            : m_texture(width, height, format, cpuAccessFlags, gpuAccessFlags, mostDetailedMipLevel, mostRoughedMipLevel, pImage)
        {
        }
        Texture2D::Texture2D(const RawTexture2D& rawTexture)
            : m_texture(rawTexture)
        {
        }
        int Texture2D::getMostDetailedMipLevel() const
        {
            return m_texture.getMostDetailedMipLevel();
        }

        int Texture2D::getMostRoughedMipLevel() const
        {
            return m_texture.getMostRoughedMipLevel();
        }

        cpp::Vector2D<int> Texture2D::getSize() const
        {
            return m_texture.getSize();
        }

        void Texture2D::generateMipMaps()
        {
            m_texture.generateMipMaps();
        }

        bool Texture2D::isResolvedTexture() const
        {
            return m_texture.isResolvedTexture();
        }

        void Texture2D::saveTo(const std::string& filename, ImageFileFormat format)
        {
            m_texture.saveTo(filename, format);
        }

        void Texture2D::set(ShaderStage stage, int unit, GPUAccessFlags usage)
        {
            std::shared_ptr<IShaderResourceMemoryAccessor> accessor;

            switch (usage)
            {
            case GPUAccessFlags::R:
                accessor = m_texture.getSRV();
                break;
            case GPUAccessFlags::RW:
                accessor = m_texture.getUAV();
                break;
            default:
                break;
            }

            Assert(accessor, "This resource does not support write operations from the GPU.");
            accessor->set(stage, unit);
        }

        BoundedBufferLocationList Texture2D::getBoundedBufferLocationList() const
        {
            auto locationList = m_texture.getSRV()->getManagedShaderResourceBufferLocationList();
            if (m_texture.getUAV())
            {
                auto UAVLocationList = m_texture.getUAV()->getManagedShaderResourceBufferLocationList();
                std::copy(locationList.begin(), locationList.end(), std::back_inserter(UAVLocationList));
            }
            return locationList;
        }
        RawTexture2D Texture2D::getRawTexture() const
        {
            return m_texture;
        }
    }
}
