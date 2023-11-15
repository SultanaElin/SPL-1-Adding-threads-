#include <windows.h>
#include <thread>
#include <queue>

using namespace std;

class KeystrokeListener : public thread {
public:
    KeystrokeListener(queue<DWORD>& queue) : queue(queue) {}

    void run() {
        while (true) {
            DWORD keystroke;
            if (GetKeyboardState(&keystroke)) {
                queue.push(keystroke);
            }
            Sleep(10);
        }
    }

private:
    queue<DWORD>& queue;
};

class KeystrokeProcessor : public thread {
public:
    KeystrokeProcessor(queue<DWORD>& queue) : queue(queue) {}

    void run() {
        while (true) {
            DWORD keystroke;
            if (queue.try_pop(keystroke)) {
                // Process the keystroke here
                cout << "Keystroke: " << keystroke << endl;
            }
        }
    }

private:
    queue<DWORD>& queue;
};

int main() {
    queue<DWORD> queue;

    KeystrokeListener listener(queue);
    KeystrokeProcessor processor(queue);

    listener.start();
    processor.start();

    // Wait for the threads to finish
    listener.join();
    processor.join();

    return 0;
}
