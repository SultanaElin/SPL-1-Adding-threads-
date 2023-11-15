#include <iostream>
#include <windows.h>

DWORD WINAPI InputThread(LPVOID lpParam) {
    while (true) {
        std::cout << "Enter a key (q to quit): ";
        char input;
        std::cin >> input;

        if (input == 'q') {
            break; // Exit the thread when 'q' is pressed
        }

        std::cout << "\nYou pressed: " << input << std::endl;
    }

    return 0;
}

int main() {
    HANDLE inputThreadHandle;
    DWORD inputThreadId;

    // Create a thread for input handling
    inputThreadHandle = CreateThread(NULL, 0, InputThread, NULL, 0, &inputThreadId);

    if (inputThreadHandle == NULL) {
        std::cerr << "Error creating input thread." << std::endl;
        return 1;
    }

    // Wait for the input thread to finish (optional)
    WaitForSingleObject(inputThreadHandle, INFINITE);

    // Close the input thread handle
    CloseHandle(inputThreadHandle);

    std::cout << "Main thread continues..." << std::endl;

    return 0;
}
