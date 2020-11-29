# Neuron Network


#Project in Informatics

##README

###group 12 (Bardel Lola,De Trogroff Coatallio Constance, Preda Alexandra,Rossignol Clara)

*************************************************

##Description of the project

This is an implementation of the model of E.M. Izhikevich
([Simple Model of Spiking Neuron, IEE Trans. Neural Net., 2003] (https://www.izhikevich.org/publications/spikes.pdf)).


*************************************************

##Commands

In order to open the project, the user can clone the repository using this command:
git clone https://gitlab.epfl.ch/sv_cpp_projects/team_12.git

After building, running and compiling the program. the user can type into the terminal the following command:

./NeuronNetwork -T 'FS:0.2,IB:0.15,CH:0.15,RS:0.5' -t 1000 -N 10000 -c 40 -L 4

,where t is the number of time-steps, N is the number of neurons, T the proportions of each type of neurons as a list.
(If total is less than 1, it will be completed with RS neurons),
 c is the average connectivity of a neuron, L si the average connections' intensity and i the proportion of inhibitor neurons

Note that the parameters c, L and i are optional, as they where defalut parameters in our program.

*************************************************

##Output

After writing the command in the terminal, the program will generat 3 output files.
Here is a short version of how the files should look like:

params:

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

spikes:
0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 
1 0 1 0 0 0 0 0 0 0 0 
2 1 1 0 0 0 0 0 0 0 0 
3 1 1 0 0 1 0 0 0 0 0 
4

samples://add later


*************************************************

##Extensions

*************************************************
##Final note:
In order to see an explicit description of every class, method and attribute, the user can type make doc in the terminal.
This will create a doc file based on the comments of every class. The user can then open the doc file-> html-> annoted.html.
This will open a web page that contains a detailed explanation of each class.


