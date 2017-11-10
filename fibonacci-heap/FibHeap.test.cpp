#include <gtest/gtest.h>

#include "fibheap.h"

TEST(insert, basic) {
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    auto a2 = heap.insert({2, 2});
    auto a3 = heap.insert({3, 3});
    auto a4 = heap.insert({4, 4});

    EXPECT_EQ(heap.numberOfTrees, 4);

    EXPECT_EQ(heap.firstTree, a1);
    EXPECT_EQ(heap.firstTree->nextBro, a2);
    EXPECT_EQ(heap.firstTree->nextBro->nextBro, a3);
    EXPECT_EQ(heap.firstTree->nextBro->nextBro->nextBro, a4);
    EXPECT_EQ(heap.firstTree->nextBro->nextBro->nextBro->nextBro, a1);

    EXPECT_EQ(heap.firstTree->prevBro, a4);
    EXPECT_EQ(heap.firstTree->prevBro->prevBro, a3);
    EXPECT_EQ(heap.firstTree->prevBro->prevBro->prevBro, a2);
    EXPECT_EQ(heap.firstTree->prevBro->prevBro->prevBro->prevBro, a1);

    EXPECT_EQ(heap.cachedMin->key, 1);
}

TEST(insert, caching_min) {
    FibonacciHeap heap;
    EXPECT_EQ(heap.cachedMin, nullptr);
    heap.insert({4, 4});
    EXPECT_EQ(heap.cachedMin->key, 4);
    heap.insert({3, 3});
    EXPECT_EQ(heap.cachedMin->key, 3);
    heap.insert({2, 2});
    EXPECT_EQ(heap.cachedMin->key, 2);
    heap.insert({1, 1});
    EXPECT_EQ(heap.cachedMin->key, 1);
}

TEST(merge, merging_two_unempty)
{
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    auto a2 = heap.insert({2, 2});
    auto a3 = heap.insert({3, 3});
    
    FibNode * list1 = heap.firstTree;

    FibonacciHeap heap2;
    a1 = heap2.insert({4, 4});
    a2 = heap2.insert({5, 5});
    a3 = heap2.insert({6, 6});

    auto list2 = heap2.firstTree;

    heap.mergeLists(list1, list2);

    EXPECT_EQ(list1->key, 1);
    EXPECT_EQ(list1->prevBro->key, 6);
    EXPECT_EQ(list1->prevBro->prevBro->key, 5);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->key, 4);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->key, 3);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->prevBro->key, 2);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->prevBro->prevBro->key, 1);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->prevBro->prevBro->prevBro->key, 6);

    EXPECT_EQ(list1->nextBro->key, 2);
    EXPECT_EQ(list1->nextBro->nextBro->key, 3);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->key, 4);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->key, 5);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->nextBro->key, 6);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->nextBro->nextBro->key, 1);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->nextBro->nextBro->nextBro->key, 2);
}

TEST(merge, merging_full_with_one_item)
{
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});

    FibNode * list1 = heap.firstTree;

    FibonacciHeap heap2;
    a1 = heap2.insert({4, 4});

    auto list2 = heap2.firstTree;

    heap.mergeLists(list1, list2);
    EXPECT_EQ(list1->key, 1);
    EXPECT_EQ(list1->prevBro->key, 4);
    EXPECT_EQ(list1->prevBro->prevBro->key, 3);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->key, 2);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->key, 1);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->prevBro->key, 4);

    EXPECT_EQ(list1->nextBro->key, 2);
    EXPECT_EQ(list1->nextBro->nextBro->key, 3);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->key, 4);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->key, 1);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->nextBro->key, 2);
}

TEST(merge, merging_one_item_with_full)
{
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});

    FibNode * list1 = heap.firstTree;

    FibonacciHeap heap2;
    a1 = heap2.insert({4, 4});

    auto list2 = heap2.firstTree;

    heap.mergeLists(list2, list1);
    list1 = list2;

    EXPECT_EQ(list1->key, 4);

    EXPECT_EQ(list1->prevBro->key, 3);
    EXPECT_EQ(list1->prevBro->prevBro->key, 2);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->key, 1);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->key, 4);
    EXPECT_EQ(list1->prevBro->prevBro->prevBro->prevBro->prevBro->key, 3);

    EXPECT_EQ(list1->nextBro->key, 1);
    EXPECT_EQ(list1->nextBro->nextBro->key, 2);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->key, 3);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->key, 4);
    EXPECT_EQ(list1->nextBro->nextBro->nextBro->nextBro->nextBro->key, 1);
}

