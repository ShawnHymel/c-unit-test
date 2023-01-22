#include "CppUTest/TestHarness.h"

extern "C" {
    #include "average.h"
}

// Create a test group
TEST_GROUP(average_test_group)
{
    void setup()
    {
        // Initialize before each test
    }
    
    void teardown()
    {
        // Deinitialize after each test
    }
};

// Test the average function
TEST(average_test_group, simple_test)
{
    float array[] = {-1.0, 0.0, 1.0, 2.0, 3.0};
    float avg = average(array, 5);
    CHECK_EQUAL(avg, 1.0);
}

// Test null array
TEST(average_test_group, null_test)
{
    float array[1];
    float avg = average(array, 0);
    CHECK_EQUAL(avg, 0.0);
}