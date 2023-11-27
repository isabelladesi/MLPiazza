#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

TEST(test_empty) {
    BinarySearchTree<int> bEmpty;
    ASSERT_TRUE(bEmpty.empty());

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_FALSE(b1.empty());
}

TEST(test_size) {
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.size(), 0u);

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(b1.size(), 1u);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(bSame.size(), 3u);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(bDiff.size(), 4u);
}

TEST(test_height) {
    BinarySearchTree<int> bEmpty;
    ASSERT_EQUAL(bEmpty.height(), 0u);

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(b1.height(), 1u);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(bSame.height(), 3u);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(bDiff.height(), 4u);
}

// TEST(test_copy_nodes) {
//     BinarySearchTree<int> b;
//     b.insert(1);
//     b.insert(0);
//     // change first datum to 2, resulting in the first broken tree above
//     *b.begin() = 2;
//     ASSERT_FALSE(b.check_sorting_invariant());
// }

// TEST(test_check_sorting_invariant) {
//     BinarySearchTree<int> b;
//     b.insert(1);
//     b.insert(0);
//     // change first datum to 2, resulting in the first broken tree above
//     *b.begin() = 2;
//     ASSERT_FALSE(b.check_sorting_invariant());
// }

TEST_MAIN()
