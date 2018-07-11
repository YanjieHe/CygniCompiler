#ifndef BYTE_CODE_READER_HPP
#define BYTE_CODE_READER_HPP
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
typedef unsigned char byte;
typedef std::vector<byte> ByteCode;
using std::ifstream;
using std::ofstream;
using std::string;
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

ByteCode ReadBytes(string path);
void WriteBytes(string path, ByteCode& code);
#endif // BYTE_CODE_READER_HPP