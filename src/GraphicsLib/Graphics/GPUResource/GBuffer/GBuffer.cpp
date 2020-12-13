#include <GraphicsLib/Graphics/GPUResource/GBuffer/GBuffer.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>





namespace cg
{
	GBuffer::BufferDict GBuffer::createBufferDict(const std::vector<GBufferContent>& contents)
	{
		BufferDict bufferDict;
		for (auto content : contents)
		{
			if (bufferDict.count(content.name) == false)
			{
				bufferDict.emplace(std::make_pair(content.name, content.buffer));
			}
			else
			{
				Assert(false, "A buffer named \"%s\" already exists.\n", content.name.c_str());
			}
		}
		return bufferDict;
	}

	GBuffer::GBuffer(const std::vector<GBufferContent>& contents)
		: m_bufferDict(createBufferDict(contents))
	{
	}

	std::shared_ptr<ITexture2D> GBuffer::get(const std::string& name) const
	{
		if (exists(name) == false)
		{
			LogEX("A buffer named \"%s\" does not exist.", name.c_str());
			return nullptr;
		}

		return m_bufferDict.at(name);
	}

	bool GBuffer::exists(const std::string& name) const noexcept
	{
		return m_bufferDict.count(name) == 1;
	}

	GBuffer::GBufferContents GBuffer::getAllContents() const noexcept
	{
		GBufferContents contents;
		for (auto pair : m_bufferDict)
		{
			contents.emplace_back(GBufferContent(pair.first, pair.second));
		}
		return contents;
	}





	GBufferContent::GBufferContent(const std::string& name, std::shared_ptr<ITexture2D> buffer)
		: name(name),
		  buffer(buffer)
	{
	}
}
