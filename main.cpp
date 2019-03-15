εκτυπωση δενδρου
#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>
using namespace std;


struct Node              
{
    int data;           
    bool deleted;       
    Node* left;         
    Node* right;       };

Node* NewNode(int data)
{
    Node* newNode=new Node();              
    newNode->data=data;
    newNode->deleted=false;           
    newNode->left=newNode->right=NULL;
    return newNode;
}

Node* Insert(Node* root,int data) 

    if(root==NULL
        root=NewNode(data);          
   
    else if(data<=root->data)              
        root->left=Insert(root->left,data);
    else 
        root->right=Insert(root->right,data);  
    return root;
}

int FindHeight(Node* root)
{
    if (root==NULL)
       return -1;                                      
    return max(FindHeight(root->left),FindHeight(root->right))+1;   
}

void MarkDeleted(Node* root,int data)    
{
    if(root==NULL)
        return ;
    else if(root->data==data && root->deleted==false)
        root->deleted=true;
    else if(data<=root->data)
        MarkDeleted(root->left,data);                  
    else if(data>=root->data)                          
        MarkDeleted(root->right,data); 
}

int FindMin(Node* root)
{
    if(root==NULL)
    {
        cout<<"The tree is empty "<<endl;
        return -1;
    }
    while(root->left!=NULL
        root=root->left;                     
    return root->data;  
}

int FindMax(Node* root)
{
    if(root==NULL)
    {
        cout<<"The tree is empty "<<endl;
        return -1;
    }
    while(root->right!=NULL)               
        root=root->right;                  
    return root->data;  
} 

Node* CreatefromList(list<int> &list,int start,int end)         
{

    if (start > end) 
	    return NULL;
   int mid = start + (end - start) / 2;
   Node *leftChild=CreatefromList(list, start, mid-1);        
   Node *root=NewNode(list.front());                      
   root->left=leftChild;                             list.pop_front();  
   root->right = CreatefromList(list, mid+1, end);            

  return root;
}
int Count(Node* root)
{	
    if(root==NULL )
        return 0;
    else
        if( root->left == NULL && root->right == NULL)
            return 1;
        else
            return(1 + (Count(root->left) + Count(root->right)));   
}
void Inorder(Node* root,list<int> &l)
{
	
    if (root==NULL) 
        return;                             
                                            
    Inorder(root->left,l);               
    if(root->deleted==false)
   {
        l.push_back(root->data);  
   }
   Inorder(root->right,l);     	
} 
/*<------Μεθοδος διαγραφης κομβου------>*/ 
Node* Delete(Node* root,int data,int &deleted,Node* ConstRoot)
{
    if(root==NULL) 
        return root;
    else if(data<root->data)                                          
        root->left=Delete(root->left,data,deleted,ConstRoot); 
    else if(data>root->data)                                  
        root->right=Delete(root->right,data,deleted,ConstRoot);    
    else       
    {                                                        
        if(root->left==NULL && root->right==NULL)            
        {                                                    
            delete root;
            root=NULL;
        }      
        else if(root->left==NULL)                          
        {
            Node* tmp=root;
            root=root->right;                             
            delete tmp;                                   
        }
        else if(root->right==NULL)                        
        {
            Node* tmp=root;                              
            root=root->left;
            delete tmp;
        }               
        else                                           
        {
            MarkDeleted(root,data);                    
			deleted++;                                 
        }
    }
    if(deleted>Count(ConstRoot)/3)              
    {
    	cout<<"Formating the tree nodes";
	    list<int> Treefix; 
		Inorder(root,Treefix);                  		root=NULL;                 
		root=CreatefromList(Treefix,1,Treefix.size()); 
	}          
    return root;     
}

bool Search(Node* root,int data)    
{
    if(root==NULL)
        return false;
    else if(root->data==data && root->deleted==false)
        return true;
    else if(data<=root->data)                              return Search(root->left,data);          
    else if(data>=root->data)
        return  Search(root->right,data);       
}

void FindBetween(int k1,int k2,Node*root)
{    
    int max= (k1>k2)?k1:k2;                   
    int min=(k1<k2)?k1:k2;
    if(root==NULL)
        return ;                            
    if(min<root->data)
        FindBetween(k1,k2,root->left);      
    if(min<=root->data && max>=root->data)
        cout<<root->data<<" ";            
    if(max>root->data)                  
        FindBetween(k1,k2,root->right);           
} 
/*<------Μεθοδος εκτυπωσης δεντρου------>*/ 
void PrintBFS(Node*root)                
{
    if(root==NULL)
        return;
    int Height=FindHeight(root);       
    queue<Node*> Queue;               
    Queue.push(root);
    int node=1;                     
    int level=0;                    
    Node* curr;                                          
    int spaces = 4 * (pow(2 , Height -level));  
    while(!Queue.empty() && level!=Height+1)   
    {
        int nodeCount=0;
        while(nodeCount<node)                 
        {
   	        cout << setw(spaces/2);
   	        if(Queue.front()!=NULL  )
   	       {
                curr=Queue.front();
                cout<<curr->data;
           }
           else 
            {
                cout<<"";                  
                Queue.push(NULL);          
                Queue.push(NULL);
            }
        
            if(Queue.front()!=NULL)   
   	       { 
                if(curr->left!=NULL)
                    Queue.push(curr->left);
                else
                    Queue.push(NULL);
                if(curr->right!=NULL)
                    Queue.push(curr->right);
                else	
		            Queue.push(NULL);
	       }
           cout << setw(spaces/2)<< "";
           Queue.pop();            
           nodeCount++;
           if(Queue.empty())
                break;
        } 
        level++; 
        spaces = 4 * (pow(2, Height -level));
        cout<<endl;   
        node=node*2;      
   }              
}  
 
 
int main()
{
bool exists;	
int deleted=0;
Node* root=NULL;
int choice;
int choice2;

 while(1)
    {
       cout<<endl;
       cout<<" Binary Search Tree Operations "<<endl;
       cout<<" <-----------------------------> "<<endl;
       cout<<" 1. Insertion/Creation of Node "<<endl;
       cout<<" 2. Find Min Node"<<endl;
       cout<<" 3. Find Max Node"<<endl;
       cout<<" 4. Find Nodes Between a distance"<<endl;
       cout<<" 5. Search a Node"<<endl;
       cout<<" 6. Delete a Node"<<endl;
       cout<<" 7. Print the Tree"<<endl;
       cout<<" 8. Exit "<<endl;
       cout<<" Enter your choice in numeric input: ";
       cin>>choice;
       switch(choice)
       {
           case 1 : cout<<" Enter Number to be inserted : ";
                    cin>>choice;
                    root=Insert(root,choice);
                    break;
           case 2 : cout<<endl;
                    cout<<" <---Min Node---> "<<endl;
                    cout<<FindMin(root);
                    break;
           case 3 : cout<<endl;
                    cout<<" <---Max Node---> "<<endl;
                    cout<<FindMax(root);
                    break;
           case 4 : cout<<endl;
                    cout<<" Enter the min number of the distance : "<<endl;
                    cin>>choice;
                    cout<<" Enter the max number of the distance : "<<endl;
                    cin>>choice2;
                    cout<<"<---Find Between "<<choice<<" and "<<choice2<<"--->"<<endl;
                    FindBetween(choice,choice2,root);
                    break;
           case 5:  cout<<endl;
                    cout<<" Enter the number to search  : ";
                    cin>>choice;     
                    exists=Search(root,choice);
                    if(exists)
					    cout<<endl<<"Number exists";
					else
					    cout<<endl<<"Number doesnt exists";
                    break;
           case 6 : cout<<endl;
		            cout<<" Enter data to be deleted : ";
                    cin>>choice;
                    root=Delete(root,choice,deleted,root);
                    break;
           case 7 : cout<<endl; 
		            cout<<"<--------BinarySearchTree------------>"<<endl;
					PrintBFS(root);  
					break;  
           case 8 : cout<<endl;
                    return 0;  
       }
   }
system("PAUSE");
return EXIT_SUCCESS;     
}
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
