#ifndef IO_FWA_H
#define IO_FWA_H
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

//transfer input network file into adjacency matrix data structure
void set_ds(double** C,fstream* file){
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
                    C[tail-1][head-1]=cost;
                }
            }
        }
        k=k+1;
    }
}

//trace predecessor to output shortest path
void trace(int** PRED,int i,int j){
    int k=j;
    cout<<k<<" ";
    while(PRED[i-1][k-1]!=i){
        k=PRED[i-1][k-1];
        cout<<k<<" ";
    }
    cout<<i;
}

#endif
