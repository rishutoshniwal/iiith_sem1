/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



#include <iostream>
#include <cstring>
using namespace std;
 
// Representation of a node
struct Node {
    int data;
    Node* next;
};
 
// Function to insert node
Node* insert(Node* root, char item)
{
    Node* temp = new Node;
    Node* ptr;
    temp->data = (int)(item-'0');
    temp->next = NULL;
 
    if (root == NULL)
        root = temp;
    else {
       temp->next=root;
       root=temp;
    }
    
    return root;
}
 
void display(Node* root)
{
    Node* temp=root;
    while (temp!= NULL) {
        cout << temp->data << " ";
       temp=temp->next;
    }
    cout<<"\n";
}
 
Node *arrayToList(char arr[], int n)
{
    Node *root = NULL;
    for (int i = 0; i < n-1; i++)
        root=insert(root, arr[i]);
   return root;
}


Node* help(Node* l1,Node* l2,int carry)
{
     if(l1==NULL && l2==NULL)
         {
             if(carry>0)
                {
                    // cout<<carry<<"\n";
                     Node* temp = new Node;
                     temp->data = carry;
                     temp->next = NULL;
                     return temp;
                }
             return NULL;
         }
         
    if(l1==NULL)
         {
            //   cout<<l2->data<<"\n";
            Node* temp = new Node;
            temp->data=(carry+l2->data)%10;
            temp->next=help(NULL,l2->next,(carry+l2->data)/10);
            return temp;
         }
         
         
    if(l2==NULL)
         {
            //   cout<<l1->data<<"\n";
            Node* temp = new Node;
            temp->data=(carry+l1->data)%10;
            temp->next=help(l1->next,NULL,(carry+l1->data)/10);
            return temp;
         }
         
         else{
             
            //  cout<<l1->data<<" "<<l2->data<<"\n";
             Node* temp = new Node;
            temp->data=(carry+l1->data+l2->data)%10;
            temp->next=help(l1->next,l2->next,(carry+l1->data+l2->data)/10);
            return temp;
             
         }
}


void output(Node* head)
{
    if(head==NULL)
    return;
    output(head->next);
    printf("%d",head->data);
    
}
Node* addition(char arr1[],char arr2[],int n1,int n2)
{
   
    Node* ll1=arrayToList(arr1,n1);
    Node* ll2=arrayToList(arr2,n2);
    // display(ll1);
    // display(ll2);
    Node* ans=help(ll1,ll2,0);
    // display(ans);
    // output(ans);

    return ans;
    
}


Node* helpMultiply(int val,Node* head,int carry)
{
    if(head==NULL)
    {
         if(carry>0)
                {
                    // cout<<carry<<"\n";
                     Node* temp = new Node;
                     temp->data = carry;
                    //   cout<<temp->data<<" ";
                     temp->next = NULL;
                     return temp;
                }
    
    return NULL;
    }
    
     Node* temp = new Node;
     temp->data=(val*head->data+carry)%10;
    //  cout<<temp->data<<" ";
     temp->next=helpMultiply(val,head->next,(val*head->data+carry)/10);
     return temp;
    
    
    
}

Node* multiply2LL(Node* l1,Node* l2)
{
     Node* temp=l2;
    int count=0;
    Node* sum=NULL;
    while(temp!=NULL)
    {
        
        Node* curr=helpMultiply(temp->data,l1,0);
        int i=0;
        while(i<count)
        {
            Node* temp = new Node;
            temp->data=0;
            temp->next=curr;
            curr=temp;
            i++;
        }
        count++;
        sum=help(sum,curr,0);
        //  output(sum);
        //  cout<<"\n";
        temp=temp->next;
    }
    
    return sum;
}


Node* multiply(char arr1[],char arr2[],int n1,int n2)
{
    
    Node* l1=arrayToList(arr1,n1);
    Node* l2=arrayToList(arr2,n2);
    // display(ll1);
    // display(ll2);
    return multiply2LL(l1,l2);
    
   
    
}


Node* exponentiationHelp(Node* head,unsigned long int n)
{
    if(n==0)
    {
        Node* temp = new Node;
        temp->data=1;
        temp->next=NULL;
        return temp;
    }
    Node* smallAns=exponentiationHelp(head,n/2);
    // display(smallAns);
    // cout<<n<<" rishu \n";
    Node* t= multiply2LL(smallAns,smallAns);
    
    if(n%2==0)
    return t;
    else
    return multiply2LL(t,head); 
}


