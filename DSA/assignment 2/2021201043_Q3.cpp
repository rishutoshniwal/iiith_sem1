/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

template <typename T>
class Deque
{
	// Initialize fr and rear
	int fr,rear,currSize,maxSize;

	T *arr;
	
	public:
	Deque()
	{
	    fr=-1;
	    rear=-1;
	    currSize=0;
	    maxSize=5;
	    arr = new T[5];
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





int main()
{


Deque<int> *q=new Deque<int>();
for(int i=1;i<=7;i++)
{ 
    cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";
    q->push_front(i);
    cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";
     q->display();
     cout<<"\n";
}


for(int i=0;i<3;i++){
     cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";
    q->pop_back();
    cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";
     q->display();
     cout<<"\n";
}



for(int i=8;i<=10;i++)
{ 
    cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";
    q->push_back(i);
    cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";
     q->display();
     cout<<"\n";
}


cout<<q->n_thElement(3)<<"\n";

q->resize(9,100);
 q->display();


q->clear();
cout<<"size : "<<q->size()<<" Empty : "<<q->empty()<<"\n";






// q->push_back(10);
// q->push_back(15);
// // cout<<"rishu\n";
// q->push_front(7);
// // cout<<"sonam\n";
// q->display();
// cout<< q->size()<<"\n";

// q->pop_back();


// q->display();
// cout<< q->size()<<"\n";



// q->pop_front();


// q->display();
// cout<< q->size()<<"\n";


// q->pop_front();


// q->display();
// cout<< q->size()<<" "<<q->empty();
	return 0;
}
