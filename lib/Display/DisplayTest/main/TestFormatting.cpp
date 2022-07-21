#include "unity.h"
#include <array>
#include "Display.h"

TEST_CASE("testRoundUpCorrectOutput", "[module name]")
{
    std::array data{
        std::array {12.302492394, 12.30}
    };

    for(int test = 0; test != data.length(); test++){
        double output = roundUp(data[test][0]);

        TEST_ASSERT_EQUAL(output, data[test][0]);
    }
}


int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(testRoundUpCorrectOutput);
    int failures = UNITY_END();
    return failures;