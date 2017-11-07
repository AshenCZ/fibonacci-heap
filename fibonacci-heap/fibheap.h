#pragma once

#ifndef HOJDAR_FIBHEAP_H
#define HOJDAR_FIBHEAP_H

template <typename T>
class CyclicList {
   public:
    struct Node {
        Node* next;
        Node* prev;
        T value;

        explicit Node(const T val) : next(nullptr), prev(nullptr), value(val){};
    };

   private:
    Node* start;

    size_t count;

    Node* end() const {
        if (start)
            return start->prev;
        else
            return nullptr;
    }

   public:
    CyclicList() : start(nullptr), count(0){};

    const Node* head() {
        return start;
    }

    const Node* tail() {
        return end();
    }

    size_t size() const {
        return count;
    }

    void pushBack(const T value) {
        if (start) {
            Node* newItem = new Node(value);
            newItem->prev = end();
            newItem->next = start;
            end()->next = newItem;
            start->prev = newItem;
        } else {
            start = new Node(value);
            start->next = start;
            start->prev = start;
        }
        count++;
    }

    void merge(CyclicList& from) {
        if (start && from.start) {
            this->count += from.count;
            Node* tempEnd = this->end();
            this->start->prev = from.end();  // gut
            from.end()->next = this->start;
            tempEnd->next = from.start;
            from.start->prev = tempEnd;
        } else if (start && !from.start) {
            return;
        } else {
            this->start = from.start;
            this->count = from.count;
        }

        from.start = nullptr;
        from.count = 0;
    }
};


struct FibNode {
    int id;
    int key;
    bool mark = false;
    int sonCount = 0;

    FibNode* parent = nullptr;
    FibNode* prevBro = nullptr;
    FibNode* nextBro = nullptr;
    FibNode* firstSon = nullptr;

    FibNode(int id_, int key_) : id(id_), key(key_){};
};

class FibonacciHeap {
    FibNode* mapa[3000000];

    FibNode* firstTree;

    static void appendToList(FibNode* list, FibNode* item) {
        FibNode* start = list;
        if (start) {
            FibNode* end = start->prevBro;
            item->prevBro = end;
            item->nextBro = start;
            end->nextBro = item;
            start->prevBro = item;
        } else {
            start = item;
        }
    }

    static void deleteMyselfFromSons(FibNode* x) {
        // \todo NullPtr exception here
        FibNode* prevBro = x->prevBro;
        FibNode* nextBro = x->nextBro;
        prevBro->nextBro = nextBro;
        nextBro->prevBro = prevBro;
    }

    void cut(FibNode* x) {
        // 2. remember the parent
        FibNode* parent = x->parent;

        // 1. if x is a root, return
        if (!parent) {
            return;
        }

        // 3. delete the edge parent-x
        deleteMyselfFromSons(x);

        // 5. take x and make it a new tree by inserting into trees
        appendToList(firstTree, x);

        // 4. reset the mark on x
        x->mark = false;
        x->parent = nullptr;  // x is a root

        // 6. consider parent's mark
        if (!parent->mark) {
            parent->mark = true;
        }
        if (parent->mark) {
            cut(parent);
        }
    }

    FibNode* findMin(FibNode* heap){};

    FibNode* deleteNode(FibNode* itemToDelete){};

    FibNode* merge(FibNode* mergeInto, FibNode* mergeFrom) {}

    void consolidate(){

    };

   public:
    void insert(std::pair<int, int> newNode) {
        FibNode* newTree = new FibNode(newNode.first, newNode.second);
        appendToList(firstTree, newTree);
       // \todo Update Cached Min
    }

    int extractMin() {
        FibNode* minElement = findMin(firstTree);
        FibNode* newHeap = deleteNode(minElement);
        firstTree = merge(firstTree, newHeap);
        consolidate();
        return minElement->key;
    }

    void decrease(int idToDecrease, int newValue) {
       // \todo Update Cached Min 
       FibNode* nodeToDec = findById(idToDecrease);
        nodeToDec->key = newValue;
        FibNode* parent = nodeToDec->parent;
        if (parent->key > newValue) {
            cut(nodeToDec);
        }
    }
};

#endif
