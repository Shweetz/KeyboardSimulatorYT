// DLLInjector.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <TlHelp32.h>

#define EXE_NAME L"ManiaPlanet32.exe"

#define DLL_PATH "KeyboardSimulatorDLL.dll"

/**
 * Get a process ID in Windows from the name of its exe
 */
DWORD GetProcID(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        while (Process32Next(snapshot, &entry))
        {
            //MessageBoxA(NULL, std::to_string(procId).c_str(), "", MB_ICONEXCLAMATION);
            if (!wcscmp(entry.szExeFile, procName))
            {
                //MessageBox(NULL, entry.szExeFile, L"", MB_ICONEXCLAMATION);
                procId = entry.th32ProcessID;
                break;
            }
        }
    }
    CloseHandle(snapshot);
    return procId;
}

int main()
{
    /**************************************** INJECT DLL IN RUNNING GAME **************************************/
    //MessageBox(NULL, L"procId " TM2_EXE_PATH, L"", MB_ICONEXCLAMATION);

    // Find dllPath
    //const char* dllpath = "C:\\Users\\rmnlm\\Documents\\GitHub\\Canyon\\CanyonDLL\\Debug\\CanyonDLL.dll";
    WCHAR path[MAX_PATH];
    if (!GetModuleFileNameW(NULL, path, MAX_PATH)) {
        return false;
    }
    std::filesystem::path dll_path = path;
    dll_path.remove_filename() /= DLL_PATH;
    std::string dllPath(dll_path.string());

    // Find game process
    DWORD procId = GetProcID(EXE_NAME);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    // Write dll in the game process and create a thread to run it
    if (hProcess && hProcess != INVALID_HANDLE_VALUE)
    {
        LPVOID dllAddr = VirtualAllocEx(hProcess, NULL, dllPath.size(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (!dllAddr) { return false; }

        WriteProcessMemory(hProcess, dllAddr, dllPath.c_str(), dllPath.size(), 0);

        HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, dllAddr, 0, 0);

        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    if (hProcess)
    {
        CloseHandle(hProcess);
    }
}
