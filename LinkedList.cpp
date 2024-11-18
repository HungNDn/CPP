#include <iostream>

using namespace std;

class Node {
    public:
        int data;
        Node * next;

        Node() {
            this->data = 0;
            this->next = NULL;
        }

        Node(int data) {
            this->data = data;
            this->next = NULL;
        }
};

class LinkedList {
    Node* head;
    public: 
        LinkedList() {
            this->head = NULL;
        }

        void insertNode(int);
        void deleteAt(int pos);
        void printList();
        int size();
};

void LinkedList::insertNode(int data) {
    Node* newNode = new Node(data);
    
    if(this->head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = this->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

int LinkedList::size() {
    Node* temp = this->head;
    int count = 0;

    if(temp == NULL) {
        return 0;
    }

    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void LinkedList::printList() {
    Node* temp = this->head;

    if(this->head == NULL) {
        cout << "List empty" << endl;
        return;
    }

    while(temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

void LinkedList::deleteAt(int pos) {
    if(pos < 1) {
        cout << "Out of range" << endl;
    }
    else if(pos == 1 && this->head != NULL) {
        Node* nodeToDelete = this->head;
        this->head = this->head->next;
        free(nodeToDelete);
    }
    else {
        Node* temp = this->head;
        for (int i = 1; i < pos -1; i++) {
            if(temp != NULL)
                temp = temp->next;
        }

        if(temp != NULL && temp->next != NULL) {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            free(nodeToDelete);
        }  
        else {
            cout<<"\nThe node is already null.";
        }    
    }
}

// Driver Code
int main()
{
    LinkedList list;
  
    // Inserting nodes
    list.insertNode(1);
    list.insertNode(2);
    list.insertNode(3);
    list.insertNode(4);
    list.insertNode(3);
    list.insertNode(4);
    list.insertNode(3);
    list.insertNode(4);
  
    cout << "Elements of the list are: ";

    list.deleteAt(3);
  
    // Print the list
    list.printList();

    cout << endl;

    return 0;
}