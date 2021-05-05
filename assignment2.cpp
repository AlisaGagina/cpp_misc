//
//ALISA GAGINA 260770497
//
#include <iostream>


using namespace std;

class Node {       // The class
  public:             // Access specifier
    int data;        
    Node* next;  
    Node* previous;
    Node();
    ~Node();
    Node( int data, Node* next, Node* previous );
};

Node::Node():data(-1), next(NULL), previous(NULL){}
Node::Node(int data, Node* next, Node* previous):data(data), next(next), previous(previous){}
Node::~Node(){
    //cout << "Destructing Node" << endl;
}

class DLLStructure{
    public:
        DLLStructure();
        DLLStructure(int array [], int size);
        ~DLLStructure();
        void printDLL();
        void InsertAfter( int valueToInsertAfter, int valueToBeInserted);
        void InsertBefore( int valueToInsertBefore, int valueToBeInserted);
        void Delete(int value);
        void Sort();
        bool IsEmpty();
        int getHead();
        int getTail();
        int getSize();
        int getMax();
        int getMin();
        DLLStructure(DLLStructure& dlls);



        Node* first;
        Node* last;
        int size;
};

DLLStructure::DLLStructure():first(NULL), last(NULL), size(0){};
DLLStructure::DLLStructure(int array [], int size){
    Node* f=new Node(array[0], NULL, NULL);
    this->first=f;
    this->last=f;
    this->size=size;
    for(int i=1; i<size; i++){
        Node* newNode= new Node(array[i], NULL, last);
        last->next=newNode;
        this->last=newNode;
    }
}
DLLStructure::~DLLStructure (){
    //cout << "Destructing DLL" << endl;
    Node* current= this->first;
    do{
        current=current->next;
        delete current->previous;
    }while(current!=this->last);
    delete this->last;
}
void DLLStructure :: printDLL(){
    Node* current= this->first;
    do{
        cout << current->data << ", ";
        current=current->next;
    }while(current!=this->last);
    cout << current->data << endl;
}
void DLLStructure::InsertAfter( int valueToInsertAfter, int valueToBeInserted){
    Node* current= this->first;
    while(current->data!=valueToInsertAfter && current != this->last){
        current=current->next;
    }
    Node* tail = current->next;
    Node* newNode = new Node(valueToBeInserted, tail, current);
    if(current == this->last){
        this->last=newNode;
    }else{
        tail->previous=newNode;
    }
    current->next=newNode;
    this->size+=1;
}
void DLLStructure ::InsertBefore( int valueToInsertBefore, int valueToBeInserted){
    Node* current= this->first;
    while(current->data!=valueToInsertBefore && current != this->last){
        current=current->next;
    }
    if(current != this->last){
        //could not figure out how to user Insert after but without inserting before the first occurence of current->previous->data
        //like technically you could change first, and then insert, and then change back??
        this->InsertAfter(current->previous->data, valueToBeInserted);
    }else{
        Node* newNode = new Node(valueToBeInserted, this->first, NULL);
        this->first->previous=newNode;
        this->first= newNode;
        this->size+=1;
    }
}
void DLLStructure::Delete(int value){
    Node* current= this->first;
    while(current->data!=value && current != this->last){
        current=current->next;
    }
    if (current->data==value){
        //if this is the value to be deleted
        this->size-=1;
        if (current== this->first){  //if at front
            this->first = this->first->next;
            this->first->previous=NULL;
            delete current;
        }else if (current == this->last){  //if at end
            this->last = this->last->previous;
            this->last->next=NULL;
            delete current;
        }else{    //has non-null next and previous
            Node* next = current->next;   
            Node* prev = current->previous;
            next->previous=prev;
            prev->next=next;
            delete current;
        }
    }
}
void DLLStructure::Sort(){
//sorta dummy way to avoid messing with pointers:
//get all data, sort data separately, overwrite data of DLL with sorted data

    if(this->first->data==-1){
        return;
    }else{
        Node* current = this->first;
        while(current->next != NULL){
            Node* nxt=current->next; //point to node next to current
            while(nxt!=NULL){
                if(current->data > nxt->data){ //compare values
                    int temp=current->data;
                    current->data=nxt->data;
                    nxt->data=temp;
                }
                nxt=nxt->next;
            }
            current=current->next;
        }
    }     
}
bool DLLStructure::IsEmpty(){
    if (this->first==NULL){
        return true;
    }else{
        return false;
    }
}
int DLLStructure ::getHead(){
    return this->first->data;
}
int DLLStructure ::getTail(){
    return this->last->data;
}

