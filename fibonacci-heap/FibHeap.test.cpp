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

TEST(merge, merging_two_unempty) {
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    auto a2 = heap.insert({2, 2});
    auto a3 = heap.insert({3, 3});

    FibNode* list1 = heap.firstTree;

    FibonacciHeap heap2;
    a1 = heap2.insert({4, 4});
    a2 = heap2.insert({5, 5});
    a3 = heap2.insert({6, 6});

    auto list2 = heap2.firstTree;

    list1 = heap.mergeLists(list1, list2);

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

TEST(merge, merging_full_with_one_item) {
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});

    FibNode* list1 = heap.firstTree;

    FibonacciHeap heap2;
    a1 = heap2.insert({4, 4});

    auto list2 = heap2.firstTree;

    list1 = heap.mergeLists(list1, list2);
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

TEST(merge, merging_one_item_with_full) {
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});

    FibNode* list1 = heap.firstTree;

    FibonacciHeap heap2;
    a1 = heap2.insert({4, 4});

    auto list2 = heap2.firstTree;

    list2 = heap.mergeLists(list2, list1);
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

TEST(delete_from_sons, simple) {
    FibonacciHeap heap;
    heap.insert({1, 1});
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
        EXPECT_EQ(vals[i], cur->key);
        i++;
        if (cur != parent->firstSon->prevBro) {
            cur = cur->nextBro;
        } else {
            break;
        }
    }

    cur = parent->firstSon->prevBro;
    i = 0;
    int valsInv[3] = {4, 2, 1};

    while (true) {
        EXPECT_EQ(valsInv[i], cur->key);
        i++;
        if (cur != parent->firstSon) {
            cur = cur->prevBro;
        } else {
            break;
        }
    }
}

TEST(cut, v_shape_cut) {
    FibonacciHeap heap;
    auto r = heap.insert({1, 1});

    heap.firstTree->firstSon = new FibNode(2, 2);
    auto n = heap.firstTree->firstSon;
    n->parent = r;
    heap.firstTree->firstSon->nextBro = new FibNode(3, 3);
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

    EXPECT_EQ(newHeap->parent, nullptr);
    EXPECT_EQ(newHeap->nextBro->parent, nullptr);
    EXPECT_EQ(newHeap->nextBro->firstSon->parent, newHeap->nextBro);
}

TEST(consolidate, four_items) {
    FibonacciHeap heap;
    auto min = heap.insert({1, 1});
    auto fs = heap.insert({2, 2});
    auto ss = heap.insert({3, 3});
    auto ls = heap.insert({4, 4});

    FibNode* newHeap = heap.consolidate();

    EXPECT_EQ(newHeap->key, 1);
    EXPECT_EQ(newHeap->nextBro->key, 1);

    EXPECT_EQ(heap.cachedMin, min);

    EXPECT_EQ(newHeap->firstSon, fs);
    EXPECT_EQ(newHeap->firstSon->nextBro, ss);
    EXPECT_EQ(newHeap->firstSon->prevBro, ss);
    EXPECT_EQ(newHeap->firstSon->prevBro->prevBro, fs);
    EXPECT_EQ(newHeap->firstSon->nextBro->nextBro, fs);

    EXPECT_EQ(ss->firstSon, ls);
    EXPECT_EQ(ss->firstSon->nextBro, ls);
    EXPECT_EQ(ss->firstSon->prevBro, ls);

    EXPECT_EQ(newHeap->sonCount, 2);
    EXPECT_EQ(newHeap->firstSon->sonCount, 0);
    EXPECT_EQ(newHeap->firstSon->nextBro->sonCount, 1);

    EXPECT_EQ(newHeap->parent, nullptr);
    EXPECT_EQ(newHeap->firstSon->parent, newHeap);
    EXPECT_EQ(newHeap->firstSon->nextBro->parent, newHeap);
    EXPECT_EQ(newHeap->firstSon->nextBro->firstSon->parent, newHeap->firstSon->nextBro);
}

