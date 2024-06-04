#pragma once
#define interface struct

interface SSD_HW{
public:
	virtual void write(int addr, unsigned int data) = 0;
	virtual void read(int addr) = 0;
};
