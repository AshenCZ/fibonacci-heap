#pragma once

#ifndef HOJDAR_FIBHEAP_H
#define HOJDAR_FIBHEAP_H

#include <cassert>

// \todo Remember to uncheck me!
// #define NDEBUG

struct FibNode {
    int id;
    int key;
    bool mark = false;
    int sonCount = 0;

    FibNode* parent = nullptr;
    FibNode* prevBro = nullptr;
    FibNode* nextBro = nullptr;
    FibNode* firstSon = nullptr;

    FibNode(int id_, int key_) : id(id_), key(key_) {
        nextBro = this;
        prevBro = this;
    };
};

class FibonacciHeap {
   public:
#define MAP_SIZE 20000
    FibNode* mapa[MAP_SIZE];
    static_assert(MAP_SIZE >= 20000, "Check if the map is big enough.");

    FibNode* cachedMin = nullptr;

    FibNode* firstTree = nullptr;

    FibNode* maxVal = new FibNode(INT_MAX, INT_MAX);

    int numberOfTrees = 0;

    /// Append one 'item' to a cyclic list of nodes 'list'
    static FibNode* appendToList(FibNode* list, FibNode* item) {
        FibNode* start = list;
        if (start) {
            FibNode* end = start->prevBro;
            item->prevBro = end;
            item->nextBro = start;
            end->nextBro = item;
            start->prevBro = item;
        } else {
            start = item;
            start->prevBro = item;
            start->nextBro = item;
        }
        return start;
    }

    /// Append a tree into the forest
    void appendTree(FibNode* tree) {
        firstTree = appendToList(firstTree, tree);
        numberOfTrees++;
    }

    /// Delete the node 'x' from x->parent's sons cyclic list
    static void deleteMyselfFromSons(FibNode* x) {
        // \todo nullptr?
        FibNode* prevPtr = x->prevBro;
        FibNode* nextPtr = x->nextBro;
        prevPtr->nextBro = nextPtr;
        nextPtr->prevBro = prevPtr;
        if (x->parent && x->parent->firstSon == x) {
            x->parent->firstSon = nextPtr;
        }
        x->nextBro = x;
        x->prevBro = x;
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
        parent->sonCount -= 1;

        // 5. take x and make it a new tree by inserting into trees
        appendTree(x);

        // 4. reset the mark on x
        x->mark = false;
        x->parent = nullptr;  // x is a root

        // 6. consider parent's mark
        if (!parent->mark) {
            parent->mark = true;
        } else if (parent->mark) {
            cut(parent);
        }
    }

    /// Delete one particular node by deleting it from its parent's sons list, then deleting the
    /// node, reducing parent's sons count and returning a CyclicList of newly formed trees without
    /// a root
    static FibNode* deleteNode(FibNode* itemToDelete) {
        FibNode* newTrees = itemToDelete->firstSon;
        // \todo reset 'parent' atribute for newTrees?
        deleteMyselfFromSons(itemToDelete);
        if (itemToDelete->parent) {
            itemToDelete->parent->sonCount--;
        }
        delete itemToDelete;
        return newTrees;
    }

    /// Merge two cyclic lists into one
    static FibNode* mergeLists(FibNode* mergeInto, FibNode* mergeFrom) {
        if (mergeFrom == nullptr) {
            return mergeInto;
        }
        if (mergeInto == nullptr) {
            return mergeFrom;
        }

        FibNode* intoEnd = mergeInto->prevBro;
        FibNode* fromEnd = mergeFrom->prevBro;
        intoEnd->nextBro = mergeFrom;
        fromEnd->nextBro = mergeInto;
        mergeInto->prevBro = fromEnd;
        mergeFrom->prevBro = intoEnd;
        return mergeInto;
    }

    static FibNode* addSon(FibNode* heap, FibNode* son) {
        heap->firstSon = appendToList(heap->firstSon, son);
        son->parent = heap;
        heap->sonCount++;
        return heap;
    }

    static FibNode* heapMerge(FibNode* heap1, FibNode* heap2) {
        // dvojku privesime pod jednicku
        if (heap1->key < heap2->key) {
            heap1 = addSon(heap1, heap2);
            return heap1;
        } else if (heap1->key > heap2->key) {
            heap2 = addSon(heap2, heap1);
            return heap2;
        } else {
            assert(false);
            return nullptr;
        }
    }

