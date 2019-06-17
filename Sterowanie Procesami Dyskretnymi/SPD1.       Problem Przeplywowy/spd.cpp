#include<iostream>
#include<fstream>
#include<cstdlib>
#include<unistd.h>
#include<cmath>
using namespace std;

int main()
{
    int n,time_of_execute[100],weight[100],time_to_end[100];
    int c=0;
    ifstream data ("data.txt");
    data>>n;

    for(int i=0;i<n;i++)
        data>>time_of_execute[i]>>weight[i]>>time_to_end[i];
        
       
        int N=1<<n;
         int *x=new int[N];
        

      for(int set=1;set<N;set++)
      {
          int c=0;

          for(int i=0,b=1;i<n;i++,b*=2)
          if(b&set)
          c+=time_of_execute[i];
          x[set]=9999;
          
            for(int i=0,b=1;i<n;i++,b*=2)
                x[set]=min(x[set],x[set-b]+weight[i]*max(0,c-time_to_end[i]));

          }
          
      

      
cout<<x[N-1];
delete [] x;
return 0;

      }  


