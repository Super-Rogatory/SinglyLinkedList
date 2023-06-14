#include "SinglyLinkedList.h"

// default constructor for the SLL, initializes head and tail to nullptr, and size to 0.
// Note, the head and tail properties can hold heap allocated objects of type Node<T>, the T is provided during object instantiation
// head and tail could point to Node<int>'s or Node<std::string>'s it is up to the template argument provided during object instantiation.
template<class T>
SinglyLinkedList<T>::SinglyLinkedList()
    :head(nullptr), tail(nullptr), size(0) {}

// push an element to the linked list, elem of type T, in alignment with the template argument provided to the scope of the entire class.
template<class T>
void SinglyLinkedList<T>::push(const T &elem) {
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(elem);
    if(!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++size;
}

template<class T>
T SinglyLinkedList<T>::pop() {
    if(size == 0) 
        throw std::out_of_range("Cannot pop from an empty linked list.");

    std::shared_ptr<Node<T>> curNode = head; // keep the current Node alive
    if(head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        // hold curNode->next's shared_ptr as a non-owning reference (weak_ptr)
        std::weak_ptr<Node<T>> nextNode = curNode->next;
        // when converting weak_ptr to shared_ptr, if the newly constructed shared pointer object does not manage any object, then .lock() returns an empty shared_ptr which evaluates to false in a boolean context.
        // we will use the nextNode variable (a weak pointer object) to seek through the list, retrieving the next node in the list. then invoking .lock() get the shared_ptr object (only if it has a valid .next shared pointer object)
        while(nextNode.lock()->next) {
            curNode = nextNode.lock(); // whatever nextNode is referring to, retrieve the shared_ptr object, and set that equal to curNode
            nextNode = curNode->next; // now curNode is pointing to the next shared_ptr object. after this line, nextNode will assume a non owning reference to the shared_ptr after curNode.
            // thus, it cycles. curNode, after each iteration will equal the next node. It will share ownership of that node.
            // yet, nextNode, only seeks to see the next node, it is a weak pointer and will not own any object it refers to.
        }
        // the penultimate node, curNode, is now copied into tail. So that curNode and tail point to the penultimate node.
        tail = curNode;
        // now curNode is set to the very last node, to keep it alive.
        curNode = tail->next;
        // our new tail, the curNode which was the penultimate node, will be accessed and will have its next property changed.
        tail->next = nullptr;
    }
    --size; // decrease size of list
    return curNode->data;
}

template<class T>
void SinglyLinkedList<T>::unshift(const T &elem) {
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(elem);
    if(!head) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

template<class T>
T SinglyLinkedList<T>::shift() {
    if(size == 0)
        throw std::out_of_range("You cannot remove elements from an empty list.");
    std::shared_ptr<Node<T>> curNode = head;
    if(head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        curNode->next = nullptr;
    }
    --size;
    return curNode->data;
}

template<class T>
void SinglyLinkedList<T>::print() const {
    std::cout << "[ ";
    std::weak_ptr<Node<T>> cur = head;
    while(cur.lock()) {
        std::cout << cur.lock()->data << " ";
        cur = cur.lock()->next;
    }
    std::cout << "]\n";
}

// #include "SinglyLinkedList.h"

// template<class T>
// SinglyLinkedList<T>::SinglyLinkedList()
//     :head(nullptr), tail(nullptr), size(0) {}


// template<class T>
// void SinglyLinkedList<T>::push(const T &elem) {
//     std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(elem);
//     if(!head) {
//         head = newNode;
//         tail = newNode;
//     } else {
//         tail->next = newNode;
//         tail = newNode;
//     }
//     ++size;
// }

// template<class T>
// T SinglyLinkedList<T>::pop() {
//     if(size == 0) {
//         throw std::out_of_range("Cannot pop from an empty linked list");
//     }
//     std::shared_ptr<Node<T>> curNode = head;
//     if(head == tail) {
//         head = nullptr;
//         tail = nullptr;
//     } else {    
//         std::weak_ptr<Node<T>> nextNode = curNode->next;
//         while(nextNode.lock()->next) {
//             curNode = nextNode.lock(); 
//             nextNode = curNode->next;
//         }
//         tail = curNode;
//         curNode = tail->next;
//         tail->next = nullptr;
//     }
//     --size;
//     return curNode->data;
// }