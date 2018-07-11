#ifndef BYTE_CODE_VIEWER_HPP
#define BYTE_CODE_VIEWER_HPP
#include "ByteCodeReader.hpp"
#include <vector>
using byte = unsigned char;
using std::vector;
using ByteCode = vector<byte>;
class ByteCodeViewer
{
public:
	ByteCode code;
	int32_t mainModule;
	int32_t mainFunction;
	ByteCodeViewer(ByteCode code);
	void View();
	void ViewHeader(ByteCodeReader& reader);
	void ViewModule(ByteCodeReader& reader);
	void ViewClass(ByteCodeReader& reader);
	void ViewFunction(ByteCodeReader& reader);
	void ViewCode(ByteCodeReader& reader);
};
#endif // BYTE_CODE_VIEWER_HPP