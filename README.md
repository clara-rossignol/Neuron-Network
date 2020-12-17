# Neuron Network

## README

### group 12 (Bardel Lola Maia Lou, De Trogroff Coatallio Constance Laure Marie Géraldine Gabrielle, Preda Alexandra-Elena, Rossignol Clara)

*************************************************

## Description of the project

This is an implementation of the model of E.M. Izhikevich
([Simple Model of Spiking Neuron, IEE Trans. Neural Net., 2003] (https://www.izhikevich.org/publications/spikes.pdf)).
The model reproduces spiking and burting behaviour of known types of cortical neurons.
This project will simulate a neuron network.


*************************************************

## Commands

In order to open the project, the user can clone the repository using this command:
git clone https://gitlab.epfl.ch/sv_cpp_projects/team_12.git

To execute the program, the user has to write the following commands in the terminal:
```
cd team_12
mkdir build
cd build
cmake ..
make
```
After building, running and compiling the program, the user can type into the terminal a command like this typical example :
```
./NeuronNetwork -B -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -i 0.2 -t 1000 -N 10000 -c 40 -L 4 -l 2
```

where **t** is the number of time-steps, **N** is the number of neurons, **T** the proportions of each type of neurons as a list
and **i** the proportion of inhibitory neurons. **c** is the average connectivity of a neuron, **L** is the average connections' intensity
and **C**, **O**, **B** represent the types of network the user can choose from, constant, overdispersed and basic, respectively.

Note that the parameters c, L and i are optional, as they are default parameters in our program. The default parameter for c is 1, for L it
is 4.
i is also an optional parameter but if its value is not precised in the command line, the program will run without using any value for i

Concerning the list of proportions, the user can add proportions for all existing types. If he doesn't specify the RS proportion,
the program will add RS neurons in order  to reach a total proportion of 1. In the same way, if the user doesn't specify the FS proportion
but did specify the total inhibitor's proportions, the program will add FS neurons in order to reach the total inhibitor's proportions.

In this manner, for a standard mode, the user can launch the program with only FS and RS types in four ways :
```
./NeuronNetwork -B -t 500 -N 1000 -T "RS:0.7,FS:0.3"
```
or
```
./NeuronNetwork -B -t 500 -N 1000  -i 0.3 -T "RS:0.7"
```
or
```
./NeuronNetwork -B -t 500 -N 1000 -T "FS:0.3"
```
or
```
./NeuronNetwork -B -t 500 -N 1000  -i 0.3 -T"  "  (with 2 spaces in the string)
```
For a more complex network, the user can also launch the program with all types of neurons in four ways, but we only specify two as it would be redundant otherwise :
```
./NeuronNetwork  -B -t 500 -N 1000 -T "IB:0.2,FS:0.3,CH:0.1,LTS:0.1,RZ:0.1,RS:0.2"
```
or
```
./NeuronNetwork  -B -t 500 -N 100 -i 0.4 -T "IB:0.2,CH:0.1,LTS:0.1,RZ:0.1"
```


*************************************************

## Output

After writing the command in the terminal, the program will generate 3 output files.
Here is a short version of how the files should look like:

params:
```
Type	a	b	c	d	Inhibitory	degree	valence
FS	0.059701	0.225187	-65	2	1	2	10.3899
FS	0.0823111	0.211056	-65	2	1	4	18.5921
RS	0.02	0.2	-61.6766	6.67065	0	2	-4.10385
RS	0.02	0.2	-64.3488	7.7395	0	1	-6.37576
RS	0.02	0.2	-57.517	5.00682	0	1	2.82024
RS	0.02	0.2	-64.9751	7.99004	0	3	10.5649
RS	0.02	0.2	-63.5046	7.40185	0	0	0
RS	0.02	0.2	-64.9999	7.99997	0	2	3.36898
RS	0.02	0.2	-64.8526	7.94103	0	1	-6.90183
RS	0.02	0.2	-64.1784	7.67137	0	1	5.24519
```
**degree** represents the number of connections to a neuron and **valence** represents the sum of intensities of these connections
spikes:
``` 
0 0 0 0 0 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 0 
2 1 1 0 0 0 0 0 0 0 0 
3 1 1 0 0 1 0 0 0 0 0 
4
```
sample_neurons:
```	
		FS.v	FS.u	FS.I	RS.v	RS.u	RS.I
1	-65.4034	-13.0296	4.80055	-66.401	-13	-5.35557
2	-67.1584	-13.0614	3.21998	-60.1158	-13.0028	-10.7405
3	-68.7662	-13.1072	0.360254	-59.9355	-12.993	6.00131
4	-69.5636	-13.1651	-0.325492	-61.5384	-12.9829	-7.72558
5	-70.4027	-13.2275	-1.3966	-69.6536	-12.9762	-7.89051
```
*************************************************

## Extensions

For the extensions, we chose to implement the one consisting in different types of network models.
Until now, we only used a basic model, namely the average connectivity is fixed and each neuron has n~Pois(c) connections.
There are however, two more models implemented in this program.

* The constant model: each neuron has exactly c connections.
* The overdispersed model: each neuron has n_i~Pois(c_i) connections and for each neuron there is a random c_i~Exp(1/c).
*************************************************

## Visualisation

In order to better understand the results, the user can write the following command in the terminal:
```
Rscript ../RasterPlots.R  NeuronNetwork_spikes NeuronNetwork_sample_neurons NeuronNetwork_parameters
```
This will allow the generation 3 plots.

*************************************************

## Final note
In order to see an explicit description of every class, method and attribute, the user can type make doc in the terminal.
This will create a doc file based on the comments of every class. The user can then open the doc file-> html-> annoted.html.
This will open a web page that contains a detailed explanation of each class.


