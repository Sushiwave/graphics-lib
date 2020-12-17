#pragma once
#include <CPPLib/C++/SFINAE.hpp>
#include <CPPLib/Log/Log.hpp>

#include <list>
#include <fstream>
#include <string>
#include <functional>



namespace cpp
{
	enum class eOpenmode
	{
		none = -1,
		in = std::ios::in,
		out = std::ios::out,
		ate = std::ios::ate,
		app = std::ios::app,
		trunc = std::ios::trunc,
		binary = std::ios::binary,
	};

	enum class eSeekDir
	{
		none = -1,
		begin = std::ios_base::beg,
		current = std::ios_base::cur,
		end = std::ios_base::end,
	};

	class SeekDir
	{
	private:
		eSeekDir m_eSeekDir;
	public:
		SeekDir(eSeekDir eSeekDir_);

		void clear();
		[[nodiscard]] eSeekDir getEnum() const;
		[[nodiscard]] std::ios_base::seekdir getSysSeekDir() const;
	};

	class Openmode
	{
	public:
		using EnumList = std::list<eOpenmode>;
	private:
		EnumList m_openmodeList;
	protected:
		Openmode& in();
		Openmode& out();
	public:
		Openmode& ate();
		Openmode& app();
		Openmode& trunc();
		Openmode& binary();

		void clear();
		[[nodiscard]] EnumList getEnumList() const;
		[[nodiscard]] std::ios_base::openmode getSysOpenmode() const;
	};

	class OpenmodeInput
		: public Openmode
	{
	public:
		OpenmodeInput() noexcept;
		virtual ~OpenmodeInput() = default;
	};
	class OpenmodeOutput
		: public Openmode
	{
	public:
		OpenmodeOutput() noexcept;
		virtual ~OpenmodeOutput() = default;
	};

	template <typename STDFStream_>
	class FileStream
	{
	private:
		template <typename T>
		using SFINAE_ifstream = SFINAE_is_same<T, std::ifstream>;
		template <typename T>
		using SFINAE_ofstream = SFINAE_is_same<T, std::ofstream>;
	public:
		using PositionGetter = std::function<std::streampos(STDFStream_&)>;
	private:
		Openmode m_openmode;
		std::string m_filename;
	    PositionGetter m_getPosition;
	protected:
		STDFStream_ m_fileStream;
	public:
		FileStream() = default;
		FileStream(const std::string& filename, Openmode openmode, const PositionGetter& positionGetter)
			: m_getPosition(positionGetter)
		{
			open(filename, openmode);
		}
		virtual ~FileStream() = default;

		void open(const std::string& filename, Openmode openmode)
		{
			m_fileStream.open(filename, openmode.getSysOpenmode());
			if (m_fileStream.is_open())
			{
				m_openmode = openmode;
				m_filename = filename;
			}
		}
		void close()
		{
			if (isOpened())
			{
				m_openmode.clear();
				m_filename.clear();
				m_fileStream.close();
			}
			else
			{
				LogEX("The file stream is already closed.");
			}
		}

		[[nodiscard]] std::streampos getPosition()
		{
			return m_getPosition(m_fileStream);
		}
		template <typename T = STDFStream_>
		void moveTo(const typename STDFStream_::pos_type& position, SFINAE_ifstream<T> = nullptr)
		{
			m_fileStream.seekg(position);
		}
		template <typename T = STDFStream_>
		void moveTo(const typename STDFStream_::pos_type& position, SFINAE_ofstream<T> = nullptr)
		{
			m_fileStream.seekp(position);
		}
		template <typename T = STDFStream_>
		void moveTo(const typename STDFStream_::off_type& offset, SeekDir seekDir, SFINAE_ifstream<T> = nullptr)
		{
			m_fileStream.seekg(offset, seekDir.getSysSeekDir());
		}
		template <typename T = STDFStream_>
		void moveTo(const typename STDFStream_::off_type& offset, SeekDir seekDir, SFINAE_ofstream<T> = nullptr)
		{
			m_fileStream.seekp(offset, seekDir.getSysSeekDir());
		}
		void removeEOFFlag()
		{
			m_fileStream.clear();
		}

		[[nodiscard]] bool isEOF() const
		{
			return m_fileStream.eof();
		}
		[[nodiscard]] bool isFailed() const
		{
			return m_fileStream.fail() || m_fileStream.bad();
		}
		[[nodiscard]] bool isOpened() const
		{
			return !m_filename.empty();
		}
		[[nodiscard]] Openmode::EnumList getOpenmodeList() const
		{
			return m_openmode.getOpenmodeList();
		}
		[[nodiscard]] std::string getFilename() const noexcept
		{
			return m_filename;
		}
	};

	class FileStreamInput
		: public FileStream<std::ifstream>
	{
	private:
		static const OpenmodeInput defaultOpenmode;
	public:
		FileStreamInput(const std::string& filename, OpenmodeInput openmode = defaultOpenmode);
		virtual ~FileStreamInput() = default;

		template <typename T>
		FileStreamInput& operator>>(T& val)
		{
			m_fileStream >> val;
			return *this;
		}

		void getLine(std::string& line);
		void getCharacter(char& chara);
		void read(std::string& data, unsigned int length);
		void readAll(std::string& all);
	};

	class FileStreamOutput
		: public FileStream<std::ofstream>
	{
	private:
		static const OpenmodeOutput defaultOpenmode;
	public:
		FileStreamOutput(const std::string& filename, OpenmodeOutput openmode = defaultOpenmode);
		virtual ~FileStreamOutput() = default;

		template <typename T>
		FileStreamInput& operator<<(const T& val)
		{
			m_fileStream << val;
			return *this;
		}

		void write(const std::string& data);
	};
}
