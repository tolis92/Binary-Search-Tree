//WARNING!υλοποιηθηκε σε c++ με χρηση του DEV-C++ IDE 5.11,υπηρξε προβλημα-bug σε παλαιοτερη εκδοση αυτου κατα την εκτυπωση δενδρου
#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <list>
using namespace std;

/*<----Δομη ενος Κομβου---->*/
struct Node              //Δομη με χρηση Pointers σε Ηeap ,Σε ολες της μεθοδους κυριαρχει η αναδρομικοτητα
{
    int data;           //Το στοιχειο του κομβου
    bool deleted;       //boolean για την τροποποιημενη διαγραφη 
    Node* left;         //Pointer στο αριστερο παιδι 
    Node* right;       //Pointer στο δεξι παιδι
};
/*<----Μεθοδος δημιουργιας Κομβου---->*/
Node* NewNode(int data)
{
    Node* newNode=new Node();              
    newNode->data=data;
    newNode->deleted=false;            //αρχικοποιηση ολων των στοιχειων της δομης 
    newNode->left=newNode->right=NULL;
    return newNode;
}
/*<----Μεθοδος εισαγωγης Κομβου---->*/
Node* Insert(Node* root,int data) 
{                               //(δεν εγινε τροποποιηση λογο της απαιτουμενης μεθοδολογιας διαγραφης,δεν ευρισκα την ουσιωδη διαφοροποιηση)
    if(root==NULL)                   //Αν δεν υπαρχει στοιχειο στην ριζα του δεντρου η υποδεντρου τοτε δημιουργησε(κυρια λειτουργια) 
        root=NewNode(data);          
   
    else if(data<=root->data)              //Αλλιως αν το στοιχειο ειναι μικροτερο απο την ριζα, αναδρομικα       
        root->left=Insert(root->left,data); //κανε εισαγωγη στο αριστερο υποδεντρο 
    else 
        root->right=Insert(root->right,data);  //Αλλιως κανε εισαγωγη στο δεξιο υποδεντρο
    return root;
}
/*<----Βοηθητικη Μεθοδος ευρεσης υψους δεντρου---->*/
int FindHeight(Node* root)
{
    if (root==NULL)
       return -1;                                      
    return max(FindHeight(root->left),FindHeight(root->right))+1;   //Λειτουργει αναδρομικα και προσαυξανετε κατα 1
}
/*<----Βοηθητικη Μεθοδος σημειωσεις κομβους σε διαγραμενο---->*/ 
void MarkDeleted(Node* root,int data)    
{
    if(root==NULL)
        return ;
    else if(root->data==data && root->deleted==false)
        root->deleted=true;
    else if(data<=root->data)
        MarkDeleted(root->left,data);                  //Λειτουργει αναδρομικα με μεθοδος αναζητησης στο αντιστοιχο υποδεντρο 
    else if(data>=root->data)                          //μεχρι την ευρεση του επιθυμητου στοιχειου και επειτα σημειωση ως διεγραμμενο
        MarkDeleted(root->right,data); 
}
/*<----Μεθοδος ευρεσης ελαχιστου---->*/ 
int FindMin(Node* root)
{
    if(root==NULL)
    {
        cout<<"The tree is empty "<<endl;
        return -1;
    }
    while(root->left!=NULL)                  //Αναζητηση στο αριστερο υποδεντρο του ποιο αριστερα κομβου  
        root=root->left;                     //οπου αντιστοιχη το min στοιχειο με βαση την δομη ενος BST
    return root->data;  
}
/*<----Μεθοδος ευρεσης μεγιστου---->*/ 
int FindMax(Node* root)
{
    if(root==NULL)
    {
        cout<<"The tree is empty "<<endl;
        return -1;
    }
    while(root->right!=NULL)               //Αναζητηση στο δεξιο υποδεντρο του ποιο δεξιου κομβου  
        root=root->right;                  //οπου αντιστοιχη το mαχ στοιχειο με βαση την δομη ενος BST
    return root->data;  
} 
/*<----Βοηθητικη μεθοδος δημιουργιας δεντρου με χρηση λιστας---->*/ 
Node* CreatefromList(list<int> &list,int start,int end)         //χρησιμοποιητε για την επαναδημιουργια του δεντρου απο ascending list
{

    if (start > end) 
	    return NULL;
   int mid = start + (end - start) / 2;
   Node *leftChild=CreatefromList(list, start, mid-1);        //εισαγωγη με DFS ΙnOrder Traversal  
   Node *root=NewNode(list.front());                      //Λογο της ταξινομησης της λιστας και για την δημιουργια πιθανοτατα"εισοζηγισμενου" δενδρου
   root->left=leftChild;                                      //Πρωτα εισαγωγη στο αριστερο υποδεντρο,μετα στην ριζα
   list.pop_front();                                          //και επειτα στο δεξιο υποδεντρο,τα στοιχεια της λιστας οπως ειναι 
   root->right = CreatefromList(list, mid+1, end);            //ειδη ταξινομημενα 

  return root;
}
/*<----Βοηθητικη μεθοδος Καταμετρησης Κομβων---->*/  
int Count(Node* root)
{	
    if(root==NULL )
        return 0;
    else
        if( root->left == NULL && root->right == NULL)
            return 1;
        else
            return(1 + (Count(root->left) + Count(root->right)));   //Αναδρομικα με προσαυξηση κατα 1 παντα(και +1 ακομα λογο ριζας) 
}
/*<----Βοηθητικη μεθοδος Εισαγωγης σε λιστα---->*/  
void Inorder(Node* root,list<int> &l)
{
	
    if (root==NULL) 
        return;                             //Αναδρομικη λειτουργια
                                            
    Inorder(root->left,l);               //Χρηση DFS Ιnorder Traversal για εισαγωγη σε αυξουσα σειρα 
    if(root->deleted==false)               //των στοιχειων στην λιστα,χωρις υπολογισμο των σημειωμενων ως διεγραμενα
   {
        l.push_back(root->data);  
   }
   Inorder(root->right,l);     	
} 
/*<------Μεθοδος διαγραφης κομβου------>*/ 
Node* Delete(Node* root,int data,int &deleted,Node* ConstRoot)//χρηση 2ης μεταβλητης για την root λογο τροποποιησης της πρωτης
{
    if(root==NULL) 
        return root;
    else if(data<root->data)                                          
        root->left=Delete(root->left,data,deleted,ConstRoot); //Αναζητηση του στοιχειου προς διαγραφη στο αντιστοιχα υποδεντρα 
    else if(data>root->data)                                  //με βαση το μεγεθος του και σε σχεση με την καθε ριζα καθε φορα                                             
        root->right=Delete(root->right,data,deleted,ConstRoot);    
    else                                                     //το στοιχειο βρεθηκε
    {                                                        //3 περιπτωσης διαγραφης 
        if(root->left==NULL && root->right==NULL)            // 1.Ο κομβος να μην εχει παιδια
        {                                                    //Οποτε απλος διαγραφεται και η υπαρξη του ειναι πλεον ΝULL
            delete root;
            root=NULL;
        }      
        else if(root->left==NULL)                          //2.α Να εχει δεξι παιδι μονο
        {
            Node* tmp=root;
            root=root->right;                             //Οποτε το παιδι του παιρνει την θεση του(ως εννοιεoς κομβος και οχι μονο ως value) 
            delete tmp;                                   //Και αυτο διαγραφεται
        }
        else if(root->right==NULL)                        //2.β Να εχει δεξι παιδι μονο
        {
            Node* tmp=root;                              
            root=root->left;
            delete tmp;
        }               
        else                                            //3.Na ειναι εσωτερικος κομβος,με δυο παιδια
        {
            MarkDeleted(root,data);                    //Οποτε απλος σημειωνεται ως διεγραμμενο με χρηση βοηθητικης μεθοδου
			deleted++;                                 //Και προσαυξανετε το πληθος των διεγραμενων
        }
    }
    if(deleted>Count(ConstRoot)/3)                    //Αν το πληθος των διεγραμενων ξεπερασει το 30% του δεντρου
    {
    	cout<<"Formating the tree nodes";
	    list<int> Treefix; 
		Inorder(root,Treefix);                  //εισαγονται ολα τα μη-διεγραμενα στοιχεια σε μια λιστα σε ascending order
		root=NULL;                                  //αρχικοποιητε η ριζα του δεντρου
		root=CreatefromList(Treefix,1,Treefix.size()); //και επαναδημιουργητε το βελτιστο δεντρο με min υψος με χρηση μεθοδου 	     
	}          
    return root;     
}
/*<------Μεθοδος αναζητησης κομβου------>*/ 
bool Search(Node* root,int data)    //επιστρεφει Boolean 
{
    if(root==NULL)
        return false;
    else if(root->data==data && root->deleted==false)
        return true;
    else if(data<=root->data)                      //αναδρομικη αναζητηση στο αντιστοιχο καθε φορα υποδενδρο
        return Search(root->left,data);           //επιστρεφει true αν βρει την τιμη,η false αν βρεθει σε Null "κομβο" επειτα απο φυλλο
    else if(data>=root->data)
        return  Search(root->right,data);       
}
/*<------Μεθοδος ευρεσης σε διαστημα------>*/ 
void FindBetween(int k1,int k2,Node*root)
{    
    int max= (k1>k2)?k1:k2;                   //Ελεγχος και επαληθευση μεγιστου,ελαχιστου
    int min=(k1<k2)?k1:k2;
    if(root==NULL)
        return ;                            
    if(min<root->data)
        FindBetween(k1,k2,root->left);      //Αναδρομικη κατευθυνση μεχρι το κατω οριο min
    if(min<=root->data && max>=root->data)
        cout<<root->data<<" ";             //Εκτυπωση  οσων ειναι στο διαστημα αυτο
    if(max>root->data)                     //Αναδρομικη κατευθυνση μεχρι το πανω οριο max
        FindBetween(k1,k2,root->right);           
} 
/*<------Μεθοδος εκτυπωσης δεντρου------>*/ 
void PrintBFS(Node*root)                 //Με χρηση BFS μεθοδου,συγκεκριμενο spacing και ειαγωγη null στους μη υπαρκτους κομβους
{
    if(root==NULL)
        return;
    int Height=FindHeight(root);       //ευρεση υψος δεντρου για να γινει σωστη η εκτυπωση του
    queue<Node*> Queue;               //χρηση queue για εισαγωγη των στοιχειων
    Queue.push(root);
    int node=1;                     //Mετρητης μεγιστων κομβων σε καθε επιπεδο
    int level=0;                    //Επιπεδο δεντρου
    Node* curr;                                          
    int spaces = 4 * (pow(2 , Height -level));  //Δημιουργια κενoν για αναπαρασταση δεντρου  
    while(!Queue.empty() && level!=Height+1)    //οσο υπαρχουν ακομα στοιχεια προς εκτυπωση και δεν εχουμε φτασει στο τελευταιο επιπεδο
    {
        int nodeCount=0;
        while(nodeCount<node)                 //Οσο ο μετρητης επιτρεπει την εκτυπωση περαιτερων κομβων σε αυτο το Level
        {
   	        cout << setw(spaces/2);
   	        if(Queue.front()!=NULL  )
   	       {
                curr=Queue.front();
                cout<<curr->data;
           }
           else 
            {
                cout<<"";                  //εκτυπωση κενου σε μη υπαρκτο κομβο
                Queue.push(NULL);          //null στοιχεια ως παιδια του μη υπαρκτου κομβου
                Queue.push(NULL);
            }
        
            if(Queue.front()!=NULL)   //ειαγωηγη των παιδιων στην queue η εισαγωγη null στην θεση τους
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
           Queue.pop();            //αφαιρεση πρωτου στοιχειου στο queue,εκτυπωθηκε ειδη
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
/*<------Μενου πλοηγησης χρηστη------>*/ 
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
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
