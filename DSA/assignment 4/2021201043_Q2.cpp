#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include<stdlib.h>
#include<string>
#include <cstring>
using namespace std;

class MinHeapNode{
    public:
   long long elem;
   long long index;

   
};

void heapifyDelete(MinHeapNode arr[],long long subParts, long long k)
{
  long long smallest=k;
  long long leftChild=2*k+1;
  long long rightChild=leftChild+1;

   if(leftChild < subParts && arr[leftChild].elem < arr[smallest].elem)
   smallest=leftChild;

   if(rightChild < subParts && arr[rightChild].elem < arr[smallest].elem)
   smallest=rightChild;

   if(smallest!=k){
        MinHeapNode swap=arr[k];
        arr[k]=arr[smallest];
        arr[smallest]=swap;
        heapifyDelete(arr,subParts,smallest);

   }

}

MinHeapNode deleteMin(MinHeapNode arr[],long long& subParts)
{
    MinHeapNode del=arr[0];
    arr[0]=arr[subParts-1];
    subParts-=1;
    heapifyDelete(arr,subParts,0);
    return del;
}


void heapifyInsert(MinHeapNode arr[],long long subParts,long long k)
{
     long long parent=(k-1)/2;

      if(arr[k].elem < arr[parent].elem)
      {
          MinHeapNode swap=arr[k];
          arr[k]=arr[parent];
          arr[parent]=swap;

          heapifyInsert(arr,subParts,parent);
      }
}


void insert(MinHeapNode arr[], long long& subParts,MinHeapNode key)
{
     subParts=subParts+1;
     arr[subParts-1]=key;
     heapifyInsert(arr,subParts,subParts-1);
}

void minHeap(MinHeapNode* arr,long long subParts,long long k)
{
    MinHeapNode store=arr[k];
   long long childIndex=2*k+1;
    
    while(childIndex<subParts)
    {
        if(childIndex<subParts-1 && arr[childIndex+1].elem < arr[childIndex].elem)
        childIndex+=1;

        if(store.elem < arr[childIndex].elem)
        break;

        else if(store.elem >= arr[childIndex].elem)
        {
            arr[(childIndex-1)/2]=arr[childIndex];
            childIndex=childIndex*2+1;
        }
    }
    arr[(childIndex-1)/2]=store;
}


void buildMinHeap(MinHeapNode* arr,long long subParts)
{
    // cout<<"Subaparts : "<<subParts<<"\n";
   long long val= subParts/2 -1;
    // cout<<"Value : "<<val<<"\n";
    while(val>=0){
       
    minHeap(arr,subParts,val);
    val--;
    }
}

int compareToSort(const void* first,const void* second){
   long long a=*(const long long*)first;
   long long b=*(const long long*)second;

    if(a>b)
    return 1;
    else if(a<b)
    return -1;
    else
    return 0;
}
  
int main(int argc, char** argv)
{
    string filename(argv[1]);
    vector<string> lines;
    string line;
    long long maxSize=20000;


    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
   long long count=0;
    
    while (getline(input_file, line,',')){
        count++;
        // lines.push_back(line);
    }

     input_file.close();

    //  for (const auto &i : lines)
    //     cout << i << endl;


    long long subParts=count/maxSize;

     if(count%maxSize!=0)
     subParts++;

     
    //   cout<<count<<"\n";

     string filename2(argv[1]);
     ifstream input_file2(filename2);
    if (!input_file2.is_open()) {
        cerr << "Could not open the file - '"
             << filename2 << "'" << endl;
        return EXIT_FAILURE;
    }

    ofstream tempArr[subParts];
   
   long long i=0,subPartCounter=0;;
   long long start=1;
    while (start<=count){
       long long* store=new long long[maxSize];
         for(i=0;i<maxSize && getline(input_file2, line,',');i++)
         {
            //  myfile.open ("txt");
             stringstream ss(line);
             ss>>store[i];
           //  cout<<start<<" : "<<line<<"\n";
            start++;
         }
         if(i==maxSize){
         qsort(store,i,sizeof(long long),compareToSort);
         string name=to_string(subPartCounter)+".txt";
         tempArr[subPartCounter].open(name);
          for(int x=0;x<i;x++){
          tempArr[subPartCounter]<<store[x]<<"\n";
        //   cout<<store[x]<<" ";
         
          }
          tempArr[subPartCounter].close();
        //    cout<<"\n";
         }
         else{
         qsort(store,count%maxSize,sizeof(long long),compareToSort);
          string name=to_string(subPartCounter)+".txt";
         tempArr[subPartCounter].open(name);
         for(int x=0;x<count%maxSize;x++){
        //   cout<<store[x]<<" ";
          tempArr[subPartCounter]<<store[x]<<"\n";
         }
           tempArr[subPartCounter].close();
        //    cout<<"\n";
         }
         
         subPartCounter++;
        //   cout<<"\n";
    }

     input_file.close();

     MinHeapNode* arr=new MinHeapNode[subParts];
     ifstream files[subParts];
     for(i=0;i<subParts;i++)
     {
         ostringstream curr;
        //  string name=
        string name=to_string(i)+".txt";
         curr<<name;
         files[i].open(curr.str());
         getline(files[i], line,'\n');
          stringstream ss(line);
         arr[i]=MinHeapNode();
         ss>>arr[i].elem;
         arr[i].index=i;


     }

    //  for( i=0;i<subParts;i++)
    //  cout<<"Index is :"<<arr[i].index<<" Element is : "<<arr[i].elem<<"\n";

     buildMinHeap(arr,subParts);
    //  cout<<"\n";
    //  cout<<"final : \n";
    //  cout<<"\n";
    //  for( i=0;i<subParts;i++)
    //  cout<<"Index is :"<<arr[i].index<<" Element is : "<<arr[i].elem<<"\n";

    //  MinHeapNode del=deleteMin(arr,subParts);
    // cout<<"Index is :"<<del.index<<" Element is : "<<del.elem<<"\n";
    
     ofstream finalAns;
     string outputFile(argv[2]);
     finalAns.open(outputFile);
     for(i=0;i<count;i++)
     {
         MinHeapNode del=deleteMin(arr,subParts);
         finalAns<<del.elem<<",";
        
         long long next=9223372036854775807;
        if (getline(files[del.index], line,'\n')){
          stringstream ss(line);
          ss>>next;
        }

    //      cout<<"After 1 deletion : \n";
    //  for( i=0;i<subParts;i++)
    //  cout<<"Index is :"<<arr[i].index<<" Element is : "<<arr[i].elem<<"\n";


         MinHeapNode newObj;
         newObj.index=del.index;
         newObj.elem=next;
         insert(arr,subParts,newObj);

     }
    //  cout<<"After end : \n";
    //  for( i=0;i<subParts;i++)
    //  cout<<"Index is :"<<arr[i].index<<" Element is : "<<arr[i].elem<<"\n";
    
    for(i=0;i<subParts;i++)
    files[i].close();
    finalAns.close();
    for(i=0;i<subParts;i++)
    {
        string name=to_string(i)+".txt";
        int nameLen=name.length();
        char deleteName[nameLen+1];
        strcpy(deleteName,name.c_str());
        if(remove(deleteName)!=0)
        perror("Error in deleting file\n");
        
        // else
        // puts("File successfully")

    }
    return EXIT_SUCCESS;
}