TEST(consolidate, five_items) {
    FibonacciHeap heap;
    FibNode* min = heap.insert({1, 1});
    FibNode* a2 = heap.insert({2, 2});
    FibNode* a3 = heap.insert({3, 3});
    FibNode* a4 = heap.insert({4, 4});
    FibNode* a5 = heap.insert({5, 5});

    FibNode* newHeap = heap.consolidate();

    EXPECT_EQ(newHeap->key, 5);
    EXPECT_EQ(newHeap->nextBro->key, 1);
    EXPECT_EQ(newHeap->nextBro->nextBro->key, 5);

    EXPECT_EQ(heap.cachedMin, min);

    EXPECT_EQ(newHeap->nextBro, min);
    EXPECT_EQ(0, a5->sonCount);
    EXPECT_EQ(nullptr, a5->firstSon);
    EXPECT_EQ(nullptr, a5->parent);
    EXPECT_EQ(min, a5->nextBro);
    EXPECT_EQ(min, a5->prevBro);

    EXPECT_EQ(min->parent, nullptr);
    EXPECT_EQ(min->sonCount, 2);
    EXPECT_EQ(min->firstSon, a2);
    EXPECT_EQ(a2->sonCount, 0);
    EXPECT_EQ(a2->nextBro, a3);
    EXPECT_EQ(a2->prevBro, a3);
    EXPECT_EQ(a2->parent, min);

    EXPECT_EQ(min->firstSon->nextBro->key, a3->key);
    EXPECT_EQ(a3->sonCount, 1);
    EXPECT_EQ(a3->nextBro, a2);
    EXPECT_EQ(a3->prevBro, a2);
    EXPECT_EQ(a3->parent, min);

    EXPECT_EQ(a3->firstSon, a4);
    EXPECT_EQ(a4->nextBro, a4);
    EXPECT_EQ(a4->prevBro, a4);
    EXPECT_EQ(a4->parent, a3);
}

TEST(consolidate, one_third_degree_tree) {
    FibonacciHeap heap;
    FibNode* min = heap.insert({1, 1});
    FibNode* a2 = heap.insert({2, 2});
    FibNode* a3 = heap.insert({3, 3});
    FibNode* a4 = heap.insert({4, 4});
    FibNode* a5 = heap.insert({5, 5});
    FibNode* a6 = heap.insert({6, 6});
    FibNode* a7 = heap.insert({7, 7});
    FibNode* a8 = heap.insert({8, 8});

    FibNode* newHeap = heap.consolidate();

    // Tree list
    EXPECT_EQ(newHeap, min);
    EXPECT_EQ(newHeap->nextBro, min);
    EXPECT_EQ(newHeap->prevBro, min);

    // SonCount correct
    EXPECT_EQ(newHeap->sonCount, 3);
    EXPECT_EQ(a3->sonCount, 1);
    EXPECT_EQ(a7->sonCount, 1);
    EXPECT_EQ(a5->sonCount, 2);
    EXPECT_EQ(a2->sonCount, 0);
    EXPECT_EQ(a2->sonCount, 0);
    EXPECT_EQ(a6->sonCount, 0);
    EXPECT_EQ(a8->sonCount, 0);

    // Parent correct
    EXPECT_EQ(min->parent, nullptr);
    EXPECT_EQ(a2->parent, min);
    EXPECT_EQ(a3->parent, min);
    EXPECT_EQ(a5->parent, min);
    EXPECT_EQ(a4->parent, a3);
    EXPECT_EQ(a6->parent, a5);
    EXPECT_EQ(a7->parent, a5);
    EXPECT_EQ(a8->parent, a7);

    // Tree structure
    EXPECT_EQ(newHeap->firstSon, a2);
    EXPECT_EQ(newHeap->firstSon->nextBro, a3);
    EXPECT_EQ(newHeap->firstSon->prevBro, a5);

    EXPECT_EQ(a3->firstSon, a4);
    EXPECT_EQ(a3->firstSon->nextBro, a4);
    EXPECT_EQ(a3->firstSon->prevBro, a4);
    EXPECT_EQ(a3->nextBro, a5);
    EXPECT_EQ(a3->prevBro, a2);

    EXPECT_EQ(a5->firstSon, a6);
    EXPECT_EQ(a5->firstSon->nextBro, a7);
    EXPECT_EQ(a5->firstSon->prevBro, a7);
    EXPECT_EQ(a5->firstSon->nextBro->nextBro, a6);
    EXPECT_EQ(a5->firstSon->nextBro->prevBro, a6);
    EXPECT_EQ(a5->nextBro, a2);
    EXPECT_EQ(a5->prevBro, a3);

    EXPECT_EQ(a4->nextBro, a4);
    EXPECT_EQ(a4->prevBro, a4);

    EXPECT_EQ(a6->nextBro, a7);
    EXPECT_EQ(a6->prevBro, a7);

    EXPECT_EQ(a7->nextBro, a6);
    EXPECT_EQ(a7->prevBro, a6);

    EXPECT_EQ(a8->nextBro, a8);
    EXPECT_EQ(a8->prevBro, a8);
}

