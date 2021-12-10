#include <bits/stdc++.h>
using namespace std;


struct suffix
{
    int rank[2]; 
	int index; 
	
};


int compare(struct suffix first,struct suffix second)
{
     if(first.rank[0] == second.rank[0])
     {
         if(first.rank[1]>=second.rank[1])
         return 0;
         else
         return 1;
     }
     else if(first.rank[0]<second.rank[0])
     return 1;
     else
     return 0;
}

vector<int> getSA(string str)
{
    
    vector<int> ans;
    int n=str.length();
	int ind[n]; 
	struct suffix arrOfSuffix[n];

    int i=0;
    while(i<n)
	{
		arrOfSuffix[i].index=i;
		arrOfSuffix[i].rank[0]=str[i]-'a';
        if(n<=i+1)
        {
           arrOfSuffix[i].rank[1] = -1;
        }
        else
        {
           arrOfSuffix[i].rank[1]=str[i+1]-'a';
        }
		i++;
	}
	sort(arrOfSuffix, arrOfSuffix+n,compare);

	int k=4;
	while(k<2*n)
	{
	
		int rank=0;
		int prev_rank=arrOfSuffix[0].rank[0];
		arrOfSuffix[0].rank[0]=rank;
		ind[arrOfSuffix[0].index]=0;

	    i=1;
	    while(i<n)
		{
		
			if(arrOfSuffix[i].rank[0] == prev_rank &&arrOfSuffix[i].rank[1] == arrOfSuffix[i-1].rank[1])
			{
				prev_rank = arrOfSuffix[i].rank[0];
				arrOfSuffix[i].rank[0] = rank;
			}
			else 
			{
				prev_rank = arrOfSuffix[i].rank[0];
				arrOfSuffix[i].rank[0] = ++rank;
			}
			ind[arrOfSuffix[i].index] = i;
			i++;
		}

	
	     i=0;
	    while(i<n)
		{
			int next=k/2+arrOfSuffix[i].index;
		    if(n<=next)
		    arrOfSuffix[i].rank[1]=-1;
		    else
		    arrOfSuffix[i].rank[1]=arrOfSuffix[ind[next]].rank[0];
			i++;
		}

	
		sort(arrOfSuffix,arrOfSuffix+n,compare);
		k=k*2;
	}



     i=0;
	 while(i<n)
	{
		ans.push_back(arrOfSuffix[i].index);
		i++;
	}

	return ans;
}



void minRotation(string str)
{
    string query=str+str;
	vector<int> suffixArr = getSA(query);
     int n = suffixArr.size();
	
	
// 	cout<<n<<"\n";
	for(int i=0;i<n;i++)
	{
	    string curr=query.substr(suffixArr[i],str.length());
	       if( curr.length()==str.length())
	       {
	           cout<<curr;
	           break;
	       }
	}
}


int main()
{
// 	string str = "banana";

// 	vector<int>suffixArr = buildSuffixArray(str, str.length());
// 	int n = suffixArr.size();

// 	cout << "Suffix Array : \n";
// 	printArr(suffixArr, n);

// 	vector<int>lcp = kasai(str, suffixArr);

// 	cout << "\nLCP Array : \n";
// 	printArr(lcp, n);
	
	string str="dcabca";
	minRotation(str);
// 	cout<<temp;
	
	
	return 0;
}
