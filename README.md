# Neuron Network


# Project in Informatics

## README

### group 12 (Bardel Lola Maia Lou,De Trogroff Coatallio Constance Laure Marie Géraldine Gabrielle, Preda Alexandra-Elena,Rossignol Clara)

*************************************************

## Description of the project

This is an implementation of the model of E.M. Izhikevich
([Simple Model of Spiking Neuron, IEE Trans. Neural Net., 2003] (https://www.izhikevich.org/publications/spikes.pdf)).
It will simulate a neuron network.


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
./NeuronNetwork -t 500 -N 10000 -T "FS:0.2,RS:0.8" -c 20
```
For a more complex network,containing also the other types of neurons (IB,CH,LTS) write the following command:
```
./NeuronNetwork -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -t 1000 -N 10000 -c 40 -L 4
```
,where t is the number of time-steps, N is the number of neurons, T the proportions of each type of neurons as a list.
(If total is less than 1, it will be completed with RS neurons),
 c is the average connectivity of a neuron, L si the average connections' intensity and i the proportion of inhibitor neurons

Note that the parameters c, L and i are optional, as they where defalut parameters in our program.

*************************************************

## Output

After writing the command in the terminal, the program will generat 3 output files.
Here is a short version of how the files should look like:

params:
```
Type	a	b	c	d	Inhibitory
CH	0.02	0.2	-50	2	0
CH	0.02	0.2	-50	2	0
FS	0.0321029	0.242436	-65	2	1
FS	0.0698489	0.218844	-65	2	1
IB	0.02	0.2	-55	4	0
IB	0.02	0.2	-55	4	0
RS	0.02	0.2	-61.8134	6.72536	0
RS	0.02	0.2	-59.4786	5.79142	0
RS	0.02	0.2	-51.292	2.5168	0
RS	0.02	0.2	-60.826	6.33041	0
RS	0.02	0.2	-54.9659	3.98635	0
```
spikes:
```
0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 0 
2 1 1 0 0 0 0 0 0 0 0 
3 1 1 0 0 1 0 0 0 0 0 
4
```
sample_neurons:
```		v	u	I
1	-73.4745	-13	-2.92929
2	-72.0292	-13.0169	3.60879
3	-76.7062	-13.0308	8.58441
4	-75.1828	-13.0539	1.98479
5	-68.8607	-13.0738	-7.77759
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


