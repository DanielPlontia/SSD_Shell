#pragma once
#define interface struct

interface TestScenarioInterface {
public:
	virtual bool execute() = 0;
};
