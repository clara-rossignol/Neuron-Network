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
After building, running and compiling the program. the user can type into the terminal the following commands, depending on the mode he wants to use:
For the standard mode (i.e. the network will only contain RS and LS neurons), the command is:
```
./NeuronNetwork -B -t 500 -N 10000 -T "FS:0.2,RS:0.8" -c 20
```
For a more complex network,containing also the other types of neurons (IB,CH,LTS) write the following command:
```
./NeuronNetwork -B -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -t 1000 -N 10000 -c 40 -L 4
```
,where **t** is the number of time-steps, **N** is the number of neurons, **T** the proportions of each type of neurons as a list.
(If total is less than 1, it will be completed with RS neurons),
 **c** is the average connectivity of a neuron, **L** is the average connections' intensity and **i** the proportion of inhibitor neurons
and **C**, **O**, **B** represent the types of network the user can choose from, constant, overdispersed and basic, respectively.

Note that the parameters c, L and i are optional, as there are default parameters in our program.

*************************************************

## Output

After writing the command in the terminal, the program will generat 3 output files.
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
Until now, we only used a basic model, namely the average connectivity is fixed and each neuron has n-Pois(c) connections.
There are however, two more models implemented in this program.

* The constant model: each neuron has exactly c connections.
* The overdispersed model: each neuron has n_i-Pois(c_i) connections and for each neuron there is a random c_i-Exp(1/c).

*************************************************

## Final note:
In order to see an explicit description of every class, method and attribute, the user can type make doc in the terminal.
This will create a doc file based on the comments of every class. The user can then open the doc file-> html-> annoted.html.
This will open a web page that contains a detailed explanation of each class.


