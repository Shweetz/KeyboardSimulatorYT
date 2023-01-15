// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

DWORD WINAPI HackThread(HMODULE hModule)
{
#ifdef _DEBUG
    // Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Yo\n";
#endif

    while (true) {
        if (GetAsyncKeyState(VK_NUMPAD0)) {
            break;
        }
        if (GetAsyncKeyState(VK_NUMPAD1)) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VkKeyScan('w');
            SendInput(1, &input, sizeof(input));
        }
        if (GetAsyncKeyState(VK_NUMPAD2)) {
            SHORT key = VkKeyScan('s');

            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.dwFlags = KEYEVENTF_SCANCODE;
            input.ki.wScan = MapVirtualKey(LOBYTE(key), 0);
            SendInput(1, &input, sizeof(input));
            Sleep(10);

            input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(input));
        }
    }

#ifdef _DEBUG
    fclose(f);
    FreeConsole();
#endif
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

