

#include <iostream>
using namespace std;

// Representation of a node
template <typename T>
struct Node {
    int r,c;
	T data;
	Node* next;
};


// Function to insert node
template <typename T>
void insert(Node<T>** root, T item,int r,int c)
{
	Node<T>* temp = new Node<T>;
	Node<T>* ptr;
	temp->data = item;
	temp->r=r;
	temp->c=c;
	temp->next = NULL;

	if (*root == NULL)
		*root = temp;
	else {
		ptr = *root;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = temp;
	}
}

template <typename T>
void matrixInTriplet(Node<T>* root)
{
    Node<T>* temp=root;
	while (temp!=NULL) {
		cout<<temp->r<<" "<<temp->c<<" "<<temp->data << "\n";
		temp=temp->next;
	}
}

template <typename T>
Node<T>* transpose(T* arr, int r,int c)
{
	Node<T> *root = NULL;
	 for(int j=0;j<c;j++)
	 {
	     for(int i=0;i<r;i++){
	         if(*(arr+i*c+j)!=0)
		     insert(&root, *(arr+i*c+j),j,i);
	     }
	 }
     return root;
}


template <typename T>
Node<T>* giveTriplet(T* arr, int r,int c)
{
    Node<T> *root = NULL;
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
             if(*(arr+i*c+j)!=0)
		     insert(&root, *(arr+i*c+j),i,j);
        }
        
    }
    return root;
}


template<class T> 
void addition(T *a, int r1,int c1,T *b, int r2,int c2)
{
        if(r1!=r2 || c1!=c2){
        return;
        }
        	Node<T>* ll1 =giveTriplet(a,r1,c1);
        	Node<T>* ll2 =giveTriplet(b,r2,c2);
        // 	matrixInTriplet(ll1);
        // 	cout<<"rishu\n";
        // 	matrixInTriplet(ll2);
        // 	cout<<"rishu\n";
        
        
        	Node<T>* sum=help(ll1,ll2);
        	matrixInTriplet(sum);
        // 	cout<<"rishu\n";
        // 	transpose(sum);
        		
}

template<class T>
Node<T>* help(Node<T>* ll1,Node<T>* ll2){
    if(ll1==NULL && ll2==NULL)
    return NULL;
    
    if(ll1==NULL)
    return ll2;
    if(ll2==NULL)
    return ll1;
    
    if(ll1->r == ll2->r  && ll1->c == ll2->c){
    Node<T>* temp = new Node<T>;
	temp->data=ll1->data+ll2->data;
	temp->r=ll1->r;
	temp->c=ll1->c;
	temp->next = help(ll1->next,ll2->next);
	return temp;
    }
    
    if(ll1->r == ll2->r  && ll1->c < ll2->c){
        ll1->next=help(ll1->next,ll2);
        return ll1;
    }
    
    if(ll1->r == ll2->r  && ll1->c > ll2->c){
        ll2->next=help(ll1,ll2->next);
        return ll2;
    }
    
    if(ll1->r < ll2->r){
          ll1->next=help(ll1->next,ll2);
        return ll1;
    }
    
    
     ll2->next=help(ll1,ll2->next);
        return ll2;
    
    
}


template <typename T> Node<T>* merge(Node<T>* head1,Node<T>* head2)
{
    Node<T>* head3=NULL;
    Node<T>* tail3=NULL;
    
    if(head1->r > head2->r)
    {
        head3=head2;
        tail3=head2;
        head2=head2->next;
    }
    else if(head1->r < head2->r)
    {
            head3=head1;
            tail3=head1;
            head1=head1->next;
    }
    else
    {
         if(head1->c >= head2->c)
         {
            head3=head2;
            tail3=head2;
            head2=head2->next;
        }
        else
        {
             head3=head1;
            tail3=head1;
            head1=head1->next;
        }
    }
    
    
    while(head1!=NULL && head2!=NULL)
    {
        if(head1->r > head2->r)
        {
            tail3->next=head2;
            tail3=tail3->next;
            head2=head2->next;
        }
         else if(head1->r < head2->r)
         {
              tail3->next=head1;
               tail3=tail3->next;
               head1=head1->next;
         }
         else{
             if(head1->c >= head2->c)
             {
                 tail3->next=head2;
                 tail3=tail3->next;
                 head2=head2->next;
             }
             else{
               tail3->next=head1;
               tail3=tail3->next;
               head1=head1->next;                
             }
         }
        
    }
    
    
    while(head1!=NULL)
    {
               tail3->next=head1;
               tail3=tail3->next;
               head1=head1->next;      
    }
    
    while(head2!=NULL)
    {
         tail3->next=head2;
                 tail3=tail3->next;
                 head2=head2->next;
    }
    
    return head3;
}

