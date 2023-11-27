#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_empty) {
    BinarySearchTree<int> b;
    ASSERT_EQUAL(b.height(), 0u);
}

TEST_MAIN()
