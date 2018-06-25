#ifndef SOURCE_READER_HPP
#define SOURCE_READER_HPP
#include <cstdint>
#include <fstream>
#include <string>
using std::string;
using std::wifstream;
class SourceReader
{
public:
	int32_t line;
	int32_t column;
	wifstream stream;
	SourceReader(string path);
	int32_t Peek();
	wchar_t Read();
	bool IsEof();
};
#endif // SOURCE_READER_HPP