#ifndef IO_DIKD_H
#define IO_DIKD_H
#include "type_dikd.h"
#include<fstream>
using namespace std;

//determine the number of nodes and arcs from input network file
void set_n_m(int * node_num,int* arc_num,fstream* file){
    string temp;
    string skip_line;
    while(!file->eof()){
        *file>>temp;
        if(temp!="p"){
            getline(*file,skip_line);
            continue;
        }
        else if(temp=="p"){
            for(int i=0;i<3;i++){
                *file>>temp;
                if(i==1)*node_num=stoi(temp);
                if(i==2)*arc_num=stoi(temp);
            }
            getline(*file,skip_line);
            break;
        }
    }
}

//transfer input network file into linked list data structure
void set_ds(LinkedList* linkedlist,fstream* file,double* max_cost,Arc*** last){
    string temp;
    string skip_line;
    int pivot=0;
    int tail;
    int head;
    double cost;
    int k=0;
    while(!file->eof()){
        *file>>temp;
        if(temp!="a" && pivot==0){
            getline(*file,skip_line);
        }
        else{
            for(int i=0;i<3;i++){
                *file>>temp;
                if(i==0){
                    tail=stoi(temp);
                }
                else if(i==1){
                     head=stoi(temp);
                }
                else{
                    cost=stod(temp);
                     if(cost>*max_cost)*max_cost=cost;
                    linkedlist[tail-1].Push_back(head,cost,last);
                }
            }
        }
        k=k+1;
    }
}

//trace predecessor to output shortest path
void trace(int* A,  int i, int source){
    int current=i;
    bool flag=true;
    while(current!=0){
        current=A[current-1];
        if(current==-1){
            flag=false;
            break;
        }
    }
    current=i;
    if(flag==true){
        cout<<current;
        while(current!=source){
            current=A[current-1];
            cout<<"<-"<<current;
        }
    }
    cout<<endl;
}

//output all node's shortest path
void print_result(double* distance, int* pred,int node_num,int source_node){
    for(int i=0;i<node_num;i++){
        if(i+1!=source_node){
            if(distance[i]==INT_MAX){
                 cout<<source_node<<"->"<<i+1<<":[can not reach]";
            }
            else{
                cout<<source_node<<"->"<<i+1<<":["<<distance[i]<<"]";
            }
            trace(pred,i+1,source_node);
        }
    }
}


void print_network(LinkedList* linkedlist, int node_num){
    for(int i=0;i<node_num;i++){
        linkedlist[i].PrintList();
        cout<<endl;
    }
}

#endif
