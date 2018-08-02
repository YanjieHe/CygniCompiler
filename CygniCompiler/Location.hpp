#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <cstdint>
class Location
{
public:
	int32_t index;
	int32_t offset;
	Location();
	Location(int32_t index, int32_t offset);
	bool IsLocal();
	Location static Local(int32_t offset);
};
#endif // LOCATION_HPP