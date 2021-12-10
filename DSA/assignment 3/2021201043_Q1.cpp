/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

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
    TrieNode* root;
     set<string> words;
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
        // cout<<"inserted :"<<s<<"\n";
         words.insert(s);
        
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
    
    void autoCompleteHelper(TrieNode* temp,string s,vector<string>& ans)
    {
        if(temp==NULL)
        return;
        
        if(temp->end==1)
        ans.push_back(s);
        
        for(int i=0;i<26;i++)
        {
            if(temp->arr[i]!=NULL)
            autoCompleteHelper(temp->arr[i],s+(char)(i+97),ans);
        }
    }
    
    void autoComplete(string s)
    {
       
        TrieNode* temp=root;
        vector<string> g1;
         for(int i=0;i<s.length();i++)
        {
            int val=(int)(s.at(i)-'a');
            temp=temp->arr[val];
            if(temp==NULL){
            return;
            }
           
        }
       
         autoCompleteHelper(temp,s,g1);
         cout<<g1.size()<<"\n";
        for(int i=0;i<g1.size();i++)
        cout<<g1[i]<<"\n";
       
       
    }
    
    int levenshtein(string s1, string s2,int m,int n)
    {

    int store[m+1][n+1];
	
	//for(int i=0;i<=m;i++)
    //		store[0][i]=0;
  
    
    for (int i=0;i<= m;i++) {
        for (int j=0;j<=n;j++) {
            
            if (i==0)
                store[i][j]=j; 
            else if (j==0)
                store[i][j]=i;
            else if (s1[i - 1]==s2[j - 1])
                store[i][j]=store[i - 1][j - 1];
            else
                store[i][j]=min(store[i][j-1],min(store[i-1][j],store[i-1][j-1])) +1;

        }
    }
  
    return store[m][n];
   }
   
   void autoCorrect(string s)
   {
       vector<string> g1;
        for (auto it : words){
        int dist=levenshtein(s,it,s.length(),it.length());
        // cout<<it<<" "<<dist<<"\n";
        if(dist<=3)
        g1.push_back(it);
        }
        
        cout<<g1.size()<<"\n";
        for(int i=0;i<g1.size();i++)
        cout<<g1[i]<<"\n";
        
        
   }
};

int main()
{
    //  vector<string> g1;
    // cout<<g1.size()<<" Hello World\n";
    // string str="rishu";
    // str=str+(char)(97+3);
    // cout<<str;

    // Trie *t=new Trie();
    // t->insert("dog");
    // t->insert("deal");
    // t->insert("done");
    // t->insert("do");
    // t->insert("donor");
    // t->insert("donest");
    
    // cout<<t->search("do")<<"\n";
    //  cout<<t->search("don")<<"\n";
    //   cout<<t->search("done")<<"\n";
    //   cout<<t->search("doner")<<"\n";
    // // //   cout<<"rishu\n";
    // //   t->autoComplete("don");
       
    //   t->autoCorrect("do");
    
    int n;
    scanf("%d\n",&n);
    Trie *t=new Trie();
    
    string str;
    int x=0;
    while(x<n)
    {
        getline(cin,str);
        t->insert(str);
        x++;
    }
    
    // char arr[120];
    // // getline(cin,arr);
    // cin.getline(arr,120);
    // char *ptr;
    // ptr=strtok(arr," "); 
    int choice;
    cin>>choice;
    if(choice==1){
        
          getline(cin,str);
        //   cout<<"here"<<str.substr(1)<<"\n";
        cout<<t->search(str.substr(1))<<"\n";
    }
    else if(choice==2){
         getline(cin,str);
         t->autoComplete(str.substr(1));
    }
    else if(choice==3){
         getline(cin,str);
         t->autoCorrect(str.substr(1));
    }
    else
    {
       
        cout<<"\nwrong input\n";
    }
    
    
    
    
       
       
    
    return 0;
}