template <typename T> Node<T>* findMiddle(Node<T>* head)
{
    Node<T>* fast=head;
    Node<T>* slow=head;
    
    while(fast->next!=NULL && fast->next->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

template <typename T> Node<T>* mergesort(Node<T>* head)
{
    if(head==NULL || head->next==NULL)
    return head;
    
    Node<T>* mid=findMiddle(head);
    Node<T>* head2=mid->next;
    mid->next=NULL;
    
    Node<T>* temp1=mergesort(head);
    Node<T>* temp2=mergesort(head2);
    Node<T>* head3=merge(temp1,temp2);
    return head3;
}

template <typename T> void multiplication(T *a, int r1,int c1,T *b, int r2,int c2)
{
    if(c1!=r2)
    return;
    
    	    Node<T>* ll1 =giveTriplet(a,r1,c1);
        	Node<T>* ll2 =transpose(b,r2,c2);
        	
        	
        // 	matrixInTriplet(ll1);
        // 	cout<<"amar hain hum \n";
        // 	matrixInTriplet(ll2);
        	
        	 Node<T>* head=NULL;
        	 Node<T>* tail=NULL;
        	
        // 	int count=0;
        	 Node<T>* temp1=ll1;
        	 while(temp1!=NULL)
        	 {
        	     Node<T>* temp2=ll2;
        	      while(temp2!=NULL){
        	          if(temp1->c == temp2->c)
        	          {
        	           //   count++;
        	              Node<T>* temp = new Node<T>;
	                      temp->data=temp1->data*temp2->data;
	                      temp->r=temp1->r;
                          temp->c=temp2->r;
                          temp->next=NULL;
                          
                          if(head==NULL && tail==NULL)
                          {
                              head=temp;
                              tail=temp;
                          }
                          else{
                          tail->next=temp;
                          tail=tail->next;
                          }
                          
        	          }
        	          temp2=temp2->next;
        	      }
        	     temp1=temp1->next;
        	 }
        
        temp1=head;
        while(temp1!=NULL)
        {
            Node<T>* temp2=temp1->next;
            while(temp2!=NULL)
            {
                if(temp1->r==temp2->r && temp1->c==temp2->c)
                {
                    temp1->data=temp1->data+temp2->data;
                    temp2->r=-1;
                    temp2->c=-1;
                }
                temp2=temp2->next;
            }
            
            
            temp1=temp1->next;
        }
        
        // cout<<" : sardar khan \n";
        head=mergesort(head);
        
        Node<T>* itr=head;
	    while (itr!=NULL) {
	    if(itr->r!=-1 && itr->c!=-1)
		cout<<itr->r<<" "<<itr->c<<" "<<itr->data << "\n";
		itr=itr->next;
	}



    
}
// Driver code
int main()
{
    // cout<<"rishu";
//   int arr1[3][3] =
//     {
//       {0,0,1},
//       {2,1,0},
//       {0,4,3}
//     };
    
    
    // transpose(*arr1,3,4);
    //  int arr2[3][3] =
    // {
       
    //   {0,0,7},
    //   {6,3,0},
    //   {5,0,0}
    // };
    // cout<<"rishu\n";
    // multiplication(*arr1,3,3,*arr2,3,3);
    
    // addition(*arr,3,3,*arr2,3,3);
    
    // Node<int>* ans=transpose(*arr,3,3);
    // matrixInTriplet(ans);
    
    // Node<int>* ll2 =giveTriplet(*arr2,4,2);
    // matrixInTriplet(ll2);
    
    
// 	Node<int>* root = transpose(*arr,3,4);
// 	matrixInTriplet(root);
// 	cout<<"rishu\n";
// 	Node<int>* root1 = giveTriplet(*arr,3,4);
// 	matrixInTriplet(root1);
// cout<<"rishu";
	return 0;
}
