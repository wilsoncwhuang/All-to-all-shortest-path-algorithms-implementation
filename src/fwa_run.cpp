#include<iostream>
#include<fstream>
#include<climits>
#include<iomanip>
#include "IO_fwa.h"
#include "check_time.c"
using namespace std;

int main(int argc, char* argv[]){
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

   set_ds(C,&file);

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
            for(int i=0;i<node_num;i++){
                for(int j=0;j<node_num;j++){
                    if(D[i][k]!=INT_MAX&&D[k][j]!=INT_MAX&&i!=k&&j!=k&&i!=j){
                        comparison=comparison+1;
                        if(D[i][j]>D[i][k]+D[k][j]){
                            D[i][j]=D[i][k]+D[k][j];
                            PRED[i][j]=PRED[k][j];
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
}
