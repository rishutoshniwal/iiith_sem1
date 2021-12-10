/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<bits/stdc++.h>
#include <string>

using namespace std;
template <typename K, typename V>
struct Node {
	K key;
	V value;
	Node* next;
};

template <typename K, typename V>
Node<K,V>* insertInLL(Node<K,V>* root,K key,V value)
{
    Node<K,V>* temp=new Node<K,V>;
    temp->key=key;
	temp->value=value;
    temp->next=NULL;
     if (root==NULL)
        root=temp;
    else {
       temp->next=root;
       root=temp;
    }
    
    return root;
}


template <typename K, typename V>
Node<K,V>* removeNodeLL(Node<K,V>* root,K key){
    
    if(root==NULL)
    return NULL;
    
    if(root->key==key)
    {
        Node<K,V>* store=root->next;
        free(root);
        return store;
    }
    
    root->next=removeNodeLL(root->next,key);
    return root;
    
    
}

template <typename K, typename V>
int searchNodeLL(Node<K,V>* root,K key){
    
     if(root==NULL)
    return 0;
    
    if(root->key==key)
    {
       
        return 1;
    }
    
    return searchNodeLL(root->next,key);
}


template <typename K, typename V>
V getValueLL(Node<K,V>* root,K key){
    
     if(root==NULL)
    return -1;
    
    if(root->key==key)
    {
       
        return root->value;
    }
    
    return getValueLL(root->next,key);
}



template <typename K, typename V>
void updateValueLL(Node<K,V>* root,K key,V value){
    
     if(root==NULL)
    return;
    
    if(root->key==key)
    {
       root->value=value;
        return ;
    }
    
   updateValueLL(root->next,key,value);
}


template <typename K, typename V>
void printLL(Node<K,V>* root){
    if(root==NULL){
        cout<<"\n";
    return;
    }
    cout<<"key : "<<root->key<<" value : "<<root->value<<" ----->";
    printLL(root->next);
    
}


template <typename K, typename V>
class HashMap
{
	
	int currSize;
	int maxSize=2000;
    Node<K,V>** arr;

	
	public:
	HashMap()
	{
	    currSize=0;
	    arr=new Node<K,V>*[maxSize];
	    for(int i=0;i<maxSize;i++)
	         arr[i]=NULL;
	}
	
	double getLoadFactor()
	{
	    return (1.0 * currSize)/maxSize;
	}
	
	
	void grow()
	{
// 	    displayMap();
// 	  cout<<"resize : "<<currSize <<" "<<maxSize<<"\n";
	  Node<K,V>** temp=arr;
	  int n=maxSize;
	   maxSize=maxSize*2;
	  arr=new Node<K,V>*[maxSize];
	  currSize=0;
	 
	  for(int i=0;i<n;i++)
	  {
	      if(temp[i]!=NULL)
	      {
	          Node<K,V>* itr=temp[i];
	          while(itr!=NULL){
	          insert(itr->key,itr->value);
	           itr=itr->next;
	          }
	      }
	  }
	  
	}
	
	int hashValue(K key)
	{
	     string s=key;
	     int p=31;
         int m=1e9 + 9;
         int hash_value=0;
         int p_pow=1;
         for (char c : s) {
             hash_value=(hash_value + (c) * p_pow)%m;
             p_pow = (p_pow*p) % m;
          }
    return hash_value;
	}
	
	
	void insert(K key,V value)
	{
	   // cout<<"sardar khan\n";
	    int index=hashValue(key)%maxSize;
	    if(searchNodeLL(arr[index],key)==0){
	       // cout<<"faizal\n";
	    arr[index]=insertInLL(arr[index],key,value);
	    currSize++;
	    }
	    else
	    {
	       // cout<<"tangent\n";
	        V ans=getValueLL(arr[index],key);
	        if(ans!=value)
	        updateValueLL(arr[index],key,value);
	        return;
	    }
	    
	    if(getLoadFactor()>0.75){
	       
	    grow();
	    }
	    
	}
	
	void erase(K key)
	{
	    int index=hashValue(key)%maxSize;
	    if(searchNodeLL(arr[index],key)){
	       // cout<<"walmart\n";
	        arr[index]=removeNodeLL(arr[index],key);
	    currSize--;
	    }
	    
	}
	
	bool find(K key)
	{
	     int index=hashValue(key)%maxSize;
	     if(searchNodeLL(arr[index],key))
	     return true;
	     else
	     return false;
	}
	
	V getValue(K key)
	{
	     int index=hashValue(key)%maxSize;
	     if(searchNodeLL(arr[index],key))
	     return getValueLL(arr[index],key);
	     else
	     return 0;
	}
	
	void displayMap()
	{
	    for(int i=0;i<maxSize;i++)
	    {
	        if(arr[i]!=NULL){
	            cout<<"index = "<<i<<"  : ";
	        printLL(arr[i]);
	        }
	    }
	}
	
