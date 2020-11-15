//tests
//this will be the main that will unite all the tests

#include <gtest/gtest.h>
#include "../src/Random.h"
#include "../src/Neuron.h"

RandomNumbers *_RNG = new RandomNumbers(23947810923);

TEST(Neuron, create_neuron)
{
	Neuron n1(RS);
	EXPECT_FALSE(n1.isFiring());
	EXPECT_FALSE(n1.isInhibitor());
	Neuron n2(FS);
	EXPECT_FALSE(n2.isFiring());
	EXPECT_TRUE(n2.isInhibitor());
}

TEST(Neuron, update)
{
	Neuron n1(RS);
	//to be completed
	
	
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
