#include<iostream>
#include<windows.h>
using namespace std;
// HANDLE: it is the index of the kernel object used by your process/program in execution
HANDLE threadReader;
HANDLE threadWriter;
DWORD ReaderID;
DWORD WriterID;
int a[10];
  void Reader(){
    cout<<endl<<"Reading Started.....";
    for(int i=0;i<10;i++){
        cout<<endl<<a[i];
      Sleep(1000);
    }

  }
  void Writer(){
    for(int i=0;i<10;i++){
        cout<<endl<<"Writer writing:"<<endl;
         a[i]=(i+1)*2;
         Sleep(1000);
    }
     cout<<endl<<"Writing completed----";
     ResumeThread(threadReader);

  }
  int main(){
     threadWriter=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Writer,NULL,0,&WriterID);
      cout<<endl<<"Thread Writer ID: "<<endl<<WriterID;  
        
     threadReader=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Reader,NULL,CREATE_SUSPENDED ,&ReaderID);
      cout<<endl<<"Thread Reader ID: "<<endl<<ReaderID;

     HANDLE th[2]={threadWriter,threadReader}  ;
    // Sleep(10000);
     WaitForMultipleObjects(2,th,TRUE,INFINITE); 
   
  


  return 0;
 }