TEST(consolidate, one_third_degree_tree_and_one_lone) {
    FibonacciHeap heap;
    FibNode* min = heap.insert({1, 1});
    FibNode* a2 = heap.insert({2, 2});
    FibNode* a3 = heap.insert({3, 3});
    FibNode* a4 = heap.insert({4, 4});
    FibNode* a5 = heap.insert({5, 5});
    FibNode* a6 = heap.insert({6, 6});
    FibNode* a7 = heap.insert({7, 7});
    FibNode* a8 = heap.insert({8, 8});
    FibNode* a9 = heap.insert({9, 9});

    FibNode* newHeap = heap.consolidate();

    // Tree list
    EXPECT_EQ(newHeap, a9);
    EXPECT_EQ(newHeap->nextBro, min);
    EXPECT_EQ(newHeap->prevBro, min);

    // SonCount correct
    EXPECT_EQ(min->sonCount, 3);
    EXPECT_EQ(a3->sonCount, 1);
    EXPECT_EQ(a7->sonCount, 1);
    EXPECT_EQ(a5->sonCount, 2);
    EXPECT_EQ(a2->sonCount, 0);
    EXPECT_EQ(a2->sonCount, 0);
    EXPECT_EQ(a6->sonCount, 0);
    EXPECT_EQ(a8->sonCount, 0);

    // Parent correct
    EXPECT_EQ(min->parent, nullptr);
    EXPECT_EQ(a2->parent, min);
    EXPECT_EQ(a3->parent, min);
    EXPECT_EQ(a5->parent, min);
    EXPECT_EQ(a4->parent, a3);
    EXPECT_EQ(a6->parent, a5);
    EXPECT_EQ(a7->parent, a5);
    EXPECT_EQ(a8->parent, a7);

    // Tree structure
    EXPECT_EQ(min->firstSon, a2);
    EXPECT_EQ(min->firstSon->nextBro, a3);
    EXPECT_EQ(min->firstSon->prevBro, a5);

    EXPECT_EQ(a3->firstSon, a4);
    EXPECT_EQ(a3->firstSon->nextBro, a4);
    EXPECT_EQ(a3->firstSon->prevBro, a4);
    EXPECT_EQ(a3->nextBro, a5);
    EXPECT_EQ(a3->prevBro, a2);

    EXPECT_EQ(a5->firstSon, a6);
    EXPECT_EQ(a5->firstSon->nextBro, a7);
    EXPECT_EQ(a5->firstSon->prevBro, a7);
    EXPECT_EQ(a5->firstSon->nextBro->nextBro, a6);
    EXPECT_EQ(a5->firstSon->nextBro->prevBro, a6);
    EXPECT_EQ(a5->nextBro, a2);
    EXPECT_EQ(a5->prevBro, a3);

    EXPECT_EQ(a4->nextBro, a4);
    EXPECT_EQ(a4->prevBro, a4);

    EXPECT_EQ(a6->nextBro, a7);
    EXPECT_EQ(a6->prevBro, a7);

    EXPECT_EQ(a7->nextBro, a6);
    EXPECT_EQ(a7->prevBro, a6);

    EXPECT_EQ(a8->nextBro, a8);
    EXPECT_EQ(a8->prevBro, a8);
}

