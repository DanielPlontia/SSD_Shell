#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include "libloaderapi.h"
#include "TestScenarioFactory.h"

LPCWSTR StringToLPCWSTR(const std::string& str) {
    int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (length == 0) {
        std::cerr << "MultiByteToWideChar failed." << std::endl;
        return nullptr;
    }

    wchar_t* buffer = new wchar_t[length];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, length);

    return buffer;
}

typedef void (WINAPI* PGNSI)();

void TestScenario::run(std::string scenario) {
    std::string dllName = scenario + ".dll";
    HINSTANCE hDLL; // Handle to DLL
    PGNSI pGNSI;
    hDLL = LoadLibrary(StringToLPCWSTR(dllName));
    if(hDLL == NULL) {
        std::cerr << "DLL을 로드할 수 없습니다." << std::endl;
        return;
    }

    pGNSI = (PGNSI)GetProcAddress(hDLL, "Run");
    if (NULL != pGNSI)
    {
        pGNSI();
    }
 
    FreeLibrary(hDLL); // DLL 언로드

    return;
};
