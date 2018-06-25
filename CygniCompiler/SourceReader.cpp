#include "SourceReader.hpp"
#include "Exception.hpp"
SourceReader::SourceReader(string path)
	: line{1}
	, column{1}
	, stream(path)
{
	if (!stream)
	{
		throw FileNotFoundException();
	}
}
int32_t SourceReader::Peek()
{
	return stream.peek();
}
wchar_t SourceReader::Read()
{
	wchar_t c;
	stream.read(&c, 1);
	if (c == L'\n')
	{
		line++;
		column = 1;
	}
	else
	{
		column++;
	}
	return c;
}
bool SourceReader::IsEof()
{
	return Peek() == EOF;
}