TEST(extractMin, simple) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    auto d = heap.insert({2, 2});
    auto t = heap.insert({3, 3});
    auto a4 = heap.insert({4, 4});
    auto a5 = heap.insert({5, 5});

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.cachedMin, d);

    EXPECT_EQ(heap.numberOfTrees, 1);

    EXPECT_EQ(heap.firstTree, d);

    EXPECT_EQ(heap.firstTree->nextBro, d);
    EXPECT_EQ(heap.firstTree->prevBro, d);

    EXPECT_EQ(heap.firstTree->firstSon, t);
    EXPECT_EQ(heap.firstTree->firstSon->nextBro, a4);
    EXPECT_EQ(heap.firstTree->firstSon->prevBro, a4);

    EXPECT_EQ(heap.firstTree->firstSon->firstSon, nullptr);
    EXPECT_EQ(a4->firstSon, a5);
}

TEST(extractMin, double_extract) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    auto d = heap.insert({2, 2});
    auto t = heap.insert({3, 3});
    auto ct = heap.insert({4, 4});
    auto p = heap.insert({5, 5});

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.cachedMin, d);

    EXPECT_EQ(heap.extractMin(), 2);

    EXPECT_EQ(heap.cachedMin, t);

    EXPECT_EQ(heap.numberOfTrees, 2);

    EXPECT_EQ(heap.firstTree, t);
    EXPECT_EQ(heap.firstTree->nextBro, ct);
    EXPECT_EQ(heap.firstTree->nextBro->firstSon, p);
}

TEST(extractMin, multiple_extract) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});
    heap.insert({4, 4});
    heap.insert({5, 5});

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.extractMin(), 2);

    EXPECT_EQ(heap.extractMin(), 3);

    EXPECT_EQ(heap.extractMin(), 4);

    EXPECT_EQ(heap.extractMin(), 5);

    EXPECT_EQ(heap.cachedMin, heap.maxVal);
    EXPECT_EQ(heap.numberOfTrees, 0);
    EXPECT_EQ(heap.firstTree, nullptr);
}

//TEST(extractMin, extract_empty) {
//    FibonacciHeap heap;
//    heap.insert({1, 1});
//    heap.insert({2, 2});
//    heap.insert({3, 3});
//
//    EXPECT_EQ(heap.extractMin(), 1);
//
//    EXPECT_EQ(heap.extractMin(), 2);
//
//    EXPECT_EQ(heap.extractMin(), 3);
//
//    EXPECT_ANY_THROW(heap.extractMin());
//}

TEST(extractMin, bigger_example) {
    FibonacciHeap heap;
    auto pt = heap.insert({5, 5});
    auto sest = heap.insert({6, 6});
    auto ct = heap.insert({4, 4});
    auto dev = heap.insert({9, 9});
    auto dv = heap.insert({2, 2});
    heap.insert({1, 1});
    auto sed = heap.insert({7, 7});
    auto tr = heap.insert({3, 3});

    EXPECT_EQ(heap.cachedMin->key, 1);

    EXPECT_EQ(heap.numberOfTrees, 8);

    EXPECT_EQ(heap.firstTree->key, 5);

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.firstTree, tr);

    EXPECT_EQ(heap.numberOfTrees, 3);
    EXPECT_EQ(heap.cachedMin->key, dv->key);

    EXPECT_EQ(tr->nextBro, dv);
    EXPECT_EQ(tr->prevBro, ct);
    EXPECT_EQ(dv->nextBro, ct);
    EXPECT_EQ(dv->prevBro, tr);
    EXPECT_EQ(ct->nextBro, tr);
    EXPECT_EQ(ct->prevBro, dv);

    EXPECT_EQ(dev->nextBro, pt);
    EXPECT_EQ(dev->prevBro, pt);

    EXPECT_EQ(pt->nextBro, dev);
    EXPECT_EQ(pt->prevBro, dev);

    EXPECT_EQ(tr->sonCount, 0);
    EXPECT_EQ(dv->sonCount, 1);
    EXPECT_EQ(ct->sonCount, 2);
    EXPECT_EQ(pt->sonCount, 1);

    EXPECT_EQ(sed->sonCount, 0);
    EXPECT_EQ(dev->sonCount, 0);
    EXPECT_EQ(sest->sonCount, 0);

    EXPECT_EQ(dev->parent, ct);
    EXPECT_EQ(pt->parent, ct);
    EXPECT_EQ(sest->parent, pt);
    EXPECT_EQ(sed->parent, dv);

    EXPECT_EQ(tr->parent, nullptr);
    EXPECT_EQ(dv->parent, nullptr);
    EXPECT_EQ(ct->parent, nullptr);
}

