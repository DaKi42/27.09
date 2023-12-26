#include <iostream>

template <typename U>
struct Node {
    U value;
    Node* next;
    Node* prev;

    Node() = default;
    Node(U val) : value(val), next(nullptr), prev(nullptr) {}
}; 

template <typename U>
class DoublyLinkedList {
    Node<U>* head;
    Node<U>* tail;
    int size;

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList&);
    ~DoublyLinkedList();
    int getSize();
    Node<U>* getNode(int);

    void clear();
    void remove(int pos = 0);
    void insert(int pos = 0);

    void addToTail(U val);
    void addToHead(U val);
    void display();
    void display(int pos);

    DoublyLinkedList& operator=(const DoublyLinkedList&);
    DoublyLinkedList operator+(const DoublyLinkedList&);

    bool operator==(const DoublyLinkedList&);
    bool operator!=(const DoublyLinkedList&);
    bool operator<=(const DoublyLinkedList&);
    bool operator>=(const DoublyLinkedList&);
    bool operator<(const DoublyLinkedList&);
    bool operator>(const DoublyLinkedList&);

    DoublyLinkedList operator-();
};

template <typename U>
DoublyLinkedList<U>::DoublyLinkedList() {
    head = tail = nullptr;
    size = 0;
}

template <typename U>
DoublyLinkedList<U>::DoublyLinkedList(const DoublyLinkedList& other) {
    head = tail = nullptr;
    size = 0;

    Node<U>* temp = other.head;
    while (temp != nullptr) {
        this->addToTail(temp->value);
        temp = temp->next;
    }
}

template <typename U>
DoublyLinkedList<U>::~DoublyLinkedList() {
    clear();
}

template <typename U>
void DoublyLinkedList<U>::addToHead(U val) {
    Node<U>* newNode = new Node<U>(val);
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr)
        head->prev = newNode;

    if (size == 0)
        head = tail = newNode;
    else
        head = newNode;

    size++;
}

template <typename U>
void DoublyLinkedList<U>::addToTail(U val) {
    Node<U>* newNode = new Node<U>(val);
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr)
        tail->next = newNode;

    if (size == 0)
        head = tail = newNode;
    else
        tail = newNode;

    size++;
}

template <typename U>
void DoublyLinkedList<U>::insert(int pos) {
    if (pos == 0) {
        std::cout << "Enter the position: ";
        std::cin >> pos;
    }

    if (pos < 1 || pos > size + 1) {
        std::cout << "Invalid position!" << std::endl;
        return;
    }

    if (pos == size + 1) {
        U val;
        std::cout << "Enter the new value: ";
        std::cin >> val;
        addToTail(val);
        return;
    }
    else if (pos == 1) {
        U val;
        std::cout << "Enter the new value: ";
        std::cin >> val;
        addToHead(val);
        return;
    }

    int i = 1;
    Node<U>* ins = head;

    while (i < pos) {
        ins = ins->next;
        i++;
    }

    Node<U>* prevIns = ins->prev;

    Node<U>* newNode = new Node<U>;

    std::cout << "Enter the new value: ";
    std::cin >> newNode->value;

    if (prevIns != nullptr && size != 1)
        prevIns->next = newNode;

    newNode->next = ins;
    newNode->prev = prevIns;
    ins->prev = newNode;

    size++;
}

template <typename U>
void DoublyLinkedList<U>::remove(int pos) {
    if (pos == 0) {
        std::cout << "Enter the position: ";
        std::cin >> pos;
    }
    if (pos < 1 || pos > size) {
        std::cout << "Invalid position!" << std::endl;
        return;
    }

    int i = 1;

    Node<U>* del = head;

    while (i < pos) {
        del = del->next;
        i++;
    }

    Node<U>* prevDel = del->prev;
    Node<U>* afterDel = del->next;

    if (prevDel != nullptr && size != 1)
        prevDel->next = afterDel;

    if (afterDel != nullptr && size != 1)
        afterDel->prev = prevDel;

    if (pos == 1)
        head = afterDel;
    if (pos == size)
        tail = prevDel;

    delete del;
    size--;
}

