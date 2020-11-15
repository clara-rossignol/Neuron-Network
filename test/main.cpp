//tests
//this will be the main that will unite all the tests

#include <gtest/gtest.h>
#include "../src/Neuron.h"
#include "../src/Random.h"
#include "../src/Network.h"


RandomNumbers *_RNG = new RandomNumbers(23947810923);

TEST(Neuron, create_neuron)
{
	Neuron n1(RS);
	EXPECT_FALSE(n1.isFiring());
}

TEST(Neuron, neuron_types)
{
	Neuron n1(RS);
	EXPECT_FALSE(n1.isInhibitor());
	Neuron n2(FS);
	EXPECT_TRUE(n2.isInhibitor());
}

TEST(Neuron, update)
{
	Neuron n1(RS);
	n1.update();
	//not sure how to calculate between what and what the potential and the recovery variables are supposed to be
	/*EXPECT_NEAR(, n1.getMembranePotential(),-);
	EXPECT_NEAR(, n1.getRecoveryVariable(),);*/

	//to be completed
	
}

/*
TEST(neuron, connection)
{
	Neuron n1(RS);
	Neuron n2(RS);
	
	Connection c;
	c.sender = *n2;
	c.intensity = ???;
	n1.newConnection(c);
}
*/

TEST(Network, setConnections)
{
    double meanIntensity(100);
    double meanConnectivity(100);

    double average(0);
    std::size_t N = 0;
    for (size_t i(0); i<100; ++i)
    {
        Network net(std::vector<Neuron>(10000, Neuron(RS)));
        net.setConnections(meanIntensity, meanConnectivity);
        double sum(0);

        for(auto& n : net.getNeurons())
        {
            for(auto c : n.getConnections())
                sum += c.intensity;
            N += n.getConnections().size();
        }
        average += sum;
    }

    average /=(N);

    EXPECT_NEAR(meanIntensity, average, 0.007);
    EXPECT_NEAR(N/(10000*100), 100, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