TEST(findById, simple) {
    FibonacciHeap heap;
    auto a1 = heap.insert({1, 1});
    auto a2 = heap.insert({2, 2});
    auto a3 = heap.insert({3, 3});

    EXPECT_EQ(heap.findById(1), a1);
    EXPECT_EQ(heap.findById(2), a2);
    EXPECT_EQ(heap.findById(3), a3);
    EXPECT_EQ(heap.findById(1337), nullptr);
}

TEST(decrease, simple) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});

    heap.decrease(3, 0);

    EXPECT_EQ(heap.firstTree->key, 1);
    EXPECT_EQ(heap.firstTree->prevBro->key, 0);
    EXPECT_EQ(heap.cachedMin->key, 0);
}

TEST(decrease, cut_second_degree_tree_in_half) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});
    heap.insert({4, 4});
    heap.insert({5, 5});

    heap.extractMin();

    heap.decrease(4, 1);

    EXPECT_EQ(heap.firstTree->key, 2);
    EXPECT_EQ(heap.firstTree->prevBro->key, 1);
    EXPECT_EQ(heap.cachedMin->key, 1);
    EXPECT_EQ(heap.numberOfTrees, 2);
}

TEST(extractMin, nine_items_build_third_degree_tree) {
    FibonacciHeap heap;

    auto pt = heap.insert({5, 5});
    auto sest = heap.insert({6, 6});
    auto ct = heap.insert({4, 4});
    auto dev = heap.insert({9, 9});
    auto dv = heap.insert({2, 2});
    heap.insert({1, 1});
    auto sed = heap.insert({7, 7});
    auto osm = heap.insert({8, 8});
    auto tr = heap.insert({3, 3});

    pt;
    sest;
    ct;
    dev;
    dv;
    sed;
    osm;
    tr;

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.numberOfTrees, 1);
    EXPECT_EQ(heap.firstTree, dv);
    EXPECT_EQ(heap.firstTree->nextBro, dv);
    EXPECT_EQ(heap.firstTree->prevBro, dv);

    EXPECT_EQ(dv->sonCount, 3);
    EXPECT_EQ(dv->firstSon, sed);
    EXPECT_EQ(dv->firstSon->nextBro, tr);
    EXPECT_EQ(dv->firstSon->nextBro->nextBro, ct);
    EXPECT_EQ(dv->firstSon->nextBro->nextBro->nextBro, sed);

    EXPECT_EQ(sed->sonCount, 0);
    EXPECT_EQ(tr->sonCount, 1);
    EXPECT_EQ(ct->sonCount, 2);
    EXPECT_EQ(osm->sonCount, 0);
    EXPECT_EQ(dev->sonCount, 0);
    EXPECT_EQ(sest->sonCount, 0);

    EXPECT_EQ(dev->parent, ct);
    EXPECT_EQ(sest->parent, pt);
    EXPECT_EQ(pt->parent, ct);
    EXPECT_EQ(ct->parent, dv);
    EXPECT_EQ(dv->parent, nullptr);
    EXPECT_EQ(osm->parent, tr);
    EXPECT_EQ(tr->parent, dv);
    EXPECT_EQ(sed->parent, dv);
}

