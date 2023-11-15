//Suta with Synchronization using Critical Secton

//Suta-4

#include<iostream>
#include<windows.h>
using namespace std;

//If you don't want one thread to wait for another thread but want to check availablity(Time fact)

// HANDLE: it is the index of the kernel object used by your process/program in execution

//Critical Section : Create two threads and synchronize them using critical section
   HANDLE threadReader;
   HANDLE threadWriter;
   DWORD ReaderID;
   DWORD WriterID;

   CRITICAL_SECTION cs;

int a[10];

  void Reader(){

    //Avoid this part of code 

    BOOL su=TryEnterCriticalSection(&cs); 

      if( !su ) {
      
        cout<<endl<<"Not able to get critical section right now";

       }
      else {    
        cout<<endl<<"Reading Started.....";

          for(int i=0;i<10;i++){

              cout<<endl<<a[i];

          Sleep(1000);
   
        }
     
   LeaveCriticalSection(&cs);
    }
     EnterCriticalSection(&cs); 
       cout<<endl<<"Recursion no."<<cs.RecursionCount;
       cout<<endl<<"Spin no."<<cs.SpinCount;
     EnterCriticalSection(&cs);
       cout<<endl<<"Recursion no."<<cs.RecursionCount;
       cout<<endl<<"Spin no."<<cs.SpinCount;
     EnterCriticalSection(&cs);
       cout<<endl<<"Recursion no."<<cs.RecursionCount;
       cout<<endl<<"Spin no."<<cs.SpinCount;
        cout<<endl<<"Reading Started.....";

           for(int i=0;i<10;i++){

               cout<<endl<<a[i];

                Sleep(1000);
            }
    LeaveCriticalSection(&cs);
    LeaveCriticalSection(&cs);
    LeaveCriticalSection(&cs);
  }


  void Writer(){
   EnterCriticalSection(&cs); 
    for(int i=0;i<10;i++){
        cout<<endl<<"Writer writing:"<<endl;
         a[i]=(i+1)*2;
         Sleep(1000);
    }
     cout<<endl<<"Writing completed----";

     //ResumeThread(threadReader);

   LeaveCriticalSection(&cs);

  }

  int main(){

   //Implementing critical section
    InitializeCriticalSection(&cs);
    
    
     threadWriter=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Writer,NULL,0,&WriterID);
      cout<<endl<<"Thread Writer ID: "<<endl<<WriterID;  
        Sleep(500);
     threadReader=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Reader,NULL,0 ,&ReaderID);
      cout<<endl<<"Thread Reader ID: "<<endl<<ReaderID;

     HANDLE th[2]={threadWriter,threadReader}  ;
    
    
     WaitForMultipleObjects(2,th,TRUE,INFINITE); 

    DeleteCriticalSection(&cs) ;
   
  


  return 0;
 }