    FibNode* consolidate() {
        numberOfTrees = 0;
        FibNode* returnVal = nullptr;
        if (firstTree == nullptr) {
            return returnVal;
        }

        FibNode* boxes[50];
        for (int i = 0; i < 50; ++i) {
            boxes[i] = nullptr;
        }

        // Fill all into boxes
        FibNode* current = firstTree;
        while (true) {
            // Work
            FibNode* nextVal = current->nextBro;
            deleteMyselfFromSons(current);
            boxes[current->sonCount] = appendToList(boxes[current->sonCount], current);

            // Next
            if (current == nextVal) {
                break;
            }
            current = nextVal;
        }

        // Go through all, merge
        for (int currentBox = 0; currentBox < 50; ++currentBox) {
            FibNode* node = boxes[currentBox];
            // Merge
            while (node != nullptr && node->nextBro != node) {
                FibNode* one = node;
                FibNode* two = node->nextBro;
                if (two->nextBro == one) {
                    boxes[currentBox] = nullptr;
                    // std::cout << "del, first in " << currentBox << " is NULL\n";
                } else {
                    boxes[currentBox] = two->nextBro;
                    // std::cout << "del, first in " << currentBox << " is value "
                    //          << boxes[currentBox]->key << "\n";
                }
                // std::cout << "Merged " << one->key << " with " << two->key << " put them in "
                //          << currentBox + 1 << "\n";
                deleteMyselfFromSons(one);
                deleteMyselfFromSons(two);
                boxes[currentBox + 1] = appendToList(boxes[currentBox + 1], heapMerge(one, two));
                node = boxes[currentBox];
            }

            if (node != nullptr) {
                assert(node == node->nextBro);
                node->parent = nullptr;
                returnVal = appendToList(returnVal, node);
                numberOfTrees++;
                cachedMin = cachedMin->key > node->key ? node : cachedMin;
                boxes[currentBox] = nullptr;
            }
        }

        return returnVal;
    }

    FibNode* findById(int id) {
        return mapa[id];
    }

   public:
    FibNode* insert(std::pair<int, int> newNode) {
        if (mapa[newNode.first] != nullptr) {
            throw std::exception("Inserting multiple same IDs!");
        }

        FibNode* newTree = new FibNode(newNode.first, newNode.second);
        mapa[newNode.first] = newTree;
        if (cachedMin == nullptr || newTree->key < cachedMin->key) {
            cachedMin = newTree;
        }
        appendTree(newTree);
        return newTree;
    }

    int extractMin() {
        if (firstTree == nullptr) {
            auto excp = std::exception("extract on empty heap");
            throw excp;
        }
        FibNode* minElement = cachedMin;
        const int retValue = minElement->key;
        cachedMin = maxVal;

        if (minElement == firstTree) {
            if (firstTree->nextBro == firstTree) {
                firstTree = nullptr;
            } else {
                firstTree = firstTree->nextBro;
            }
        }

        FibNode* newHeap = deleteNode(minElement);

        if (newHeap) {
            FibNode* cur = newHeap;
            while (true) {
                cur->parent = nullptr;
                if (cur != newHeap->prevBro) {
                    cur = cur->nextBro;
                } else {
                    break;
                }
            }
            firstTree = mergeLists(firstTree, newHeap);
        }

        firstTree = consolidate();
        return retValue;
    }

    void decrease(int idToDecrease, int newValue) {
        FibNode* nodeToDec = findById(idToDecrease);
        assert(nodeToDec->id == idToDecrease);
        assert(nodeToDec->key > newValue);
        nodeToDec->key = newValue;

        // Update the mininum
        if (nodeToDec->key < cachedMin->key) {
            cachedMin = nodeToDec;
        }

        // Cut if we break the heap invariant
        FibNode* parent = nodeToDec->parent;
        if (parent && parent->key > newValue) {
            cut(nodeToDec);
        }
    }

    void deleteItem(int idToDelete) {
        decrease(idToDelete, INT_MIN);
        int value = extractMin();
        assert(value == INT_MIN);
    }
};

#endif