#ifndef BYTE_CODE_READER_HPP
#define BYTE_CODE_READER_HPP
#include <cstdint>
#include <string>
#include <vector>
typedef unsigned char byte;
typedef std::vector<byte> ByteCode;
using std::wstring;
class ByteCodeReader
{
public:
	ByteCode byteCode;
	int32_t index;
	ByteCodeReader(ByteCode byteCode);
	bool IsEof();
	int32_t Read();
	int32_t Peek();
	int32_t ReadUShort();
	int32_t ReadInt();
	int64_t ReadLong();
	float ReadFloat();
	double ReadDouble();
	wstring ReadString();
};
#endif // BYTE_CODE_READER_HPP