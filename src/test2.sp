c a simple network with 6 nodes 9 arcs
c this file has the following format: (in the order)
c if a line starts by
c   c : whatever follows is comment, you may ignore
c   t : title of the problem_name, you have to read it
c   p : problem type(sp), n (# nodes), m (# arcs)
c   n : #nodes
c   a : from to length
c Thus your code has to 
c   1. ignore each comment line (starts by c)
c   2. read problem_name (e.g. test1_6_9)
c   3. read problem type, # nodes, and # arcs
c   4. read # nodes (in this case, 6)
c   5. read each arc one by one (from to arc_length)
c
t test2_8_14
p sp 	8	14
n	8
a	1	2	4.0
a	2	4	8.0
a	2	5	2.0
a	3	1	2.0
a 	3	2	7.0
a	3	5	4.0
a	4	5	3.0
a	4	7	9.0
a	5	6	9.0
a	5	8	6.0
a 	6	3	3.0
a 	6	7	8.0
a 	7	8	4.0
a 	8 	6	5.0