TEST(delete_from_sons, simple)
{
    FibonacciHeap heap;
    heap.insert({1,1});
    heap.insert({2, 2});
    FibNode* me = heap.insert({3, 3});
    heap.insert({4, 4});

    FibNode* parent = new FibNode(5, 5);

    FibNode* cur = heap.firstTree;
    while (true) {
        cur->parent = parent;
        if (cur != heap.firstTree->prevBro) {
            cur = cur->nextBro;
        } else {
            break;
        }
    }

    parent->prevBro = parent;
    parent->nextBro = parent;
    parent->firstSon = heap.firstTree;

    heap.deleteMyselfFromSons(me);

    cur = parent->firstSon;
    int vals[3] = {1, 2, 4};
    int i = 0;
    while (true) {
        EXPECT_EQ(vals[i],cur->key);
        i++;
        if (cur != parent->firstSon->prevBro) {
            cur = cur->nextBro;
        } else {
            break;
        }
    }

    cur = parent->firstSon->prevBro;
    i = 0;
    int valsInv[3] = {4,2 ,1};

    while (true) {
        EXPECT_EQ(valsInv[i],cur->key);
        i++;
        if (cur != parent->firstSon) {
            cur = cur->prevBro;
        } else {
            break;
        }
    }

}

TEST(cut, v_shape_cut)
{
    FibonacciHeap heap;
    auto r = heap.insert({1,1});

    heap.firstTree->firstSon = new FibNode(2,2);
    auto n = heap.firstTree->firstSon;
    n->parent = r;
    heap.firstTree->firstSon->nextBro = new FibNode(3,3);
    auto s = heap.firstTree->firstSon->nextBro;
    s->parent = r;
    heap.firstTree->firstSon->prevBro = heap.firstTree->firstSon->nextBro;
    r->sonCount = 2;

    heap.cut(heap.firstTree->firstSon);

    EXPECT_EQ(r->sonCount, 1);

    EXPECT_EQ(heap.numberOfTrees, 2);

    EXPECT_EQ(heap.firstTree, r);
    EXPECT_EQ(heap.firstTree->nextBro, n);
    EXPECT_EQ(heap.firstTree->prevBro, n);

    EXPECT_EQ(heap.firstTree->firstSon, s);
    EXPECT_EQ(heap.firstTree->firstSon->nextBro, s);

    EXPECT_EQ(n->nextBro, heap.firstTree);
    EXPECT_EQ(n->prevBro, heap.firstTree);
    EXPECT_EQ(n->parent, nullptr);
}

TEST(consolidate, three_items) {
    FibonacciHeap heap;
    auto min = heap.insert({1, 1});
    auto d = heap.insert({2, 2});
    heap.insert({3, 3});

    FibNode* newHeap = heap.consolidate();

    EXPECT_EQ(newHeap->key, 3);
    EXPECT_EQ(newHeap->sonCount, 0);
    EXPECT_EQ(newHeap->nextBro->sonCount, 1);
    EXPECT_EQ(newHeap->nextBro->firstSon, d);
    EXPECT_EQ(newHeap->nextBro->key, 1);

    EXPECT_EQ(heap.cachedMin, min);
}

TEST(consolidate, four_items)
{
    FibonacciHeap heap;
    auto min = heap.insert({1, 1});
     heap.insert({2, 2});
    heap.insert({3, 3});
    heap.insert({4, 4});

    FibNode* newHeap = heap.consolidate();

    EXPECT_EQ(newHeap->key, 1);
    EXPECT_EQ(newHeap->nextBro->key, 1);

    EXPECT_EQ(heap.cachedMin, min);

}

TEST(consolidate, five_items)
{
    FibonacciHeap heap;
    auto min = heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});
    heap.insert({4, 4});
    heap.insert({5, 5});

    FibNode* newHeap = heap.consolidate();

    EXPECT_EQ(newHeap->key, 5);
    EXPECT_EQ(newHeap->nextBro->key, 1);
    EXPECT_EQ(newHeap->nextBro->nextBro->key, 5);

    EXPECT_EQ(heap.cachedMin, min);
}