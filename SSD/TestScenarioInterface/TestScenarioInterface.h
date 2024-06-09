#pragma once

#ifdef TESTAPP_EXPORT
#define TESTAPP_DECLSPEC __declspec(dllexport)
#else
#define TESTAPP_DECLSPEC __declspec(dllimport)
#endif

class testApp {
public:
	void execute();
};

extern "C" {
	TESTAPP_DECLSPEC void Run();
}