int DLLStructure ::getSize(){
    //Instead of looping over elements, I decided to add a parameter size 
    //to the class DLLStructure instead
    //This parameter is intialized in the constructor. 
    //If there is a deletion / addition operation happening, size is adjusted accordingly
    return this->size;
}

int DLLStructure ::getMax(){
    if(this->IsEmpty()){
        return(-1);
    }else{
        int max=this->first->data;
        Node* current = this->first;
        while(current->next != NULL){
            if(current->data> max){
                max=current->data;
            }
            current=current->next;
        }
        if(current->data> max){
                max=current->data;
            }
        return max;
    }

}
int DLLStructure ::getMin(){
     if(this->IsEmpty()){
        return(-1);
    }else{
        int min=this->first->data;
        Node* current = this->first;
        while(current->next != NULL){
            if(current->data< min){
                min=current->data;
            }
            current=current->next;
        }
        if(current->data< min){
                min=current->data;
        }
        return min;
    }
}

DLLStructure::DLLStructure( DLLStructure& dlls){
    this->size=dlls.size;
    Node* current= dlls.first;
    Node* f=new Node(current->data, NULL, NULL);
    this->first=f;
    this->last=f;
    for(int i=1; i<dlls.size; i++){
        current=current->next;
        Node* newNode= new Node(current->data, NULL, last);  //new Node! new location in memory!
        last->next=newNode;
        this->last=newNode;
    }
}





int main() {
// Q 1, 2, 3 should obviously be implemented successfully
// in order to run the following code
int array[5] = {11, 2, 7, 22, 4};
DLLStructure dll(array, 5); // note that 5 is the size of the array
dll.printDLL(); // the output should be: 11, 2, 7, 22, 4
// Q 4
dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4
dll.InsertAfter(25, 7); // To insert 7 after the first occurence of 25
dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4, 7
// Q 5
dll.InsertBefore(7, 26); // To insert 26 before the first occurence of 7
dll.printDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
dll.InsertBefore(19, 12); // To insert 12 before the first occurence of 19
dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
// Q 6
dll.Delete(22);
dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
// Q 7
dll.Sort();
dll.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
// Q 8
if(dll.IsEmpty()){
    cout << "The list is empty" << endl;
}
// Q 9
cout << "Head element is: " << dll.getHead() << endl;
cout << "Tail element is: " << dll.getTail() << endl;
// Q 10
cout << "Number of elements in the list is: " << dll.getSize() << endl<<endl;
cout <<"QUESTION 10"<<endl<<" Instead of looping over elements, I decided to add a parameter size "<<endl;
cout <<"to the class DLLStructure instead"<<endl;
cout <<"This parameter is intialized in the constructor. "<<endl;
cout <<"If there is a deletion / addition operation happening, size is adjusted accordingly"<<endl<<endl;
// Q 11
cout << "Max element is: " << dll.getMax() << endl;
cout << "Min element is: " << dll.getMin() << endl;
cout <<endl<<"QUESTION 11"<<endl<<" Just like with question 10, the best way would be to add two data members: "<<endl;
cout <<"int max and int min"<<endl;
cout <<"Then these are updated during the constructing process"<<endl;
cout <<"If there is a deletion / addition operation happening, they are also checked and changed if needed"<<endl;
cout <<"Got too lazy to implement this though"<<endl<<endl;

cout <<endl<<"QUESTION 11"<<endl<<" Just like with question 10, the best way would be to add two data members: "<<endl;
cout <<"int max and int min"<<endl;
cout <<"Then these are updated during the constructing process"<<endl;
cout <<"If there is a deletion / addition operation happening, they are also checked and changed if needed"<<endl;
cout <<"Got too lazy to implement this though"<<endl<<endl;

cout <<endl<<"QUESTION 12"<<endl<<"If you do use the default copy maker "<<endl;
cout<<"And then change dll, dll2 will be changed as well."<<endl;
cout<<"Both objects will reference to the same memory location, which is a problem"<<endl;
cout<<"For example: DLLStructure dll2 (dll); dll.InsertAfter(7,100); dll2.printDLL(); "<<endl;
cout<<"Will print 2, 4, 7, 100, 7, 11, 12, 13, 26"<<endl<<endl;

DLLStructure dll2 (dll);
dll2.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
// dll.InsertAfter(7,100);
// dll2.printDLL(); // the output should still be: 2, 4, 7, 7, 11, 12, 13, 26

return 0;
}