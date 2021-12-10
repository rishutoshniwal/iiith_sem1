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



vector<int> getLCPfromSA(string str, vector<int> suffixArr)
{
	int n = suffixArr.size();

	vector<int> lcp(n,0);
	vector<int> invSuff(n,0);
	int i=0;
	while(i<n){
		invSuff[suffixArr[i]]=i;
		i++;
	}

	int k=0;
	i=0;
     while(i<n)
	{
		
		if (invSuff[i] == n-1)
		{
			k = 0;
			i++;
			continue;
		}

	
		int j = suffixArr[invSuff[i]+1];

		while (i+k<n && j+k<n && str[i+k]==str[j+k])
			k++;

		lcp[invSuff[i]] = k; 
		if (k>0)
			k--;
		i++;
	}

	return lcp;
}


void longestPalindrome(string str)
{
    string rev="";
    for(int i=0;i<str.length();i++)
    rev=str.at(i)+rev;
    
    
    str=str+"$"+rev;
    // cout<<str<<"\n";
    vector<int>suffixArr = getSA(str);
	vector<int>lcp = getLCPfromSA(str,suffixArr);
	
	int maxIndex=0;
	for(int i=1;i<suffixArr.size();i++){
	   if(lcp[i]>lcp[maxIndex])
	   maxIndex=i;
	}
	
	
	int maxLen=lcp[maxIndex];
    
    // cout<<suffixArr[maxIndex]<<"\n";
    cout<<str.substr(suffixArr[maxIndex],maxLen);
    
}


int main()
{
// 	string str = "banana";

// 	vector<int>suffixArr=getSA(str);
// 	int n = suffixArr.size();

// 	cout << "Suffix Array : \n";
// 	printArr(suffixArr, n);

// 	vector<int>lcp=getLCPfromSA(str, suffixArr);

// 	cout << "\nLCP Array : \n";
// 	printArr(lcp, n);
	

//	cout<<temp;
	longestPalindrome("dxabcbayz");
	
	return 0;
}
