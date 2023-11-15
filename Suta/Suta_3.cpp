//Suta with Synchronization using Critical Secton

//Suta-3

#include<iostream>
#include<windows.h>
using namespace std;


// HANDLE: it is the index of the kernel object used by your process/program in execution
//Critical Section : Create two threads and synchronize them using critical section
HANDLE threadReader;
HANDLE threadWriter;
DWORD ReaderID;
DWORD WriterID;

CRITICAL_SECTION cs;

int a[10];

  void Reader(){
   EnterCriticalSection(&cs); 

    cout<<endl<<"Reading Started.....";

    for(int i=0;i<10;i++){

        cout<<endl<<a[i];

      Sleep(1000);
    }
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
        
     threadReader=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Reader,NULL,0 ,&ReaderID);
      cout<<endl<<"Thread Reader ID: "<<endl<<ReaderID;

     HANDLE th[2]={threadWriter,threadReader}  ;
    
    
     WaitForMultipleObjects(2,th,TRUE,INFINITE); 

    DeleteCriticalSection(&cs) ;
   
  


  return 0;
 }