
#include <iostream>

using namespace std;

template<typename K>
class Comparator{
    public:
    int operator()(K* obj1,K* obj2)
    {
        
         if(obj1->operator>(obj2))
        return 1;
        else if(obj1->operator<(obj2))
        return -1;
        else
        return 0;
    }
};

class Student{
    public:
    int roll;
    string name;
    
    public:
    Student(int r,string n)
    {
        this->roll=r;
        this->name=n;
    }
    
    public:
    int operator ==(Student* s2)
    {
        if(this->roll==s2->roll)
        return 1;
        else
        return 0;
    }
    
    
    public:
    int operator >(Student* s2)
    {
        cout<<"greater than : "<<this->roll<<" "<<s2->roll<<"\n";
        if(this->roll>s2->roll)
        return 1;
        else
        return 0;
    }
    
    public:
    int operator <(Student* s2)
    {
         cout<<"less than : "<<this->roll<<" "<<s2->roll<<"\n";
        if(this->roll<s2->roll)
        return 1;
        else
        return 0;
    }
};

template <typename T>
class Node
{
    public:
    T key;
    int h,count;
    Node<T> *right;
    Node<T> *left;
    
    
    public:
    Node(T key)
    {
        // this->key=key;
         this->key=key;
         this->h=0;
		 this->count=1;
         this->right=NULL;
         this->left=NULL;
         
    }
    
    
 
};

template <typename T>
class AVL{
 public : Node<T>* root=NULL; 

 
 int height(Node<T>* curr)
{
    if (curr==NULL)
        return -1;
    return curr->h;
}


 
 int getBalance(Node<T> *curr)
{
    if (curr==NULL)
        return 0;
    return height(curr->left) - height(curr->right);
}
 

 
 Node<T>* rightRotate(Node<T>* curr)
{
	Node<T>* newRoot=curr->left;
    curr->left=newRoot->right;
    newRoot->right=curr;


	curr->h=max(height(curr->left),height(curr->right))+1;
	newRoot->h=max(height(newRoot->left),height(newRoot->right))+1;

	return newRoot;
}


Node<T> *leftRotate(Node<T> *curr)
{
	Node<T> *newRoot=curr->right;
	curr->right=newRoot->left;
	newRoot->left = curr;
	
	
	curr->h=max(height(curr->left),height(curr->right)) + 1;
	newRoot->h=max(height(newRoot->left),height(newRoot->right)) + 1;

	
	return newRoot;
} 
      Node<T>* insert(Node<T>* curr, T key)
    {

	if (curr==NULL){
		Node<T>* newNode=new Node<T>(key);
		return newNode;
	}

	if (key<curr->key)
		curr->left=insert(curr->left,key);
	else if (key> curr->key)
		curr->right=insert(curr->right,key);
	else {
	    curr->count+=1;
		return curr;
	}

	curr->h=max(height(curr->left),height(curr->right))+1;
	int bf=getBalance(curr);



	
	if (bf>1 && key<curr->left->key)
		return rightRotate(curr);

	if (bf<-1 && key>curr->right->key)
		return leftRotate(curr);


	if (bf>1 && key>curr->left->key)
	{
		curr->left=leftRotate(curr->left);
		return rightRotate(curr);
	}
	
	if (bf<-1 && key<curr->right->key)
	{
		curr->right=rightRotate(curr->right);
		return leftRotate(curr);
	}


	return curr;
}


  void insert(T key)
  {
    root=insert(root,key);
   }
   
   
    void inOrder(Node<T>* curr)
   {
       if(curr==NULL)
       return;
       inOrder(curr->left);
       cout<<curr->key<<"(count : "<<curr->count<<") ";
       inOrder(curr->right);
   }
   void inOrder()
   {
       cout<<"Inorder is : \n";
       inOrder(root);
       cout<<"\n";
   }
   
   
   
   void preOrder(Node<T>* curr)
   {
       if(curr==NULL)
       return;
       cout<<curr->key<<"(count : "<<curr->count<<") ";
       preOrder(curr->left);
       preOrder(curr->right);
   }
   void preOrder()
   {
       cout<<"Preorder is : \n";
       preOrder(root);
       cout<<"\n";
   }
   
   
   int countOccurences(Node<T>* curr,T key)
   {
       if (curr==NULL)
       return 0;
    
    if(curr->key==key)
	return curr->count;
    else  if (curr->key<key)
    return countOccurences(curr->right,key);
    else
    return countOccurences(curr->left,key);
       
   }
   
   int countOccurences(T key)
   {
       return countOccurences(root,key);
   }
   
