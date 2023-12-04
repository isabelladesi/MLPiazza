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
// TEST(test_destroy) {
//     BinarySearchTree<int> bSame;
//     bSame.insert(22);
//     bSame.insert(15);
//     bSame.insert(30);

//    BinarySearchTree<int> b;
//    b.insert(2);
//    b.insert(1);
//    b.insert(3);
//    BinarySearchTree<int> b_copied(b);

//    delete *b_copied;
   

//     //delte all nodes from a BST and then assure BinarySearchTree is empty
// }

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
    ASSERT_EQUAL(os.str(), "1 2 5 6 7 9 10 ");

    BinarySearchTree<int> bEmpty;
    std::ostringstream as;
    bEmpty.traverse_inorder(as);
    ASSERT_EQUAL(as.str(), "");

    BinarySearchTree<int> b1;
    std::ostringstream bs;
    b1.insert(2);
    b1.traverse_inorder(bs);
    ASSERT_EQUAL(bs.str(), "2 ");
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
    ASSERT_EQUAL(os.str(), "6 5 1 2 9 7 10 ");

    BinarySearchTree<int> bEmpty;
    std::ostringstream as;
    bEmpty.traverse_preorder(as);
    ASSERT_EQUAL(as.str(), "");

    BinarySearchTree<int> b1;
    std::ostringstream bs;
    b1.insert(2);
    b1.traverse_preorder(bs);
    ASSERT_EQUAL(bs.str(), "2 ");
}

TEST(test_copy_nodes) {
   BinarySearchTree<int> b;
   b.insert(2);
   b.insert(1);
   b.insert(3);
   
   BinarySearchTree<int> b_copied(b);

   std::ostringstream as;
   b.traverse_preorder(as);
   std::ostringstream bs;
   b_copied.traverse_preorder(bs);
   
   ASSERT_EQUAL(b_copied.size(), b.size());
   ASSERT_EQUAL(b_copied.height(), b.height());
   ASSERT_EQUAL(bs.str(), as.str());
    b.insert(9);
    b.traverse_preorder(as);
    ASSERT_NOT_EQUAL(b_copied.size(), b.size());
    ASSERT_NOT_EQUAL(b_copied.height(), b.height());
    ASSERT_NOT_EQUAL(bs.str(), as.str());
}

TEST(test_assignmentOp_nodes) {
   BinarySearchTree<int> b;
   b.insert(2);
   b.insert(1);
   b.insert(3);
   
   BinarySearchTree<int> b_copied;
    b_copied.insert(4);
    b_copied.insert(8);

   b_copied = b;

   std::ostringstream as;
   b.traverse_preorder(as);
   std::ostringstream bs;
   b_copied.traverse_preorder(bs);
   
   ASSERT_EQUAL(b_copied.size(), b.size());
   ASSERT_EQUAL(b_copied.height(), b.height());
   ASSERT_EQUAL(bs.str(), as.str());
    b.insert(9);
    b.traverse_preorder(as);
    ASSERT_NOT_EQUAL(b_copied.size(), b.size());
    ASSERT_NOT_EQUAL(b_copied.height(), b.height());
    ASSERT_NOT_EQUAL(bs.str(), as.str());
}

TEST(test_check_sorting_invariant) {
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());
}

TEST(test_check_sorting_invariant_moreInDepth) {
    BinarySearchTree<int> b;
    b.insert(5);
    b.insert(6);
    b.insert(7);
    b.insert(9);
    // b.insert(4);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 8;
    ASSERT_FALSE(b.check_sorting_invariant());

    BinarySearchTree<int> b1;
    b1.insert(5);
    b1.insert(4);
    b1.insert(6);
    *b1.begin() = 8;
    ASSERT_FALSE(b1.check_sorting_invariant());
}

TEST(test_min_element) {
    BinarySearchTree<int> b; //how do u check this then
    ASSERT_EQUAL(b.min_element(), b.end());

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
    ASSERT_EQUAL(b.max_element(), b.end()); //this isnt working
  
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
    ASSERT_EQUAL(b.min_greater_than(0), b.end());

    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(*b1.min_greater_than(0), 2);
    ASSERT_EQUAL(b1.min_greater_than(2), b.end());
    ASSERT_EQUAL(b1.min_greater_than(3), b1.end());

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    bSame.insert(15);
    bSame.insert(30);
    bSame.insert(14);
    bSame.insert(16);
    bSame.insert(26);
    bSame.insert(39);
    ASSERT_EQUAL(*bSame.min_greater_than(16), 22);
    ASSERT_EQUAL(bSame.min_greater_than(39), bSame.end());
    ASSERT_EQUAL(bSame.min_greater_than(40), bSame.end());
    ASSERT_EQUAL(*bSame.min_greater_than(14), 15);
    ASSERT_EQUAL(*bSame.min_greater_than(30), 39);
}

TEST(test_find) {
    BinarySearchTree<int> b; //same here
    ASSERT_EQUAL(b.find(1), b.end());

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
    BinarySearchTree<int> b1;
    b1.insert(2);
    ASSERT_EQUAL(b1.size(), 1);
    ASSERT_EQUAL(*b1.find(2), 2);

    BinarySearchTree<int> bSame;
    bSame.insert(22);
    //bSame.insert(22); should we test if 2 same things get inserted?
    ASSERT_EQUAL(bSame.size(), 1);

    BinarySearchTree<int> bDiff;
    bDiff.insert(2);
    bDiff.insert(3);
    bDiff.insert(7);
    bDiff.insert(1);
    bDiff.insert(22);
    ASSERT_EQUAL(bDiff.size(), 5);
}

// should we test through the deconstructor?
// TEST(test_destroy_impl) {
//     BinarySearchTree<int> b1;
//     b1.insert(2);
//     destroy_nodes_impl(b1);
//     ASSERT_EQUAL(b1.size(), 1);
//     ASSERT_EQUAL(*b1.find(2), 2);

//     BinarySearchTree<int> bSame;
//     bSame.insert(22);
//     //bSame.insert(22); should we test if 2 same things get inserted?
//     ASSERT_EQUAL(bSame.size(), 1);

//     BinarySearchTree<int> bDiff;
//     bDiff.insert(2);
//     bDiff.insert(3);
//     bDiff.insert(7);
//     bDiff.insert(1);
//     bDiff.insert(22);
//     ASSERT_EQUAL(bDiff.size(), 5);
// }



TEST_MAIN()
