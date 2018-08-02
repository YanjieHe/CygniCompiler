#ifndef BIT_CONVERTER_HPP
#define BIT_CONVERTER_HPP
#include <cstdint>
#include <string>
#include <vector>
using byte = unsigned char;
using std::vector;
using std::wstring;
namespace BitConverter
{
void AppendBytes(vector<byte>& bytes, byte* pointer, int32_t length);
void AppendUShort(vector<byte>& bytes, uint16_t value);
void AppendInt(vector<byte>& bytes, int32_t value);
void AppendLong(vector<byte>& bytes, int64_t value);
void AppendFloat(vector<byte>& bytes, float value);
void AppendDouble(vector<byte>& bytes, double value);
void AppendString(vector<byte>& bytes, wstring text);
};	 // namespace BitConverter
#endif // BIT_CONVERTER_HPP