TEST(decrease, decrease_cuts_a_third_degree_tree) {
    FibonacciHeap heap;

    auto pt = heap.insert({5, 5});
    auto sest = heap.insert({6, 6});
    auto ct = heap.insert({4, 4});
    auto dev = heap.insert({9, 9});
    auto dv = heap.insert({2, 2});
    heap.insert({1, 1});
    auto sed = heap.insert({7, 7});
    auto osm = heap.insert({8, 8});
    auto tr = heap.insert({3, 3});
    pt;
    sest;
    ct;
    dev;
    dv;
    sed;
    osm;
    tr;

    // Structure tested in extractMin--nine_items_build_third_degree_tree
    EXPECT_EQ(heap.extractMin(), 1);
    EXPECT_NO_THROW(heap.decrease(5, 1));

    // should cut the 5--6 subtree and insert it as 1--6 instead and MARK 4

    EXPECT_EQ(ct->mark, true);

    EXPECT_EQ(heap.numberOfTrees, 2);

    EXPECT_EQ(heap.firstTree, dv);
    EXPECT_EQ(heap.firstTree->nextBro->key, 1);
    EXPECT_EQ(heap.firstTree->nextBro, pt);
    EXPECT_EQ(heap.cachedMin->key, 1);
    EXPECT_EQ(pt->sonCount, 1);
    EXPECT_EQ(pt->firstSon, sest);
    EXPECT_EQ(dv->sonCount, 3);
    EXPECT_EQ(pt->parent, nullptr);
    EXPECT_EQ(ct->sonCount, 1);
    EXPECT_EQ(ct->firstSon, dev);
    EXPECT_EQ(dev->nextBro, dev);
}

TEST(decrease, decrease_and_extractMin_do_not_set_INT_MIN) {
    FibonacciHeap heap;

    auto je = heap.insert({1, 1});
    auto dv = heap.insert({2, 2});
    heap.insert({3, 3});

    heap.deleteItem(3);

    EXPECT_EQ(heap.cachedMin, je);
    EXPECT_EQ(heap.firstTree, je);
    EXPECT_EQ(heap.firstTree->nextBro, je);
    EXPECT_EQ(heap.firstTree->sonCount, 1);
    EXPECT_EQ(heap.firstTree->firstSon, dv);
}

TEST(Logger, logs_correctly_simple) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    heap.insert({2, 2});
    heap.insert({3, 3});

    heap.extractMin();

    EXPECT_EQ(heap.log.numberOfLogs, 1);
    EXPECT_EQ(heap.log.cumulativeLog, 1);
    EXPECT_EQ(heap.log.getAverage(), 1.f);
}

TEST(Logger, logs_correctly_complicated) {
    FibonacciHeap heap;

    heap.insert({5, 5});
    heap.insert({6, 6});
    heap.insert({4, 4});
    heap.insert({9, 9});
    heap.insert({2, 2});
    heap.insert({1, 1});
    heap.insert({7, 7});
    heap.insert({8, 8});
    heap.insert({3, 3});

    // Structure tested in extractMin--nine_items_build_third_degree_tree
    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.log.numberOfLogs, 1);
    EXPECT_EQ(heap.log.cumulativeLog, 7);
    EXPECT_EQ(heap.log.getAverage(), 7.f);

    EXPECT_NO_THROW(heap.decrease(5, 1));

    EXPECT_EQ(heap.log.numberOfLogs, 1);
    EXPECT_EQ(heap.log.cumulativeLog, 7);
    EXPECT_EQ(heap.log.getAverage(), 7.f);

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.log.numberOfLogs, 2);
    EXPECT_EQ(heap.log.cumulativeLog, 8);
    EXPECT_EQ(heap.log.getAverage(), 4.f);

    EXPECT_EQ(heap.extractMin(), 2);

    EXPECT_EQ(heap.log.numberOfLogs, 3);
    EXPECT_EQ(heap.log.cumulativeLog, 13);
    EXPECT_EQ(heap.log.getAverage(), 13.f / 3.f);


    EXPECT_EQ(heap.extractMin(), 3);

    EXPECT_EQ(heap.log.numberOfLogs, 4);
    EXPECT_EQ(heap.log.cumulativeLog, 16);
    EXPECT_EQ(heap.log.getAverage(), 16.f / 4.f);
}

