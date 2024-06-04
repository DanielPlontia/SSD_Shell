#pragma once
#define interface struct

interface SSD_HW{
public:
	virtual void sector() = 0;
	virtual void writeNandFile() = 0;
	virtual void writeResultFile() = 0;
	virtual void readNandFile() = 0;
};
