// KeyboardSimulatorYT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

int main()
{
    while (true) {
        if (GetAsyncKeyState(VK_NUMPAD0)) {
            return 0;
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
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
