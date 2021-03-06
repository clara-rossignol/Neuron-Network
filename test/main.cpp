//tests
//this will be the main that will unite all the tests

#include <gtest/gtest.h>
#include "../src/Neuron.h"
#include "../src/Random.h"
#include "../src/Network.h"
#include "../src/ConstNetwork.h"
#include "../src/DispNetwork.h"
#include "../src/Simulation.h"

RandomNumbers *_RNG = new RandomNumbers(23948710923);

TEST(Simulation, readTypesProportions)
{
    Simulation sim;

    std::string types1 = "RS:0.3,FS:0.2,CH:0.1,IB:0.1,LTS:0.1,TC:0.1,RZ:0.1";
    sim.readTypesProportions(types1, false, 0.2);
    TypesProportions  test  {{"RS",0.3}, {"IB",0.1}, {"CH",0.1}, {"FS",0.2}, {"LTS", 0.1}, {"TC", 0.1}, {"RZ", 0.1}};
    for(const auto& type : sim.getProp())
    {
        EXPECT_EQ(type.second, test.at(type.first));
    }
    std::string types2 = "CH:0.1,IB:0.1,LTS:0.1,TC:0.1,RZ:0.1";
    sim.readTypesProportions(types2, true, 0.3);
    for(const auto& type : sim.getProp())
    {
        EXPECT_NEAR(type.second, test.at(type.first), 0.0000000001);
    }

}

TEST(Simulation, checkMatchingProportions)
{
    Simulation sim;

    std::string types3 = "RS:1.5,FS:0.2,CH:0.1,IB:0.1,LTS:0.1";
    EXPECT_ANY_THROW(sim.readTypesProportions(types3, false, 0.3));
    std::string types1 = "RS:0.5,FS:0.2,CH:0.1,IB:0.1,LTS:0.1";
    EXPECT_ANY_THROW(sim.readTypesProportions(types1, true, 0.1));
}


TEST(Simulation, checkInBound)
{
    Simulation sim;
    EXPECT_ANY_THROW(sim.checkInBound("test", -4, 5, 10));
}

TEST(Neuron, neuronTypes) {
    Neuron n1("RS");
    EXPECT_TRUE("RS" == n1.getType());
    EXPECT_FALSE(n1.isGoingToFire());
    EXPECT_FALSE(n1.isFiring());
    EXPECT_EQ(n1.getCurrent(), 0);
    EXPECT_EQ(n1.getNInhibitory(), 0);
    EXPECT_FALSE(n1.isInhibitor());

    Neuron n2("FS");
    EXPECT_TRUE("FS" == n2.getType());
    EXPECT_TRUE(n2.isInhibitor());

    Neuron n3("IB");
    EXPECT_TRUE("IB" == n3.getType());
    EXPECT_FALSE(n3.isInhibitor());
    Neuron n4("CH");
    EXPECT_TRUE("CH" == n4.getType());
    EXPECT_FALSE(n4.isInhibitor());

    Neuron n5("LTS");
    EXPECT_TRUE("LTS" == n5.getType());
    EXPECT_TRUE(n5.isInhibitor());

    Neuron n6("TC");
    EXPECT_TRUE("TC" == n6.getType());
    EXPECT_FALSE(n6.isInhibitor());

    Neuron n7("RZ");
    EXPECT_TRUE("RZ" == n7.getType());
    EXPECT_FALSE(n7.isInhibitor());
}

TEST(Neuron, update)
{
    Neuron n1("RS");
    n1.update(_AVG_THAL_);
    EXPECT_EQ(n1.getRecoveryVariable(), -13);
    Neuron n2("FS", true);
    n2.update(_AVG_THAL_);
    EXPECT_EQ(n2.getMembranePotential(), -65);
}

TEST(Neuron, currentCalculation)
{
    double meanCurrent(0);
    for(size_t i(0); i<100; ++i)
    {
        Neuron n("FS");
        Neuron n1("RS");
        n1.setFiring(true);
        Neuron n2("RS");
        n2.setFiring(true);
        n.setConnections({}, {{&n1,10}, {&n2, 10}});
        n.currentCalculation(_AVG_THAL_);
        meanCurrent += n.getCurrent();
    }
    meanCurrent /= 100;
	EXPECT_NEAR(meanCurrent, 10, 0.5);
}

TEST(Neuron, setConnections)
{
    Neuron n("RS");
    std::vector<Connection> inhib= {{new Neuron("FS"), 0},
                                    {new Neuron("FS"), 0}} ;
    std::vector<Connection> excit ({{new Neuron("RS"), 0},
                                    {new Neuron("RS"), 0}});
    n.setConnections(inhib, excit);
    EXPECT_EQ(n.getNInhibitory(), 2);
    EXPECT_EQ(n.getConnections().size(), 4);
}

TEST (Network, proportionConstructor)
{
    std::size_t size_net (5);
    TypesProportions proportion ({{"FS",0.2},{"RS",0.2},{"CH",0.2},{"IB",0.2},{"LTS",0.2}});
    Network net1 (size_net, proportion);

    EXPECT_EQ(net1.getNeurons()[0].getType(), "CH");
    EXPECT_EQ(net1.getNeurons()[1].getType(), "FS");
    EXPECT_EQ(net1.getNeurons()[2].getType(), "IB");
    EXPECT_EQ(net1.getNeurons()[3].getType(), "LTS");
    EXPECT_EQ(net1.getNeurons()[4].getType(), "RS");
}

TEST (Network, indexes) 
{
	size_t size(20);
	TypesProportions prop({{"CH",0.2},{"FS",0.4},{"LTS",0.1},{"RS",0.3}});
	Network net(size, prop);
	EXPECT_EQ(net.getIndexes()[0],4);
	EXPECT_EQ(net.getIndexes()[1],12);
	EXPECT_EQ(net.getIndexes()[2],14);
	EXPECT_EQ(net.getIndexes()[3],20);
}

TEST(Network, setConnections)
{
    double meanIntensity(100);
    double meanConnectivity(100);

    double average(0);
    size_t N(0);
    size_t size (5000);

    for (size_t i(0); i<100; ++i)
    {
        Network net(size, {{"RS",1}});
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

    EXPECT_NEAR(meanIntensity, average, 0.03);
    EXPECT_NEAR(N/(size*100), meanConnectivity, 1);
}

TEST(ConstNetwork, setConnections)
{
    double meanIntensity(100);
    double meanConnectivity(100);
    ConstNetwork net(3, {{"RS",1}});
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

    size_t N(0);
    size_t size (5000);

    for (size_t i(0); i<100; ++i)
    {
        DispNetwork net (size, {{"RS",1}});
        net.setConnections(meanIntensity, meanConnectivity);

        for(const auto& n : net.getNeurons())
            N += n.getConnections().size();
    }
    EXPECT_NEAR(N/(size*100), meanConnectivity, 1);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