   bool search(T key)
   {
        // cout<<"sonam\n";
        int count=countOccurences(root,key);
        
        return (count>0);
   }
   
   
   T ceilValue(Node<T>* curr,T key)
{
   
    if (curr==NULL)
        return -2147483648;
 
   
    if (curr->key == key)            // if found it is itself upper bound or lower bound
        return curr->key;
 
    if (curr->key<key)
        return ceilValue(curr->right, key);
 
   
    T leftAns=ceilValue(curr->left,key);
	if(leftAns>=key)
	return leftAns;
	else
	return curr->key;
   
}

T ceilValue(T key)
{
    return ceilValue(root,key);
}


T floorValue(Node<T>* curr, int key)
{
    if (curr==NULL)
        return 2147483647;
 
   
    if (curr->key==key)
        return curr->key;
 
   
    if (curr->key>key)
        return floorValue(curr->left,key);
 
   
    T rightAns=floorValue(curr->right,key);
	if(rightAns<=key)
	return rightAns;
	else
	return curr->key;
	
   
}


T floorValue(T key)
{
    return floorValue(root,key);
}


T closestValue(T key)
{
    T upper=ceilValue(root,key);
    T lower=floorValue(root,key);
     int diff1=upper-key;
     int diff2=key-lower;
     return diff1<diff2?upper:lower;
}


int range(Node<T>* curr,int low,int high)
{
   
    if (curr==NULL) 
	return 0;
 
   
    if (curr->key == high && curr->key == low)
        return curr->count;
 
    if (curr->key<=high && curr->key>=low)
         return  curr->count + range(curr->left,low,high)+range(curr->right,low,high);
 
   
    else if (curr->key>high)
	      return range(curr->left,low,high);
 
    else
	      return range(curr->right,low,high);
}


int range(int low,int high)
{
    return range(root,low,high);
}



Node<T>* maxInLeftSubtree(Node<T>* curr)
{
	Node<T>* temp=curr;
	while (temp->right!=NULL)
		temp=temp->right;
	return temp;
}




Node<T>* deleteNode(Node<T>* curr,T key)
{
	
	
	if (curr==NULL)
		return curr;

	if (key<curr->key)
		curr->left=deleteNode(curr->left,key);

	else if(key>curr->key)
		curr->right=deleteNode(curr->right,key);

	
	else
	{
	      if(curr->count==1){                                                                // delete a node only when it occurs once
				
				if(curr->left==NULL && curr->right==NULL){                                // remove the leaf node                               
				free(curr);
				return NULL;
				}
				else if(curr->left==NULL && curr->right!=NULL){                          // remove a node with only 1 child (right child)
				 Node<T>* store=curr->right;
				 free(curr);
				 return store;
				}
				else if(curr->left!=NULL && curr->right==NULL)  {                         // remove a node with only 1 child (left child)
				   Node<T>* store=curr->left;
				   free(curr);
				   return store;
				}
				else                                                                        // remove node with 2 children        
				{
					Node<T>* leftMax=maxInLeftSubtree(curr->left);
					curr->key=leftMax->key;
					curr->right= deleteNode(curr->left,leftMax->key);
				}
			}
			
			             
         else{                                                                             // if key occurs more than once just decrease its count by 1
		         curr->count= curr->count-1; 
				 return curr;
		 }
		 
	}

	
	if (curr == NULL)
	return curr;
	
	


	curr->h=1+max(height(curr->left),height(curr->right));
	int bf=getBalance(curr);


	
	if (bf==2 && getBalance(curr->left)>=0)                                                 // Left Left Imbalance
		return rightRotate(curr);

	if (bf==2 && getBalance(curr->left)<0)                                                  // Left Right Imbalance
	{
		curr->left=leftRotate(curr->left);
		return rightRotate(curr);
	}

	if (bf==-2 && getBalance(curr->right)<=0)                                           // Right Right Imbalance
		return leftRotate(curr);

	if (bf==-2 && getBalance(curr->right)>0)                                           // Right Left Imbalance
	{
		curr->right=rightRotate(curr->right);
		return leftRotate(curr);
	}

	return curr;
}

Node<T>* deleteNode(T key)
{
    return deleteNode(root,key);
}

void kthLargest(Node<T>* curr,int k,int &countTillNow)
{
    if(curr==NULL)  
        return;
    if(countTillNow>=k)
        return;
    kthLargest(curr->right,k,countTillNow);
    countTillNow++;
 
    if (countTillNow==k){
       cout<<curr->key<<"\n";
	    return ;
		}
    kthLargest(curr->left,k,countTillNow);
}


void kthLargest(int k)
{
    int countTillNow=0;
     kthLargest(root,k,countTillNow);
}


Node<T>* upperBound(Node<T>* curr,Node<T>* parent,T key){

    if (curr==NULL)
        return parent;

    if (curr->key<=key)
        return upperBound(curr->right,curr,key);
 
      
    Node<T>* leftAns=upperBound(curr->left,curr,key);
	if(leftAns->key>key)
	return leftAns;
	else
	return curr;
	}
	
void upperBound(T key)
{
    if(root==NULL)
    {
        cout<<"upperBound does not exist\n";
        return;
    }
    Node<T>* ans=upperBound(root,NULL,key);
    if(ans->key>key)
    cout<<ans->key<<"\n";
    else
    cout<<"upperBound does not exist\n";
}


void lowerBound(T key)
{
    if(root==NULL)
    {
        cout<<"lowerBound does not exist\n";
        return;
    }
   
    if(search(key)){
    cout<<key<<"\n";
    return;
    }
    Node<T>* ans=upperBound(root,NULL,key);
    if(ans->key>key)
    cout<<ans->key<<"\n";
    else
    cout<<"lowerBound does not exist\n";
}



};

