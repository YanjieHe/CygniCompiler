#ifndef STRING_BUILDER_HPP
#define STRING_BUILDER_HPP
#include <string>
#include <vector>
using std::vector;
using std::wstring;
class StringBuilder
{
public:
	void Append(wchar_t c);
	void AppendStr(wstring s);
	void Clear();
	wstring ToString();

private:
	vector<wchar_t> characters;
};

inline void StringBuilder::Append(wchar_t c)
{
	characters.push_back(c);
}
inline void StringBuilder::Clear()
{
	characters.clear();
}
inline wstring StringBuilder::ToString()
{
	return wstring(characters.begin(), characters.end());
}
inline void StringBuilder::AppendStr(wstring s)
{
	characters.insert(characters.end(), s.begin(), s.end());
}
#endif // STRING_BUILDER_HPP