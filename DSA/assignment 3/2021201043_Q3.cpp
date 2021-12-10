
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
class Deque
{
	// Initialize fr and rear
	public:
	int fr,rear,currSize,maxSize;
    
    public:
	T *arr;
	
	public:
	Deque()
	{
	    fr=-1;
	    rear=-1;
	    currSize=0;
	    maxSize=10;
	    arr = new T[10];
	}
	
	Deque(int n,T x)
	{
	    fr=0;
	    rear=n-1;
	    currSize=n;
	    maxSize=n;
	    arr = new T[n];
	    for(int i=0;i<n;i++)
	    arr[i]=x;
	    
	    
	}
	
	void grow()
	{
	    T* temp=arr;
	    arr=new T[maxSize*2];
	    int j=0;
	    for(int i=fr;j<currSize;i=(i+1)%maxSize)
	    arr[j++]=temp[i];
	    fr=0;
	    rear=maxSize-1;
	    maxSize*=2;
	    
	}
	
	int size()
	{
	    return currSize;
	}
	
	bool empty(){
	    if(currSize==0)
	    return true;
	    else
	    return false;
	}
	
	void clear()
	{
	    fr=-1;
	    rear=-1;
	    currSize=0;
	}
	
	
	T front()
	{
	    if(currSize==0)
	    return NULL;
	    return arr[fr];
	}
	
	
	T back()
	{
	    if(currSize==0)
	    return NULL;
	    return arr[rear];
	}
	
	
	void push_back(T x)
	{
	    if(currSize==0)
	    {
	        fr=0;
	        rear=0;
	        arr[fr]=x;
	        currSize++;
	        return;
	    }
	    if(currSize==maxSize)
	    grow();
	    
	    rear=(rear+1)%maxSize;
	    arr[rear]=x;
	    currSize++;
	    
	}
	
	void push_front(T x)
	{
	   // cout<<"lmc\n";
	    if(currSize==0)
	    {
	       //  cout<<"lmc no\n";
	        fr=0;
	        rear=0;
	        arr[fr]=x;
	        currSize++;
	        return;
	    }
	    if(currSize==maxSize){
	       //  cout<<"lmc yes\n";
	    grow();
	    }
	    
	   //  cout<<"lmc rishu\n";
	    fr=((fr-1)%maxSize + maxSize)%maxSize;
	    arr[fr]=x;
	    currSize++;
	}
	
	
	T pop_front()
	{
	    if(currSize==0){
	       cout<<"Deque is empty\n";
	    return -1;
	    }
	    
	    if(currSize==1)
	    {
	        T store=arr[fr];
	        currSize=0;
	        fr=-1;
	        rear=-1;
	        return store;
	    }
	    
	     T store=arr[fr];
	     fr=(fr+1)%maxSize;
	     currSize--;
	     return store;
	    
	    
	}
	
	
T pop_back()
	{
	    if(currSize==0){
	    cout<<"Deque is empty\n";
	    return -1;
	    }
	    
	    if(currSize==1)
	    {
	        T store=arr[rear];
	        currSize=0;
	        fr=-1;
	        rear=-1;
	        return store;
	    }
	    
	    
	      T store=arr[rear];
	      currSize--;
	      rear=((rear-1)%maxSize + maxSize)%maxSize;
	      return store;
	    
	    
	}
	
	void display()
	{
	    int j=0;
	    for(int i=fr;j<currSize;i=(i+1)%maxSize){
	         cout<<arr[i]<<" ";
	         j++;
	    }
	         cout<<"\n";
	}
	
	T n_thElement(int n)
	{
	    if(n>=currSize)
	    {
	     cout<<"Deque is empty\n";
	     return -1;
	    }
	    
	    cout<<"rishu : "<<fr<<"\n";
	    int actual=(fr+n)%maxSize;
	    return arr[actual];
	}
	
	void resize(int x,T d)
	{
	   
	    if(x<=currSize)
	    return;
	    else
	    {
	        int val=x-this->size();
	        while(val>0)
	        {
	            push_back(d);
	            val--;
	        }
	    }
	}
	
};
class TrieNode{
    public:
    TrieNode* arr[26];
    int end;
    
