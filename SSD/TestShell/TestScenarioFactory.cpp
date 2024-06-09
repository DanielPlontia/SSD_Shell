#pragma once
#include "../TestScenarioInterface/TestScenarioInterface.h"
#pragma comment (lib, "../x64/Debug/TestScenarioInterface.lib")
#include <string>
#include <iostream>
#include <windows.h>
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


void TestScenario::run(std::string scenario) {
    std::string dllName = scenario + ".dll";
    HINSTANCE hDLL = LoadLibrary(StringToLPCWSTR(dllName));
    if (hDLL == NULL) {
        std::cerr << "DLL�� �ε��� �� �����ϴ�." << std::endl;
        return;
    }

    Run();

    // DLL ��ε�
    FreeLibrary(hDLL);

    return;
};
