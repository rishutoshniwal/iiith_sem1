/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<sstream>  

using namespace std;

class TrieNode{
    public:
    TrieNode* arr[2];
    long long int end;
    
     public:
     TrieNode(){
         for(int i=0;i<2;i++)
         arr[i]=NULL;
         end=0;
     }
  
};


class Trie{
    public:
    TrieNode* root;
    
    
    Trie()
    {
        root=new TrieNode();
    }
    
    void insert(long long int val){
      
        TrieNode* temp=root;
        long long int mul=1;
        
        for(int i=63;i>=0;i--)
        {
            //  cout<<i<<"  insideForLopp\n";
            mul=1<<i;
            long long int i_th_bit=val&mul;
           
            
            if(i_th_bit>0)
            i_th_bit=1;
            
            if(temp->arr[i_th_bit]==NULL)
              temp->arr[i_th_bit]=new TrieNode();
            
            temp=temp->arr[i_th_bit];
               
        }
       
        temp->end=val;
       
    } 
    
    int max_xor_in_trie(long long int search)
    {
        TrieNode* temp=root;
        long long int mul=1;
        for(int i=63;i>=0;i--)
        {
            mul=1<<i;
            long long int i_th_bit=search&mul;
           
            
            int checkIndex=1;
            if(i_th_bit>0)
               checkIndex=0;
               
            if(temp->arr[checkIndex]!=NULL)
                temp=temp->arr[checkIndex];
            else
                temp=temp->arr[1-checkIndex];
            
            
            
        }
        
        return search^temp->end;
   
        
    }
    
    
};

int main()
{


     int n,q;
     scanf("%d",&n);
     scanf("%d\n",&q);
     Trie *t=new Trie();
     
          for (int i=0;i<n;i++){
          long long int next;
          scanf("%lld",&next);
          t->insert(next);
          }
          
          
           for (int i=0;i<q;i++){
               long long int next;
               scanf("%lld",&next);
               cout << t->max_xor_in_trie(next) <<"\n";
           }
     
     
     
     
     
     
    return 0;
}