Node* exponentiation(char arr1[],unsigned long int n,int size)
{
    // cout<<"rishu \n";
     Node* l1=arrayToList(arr1,size);
    // cout<<"sonam \n";
     return exponentiationHelp(l1,n);
}

Node* subtractionHelp(Node* l1,Node* l2,int borr)
{
   
   if(l1==NULL && l2==NULL)
   return NULL;
   
   
    if(l2==NULL){
        if(l1->data>=borr)
        {
           Node* temp = new Node; 
           temp->data=l1->data-borr;
           temp->next=subtractionHelp(l1->next,NULL,0);
           return temp;
        }
        else
        {
           Node* temp = new Node;
           temp->data=(l1->data+10)-borr;
           temp->next=subtractionHelp(l1->next,NULL,1);
           return temp;
        }
        
    }
    else{
        if(l1->data - l2->data - borr >=0)
        {
            Node* temp = new Node; 
           temp->data=l1->data - l2->data - borr;
            temp->next=subtractionHelp(l1->next,l2->next,0);
            return temp;
        }
        else{
             Node* temp = new Node; 
           temp->data=l1->data - l2->data - borr+10;
            temp->next=subtractionHelp(l1->next,l2->next,1);
            return temp;
        }
        
    }
   
   
    
}


Node* removeLeadingZeros(Node* head)
{
    if(head==NULL)
    return head;
    
    if(head->data==0)
    {
       Node* temp=removeLeadingZeros(head->next);
       if(temp==NULL)
       return NULL;
       else
      {
          head->next=temp;
          return head;
      }
       
    }
    
    head->next=removeLeadingZeros(head->next);
    return head;
}

Node* subtraction(char arr1[],char arr2[],int n1,int n2)
{
   
    Node* ll1=arrayToList(arr1,n1);
    Node* ll2=arrayToList(arr2,n2);
    
    // display(ll1);
    // display(ll2);
    
    Node* temp=subtractionHelp(ll1,ll2,0);
   Node* out=removeLeadingZeros(temp);
   if(out==NULL)
   {
       Node* temp = new Node;
       temp->data=0;
       temp->next=NULL;
       return temp;
   }
   return out;
    
}


int length(Node* l1)
{
    if(l1==NULL)
    return 0;
    return 1+length(l1->next);
}


int recursion(Node* l1,Node* l2)
{
    if(l1->next==NULL && l2->next==NULL)
    {
        if(l1->data-l2->data<0)
        return -1;
        if(l1->data-l2->data>0)
        return 1;
        return 0;
    }
    
   int smallAns=recursion(l1->next,l2->next);
   if(smallAns==-1)
   return -1;
    if(smallAns==1)
   return 1;
   
    if(l1->data-l2->data<0)
        return -1;
        if(l1->data-l2->data>0)
        return 1;
        return 0;
   
    
    
}

Node* reverse(Node* head)
{
    if(head==NULL || head->next==NULL)
    return head;
    
    Node* newTail=head->next;
    Node* smallAns=reverse(head->next);
    newTail->next=head;
    return smallAns;
}


int lseForGCD(Node* l1,Node* l2)
{
     int len1=length(l1);
     int len2=length(l2);
     
     if(len1<len2)
     return -1;
     if(len1>len2)
     return 1;
     
     return recursion(l1,l2);
     
}


int lse(Node* l1,Node* l2,int len2)
{
    int len1=length(l1);
    if(len1<len2)
    return 1;
    if(len1>len2)
    return 0;
    
    // l1=reverse(l1);
    // l2=reverse(l2);
    
     int val=recursion(l1,l2);
     if(val==0 || val==-1)
     return 1;
     else
     return 0;
    
}


Node* gcdHelp(Node* l1,Node*l2)
{
    // output(l1);
    // cout<<" ";
    // output(l2);
    // cout<<"\n";
    Node* n=new Node;
    n->data=0;
    n->next=NULL;
    int val=lseForGCD(l1,n);
    if(val==0)
    return l2;
    
    
    n->data=0;
    n->next=NULL;
    val=lseForGCD(l1,n);
    if(val==0)
    return l1;
    
    
    val=lseForGCD(l1,l2);
    if(val==0)
    return l1;
    
    // if(val<0)
    // return gcdHelp(l1,subtractionHelp(l2,l1,0));
    
    if(val<0)
    {
        Node* temp=subtractionHelp(l2,l1,0);
        temp=removeLeadingZeros(temp);
        return gcdHelp(l1,temp);
    }
    
     Node* temp=subtractionHelp(l1,l2,0);
     temp=removeLeadingZeros(temp);
        return gcdHelp(temp,l2);
    
    // return gcdHelp(subtractionHelp(l1,l2,0),l2);
}


