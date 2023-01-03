#include<iostream>
#include<fstream>
#include<vector>
#include<climits>
#include<deque>
#include<iomanip>
#include "type_pape.h"
#include "IO_pape.h"
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
    long long int comparison=0;
    int n_loop=stoi(argv[2]);
    int seed=stoi(argv[3]);
    int cost_type=stoi(argv[4]);
    Arc** last;

    set_n_m(&node_num,&arc_num,&file);
    LinkedList* linkedlist=new LinkedList[node_num];
    set_ds(linkedlist, &file,&last);

    double* distance=new double[node_num];
    int* pred=new int[node_num];
    bool* check=new bool[node_num]; //whether have been scanned
    bool* flag=new bool[node_num];//whether have been push into LIST

     t1=mytimer();
    for(int r=0;r<n_loop;r++){
        for(int i=0;i<node_num;i++){
            source_node=i+1;
            deque<int> LIST;

             //initialize
            for(int i=0;i<node_num;i++){
                distance[i]=INT_MAX;
                pred[i]=-1;
                check[i]=false;
                flag[i]=false;
            }
            distance[source_node-1]=0;
            pred[source_node-1]=0;
            LIST.push_back(source_node);

            //begin
            while(!LIST.empty()){
                int tail=LIST.front();
                LIST.pop_front();
                Arc* current=linkedlist[tail-1].first;
                while(current!=0){
                    int j=current->head;
                    double original_distance=distance[j-1];
                    double new_distance=distance[tail-1]+current->cost;

                    comparison=comparison+1;
                    if(original_distance>new_distance){
                        distance[j-1]=new_distance;
                        pred[j-1]=tail;
                        if(check[j-1]==false){
                            check[j-1]=true;
                            if(flag[j-1]==false){
                                LIST.push_back(j);
                                flag[j-1]=true;
                            }
                        }
                        else{
                            if(flag[j-1]==false){
                                LIST.push_front(j);
                                flag[j-1]=true;
                            }
                        }
                    }
                    current=current->next;

                }
            }
        }
    }

    t2=mytimer();
    cout<<seed<<"\t"<<node_num<<"\t"<<arc_num<<"\t"<<cost_type<<"\t"<<t2-t1<<"\t"<<comparison<<endl;
    delete [] distance;
    delete [] pred;
    delete [] flag;
    delete [] check;

}
