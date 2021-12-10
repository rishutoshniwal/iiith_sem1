class LRUCache{
	int capacity=0;
	public:
	class Node{
        public:
		Node *next,*prev;
		int key,val;
		public:
        Node(int key,int val)
        {
            this->key=key;
            this->val=val;
			this->next=NULL;
			this->prev=NULL;
        }
    };
	
	unordered_map<int, Node*> cache;
    Node* head=new Node(-1,-1);
    Node* tail=new Node(-1,-1);
	
	LRUCache(int capacity)
	{
		this->capacity=capacity;
        tail->prev=head;
		head->next=tail;
		
	}
	
	void add(Node* newNode)
	{
		newNode->next=head->next;
		newNode->prev=head;
		head->next->prev=newNode;
		head->next=newNode;
	}
	
	void toDelete(Node* del)
	{
		del->next->prev=del->prev;
		del->prev->next=del->next;
        //free(del);
        del->next=NULL;
        del->prev=NULL;
		
	}
	
	int get(int key)
    {
        if(cache.find(key)!=cache.end())
        {
            Node* temp=cache[key];
            int val=temp->val;
            cache.erase(key);
            toDelete(temp);
            add(temp);
            cache[key]=head->next;
            return val;
        }
		else
        return -1;      
    }
	
	
	void put(int key,int value)
    {
        if (cache.find(key)!=cache.end())
        {
            Node* temp=cache[key];
            cache.erase(key);
            toDelete(temp);
        }
        if (cache.size()>=capacity)
        {
            cache.erase(tail->prev->key);
            toDelete(tail->prev);
        }
		Node* newNode=new Node(key,value);
        add(newNode);
        cache[key]=head->next;
    }

	
};