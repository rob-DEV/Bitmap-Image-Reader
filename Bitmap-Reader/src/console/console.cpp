#include "console.h"

const std::string CurrentDateTime()
	{
		time_t     now = time(NULL);
		struct tm  tstruct;
		char       buf[80];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}

const std::string Console::m_sFileName = "ApplicationLog.txt";
Console* Console::m_pThis = NULL;
std::ofstream Console::m_Logfile;

Console::Console()
{
}


struct Console::console_deleter
{
	void operator()(const Console* const p)
	{
		std::cout << "Console deleter" << std::endl;
		delete p;
	}
};

Console& Console::GetConsole()
{
	if (m_pThis == NULL)
	{
		m_pThis = new Console();
	}
	static std::unique_ptr<Console, console_deleter> instance(m_pThis);
	return *instance;
}

void Console::Log()
{
	std::cout << "\r\n" << std::endl;
}

void Console::Log(const std::string& sMessage)
{
	std::cout << sMessage << std::endl;
}

void Console::Log(const char * format, ...)
{
	char* sMessage = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	nLength = _vscprintf(format, args) + 1;
	sMessage = new char[nLength];
	vsprintf_s(sMessage, nLength, format, args);
	//vsprintf(sMessage, format, args);
	std::cout << sMessage << "\n";
	va_end(args);

	delete[] sMessage;
}


void Console::Log(float f)
{
	std::cout << f << std::endl;
}

void Console::Log(int i)
{
	std::cout << i << std::endl;
}

void Console::Log(bool b)
{
	std::cout << b << std::endl;
}

void Console::LogAndFile(const std::string& sMessage)
{
	if(!m_Logfile)
		m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
	std::cout << CurrentDateTime() << ":\t" << sMessage << "\n";

	m_Logfile << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
}

void Console::LogAndFile(const char * format, ...)
{
	if (!m_Logfile)
		m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);

	char* sMessage = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	nLength = _vscprintf(format, args) + 1;
	sMessage = new char[nLength];
	vsprintf_s(sMessage, nLength, format, args);
	//vsprintf(sMessage, format, args);
	std::cout << CurrentDateTime() << ":\t" << sMessage << "\n";
	m_Logfile << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
	va_end(args);

	delete[] sMessage;
}

int Console::Pause()
{
	return std::cin.get();
}

Console& Console::operator<<(const std::string& sMessage)
{
	m_Logfile << "\n" << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
	return *this;
}
