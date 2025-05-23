#pragma once
#include <iostream>
#include <string>

//? Debug Functions (Logging)
#if defined(DEBUG)
template <typename ...Args>
inline void do_log(Args&& ...args) {
    (std::cout << ... << args) << std::endl;
}
#define LOG(...) do_log(__VA_ARGS__)
#else
#define LOG(...)
#endif

//? OS-reliant functions
// OpenFile Dialog
std::string mb_MacOpenFileDialog();
std::string mb_WindowsOpenFileDialog();

#if defined(__APPLE__)
    #define mb_OpenFileDialog mb_MacOpenFileDialog
#elif defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    #define mb_OpenFileDialog mb_WindowsOpenFileDialog
#else
    #error "Unsupported platform"
#endif

void ReadFile(std::string& path , std::string& file_text);