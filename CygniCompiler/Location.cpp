#include "Location.hpp"
Location::Location()
	: index{-1}
	, offset{-1}
{
}
Location::Location(int32_t index, int32_t offset)
	: index{index}
	, offset{offset}
{
}
bool Location::IsLocal()
{
	return index == -1;
}
Location Location::Local(int32_t offset)
{
	return Location(-1, offset);
}