TEST(deleteNode, deleting_son_fuck_up) {
    FibonacciHeap heap;
    heap.insert({1, 1});
    heap.insert({2, 2});
    auto tri = heap.insert({3, 3});

    EXPECT_EQ(heap.extractMin(), 1);

    EXPECT_EQ(heap.firstTree->key, 2);
    EXPECT_EQ(heap.firstTree->nextBro->key, 2);
    EXPECT_EQ(heap.firstTree->prevBro->key, 2);

    EXPECT_EQ(heap.firstTree->firstSon, tri);

    heap.cut(tri);

    EXPECT_EQ(heap.firstTree->firstSon, nullptr);
    EXPECT_NE(heap.firstTree->firstSon, tri);
}

TEST(naive, naive_cut_from_example)
{
    FibonacciHeap heap;

    auto one = heap.insert({1,1});

    FibNode* A = new FibNode({100, 100});
    FibNode* B = new FibNode({101, 101});
    FibNode* C = new FibNode({102, 102});
    FibNode* D = new FibNode({103, 103});
    FibNode* E = new FibNode({105, 104});
    FibNode* F = new FibNode({104, 105});

    FibNode* three = new FibNode({3,3});
    FibNode* four = new FibNode({4,4});
    FibNode* seven = new FibNode({7,7});
    FibNode* eight = new FibNode({8,8});

    heap.firstTree->firstSon = A;
    heap.firstTree->nextBro = heap.firstTree;
    heap.firstTree->sonCount = 2;
    heap.firstTree->prevBro = heap.firstTree;

    A->nextBro = three;
    A->prevBro = three;
    A->parent = one;

    three->nextBro = A;
    three->prevBro = A;
    three->sonCount = 2;
    three->firstSon = four;
    three->parent = one;
    
    B->nextBro = four;
    B->prevBro = four;
    B->parent = three;

    four->nextBro = B;
    four->prevBro = B;
    four->mark = true;
    four->sonCount = 2;
    four->firstSon = C;

    C->nextBro = seven;
    C->prevBro = seven;
    C->parent = four;

    seven->nextBro = C;
    seven->prevBro = C;
    seven->mark = true;
    seven->sonCount = 2;
    seven->firstSon = D;

    D->nextBro = eight;
    D->prevBro = eight;
    D->parent = seven;

    eight->nextBro = D;
    eight->prevBro = D;
    eight->mark = false;
    eight->sonCount = 2;
    eight->parent = seven;
    eight->firstSon = E;

    E->nextBro = F;
    E->prevBro = F;
    E->parent = eight;

    F->nextBro = E;
    F->prevBro = E;
    F->parent = eight;

    heap.naive = true;
    heap.mapa[8] = eight;
    heap.decrease(8, 6);

    EXPECT_EQ(heap.numberOfTrees, 2);
    EXPECT_EQ(heap.firstTree->key, 1);
    EXPECT_EQ(one->nextBro->key, 6);
    EXPECT_EQ(one->prevBro->key, 6);
    EXPECT_EQ(eight->nextBro->key, 1);
    EXPECT_EQ(eight->prevBro->key, 1);

    EXPECT_EQ(four->firstSon->prevBro->key, 7);
    EXPECT_EQ(four->firstSon, C);

    EXPECT_EQ(eight->firstSon, E);
    EXPECT_EQ(eight->firstSon->nextBro, F);
}

// \todo TEST for marks
// \todo TEST for decrease + extractMin should check if cachedMin != INT_MIN





















