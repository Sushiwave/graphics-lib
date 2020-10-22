#include <ThirdParty/CPPLib/File/FileStream.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>





namespace cpp
{
	const OpenmodeInput FileStreamInput::defaultOpenmode;
	const OpenmodeOutput FileStreamOutput::defaultOpenmode;





	Openmode& Openmode::in()
	{
		m_openmodeList.emplace_back(eOpenmode::in);
		return *this;
	}
	Openmode& Openmode::out()
	{
		m_openmodeList.emplace_back(eOpenmode::out);
		return *this;
	}
	Openmode& Openmode::ate()
	{
		m_openmodeList.emplace_back(eOpenmode::ate);
		return *this;
	}
	Openmode& Openmode::app()
	{
		m_openmodeList.emplace_back(eOpenmode::app);
		return *this;
	}
	Openmode& Openmode::trunc()
	{
		m_openmodeList.emplace_back(eOpenmode::trunc);
		return *this;
	}
	Openmode& Openmode::binary()
	{
		m_openmodeList.emplace_back(eOpenmode::binary);
		return *this;
	}
	void Openmode::clear()
	{
		m_openmodeList.clear();
	}
	Openmode::EnumList Openmode::getEnumList() const
	{
		return m_openmodeList;
	}
	std::ios_base::openmode Openmode::getSysOpenmode() const
	{
		std::ios_base::openmode sysOpenmode = 0x00;
		for (auto openmode : m_openmodeList)
		{
			sysOpenmode |= static_cast<std::ios_base::openmode>(openmode);
		}
		return sysOpenmode;
	}

	FileStreamInput::FileStreamInput(const std::string& filename, OpenmodeInput openmode)
		: FileStream<std::ifstream>(filename, openmode, [](std::ifstream& fs)->std::streampos{ return fs.tellg(); })
	{
	}
	void FileStreamInput::getLine(std::string& line)
	{
		std::getline(m_fileStream, line);
	}
	void FileStreamInput::getCharacter(char& chara)
	{
		m_fileStream.get(chara);
	}

	void FileStreamInput::read(std::string& string, unsigned int length)
	{
		if (length > 0)
		{
			string.resize(length);
			m_fileStream.read(&string[0], sizeof(char) * length);
		}
	}

	void FileStreamInput::readAll(std::string& all)
	{
		int begin = static_cast<int>(m_fileStream.tellg());
		m_fileStream.seekg(0, m_fileStream.end);
		int end = static_cast<int>(m_fileStream.tellg());
		int length = end - begin;
		m_fileStream.clear();
		m_fileStream.seekg(0, m_fileStream.beg);
		read(all, length);
	}

	FileStreamOutput::FileStreamOutput(const std::string& filename, OpenmodeOutput openmode)
		: FileStream<std::ofstream>(filename, openmode, [](std::ofstream& fs)->std::streampos{ return fs.tellp(); })
	{
	}

	void FileStreamOutput::write(const std::string& data)
	{
		m_fileStream.write(data.c_str(), sizeof(char) * data.size());
	}

	OpenmodeInput::OpenmodeInput() noexcept
	{
		in();
	}
	OpenmodeOutput::OpenmodeOutput() noexcept
	{
		out();
	}
	SeekDir::SeekDir(eSeekDir eSeekDir_)
		: m_eSeekDir(eSeekDir_)
	{
	}

	void SeekDir::clear()
	{
		m_eSeekDir = eSeekDir::none;
	}
	eSeekDir SeekDir::getEnum() const
	{
		return m_eSeekDir;
	}
	std::ios_base::seekdir SeekDir::getSysSeekDir() const
	{
		return static_cast<std::ios_base::seekdir>(m_eSeekDir);
	}
}
