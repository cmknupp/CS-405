/* test.cpp code provided by SNHU for CS-405  *
 * Updated by Connie Knupp on 07/27/2025.     */

// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUpCollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection) << "Collection not created" << std::endl;

    // if created the function .get does not return a nullptr
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// DONE: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    //now is the collection empty?  
    ASSERT_FALSE(collection->empty()) << "Collection is empty after adding 1 entry" << std::endl;

    // if not empty, the size must be 1
    ASSERT_EQ(collection->size(), 1);
}

// DONE: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    //now is the collection empty?  
    ASSERT_FALSE(collection->empty()) << "Collection is empty after adding 5 entries" << std::endl;

    // if not empty, the size must be 5
    ASSERT_EQ(collection->size(), 5);
}

// DONE: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyMaxSizeGreaterThanSizeWithVaryingSizes)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // is max size greater than or equal to size 0
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection max size " << collection->max_size() << " not greater than collection size " << collection->size() << std::endl;

    //
    add_entries(1);

    //now is the collection empty?  
    EXPECT_FALSE(collection->empty()) << "Collection empty after adding 1 entry." << std::endl;

    // if not empty, the size should be 1
    EXPECT_EQ(collection->size(), 1);

    // is max size greater than or equal to size 1
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection max size " << collection->max_size() << " is less than collection size " << collection->size() << std::endl;

    add_entries(4); // 5 entries total

    // the size should be 5
    EXPECT_EQ(collection->size(), 5);

    // is max size greater than or equal to size 5
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection max size " << collection->max_size() << " is less than collection size " << collection->size() << std::endl;


    add_entries(5); // 10 entries total

    // the size should be 10
    EXPECT_EQ(collection->size(), 10);

    // is max size greater than or equal to size 10
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection max size " << collection->max_size() << " is less than collection size " << collection->size() << std::endl;
}


// DONE: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, VerifyCapacityGreaterThanSizeWithVaryingSizes)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // is capacity greater than or equal to size 0
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection capacity " << collection->capacity() << " not greater than collection size " << collection->size() << std::endl;

    //
    add_entries(1);

    //now is the collection empty?  
    EXPECT_FALSE(collection->empty()) << "Collection empty after adding 1 entry." << std::endl;

    // if not empty, the size should be 1
    EXPECT_EQ(collection->size(), 1);

    // is capacity greater than or equal to size 1
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection capacity " << collection->capacity() << " is less than collection size " << collection->size() << std::endl;

    add_entries(4); // 5 entries total

    // the size should be 5
    EXPECT_EQ(collection->size(), 5);

    // is capacity greater than or equal to size 5
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection capacity " << collection->capacity() << " is less than collection size " << collection->size() << std::endl;


    add_entries(5); // 10 entries total

    // the size should be 10
    EXPECT_EQ(collection->size(), 10);

    // is capacity greater than or equal to size 10
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection capacity " << collection->capacity() << " is less than collection size " << collection->size() << std::endl;
}

// DONE: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, VerifyResizingIncreasesCollectionSize)
{
    //variable for sizes
    int initial_size = 0;
    int new_size = 10;

    // is the collection empty?
    EXPECT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be initial size
    EXPECT_EQ(collection->size(), initial_size);

    //resize to new size
    collection->resize(new_size);

    //was collection size increased?
    ASSERT_GT(collection->size(), initial_size) << "Collection size " << collection->size() << " is less than inital size " << initial_size << std::endl;

    //if increased collection size should equal new size
    ASSERT_EQ(collection->size(), new_size) << "Collection size " << collection->size() << "does not equal expected size " << new_size << std::endl;
}

// DONE: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, VerifyResizingDecreasesCollectionSize)
{
    //variable for sizes
    int initial_size = 10;
    int new_size = 8;

    //add entries to get starting size
    add_entries(initial_size);

    // is the collection empty?
    EXPECT_FALSE(collection->empty()) << "Collection is empty after adding entries." << std::endl;

    // if not empty, the size must be equal to starting size variable
    EXPECT_EQ(collection->size(), initial_size);

    //resize to new size
    collection->resize(new_size);

    //was collection size decreased?
    ASSERT_LT(collection->size(), initial_size) << "Collection size " << collection->size() << " is greater than inital size " << initial_size << std::endl;

    //if decreased collection size should equal new size
    ASSERT_EQ(collection->size(), new_size) << "Collection size " << collection->size() << "does not equal expected size " << new_size << std::endl;
}

// DONE: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, VerifyResizingDecreasesCollectionSizeToZero)
{
    //variables for sizes
    int initial_size = 10;
    int new_size = 0;  //should be zero

    //add entries to get starting size
    add_entries(initial_size);

    // is the collection empty?
    EXPECT_FALSE(collection->empty()) << "Collection is empty after adding entries." << std::endl;

    // if not empty, the size must be equal to starting size variable
    EXPECT_EQ(collection->size(), initial_size);

    //resize to new size
    collection->resize(new_size);

    //was collection size decreased?
    ASSERT_LT(collection->size(), initial_size) << "Collection size " << collection->size() << " is greater than inital size " << initial_size << std::endl;

    //if decreased collection size should equal new size
    ASSERT_EQ(collection->size(), new_size) << "Collection size " << collection->size() << "does not equal expected size " << new_size << std::endl;
}

