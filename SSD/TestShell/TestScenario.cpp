#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <stdexcept>
#include "libloaderapi.h"
#include "TestScenario.h"

typedef bool (WINAPI* DllFunction)();

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
    std::string dll_name = scenario + ".dll";
    HINSTANCE dll_handle; // Handle to DLL
    DllFunction dll_function;
    bool dll_return_value = false;

    dll_handle = LoadLibrary(StringToLPCWSTR(dll_name));
    if(dll_handle == NULL) {
        std::cerr << "DLL을 로드할 수 없습니다." << std::endl;
        throw std::runtime_error("Scenario Test Fail");
        return;
    }

    dll_function = (DllFunction)GetProcAddress(dll_handle, "Run");
    if (NULL != dll_function)
    {
        dll_return_value = dll_function();
    }
 
    FreeLibrary(dll_handle); // DLL 언로드

    if (dll_return_value == false)
        throw std::runtime_error("Scenario Test Fail");

    return;
};
