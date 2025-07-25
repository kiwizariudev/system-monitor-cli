#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

float getMemoryUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG total = memInfo.ullTotalPhys;
    DWORDLONG free = memInfo.ullAvailPhys;
    return 100.0f * (1.0f - (float)free / (float)total);
}

float getCPUUsage() {
    static FILETIME prevIdle, prevKernel, prevUser;
    FILETIME idle, kernel, user;

    GetSystemTimes(&idle, &kernel, &user);

    ULARGE_INTEGER idleDiff, kernelDiff, userDiff;
    ULARGE_INTEGER prevIdle64, prevKernel64, prevUser64;
    ULARGE_INTEGER idle64, kernel64, user64;

    memcpy(&idle64, &idle, sizeof(FILETIME));
    memcpy(&kernel64, &kernel, sizeof(FILETIME));
    memcpy(&user64, &user, sizeof(FILETIME));

    memcpy(&prevIdle64, &prevIdle, sizeof(FILETIME));
    memcpy(&prevKernel64, &prevKernel, sizeof(FILETIME));
    memcpy(&prevUser64, &prevUser, sizeof(FILETIME));

    idleDiff.QuadPart = idle64.QuadPart - prevIdle64.QuadPart;
    kernelDiff.QuadPart = kernel64.QuadPart - prevKernel64.QuadPart;
    userDiff.QuadPart = user64.QuadPart - prevUser64.QuadPart;

    prevIdle = idle;
    prevKernel = kernel;
    prevUser = user;

    ULONGLONG total = kernelDiff.QuadPart + userDiff.QuadPart;
    if (total == 0) return 0.0f;

    float cpu = (float)(total - idleDiff.QuadPart) * 100.0f / total;
    return cpu;
}

int main() {
    getCPUUsage();
    Sleep(1000);
    json stats;
    stats["cpu"] = getCPUUsage();
    stats["ram"] = getMemoryUsage();
    std::cout << stats.dump() << std::endl;
    return 0;
}