// DONE: Create a test to verify clear erases the collection
TEST_F(CollectionTest, VerifyCollectionClearErasesCollection)
{
    //variable for sizes
    int initial_size = 10;

    //add entries to get starting size
    add_entries(initial_size);

    // is the collection empty?
    EXPECT_FALSE(collection->empty()) << "Collection is empty after adding entries." << std::endl;

    //clear collection
    collection->clear();

    //is collection now empty?
    ASSERT_TRUE(collection->empty()) << "Collection is not empty after clear()." << std::endl;
}

// DONE: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, VerifyEraseBeginToEndErasesCollection)
{
    //variable for sizes
    int initial_size = 10;

    //add entries to get starting size
    add_entries(initial_size);

    // is the collection empty?
    EXPECT_FALSE(collection->empty()) << "Collection is empty after adding entries." << std::endl;

    //erase (begin, end)
    collection->erase(collection->begin(), collection->end());

    //is collection now empty?
    ASSERT_TRUE(collection->empty()) << "Collection is not empty after erase(begin, end)." << std::endl;
}

// DONE: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, VerifyReserveIncreasesCollectionCapacityNotSize)
{
    //variable for sizes
    int initial_size = 0;
    int initial_capacity = collection->capacity(); //should initialize empty
    int new_capacity = 8;

    // verify the collection is empty?
    EXPECT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be initial size (0)
    EXPECT_EQ(collection->size(), initial_size);

    // reserve capacity of new capacity
    collection->reserve(new_capacity);

    //does collection size still equal initial size
    ASSERT_EQ(collection->size(), initial_size) << "Collection size " << collection->size() << " does not equal initial size " << initial_size << std::endl;

    //has collection capacity increased
    ASSERT_GT(collection->capacity(), initial_capacity) << "Collection capacity " << collection->capacity() << " is not greater than initial capacity " << initial_capacity << std::endl;

    // if increased collection capacity should equal new capacity
    ASSERT_EQ(collection->capacity(), new_capacity) << "Collection capacity " << collection->capacity() << " does not equal new capacity " << new_capacity << std::endl;
    
}

// DONE: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test (1 of 2)
TEST_F(CollectionTest, VerifyOutOfRangeExceptionThrownWhenCallingOutOfBoundsIndex)
{
    //variable for sizes
    int expected_size = 5;
    int out_of_bounds_index = 8;

    //add entries to get starting size
    add_entries(expected_size);

    // is the collection empty?
    EXPECT_FALSE(collection->empty()) << "Collection is empty after adding entries." << std::endl;

    // if not empty, the size must be equal to expected size variable
    EXPECT_EQ(collection->size(), expected_size);

    ASSERT_THROW(collection->at(out_of_bounds_index), std::out_of_range) << "Should have thrown out of range exception" << std::endl;
}


// DONE: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

/* 1 of 2 created unit tests, positive test
 * Verifying pop_back() removes the last entry and leaves other entries unchanged  */
TEST_F(CollectionTest, VerifyPopBackRemovesLastEntry)
{
    //variable for sizes
    int initial_size = 5;
    int valueOfLastEntry;

    //add initial entries
    for (int i = 1; i <= initial_size; i++) {
        collection->push_back(i); // add entries with values 1-5
    }

    // is the collection empty?
    EXPECT_FALSE(collection->empty()) << "Collection is empty after adding entries." << std::endl;

    // if not empty, the size must be equal to initial_size
    EXPECT_EQ(collection->size(), initial_size);

    // verify values for entries number from 1 to initial size
    for (int i = 1; i <= initial_size; i++) {
        EXPECT_EQ(collection->at(i-1), i);
    }

    //get last entry value
    valueOfLastEntry = collection->back();

    //verify last entry value equals initial_size variable (5)
    EXPECT_EQ(valueOfLastEntry, initial_size) << "Value of last entry " << valueOfLastEntry << " should equal initial size " << initial_size << std::endl;

    //remove last entry using pop_back()
    collection->pop_back();

    // verify values other entries remain unchanged
    for (int i = 1; i <= (initial_size - 1); i++) {
        ASSERT_EQ(collection->at(i-1), i);
    }

    //verify size is now initial size -1
    ASSERT_EQ(collection->size(), initial_size - 1) << "Collection size " << collection->size() << "should equal initial_size " 
        << initial_size << " - 1." << std::endl;
}

/* 2 of 2 created unit tests
 * NOTE: this is negative test 2 of 2
 * Tests if exception is thrown when attempting to reserve more than the max_size. 
 */
TEST_F(CollectionTest, VerifyExceptionThrownWhenReservingMoreThanMaxSize)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty()) << "Collection is not empty at create" << std::endl;

    // if empty, the size must be 0
    EXPECT_EQ(collection->size(),0);

    //does reserving more than max size throw expected exception?
    ASSERT_THROW(collection->reserve(collection->max_size() + 10), std::length_error) << "Reserving ten more than max size " << collection->max_size()
        << "should throw length error." << std::endl;
}