int main()
{
    
    AVL<double> *t=new AVL<double>();
    for(int i=5;i<=50;i+=5){
    t->insert(i+0.5);
    t->preOrder();
    t->inOrder();
    cout<<"\n";
    }
    
    
    
    t->insert(25);
    t->preOrder();
    t->inOrder();
    
    cout<<"\n";
    cout<<"\n";
    cout<<t->root->key<<" "<<t->root->h<<"\n";
    
    cout<<"search 25 : "<<t->search(25)<<"\n";
    cout<<"number of times 25 appear : "<<t->countOccurences(25)<<"\n";
    
    cout<<"upper bound of 60 : "<<t->ceilValue(60)<<" and lower Bound of 60 : "<<t->floorValue(60)<<"\n";
     cout<<"upper bound of 2 : "<<t->ceilValue(2)<<" and lower Bound of 2 : "<<t->floorValue(2)<<"\n";
     
     cout<<"closest value to 60 : "<<t->closestValue(60)<<"\n";
     cout<<"Numbers in range 21 and 30 : "<<t->range(21,30)<<"\n"; 
     
     
      t->upperBound(0) ;
      t->upperBound(1) ;
      t->upperBound(5) ;
      t->upperBound(6) ;
      t->upperBound(11);
      t->upperBound(15);
      t->upperBound(50) ;
      t->upperBound(60) ;
      t->upperBound(49) ;
      
      cout<<"\n";
      cout<<"\n";
        cout<<"\n";
      
       
      t->lowerBound(0);
      t->lowerBound(1);
     t->lowerBound(5);
     t->lowerBound(6);
    
     
      t->lowerBound(11);
      t->lowerBound(15);
     t->lowerBound(50);
     t->lowerBound(60);
      t->lowerBound(49);
     
     
     
      cout<<"\n";
      cout<<"\n";
        cout<<"\n";
     
     
   
     t->deleteNode(25);
     
      cout<<"search 25 : "<<t->search(25)<<"\n";
    cout<<"number of times 25 appear : "<<t->countOccurences(25)<<"\n";
    
    
    
     t->deleteNode(25);
     
      cout<<"search 25 : "<<t->search(25)<<"\n";
    cout<<"number of times 25 appear : "<<t->countOccurences(25)<<"\n";
    
     t->inOrder();
    cout<<"\n";
     
     t->kthLargest(9);
    
    // AVL<string> *t=new AVL<string>();
    // t->insert("a");
    // t->insert("j");
    // t->insert("h");
    // t->insert("f");
    // t->insert("i");
    // t->insert("e");
    // t->insert("g");
    
    //  t->inOrder();
    // cout<<"\n";
    
    // t->upperBound("a");
    // t->lowerBound("a");
    
    
    //   t->upperBound("b");
    // t->lowerBound("b");
    
    
    //   t->upperBound("g");
    // t->lowerBound("g");
    
    
    //   t->upperBound("j");
    // t->lowerBound("j");
    
    
    //   t->upperBound("k");
    // t->lowerBound("k");
    
    Comparator<Student> *cmp=new Comparator<Student>();
    
    AVL<Student> *tree=new AVL<Student>();
    Student *s1=new Student(2,"rishu");
    Student *s2=new Student(1,"ishu");
    cout<<cmp->operator()(s1,s2)<<": rishu\n";
    
    return 0;
}
