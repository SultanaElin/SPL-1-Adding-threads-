//Read or write in an array using thread
#include<windows.h>
#include<iostream>
using namespace std;

int a[10];
void Reader(){
  for(int i=0;i<10;i++){
   cout<<endl<<"Reader Reading: "<< a[i];
    Sleep(1000);//Sleep for 1sec
  }

}
void Write(){
    for(int i=0;i<10;i++){
      cout<<endl<<"Writer writing:";
        a[i]=1000+i;
        Sleep(1000);//Sleep for 1 sec
    }
}
int main(){
    HANDLE theRead=NULL;
    HANDLE thewrite=NULL;
    // for(int i=0;i<2;i++){
       
       thewrite=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Write,NULL,0,NULL);
       Sleep(1000);
       theRead=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Reader,NULL,0,NULL);
       
        Sleep(10000);
    return 0;  
}