Node* gcd(char arr1[],char arr2[],int n1,int n2){
    
    
    Node* ll1=arrayToList(arr1,n1);
    Node* ll2=arrayToList(arr2,n2);
    
    return gcdHelp(ll1,ll2);
    
}


Node* factorial(char arr[],int n)
{
    
    
     Node* one=new Node;
     one->data=1;
     one->next=NULL;
          
          
     Node* l1=arrayToList(arr,n);
     int len=length(l1);
     
      Node* l2=new Node; 
      l2->data=1;
      l2->next=NULL;
      
      
       Node* ans=new Node; 
      ans->data=1;
      ans->next=NULL;
      
      while(lse(l2,l1,len))
      {
        
          ans=multiply2LL(l2,ans);
          l2=help(l2,one,0);
        //   output(ans);
        //   cout<<"\n";
          
          
      }
      
      return ans;
     
}


 
// Driver code
int main()
{
    // char arr1[] = "99893271223";
    // char arr2[]="9203232392";
    // char arr3[]="32789123";
    // char arr4[]="4874223";
    // int n1 = sizeof(arr1) / sizeof(arr1[0]);
    //  int n2= sizeof(arr2) / sizeof(arr2[0]);
    //   int n3= sizeof(arr3) / sizeof(arr3[0]);
    //   int n4= sizeof(arr4) / sizeof(arr4[0]);
     
     
    //  Node* ans1= multiply(arr1,arr2,n1,n2);
     
    //  Node* ans2=subtraction(arr3,arr4,n3,n4);
    //  Node* bhojan=help(ans1,ans2,0);
    //  output(bhojan);
     
    //  char arr1[] = "102";
    //  char arr2[] = "36";
    //  int n1 = sizeof(arr1) / sizeof(arr1[0]);
    //  int n2= sizeof(arr2) / sizeof(arr2[0]);
    //  Node* res=gcd(arr1,arr2,n1,n2);
    //  output(res);
     
    //  char arr1[] = "100";
    //   int n1 = sizeof(arr1) / sizeof(arr1[0]);
    //  Node* fac=factorial(arr1,n1);
    //  output(fac);
    
    
    
    int day;
    scanf("%d\n",&day);
  switch (day) {
   case 1:
    {
        string s;
        getline(cin, s);
        int n=s.length();
        char array[n + 1];
        strcpy(array, s.c_str());
        unsigned long int val;
        cin>>val;
        Node* ans=exponentiation(array,val,n+1);
        output(ans);
        
        break;
    }
  case 2:
   {
       string s1;
        getline(cin, s1);
        // scanf("\n");
        string s2;
        getline(cin, s2);
        int n1=s1.length();
         int n2=s2.length();
         char arr1[n1+1];
          char arr2[n2+1];
          strcpy(arr1,s1.c_str());
           strcpy(arr2,s2.c_str());
           
    // for (int i = 0; i < n1; i++)
    //     cout << arr1[i];
    //     cout<<"\n";
    //     for (int i = 0; i < n2; i++)
    //     cout << arr2[i];
    //       cout<<"\n";
           Node* ans=gcd(arr1,arr2,n1+1,n2+1);
           output(ans);
           
       break;
   }
   
  case 3:
    {
      string s;
        getline(cin, s);
        int n=s.length();
        char array[n + 1];
        strcpy(array, s.c_str());
        // unsigned long int val;
        // cin>>val;
        Node* ans=factorial(array,n+1);
        output(ans);
        
        break;
    }
  case 4:
    cout << "Thursday";
    break;
    default:
    cout << "wrong input";
  }
     
     
    //  cout<<"\n";
    //  output(ans2);
     
     
    //  Node* ans=exponentiation(arr1,5,n1);
    //  output(ans);
    //  cout<<"\n";
    //  cout<<"\nnrishu\n";
    // Node* ans= multiply(arr1,arr2,n1,n2);
    // output(ans);
    //  cout<<"\n rishu w\n";
    // cout<<arr[5]<<"rishu \n";
    // Node* root = arrayToList(arr, n);
    // display(root);
    return 0;
}