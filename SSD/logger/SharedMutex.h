#pragma once

#include <iostream>
#include <windows.h>

class SharedMutex {
public:
    SharedMutex(const char* name) {
        mutex = CreateMutex(NULL, FALSE, AnsiToUnicode(name));
        if (mutex == NULL) {
            std::cerr << "Failed to create mutex." << std::endl;
        }
    }

    ~SharedMutex() {
        CloseHandle(mutex);
    }

    void lock() {
        WaitForSingleObject(mutex, INFINITE);
    }

    void unlock() {
        ReleaseMutex(mutex);
    }
private:
    HANDLE mutex;
    LPCWSTR AnsiToUnicode(const char* str)
    {
        int size = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
        if (size == 0) {
            std::cerr << "Error calculating size for conversion." << std::endl;
            return NULL;
        }

        wchar_t* buffer = new wchar_t[size];

        MultiByteToWideChar(CP_ACP, 0, str, -1, buffer, size);

        return buffer;
    }
};
