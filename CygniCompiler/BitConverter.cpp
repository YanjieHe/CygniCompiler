#include "BitConverter.hpp"
void BitConverter::AppendBytes(vector<byte>& bytes, byte* pointer,
							   int32_t length)
{
	for (int32_t i = 0; i < length; i++)
	{
		bytes.push_back(pointer[i]);
	}
}
void BitConverter::AppendUShort(vector<byte>& bytes, uint16_t value)
{
	AppendBytes(bytes, (byte*) &value, sizeof(uint16_t));
}
void BitConverter::AppendInt(vector<byte>& bytes, int32_t value)
{
	AppendBytes(bytes, (byte*) &value, sizeof(int32_t));
}
void BitConverter::AppendLong(vector<byte>& bytes, int64_t value)
{
	AppendBytes(bytes, (byte*) &value, sizeof(int64_t));
}
void BitConverter::AppendFloat(vector<byte>& bytes, float value)
{
	AppendBytes(bytes, (byte*) &value, sizeof(float));
}
void BitConverter::AppendDouble(vector<byte>& bytes, double value)
{
	AppendBytes(bytes, (byte*) &value, sizeof(double));
}
void BitConverter::AppendString(vector<byte>& bytes, wstring text)
{
	int32_t n = text.size();
	AppendInt(bytes, n);
	for (int32_t i = 0; i < n; i++)
	{
		int32_t character = text[i];
		AppendInt(bytes, character);
	}
}