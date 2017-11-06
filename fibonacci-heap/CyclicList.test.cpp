#include <gtest/gtest.h>

#include "fibheap.h"

TEST(push_back, increases_size) {
    CyclicList<int> list;
    list.pushBack(1);
    EXPECT_EQ(list.size(), 1);
    list.pushBack(2);
    EXPECT_EQ(list.size(), 2);
    list.pushBack(3);
    EXPECT_EQ(list.size(), 3);
}

TEST(push_back, head_stays_tail_changes) {
    CyclicList<int> list;
    list.pushBack(1);
    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 1);

    list.pushBack(2);
    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 2);

    list.pushBack(3);
    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 3);
}

#define VALS_N 5
TEST(push_back, all_values_inside) {
    int vals[VALS_N] = {1, 2, 3, 4, 5};

    CyclicList<int> list;
    for (int i = 0; i < VALS_N; ++i) {
        list.pushBack(vals[i]);
    }

    const CyclicList<int>::Node *cur = list.head();
    int i = 0;
    while (cur != list.tail()) {
        EXPECT_EQ(cur->value, vals[i]);
        ++i;
        cur = cur->next;
    }
}

TEST(merge, all_values_inside) {
    int vals[3] = {1, 2, 3};
    int vals2[3] = {4, 5, 6};

    CyclicList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.pushBack(vals[i]);
    }

    CyclicList<int> list2;
    for (int i = 0; i < 3; ++i) {
        list2.pushBack(vals2[i]);
    }

    list.merge(list2);

    EXPECT_EQ(list.size(), 6);
    const CyclicList<int>::Node *cur = list.head();
    int i = 0;
    while (cur != list.tail() && i < 7) {
        if (i < 3) {
            EXPECT_EQ(cur->value, vals[i]);

        } else {
            EXPECT_EQ(cur->value, vals2[i-3]);
        }
        ++i;
        cur = cur->next;
    }
}

TEST(merge, new_from_empty) {
    int vals[3] = {1, 2, 3};
    int vals2[3] = {4, 5, 6};

    CyclicList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.pushBack(vals[i]);
    }

    CyclicList<int> list2;
    for (int i = 0; i < 3; ++i) {
        list2.pushBack(vals2[i]);
    }

    list.merge(list2);

    EXPECT_EQ(list2.size(), 0);
    EXPECT_EQ(list2.head(), nullptr);
    EXPECT_EQ(list2.tail(), nullptr);
}

TEST(merge, merge_into_empty) {
    int vals2[3] = {4, 5, 6};

    CyclicList<int> list;

    CyclicList<int> list2;
    for (int i = 0; i < 3; ++i) {
        list2.pushBack(vals2[i]);
    }

    list.merge(list2);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->value, 4);
    EXPECT_EQ(list.tail()->value, 6);
}

TEST(merge, merge_from_empty) {
    int vals[3] = {4, 5, 6};

    CyclicList<int> list2;

    CyclicList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.pushBack(vals[i]);
    }

    list.merge(list2);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.head()->value, 4);
    EXPECT_EQ(list.tail()->value, 6);
}

TEST(merge, merge_from_size1) {
    int vals[3] = {4, 5, 6};

    CyclicList<int> list2;
    list2.pushBack(1);

    CyclicList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.pushBack(vals[i]);
    }

    list.merge(list2);

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.head()->value, 4);
    EXPECT_EQ(list.tail()->value, 1);
}

TEST(merge, merge_to_size1) {
    int vals[3] = {4, 5, 6};

    CyclicList<int> list2;
    list2.pushBack(1);

    CyclicList<int> list;
    for (int i = 0; i < 3; ++i) {
        list.pushBack(vals[i]);
    }

    list2.merge(list);

    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.head()->value, 1);
    EXPECT_EQ(list2.tail()->value, 6);
}