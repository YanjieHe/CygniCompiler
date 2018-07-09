#include "ByteCodeReader.hpp"
ByteCodeReader::ByteCodeReader(ByteCode byteCode)
	: byteCode{byteCode}
	, index{0}
{
}
bool ByteCodeReader::IsEof()
{
	int32_t n = byteCode.size();
	return index >= n;
}
int32_t ByteCodeReader::Read()
{
	if (IsEof())
	{
		return (-1);
	}
	else
	{
		int32_t b = byteCode[index];
		index++;
		return b;
	}
}
int32_t ByteCodeReader::Peek()
{
	if (IsEof())
	{
		return (-1);
	}
	else
	{
		return byteCode[index];
	}
}
int32_t ByteCodeReader::ReadUShort()
{
	int32_t a = byteCode[index];
	int32_t b = byteCode[index + 1];
	index += 2;
	return (b << 8) + a;
}
int32_t ByteCodeReader::ReadInt()
{
	int32_t a = byteCode[index];
	int32_t b = byteCode[index + 1];
	int32_t c = byteCode[index + 2];
	int32_t d = byteCode[index + 3];
	index += 4;
	return (d << 24) + (c << 16) + (b << 8) + a;
}
int64_t ByteCodeReader::ReadLong()
{
	int64_t a = byteCode[index];
	int64_t b = byteCode[index + 1];
	int64_t c = byteCode[index + 2];
	int64_t d = byteCode[index + 3];
	int64_t e = byteCode[index + 4];
	int64_t f = byteCode[index + 5];
	int64_t g = byteCode[index + 6];
	int64_t h = byteCode[index + 7];
	index += 8;
	return (h << 56) + (g << 48) + (f << 40) + (e << 32) + (d << 24) +
		   (c << 16) + (b << 8) + a;
}
float ByteCodeReader::ReadFloat()
{
	union {
		float float_v;
		int32_t int_v;
	} u;
	int32_t value = ReadInt();
	u.int_v = value;
	index += 4;
	return u.float_v;
}
double ByteCodeReader::ReadDouble()
{
	union {
		double double_v;
		int64_t long_v;
	} u;
	int64_t value = ReadLong();
	u.long_v = value;
	index += 8;
	return u.double_v;
}
wstring ByteCodeReader::ReadString()
{
	using std::vector;
	int32_t length = ReadInt();
	vector<wchar_t> characters(length);
	for (int i = 0; i < length; i++)
	{
		characters[i] = ReadInt();
	}
	index += 4;
	index += (length * 4);
	return wstring(characters.begin(), characters.end());
}