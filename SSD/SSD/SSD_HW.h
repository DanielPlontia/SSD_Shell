#pragma once
#define interface struct

#ifdef DEBUG
#pragma comment (lib, "../x64/Debug/logger.lib")
#else
#pragma comment (lib, "../x64/Release/logger.lib")
#endif // DEBUG


interface SSD_HW{
public:
	SSD_HW() = default;
	virtual void read(int addr) = 0;
	virtual void write(int addr, unsigned int data) = 0;
	virtual ~SSD_HW() = default;
};
