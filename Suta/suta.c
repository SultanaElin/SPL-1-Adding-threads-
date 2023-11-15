#include <stdio.h>
#include <windows.h>

DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
    int threadID = *(int*)lpParam;

    for (int i = 1; i <= 10; i++) {
        printf("Thread %d: Count %d\n", threadID, i);
        Sleep(1000); // Sleep for 1 second
    }

    return 0;
}

int main() {
    HANDLE hThread;
    DWORD threadId;

    int threadData = 1; // You can pass any data to the thread using a pointer

    // Create a thread
    hThread = CreateThread(NULL, 0, MyThreadFunction, &threadData, 0, &threadId);

    if (hThread == NULL) {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }

    printf("Thread created with ID: %d\n", threadId);

    // Wait for the thread to finish
    WaitForSingleObject(hThread, INFINITE);

    // Check if the thread is still active
    DWORD exitCode;
    GetExitCodeThread(hThread, &exitCode);

    if (exitCode == STILL_ACTIVE) {
        printf("Thread is still active.\n");
    } else {
        printf("Thread has finished with exit code: %d\n", exitCode);
    }

    // Close the thread handle
    CloseHandle(hThread);

    printf("Main thread continues...\n");

    return 0;
}
