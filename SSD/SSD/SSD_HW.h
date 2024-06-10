#pragma once
#define interface struct


interface SSD_HW{
public:
	SSD_HW() = default;
	virtual void read(int addr) = 0;
	virtual void write(int addr, unsigned int data) = 0;
	virtual ~SSD_HW() = default;
};