     public:
     TrieNode(){
         for(int i=0;i<26;i++)
         arr[i]=NULL;
         end=0;
     }
    
    
};

class Trie{
    public:
    TrieNode* root;
    public:
    Trie()
    {
        root=new TrieNode();
    }
    
    void insert(string s){
        
        TrieNode* temp=root;
        for(int i=0;i<s.length();i++)
        {
            int val=(int)(s.at(i)-'a');
            if(temp->arr[val]==NULL)
            temp->arr[val]=new TrieNode();
            temp=temp->arr[val];
        }
        temp->end=1;
        
    }
    
    int search(string s)
    {
         TrieNode* temp=root;
        for(int i=0;i<s.length();i++)
        {
            int val=(int)(s.at(i)-'a');
            if(temp->arr[val]==NULL)
            return 0;
            temp=temp->arr[val];
        }
        
        return temp->end;
        
    }
};
void merge(string arr[],int l,int m,int r)
{
   
    int n1=m-l+1;
    int n2=r-m;
  
   
    string left[n1],right[n2];
  
    
    for(int i = 0; i < n1; i++)
        left[i] = arr[l+i];
    for(int j = 0; j < n2; j++)
        right[j] = arr[m+ 1 + j];
  
    
   int i=0; 
   int j=0; 
   int k=l; 
    while(i<n1 && j<n2) {
        if (left[i]<=right[j]) {
            arr[k]=left[i];
            i++;
        }
        else {
            arr[k]=right[j];
            j++;
        }
        k++;
    }
  
   
    while(i<n1) {
        arr[k]=left[i];
        i++;
        k++;
    }
  
   
    while(j<n2) {
        arr[k]=right[j];
        j++;
        k++;
    }
}



  

void mergeSort(string arr[], int left, int right)
{
    if (left < right) {
       
        int mid=(right +left)/2;
  
      
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
  
        merge(arr, left, mid, right);
    }
}

void search(TrieNode* temp,Deque<string> *q,char* arr,int r,int c,int i,int j,string found)
{
     if(i<0 || i>=r || j<0 || j>=c)
     return;
     
     int val=(int)(*(arr+i*c+j)-'a');
     if(*(arr+i*c+j)=='#' || temp->arr[val]==NULL)
     return;
     
     found=found+*(arr+i*c+j);
     temp=temp->arr[val];
     if(temp->end==1){
         q->push_front(found);
         temp->end=-1;
     }
     
     char store=*(arr+i*c+j);
    *(arr+i*c+j)='#';               // mark visited
    
      search(temp,q,arr,r,c,i+1,j,found);   
       search(temp,q,arr,r,c,i-1,j,found);
        search(temp,q,arr,r,c,i,j+1,found);
         search(temp,q,arr,r,c,i,j-1,found);
    
     *(arr+i*c+j)=store;
}


int main()
{
    int r,c,x;
    scanf("%d",&r);
    scanf("%d",&c);
   
    char arr[r][c];
    string s;
    getline(cin,s);
    
    for(int i=0;i<r;i++){
       for(int j=0;j<c;j++){
       cin>>arr[i][j];
    //   cout<<arr[i][j];
       }
    }
       
     scanf("%d",&x);
     getline(cin,s);
     string str[x];
      Trie *t=new Trie();
     for(int i=0;i<x;i++){
      getline(cin,str[i]);
      t->insert(str[i]);
     }
      
    //   mergeSort(str,0,x-1);
    Deque<string> *q=new Deque<string>();
    string found="";
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            
            search(t->root,q,*arr,r,c,i,j,found);
        }
    }
    
    // q->display();
      if(q->size()<=0)
        return 0;
    
    string ans[q->size()];
    int j=0;
	 for(int i=q->fr;j<q->size();i=(i+1)%q->maxSize)
	 ans[j++]=q->arr[i];
	 
	 mergeSort(ans,0,q->size()-1);
	 
	 for(int i=0;i<q->size();i++)
	 cout<<ans[i]<<" ";
    
   

    return 0;
}
