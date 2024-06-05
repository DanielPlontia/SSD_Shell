#pragma once
#define interface struct

interface SSD_HW{
public:
	virtual void read(int addr) = 0;
	virtual void write(int addr, unsigned int data) = 0;
	virtual ~SSD_HW() { };
};
