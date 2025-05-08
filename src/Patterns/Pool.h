#pragma once
#include <vector>

template <typename T>
class Pool
{
public:
	Pool(size_t poolSize = 30);
	~Pool();
	void* Allocate();
	void Deallocate(void* ptr);
private:

};