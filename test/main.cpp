//tests
//this will be the main that will unite all the tests

#include <gtest/gtest.h>
#include "../src/Neuron.h"
#include "../src/Random.h"
#include "../src/Network.h"
#include "../src/ConstNetwork.h"
#include "../src/DispNetwork.h"

RandomNumbers *_RNG = new RandomNumbers(23948710923);

TEST(Neuron, create_neuron)
{
	Neuron n1("RS");
	EXPECT_FALSE(n1.isFiring());
    Neuron n("RS");
    EXPECT_FALSE(n.isFiring());
}

TEST(Neuron, neuron_types)
{
	Neuron n1("RS");
	EXPECT_FALSE(n1.isInhibitor());
	Neuron n2("FS");
	EXPECT_TRUE(n2.isInhibitor());
}

TEST(Neuron, update)
{
	Neuron n1("RS");
	n1.update();
	EXPECT_EQ(n1.getRecoveryVariable(), -13);
    Neuron n2("FS", true);
    n2.update();
    EXPECT_EQ(n2.getMembranePotential(), -65);
    EXPECT_EQ(n2.getRecoveryVariable(), -11);
}


TEST(Neuron, current_calculation)
{
    double meanCurrent(0);
    for(size_t i(0); i<100; ++i)
    {
        Neuron n("FS");
        Neuron n1("RS");
        Neuron n2("RS");
        n.newConnection({&n1,10});
        n.newConnection({&n2, 10});
        meanCurrent += n.currentCalculation();
    }
    meanCurrent /= 100;
	EXPECT_NEAR(meanCurrent, 10, 0.5);
}


TEST(Network, setConnections)
{
    double meanIntensity(100);
    double meanConnectivity(100);

    double average(0);
    std::size_t N = 0;
    for (size_t i(0); i<100; ++i)
    {
        Network net(std::vector<Neuron>(10000, Neuron("RS")));
        net.setConnections(meanIntensity, meanConnectivity);
        double sum(0);

        for(const auto& n : net.getNeurons())
        {
            for(auto c : n.getConnections())
                sum += c.intensity;
            N += n.getConnections().size();
        }
        average += sum;
    }

    average /=(N);

    EXPECT_NEAR(meanIntensity, average, 0.01);
    EXPECT_NEAR(N/(10000*100), 100, 1);
}

TEST(ConstNetwork, setConnections)
{
    double meanIntensity(100);
    double meanConnectivity(100);
    ConstNetwork net(std::vector<Neuron>(3, Neuron("RS")));
    net.setConnections(meanIntensity, meanConnectivity);
    for(const auto& n : net.getNeurons() )
    {
        EXPECT_EQ(n.getConnections().size(), meanConnectivity);
    }
}

TEST(DispNetwork, setConnections)
{
    double meanIntensity(100);
    double meanConnectivity(100);
    std::size_t N = 0;
    for (size_t i(0); i<100; ++i)
    {
        DispNetwork net(std::vector<Neuron>(10000, Neuron("RS")));
        net.setConnections(meanIntensity, meanConnectivity);

        for(const auto& n : net.getNeurons())
            N += n.getConnections().size();
    }
    EXPECT_NEAR(N/(10000*100), 100, 1);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
