/*
  This code can be compiled and run ok.

   use Dijkstra's Dial implementation to output a shortest path with its length from s to all the other nodes.

  input file:
    test1.sp

  compile:
    gcc -o spdial1 spdial1.cpp

  pseudocode:

    ----------------------------------------------------------------
    int main()
        create dial array
        initialization
        while H!=0
           find min in dial array
            scan all arc with tail i
                if d(j)>d(i)+Cij
                    if distance(j)=infinite
                        create value in dial array
                    else
                        change node j position in dial array
                    d(j)=d(i)+Cij
                end
            end
        end
        print result by pred

  coded by Cheng-Wei Huang, ID:H34076039, email: wilson10400235@gmail.com
  date: 2021.05.13
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<climits>
#include<time.h>
#include<iomanip>
#include "type_dikd.h"
#include "IO_dikd.h"
#include "check_time.c"

using namespace std;

int main(int argc, char* argv[]){
    float t1,t2;
    string filename;
    filename=argv[1];

    fstream file;
    file.open(filename, ios::in);
    if(!file.is_open()){
        cout<<"Please input correct file!"<<endl;
        return 0;
    }

    int source_node;
    int node_num;
    int arc_num;
    double max_cost=-1;
    long long int comparison=0;
    int n_loop=stoi(argv[2]);
    int seed=stoi(argv[3]);
    int cost_type=stoi(argv[4]);
    Arc** last;

    set_n_m(&node_num,&arc_num,&file);
    LinkedList* linkedlist=new LinkedList[node_num];
    set_ds(linkedlist, &file,&max_cost,&last);
    //cout<<"n:"<<node_num<<" m:"<<arc_num<<endl;
    //print_network(linkedlist,node_num);

    int dial_index=1+(node_num-1)*(max_cost/1000);
    //cout<<max_cost<<endl;
    //cout<<dial_index<<endl;
    vector<int>* dial=new vector<int>[dial_index];
    int* pred=new int[node_num];
    double* distance=new double[node_num];


    t1=mytimer();
    for(int r=0;r<n_loop;r++){
        for(int k=0;k<node_num;k++){
            source_node=k+1;
            //cout<<source_node<<endl;
            for(int i=0;i<node_num;i++){
                distance[i]=INT_MAX;
                pred[i]=-1;
            }


            vector<int> S;
            distance[source_node-1]=0;
            pred[source_node-1]=0;
            dial[0].push_back(source_node);
            int flag=0;
            /*
            for(int i=0;i<dial_index;i++){
                cout<<"bucket"<<i+1<<":";
                for(int j=0;j<dial[i].size();j++){
                    cout<<dial[i][j]<<" ";
                }
            cout<<endl;
            }
            */
            //begin
            while(S.size()!=node_num){
                int check_end=0;//check when the source node can't go through every node therefore can't jump out the first while loop
                while(dial[flag].size()==0){
                    flag++;
                    check_end++;
                    if(check_end>max_cost/1000)break;
                }
                if(check_end>max_cost/1000)break;

                int min_node;
                int minimum=INT_MAX;
                int min_index;
                for(int i=0;i<dial[flag].size();i++){
                    if(distance[dial[flag][i]-1]<minimum){
                        minimum=distance[dial[flag][i]-1];
                        min_node=dial[flag][i];
                        min_index=i;
                    }
                }
                S.push_back(min_node);
                dial[flag].erase(dial[flag].begin()+min_index);
                Arc* current=linkedlist[min_node-1].first;
                //cout<<"min:"<<min_node<<" min_d:"<<minimum<<endl;

                while(current!=0){
                    int head=current->head;
                     //cout<<"j:"<<head<<endl;
                    double original_distance=distance[head-1];
                    double new_distance=distance[min_node-1]+current->cost;
                    int original_index=original_distance/1000;
                    int new_index=new_distance/1000;
                    //cout<<"o_d:"<<original_distance<<" n_d:"<<new_distance<<endl;
                    //cout<<"o_i:"<<original_index<<" n_i:"<<new_index<<endl;
                    comparison=comparison+1;
                    if(original_distance>new_distance){
                        if(original_distance!=INT_MAX){
                            int erase_target;
                            for(int i=0;i<dial[original_index].size();i++){
                                if(dial[original_index][i]==current->head){
                                    dial[original_index].erase(dial[original_index].begin()+i);
                                }
                            }
                        }

                        dial[new_index].push_back(current->head);
                        distance[current->head-1]=new_distance;
                        pred[current->head-1]=min_node;

                    }
                    current=current->next;
                }
                //cout<<endl;
            }
       }
   }

    t2=mytimer();
    cout<<seed<<"\t"<<node_num<<"\t"<<arc_num<<"\t"<<cost_type<<"\t"<<t2-t1<<"\t"<<comparison<<endl;
    delete [] distance;
    delete [] pred;
    delete [] dial;


}
