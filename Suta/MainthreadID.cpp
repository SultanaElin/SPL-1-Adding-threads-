//How to print mainThread ID
#include<windows.h>
#include<iostream>
using namespace std;
//A Process is in inert
//A process is a container of threads
//Every process must have one thread at least to start the execution
//The only thread(if it is only thread in process ) is main thread

/*The thread itself inside a program is not a kernel object but 
there is an associated kernel object through which this thread is managed*/
 
int main(){
  //Main thread Id will change every time I run the code
  //Reason-There are several processes that are running at the same time  
    cout<<endl<<"Main Thread ID:"<< GetCurrentThreadId();

return 0;
} 