	int getSize()
	{
	   return currSize; 
	}
	
	
	

//shi wala yeh hai
	V  operator[](K key){
	    
      return getValue(key);
	}
	

	
};


class Edge{
    public:
    int src,dest,wt;
    
    public:
    Edge(int s,int d,int w)
    {
        this->src=s;
        this->dest=d;
        this->wt=w;
    }
};


bool customSort(const pair<string,int> &a,const pair<string,int> &b)
{
    if(a.second!=b.second)
    return (a.second < b.second);
    else{
    int val= a.first.compare(b.first);
    if(val<0)
    return 1;
    return  0;
    }
}

void allPaths(vector<Edge>* arr,int n,vector<bool>& visited,vector<pair<string,int>> &vect,
HashMap<string,int>* mp,string path,string revPath,int cost,int curr)
{
    // cout<<curr<<"\n";
    // for(int i=0;i<visited.size();i++)
    // cout<<i<<" "<<visited[i]<<"   ";
    // cout<<"\n";
   
    vector<Edge> temp=arr[curr];
     for (int j=0;j<temp.size();j++){
          Edge e=temp[j];
        //   cout<<e.src<<" "<<e.dest<<" "<<e.wt<<"     "<<visited[e.dest]<<"\n";
         if(visited[e.dest]==false){
             visited[e.dest]=true;
            //  path=path+to_string(e.dest);
            //  revPath=to_string(e.dest)+revPath;
            //  cost+=e.wt;
            string s1=path+to_string(e.dest);
            string s2=to_string(e.dest)+revPath;
            // cout<<s1<<" "<<s2<<"\n";
             if(s1.compare(s2)<0){
                 if(!mp->find(s1)){
              mp->insert(s1,cost+e.wt);
              vect.push_back(make_pair(s1,cost+e.wt));
                 }
             }
             else{
                  if(!mp->find(s2)){
              mp->insert(s2,cost+e.wt);
              vect.push_back(make_pair(s2,cost+e.wt)); 
                  }
             }
             allPaths(arr,n,visited,vect,mp,s1,s2,cost+e.wt,e.dest);
            //  cout<<s1<<" negate\n";
              visited[e.dest]=false;
        //       for(int i=0;i<visited.size();i++)
        //     cout<<i<<" "<<visited[i]<<"   ";
        //   cout<<"\n";
         }
          
     }
    
}
void printKpath(vector<Edge>* arr,int n,int k)
{
    vector<pair<string,int>> vect;
    vector<bool> visited(n,false);
    HashMap<string,int> *mp=new HashMap<string,int>();
    // for(int i=0;i<n;i++)
    // {
    //     cout<< "for i = "<<i<<"\n";
    //      for (auto j =arr[i].begin();j!=arr[i].end();j++)
    //      {
    //          Edge e=*j;
    //          cout<<e.src<<" "<<e.dest<<" "<<e.wt<<"\n";
    //      }
    // }
    
    for(int i=0;i<n;i++)
    {
        visited[i]=true;
        string p=to_string(i);
        allPaths(arr,n,visited,vect,mp,p,p,0,i);
        visited[i]=false;
    }
    
    //  cout<<"before sort :\n";
    //   for (auto i = vect.begin(); i != vect.end(); ++i)
    //       {
    //           pair<string,int> p=*i;
    //           cout<<p.first<<" "<<p.second<<"\n";
    //       }
    
     sort(vect.begin(), vect.end(),customSort);
        
        // cout<<"\n";
        // cout<<"\n";
        // cout<<"\n";
        //  cout<<"after sort :\n";
        //   for (auto i = vect.begin(); i != vect.end(); ++i)
        //   {
        //       pair<string,int> p=*i;
        //       cout<<p.first<<" "<<p.second<<"\n";
        //   }
        
        for(int i=0;i<k && i<vect.size();i++)
        {
            string temp=vect[i].first;
            for(int j=0;j<temp.length();j++)
            cout<<temp.at(j)<<" ";
            // cout<<"cost :" <<vect[i].second;
            cout<<"\n";
        }
    
}

int main()
{
    int n,e;
    scanf("%d",&n);
    scanf("%d",&e);
    vector<Edge> arr[n];
    for(int i=0;i<e;i++)
    {
        int first,second,wt;
     
       scanf("%d",&first);
        scanf("%d",&second);
        scanf("%d",&wt);
        
       Edge e1(first,second,wt);
       Edge e2(second,first,wt);
       
       arr[first].push_back(e1);
        arr[second].push_back(e2);
    
    }
    
    int k;
    scanf("%d",&k);
    
    printKpath(arr,n,k);

    return 0;
}


/*
4 5            
0 1 1
1 3 2
0 3 3
0 2 2
2 3 1
3         

*/



/*
5 10
0 1 1
0 2 2
0 3 3
0 4 4
1 2 5
1 3 6
1 4 7
2 3 8
2 4 9
3 4 10
20
*/
