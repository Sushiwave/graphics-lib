#include "D3D11Texture2D.hpp"
#include <iterator>





namespace cg
{
    namespace d3d11
    {
        Texture2D::Texture2D(const std::string& filename, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, bool forceSRGB)
            : m_texture(filename, cpuAccessType, gpuAccessType, forceSRGB)
        {
        }
        Texture2D::Texture2D(int width, int height, TextureFormat format, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, ImageXY* pImage)
            : m_texture(width, height, format, cpuAccessType, gpuAccessType, pImage)
        {
        }
        Texture2D::Texture2D(int width, int height, TextureFormat format, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage)
            : m_texture(width, height, format, cpuAccessType, gpuAccessType, mostDetailedMipLevel, mostRoughedMipLevel, pImage)
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

        void Texture2D::set(ShaderStage stage, int unit, GPUAccessType usage)
        {
            std::shared_ptr<IShaderResourceMemoryAccessor> accessor;

            switch (usage)
            {
            case GPUAccessType::R:
                accessor = m_texture.getSRV();
                break;
            case GPUAccessType::RW:
                accessor = m_texture.getUAV();
                break;
            default:
                break;
            }

            Assert(accessor, "This resource does not support write operations from the GPU.");
            accessor->set(stage, unit, getID());
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
