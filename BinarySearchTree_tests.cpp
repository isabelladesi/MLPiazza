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
    ASSERT_EQUAL(bSame.size(), 7u);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(bDiff.size(), 5u);
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

TEST(test_traverse_inorder) {
    BinarySearchTree<int> b;
    std::ostringstream os;
    b.insert(6);
    b.insert(5);
    b.insert(9);
    b.insert(1);
    b.insert(2);
    b.insert(7);
    b.insert(10);
    b.traverse_inorder(os);
    // change first datum to 2, resulting in the first broken tree above
    ASSERT_EQUAL(os.str(), "1 2 5 6 7 9 10");
}

TEST(test_traverse_preorder) {
    BinarySearchTree<int> b;
    std::ostringstream os;
    b.insert(6);
    b.insert(5);
    b.insert(9);
    b.insert(1);
    b.insert(2);
    b.insert(7);
    b.insert(10);
    b.traverse_preorder(os);
    // change first datum to 2, resulting in the first broken tree above
    ASSERT_EQUAL(os.str(), "6 5 1 2 9 7 10");
}

// TEST(test_copy_nodes) {
//     BinarySearchTree<int> b;
//     b.insert(1);
//     b.insert(0);
//     // change first datum to 2, resulting in the first broken tree above
//     *b.begin() = 2;
//     ASSERT_FALSE(b.check_sorting_invariant());
// }

TEST(test_check_sorting_invariant) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_min_element) {
    BinarySearchTree<int> b;

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(*b1.min_element(), 2);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(*bSame.min_element(), 14);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(*bDiff.min_element(), 1);
}

TEST(test_max_element) {
    BinarySearchTree<int> b;
  

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(*b1.max_element(), 2);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(*bSame.max_element(), 39);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(*bDiff.max_element(), 22);
}

TEST(test_min_greater_than) {
    BinarySearchTree<int> b;

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(b1.size(), 1);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(bSame.size(), 7);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(bDiff.size(), 5);
}

TEST(test_find) {
    BinarySearchTree<int> b;
   

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(*b1.find(2), 2);
    ASSERT_EQUAL(b1.find(0), b1.end());

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(bSame.find(0), bSame.end());
    ASSERT_EQUAL(*bSame.find(26), 26);
}

TEST(test_insert) {
    BinarySearchTree<int> b;


    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(b1.size(), 1);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(bSame.size(), 7);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(bDiff.size(), 5);
}



TEST_MAIN()
