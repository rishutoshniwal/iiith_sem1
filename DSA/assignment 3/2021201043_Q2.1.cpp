#include<bits/stdc++.h>
#include <string>
using namespace std;



int nextVertex(vector<int>& value,vector<bool>& visited)
{
    int next;
	int min=INT_MAX;
	for(int i=0;i<visited.size();++i)
	{
		if(visited[i]==false && value[i]<min)
		{
			next=i;
			min=value[i];
		}
	}
	return next;
}


void dijkstra(int* arr,int n,int dest)
{
    string path[n];
    // vector<vector<int>> vect(n);
    for(int i=0;i<n;i++)
    path[i]="";
	int parent[n];	
	vector<int> cost(n,INT_MAX);
	vector<bool> visited(n,false);	


	parent[dest]=-1;	
	cost[dest]=0;	
	path[dest]=to_string(dest);
// 	vect[dest].push_back(dest);


	for(int i=0;i<n-1;i++)
	{
	
		int u=nextVertex(cost,visited);
		visited[u]=true;	


		for(int j=0;j<n;++j)
		{
			
			if(*(arr+u*n+j)!=0 && visited[j]==false && cost[u]!=INT_MAX && (cost[u]+*(arr+u*n+j) < cost[j]))
			{
				cost[j] = cost[u]+ *(arr+u*n+j);
				parent[j] = u;
				path[j]=to_string(j)+" "+path[u];
				
			}
		 else if(*(arr+u*n+j)!=0 && visited[j]==false && cost[u]!=INT_MAX
			&& (cost[u]+*(arr+u*n+j) == cost[j])){
			    
			    string otherPath=to_string(j)+" "+path[u];
			 //   cout<<otherPath<<" "<<path[j]<<"\n";
			    if(otherPath.compare(path[j])<0)
			    path[j]=otherPath;
			}
		}
	}

     for(int i=0;i<n;i++){
         
     if(i!=dest){
         cout<<path[i]<<"\n";
        }
     }
}

int main()
{

    int n,e;
    scanf("%d",&n);
    scanf("%d",&e);
    int arr[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        arr[i][j]=0;
    }
    for(int i=0;i<e;i++)
    {
        int first,second,wt;
     
       scanf("%d",&first);
        scanf("%d",&second);
        scanf("%d",&wt);
        
        arr[first][second]=wt;
        arr[second][first]=wt;
    
    }
    int dest;
     scanf("%d",&dest);

	dijkstra(*arr,n,dest);	
	return 0;
}