template <typename U>
void DoublyLinkedList<U>::display(int pos) {
    if (pos < 1 || pos > size) {
        std::cout << "Invalid position!" << std::endl;
        return;
    }

    Node<U>* temp;
    if (pos <= size / 2) {
        temp = head;
        int i = 1;

        while (i < pos) {
            temp = temp->next;
            i++;
        }
    }
    else {
        temp = tail;
        int i = 1;

        while (i <= size - pos) {
            temp = temp->prev;
            i++;
        }
    }
    std::cout << "Element " << pos << ": ";
    std::cout << temp->value << std::endl;
}

template <typename U>
void DoublyLinkedList<U>::display() {
    if (size != 0) {
        Node<U>* temp = head;
        std::cout << "( ";
        while (temp->next != nullptr) {
            std::cout << temp->value << ", ";
            temp = temp->next;
        }

        std::cout << temp->value << " )" << std::endl;
    }
}

template <typename U>
void DoublyLinkedList<U>::clear() {
    while (size != 0)
        remove(1);
}

template <typename U>
int DoublyLinkedList<U>::getSize() {
    return size;
}

template <typename U>
Node<U>* DoublyLinkedList<U>::getNode(int pos) {
    Node<U>* temp = head;
    if (pos < 1 || pos > size) {
        std::cout << "Invalid position!" << std::endl;
        return nullptr;
    }

    int i = 1;
    while (i < pos && temp != nullptr) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr)
        return nullptr;
    else
        return temp;
}

template <typename U>
DoublyLinkedList<U>& DoublyLinkedList<U>::operator=(const DoublyLinkedList& other) {
    if (this == &other)
        return *this;

    this->clear();

    Node<U>* temp = other.head;

    while (temp != nullptr) {
        addToTail(temp->value);
        temp = temp->next;
    }

    return *this;
}

template <typename U>
DoublyLinkedList<U> DoublyLinkedList<U>::operator+(const DoublyLinkedList& other) {
    DoublyLinkedList<U> result(*this);
    Node<U>* temp = other.head;
    while (temp != nullptr) {
        result.addToTail(temp->value);
        temp = temp->next;
    }

    return result;
}

template <typename U>
bool DoublyLinkedList<U>::operator==(const DoublyLinkedList& other) {
    if (size != other.size)
        return false;

    Node<U>* t1, * t2;

    t1 = head;
    t2 = other.head;

    while (t1 != nullptr) {
        if (t1->value != t2->value)
            return false;

        t1 = t1->next;
        t2 = t2->next;
    }

    return true;
}

template <typename U>
bool DoublyLinkedList<U>::operator!=(const DoublyLinkedList& other) {
    return !(*this == other);
}

template <typename U>
bool DoublyLinkedList<U>::operator>=(const DoublyLinkedList& other) {
    if (size > other.size)
        return true;
    if (*this == other)
        return true;

    return false;
}

template <typename U>
bool DoublyLinkedList<U>::operator<=(const DoublyLinkedList& other) {
    if (size < other.size)
        return true;
    if (*this == other)
        return true;

    return false;
}

template <typename U>
bool DoublyLinkedList<U>::operator>(const DoublyLinkedList& other) {
    if (size > other.size)
        return true;

    return false;
}

template <typename U>
bool DoublyLinkedList<U>::operator<(const DoublyLinkedList& other) {
    if (size < other.size)
        return true;

    return false;
}

template <typename U>
DoublyLinkedList<U> DoublyLinkedList<U>::operator-() {
    DoublyLinkedList<U> result;

    Node<U>* temp = head;
    while (temp != nullptr) {
        result.addToHead(temp->value);
        temp = temp->next;
    }

    return result;
}

template <typename U>
class Queue {
    DoublyLinkedList<U> data;

public:
    Queue() {}
    void enqueue(U value) {
        data.addToTail(value);
    }
    U dequeue() {
        if (!isEmpty()) {
            Node<U>* first = data.getNode(1);
            U value = first->value;
            data.remove(1);
            return value;
        }
        else {
            std::cout << "The queue is empty." << std::endl;
            return U();
        }
    }
    bool isEmpty() {
        return data.getSize() == 0;
    }
    int getSize() {
        return data.getSize();
    }
    void print() {
        std::cout << "Queue: ";
        data.display();
    }
};

int main() {
    Queue<int> queue;
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(8);
    queue.print();

    std::cout << "Dequeuing: " << std::endl;
    while (!queue.isEmpty()) {
        int item = queue.dequeue();
        std::cout << item << std::endl;
    }

    return 0;
}
