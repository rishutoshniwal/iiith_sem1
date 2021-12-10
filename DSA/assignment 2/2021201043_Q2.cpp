#include <iostream>
#include <string.h>
#include <vector>

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
	int maxSize=5;
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
	     string s=to_string(key);
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
	    int index=hashValue(key)%maxSize;
	    if(searchNodeLL(arr[index],key)==0){
	    arr[index]=insertInLL(arr[index],key,value);
	    currSize++;
	    }
	    else
	    {
	        V ans=getValueLL(arr[index],key);
	        if(ans!=value)
	        updateValueLL(arr[index],key,value);
	        return;
	    }
	    
	    if(getLoadFactor()>0.75)
	    grow();
	    
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
	
// 	V  operator[](K key);
	
// void operator[] (K key)
// 	{
// 	   // K key;
// 	    cout<<"check\n";
// 	     int index=hashValue(key)%maxSize;
// 	     if(searchNodeLL(arr[index],key)){
// 	     V ans= getValueLL(arr[index],key);
// 	     cout<<ans<<"\n";
// 	     }
// 	     else
// 	     cout<<"-1\n";
// 	}


	

	
	
};

// template <typename K, typename V>
//  V HashMap<K,V>:: operator[](K key)
// 	{
// 	   // K key;
// 	     int index=hashValue(key)%maxSize;
// 	     if(searchNodeLL(arr[index],key))
// 	     return getValueLL(arr[index],key);
// 	     else
// 	     return -1;
// 	}



// template <class K, class V>
// V HashMap<K, V> ::operator[] (K key)
// {
//      int index=hashValue(key)%maxSize;
//      if(searchNodeLL(arr[index],key))
// 	     return getValueLL(arr[index],key);
// 	 else
// 	     return -1;


// }


  vector<int> countDistinct (int arr[], int n, int k)
    {
        vector<int> g1;
        HashMap<int,int> *mp=new HashMap<int,int>();
    for(int i=0;i<k-1;i++)
    {
        if(!mp->find(arr[i]))
        mp->insert(arr[i],1);
        else{
            int val=mp->getValue(arr[i])+1;
            mp->insert(arr[i],val);
        }
        

    }
    
    // mp->displayMap();
    
    int j=0;
    for(int i=k-1;i<n;i++)
    {
        if(!mp->find(arr[i]))
        mp->insert(arr[i],1);
        else{
            int val=mp->getValue(arr[i])+1;
            mp->insert(arr[i],val);
        }
        
        g1.push_back(mp->getSize());
        
        int val=mp->getValue(arr[j]);
        // cout<<val<<"\n";
        if(val<=1)
        mp->erase(arr[j]);
        else
        mp->insert(arr[j],val-1);
        
        
         j++;
        
    }
        //code here.
        return g1;
    }


int main()
{
    // HashMap<int,int> *mp=new HashMap<int,int>();
    // for(int i=0;i<10;i++)
    // mp->insert(i,i);
    // mp->displayMap();
    // //  cout<<"rishu \n";
    // mp->insert(5,99);
    // mp->insert(100,100);
    // mp->displayMap();
    // cout<<"rishu \n";
    // mp->erase(8);
    // mp->displayMap();
    
    // cout<<mp->getValue(5)<<"\n";
    // cout<<mp->getValue(12)<<"\n";
    // cout<<mp->getValue(7)<<"\n";
    
    // cout<<mp<<"n";
    //  mp[5];
    //   cout<<mp[7]<<"\n";
    
    // int val=mp->operator[](5);
    // printf("%d\n",val);
    
    // val=mp->operator[](7);
    // printf("%d\n",val);
    
    //  val=mp->operator[](12);
    // printf("%d\n",val);
    
    
    
    // printf("%s",mp[5]);
    
    //  cout<<mp->find(5)<<"\n";
    // cout<<mp->find(5)<<"\n";
    //  cout<<mp->find(7)<<"\n";
     
    //  mp->erase(7);
    //  mp->erase(5);
     
    //   cout<<mp->find(5)<<"\n";
    // cout<<mp->find(5.1)<<"\n";
    
    
    //   mp->displayMap();
    //   cout<<"rishu\n";
    //   mp->erase(3);
    //  mp->erase(0);
     
     
    //   mp->displayMap();
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    cin>>arr[i];
    int k;
    cin>>k;
    
    vector<int> ans=countDistinct(arr,n,k);
    for(int i=0;i<ans.size();i++)
    cout<<ans[i]<<" ";
    cout<<"\n";
     
     
     
    
    return 0;
}