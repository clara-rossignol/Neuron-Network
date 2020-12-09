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
        n1.setFiring(true);
        Neuron n2("RS");
        n2.setFiring(true);
        n.setConnections({}, {{&n1,10}, {&n2, 10}});
        meanCurrent += n.currentCalculation();
    }
    meanCurrent /= 100;
	EXPECT_NEAR(meanCurrent, 10, 0.5);
}

/*
TEST(Simulation, readTypesProportions)
{  
    std::string types1 = "RS:0.3,FS:0.2,CH:0.1,IB:0.1,LTS:0.1,TC:0.1,RZ:0.1";
    TypesProportions  prop1 (Simulation::readTypesProportions(types1, false, 0.2));
    TypesProportions  test  {{"RS",0.3}, {"IB",0.1}, {"CH",0.1}, {"FS",0.2}, {"LTS", 0.1}, {"TC", 0.1}, {"RZ", 0.1}};
    for(const auto& type : prop1)
    {
        EXPECT_EQ(type.second, test.at(type.first));
    }
    std::string types2 = "CH:0.1,IB:0.1,LTS:0.1,TC:0.1,RZ:0.1";
    TypesProportions  prop2 (Simulation::readTypesProportions(types2, true, 0.3));
    for(const auto& type : prop2)
    {
        EXPECT_NEAR(type.second, test.at(type.first), 0.0000000001);
    }
    
}

TEST(Simulation, checkTypes)
{
    std::string types3 = "RS:1.5,FS:0.2,CH:0.1,IB:0.1,LTS:0.1";
    EXPECT_ANY_THROW(Simulation::readTypesProportions(types3, false, 0.3));
    std::string types1 = "RS:0.5,FS:0.2,CH:0.1,IB:0.1,LTS:0.1";
    EXPECT_ANY_THROW(Simulation::readTypesProportions(types1, true, 0.1));
}
*/
/*
TEST(Network, simpleConstructor)
{
    Neuron n1("FS");
    Neuron n2("RS");
    Neuron n3("CH");
    Neuron n4("IB");
    Neuron n5("LTS");
    std::vector<Neuron> neurons {n1, n2, n3, n4, n5};
    Network net (neurons);

    EXPECT_EQ(net.getNeurons().size(), 5);
    // Besoin de tester proportions avec constructeur simple ?
    // EXPECT_EQ(network.getNeurons().)
}

TEST (Network, proportionConstructor)
{
    Neuron n1("FS"), n2("RS"), n3("CH"), n4("IB"), n5("LTS");
    std::vector<Neuron> neurons {n1, n2, n3, n4, n5};
    Network net_check (neurons);

    std::size_t net_size (5);
    std::string type1 = "FS:0.2,RS:0.2,CH:0.2,IB:0.2,LTS:0.2";
    Network net (net_size, Simulation::readTypesProportions(type1, true, 1));

    EXPECT_NEAR(net, net_check);
    EXPECT_EQ(net.getNeurons().size(), net_size);
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
