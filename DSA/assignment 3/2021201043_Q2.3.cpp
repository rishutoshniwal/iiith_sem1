/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


// 7 8
// ########
// .......#
// #####..#
// #.#.#..#
// #R#..#.#
// #.....A#
// ########

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void distance(char* arr,int* path,int* visited,int i,int j,int r,int c,int dist)
{
    
    
     if(i<0 || i>=r || j<0 || j>=c || *(arr+i*c+j)=='#' || *(visited+i*c+j)==1)
     return;
    //  cout<<i<<" "<<j<<"\n";
     if(*(path+i*c+j)>dist){
        //  cout<<"here";
     *(path+i*c+j)=dist;
     }
     
     *(visited+i*c+j)=1;
     distance(arr,path,visited,i+1,j,r,c,dist+1);
      distance(arr,path,visited,i-1,j,r,c,dist+1);
      distance(arr,path,visited,i,j+1,r,c,dist+1);
      distance(arr,path,visited,i,j-1,r,c,dist+1);
      *(visited+i*c+j)=0;
    // cout<<"maa\n";
     
}

int main()
{
    vector<pair<int,int>> vect;
    int x,y;
    int r,c;
    scanf("%d",&r);
    scanf("%d",&c);
   
    char arr[r][c];
    int path[r][c],visited[r][c];
    string s;
    getline(cin,s);
    
    for(int i=0;i<r;i++){
       for(int j=0;j<c;j++){
       cin>>arr[i][j];
       path[i][j]=INT_MAX;
       visited[i][j]=0;
       
       if(arr[i][j]=='R')
        vect.push_back(make_pair(i,j));
        
        if(arr[i][j]=='A')
        {
            x=i;
            y=j;
        }
       
       }
    }
    // cout<<"rishu\n";
    distance(*arr,*path,*visited,1,0,r,c,0);
   
    // for(int i=0;i<r;i++)
    // {
    //     for(int j=0;j<c;j++)
    //     cout<<path[i][j]<<" ";
    //     cout<<"\n";
    // }
    
    int myDist=path[x][y];
    int minRiderDist=INT_MAX;
    
    for(int i=0;i<vect.size();i++){
        if(minRiderDist > path[vect[i].first][vect[i].second]){
        minRiderDist=path[vect[i].first][vect[i].second];
        }
    }
  
    // cout<<myDist<<" "<<minRiderDist<<"\n";
    
    if(myDist!=INT_MAX && myDist<=minRiderDist){
        cout<<"YES\n";
        cout<<myDist<<"\n";
    }
    else{
        cout<<"NO\n";
    }
    
    

    return 0;
}
