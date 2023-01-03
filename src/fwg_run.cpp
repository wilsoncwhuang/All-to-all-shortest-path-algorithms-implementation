#include<iostream>
#include<fstream>
#include<climits>
#include<vector>
#include<iomanip>
#include "IO_fwg.h"
#include "check_time.c"
using namespace std;

int main(int argc,char* argv[]){
    float t1,t2;
    t1=mytimer();
    long long int comparison=0;
    int node_num;
    int arc_num;
    int n_loop=stoi(argv[2]);
    int seed=stoi(argv[3]);
    int cost_type=stoi(argv[4]);
    string filename;
    filename=argv[1];

    fstream file;
    file.open(filename, ios::in);
    if(!file.is_open()){
        cout<<"Please input correct file!"<<endl;
        return 0;
    }

    set_n_m(&node_num,&arc_num,&file);


    double** C=new double*[node_num];
    double** D=new double*[node_num];
    int** PRED=new int*[node_num];
    for(int i=0;i<node_num;i++){
        C[i]=new double[node_num];
        D[i]=new double[node_num];
        PRED[i]=new int[node_num];
    }

    for(int i=0;i<node_num;i++){
        for(int j=0;j<node_num;j++){
            if(j==i){
                C[i][j]=0;
            }
            else{
                C[i][j]=INT_MAX;
            }
            D[i][j]=0;
        }
   }

    vector<int>* input=new vector<int>[node_num];
    vector<int>* output=new vector<int>[node_num];


    set_ds(C,&file,input,output);

     t1=mytimer();
    for(int r=0;r<n_loop;r++){

        //initialize
        for(int i=0;i<node_num;i++){
            for(int j=0;j<node_num;j++){
                D[i][j]=C[i][j];
                PRED[i][j]=i+1;
            }
        }

       //begin
        for(int k=0;k<node_num;k++){

            for(int i=0;i<input[k].size();i++){
                int in_index=input[k][i]-1;

                for(int j=0;j<output[k].size();j++){
                    int out_index=output[k][j]-1;
                    if(in_index==out_index||in_index==k||out_index==k){
                            continue;
                    }
                    else{
                        comparison++;
                        if(D[in_index][out_index]>D[in_index][k]+D[k][out_index]){
                            if(D[in_index][out_index]==INT_MAX){
                                output[in_index].push_back(out_index+1);
                                input[out_index].push_back(in_index+1);
                            }
                            D[in_index][out_index]=D[in_index][k]+D[k][out_index];
                            PRED[in_index][out_index]=PRED[in_index][out_index];
                        }

                    }
                }

            }

        }
    }

    t2=mytimer();
   cout<<seed<<"\t"<<node_num<<"\t"<<arc_num<<"\t"<<cost_type<<"\t"<<t2-t1<<"\t"<<comparison<<endl;
   delete [] C;
   delete [] D;
   delete [] PRED;
   delete [] input;
   delete [] output;

}








