#include<iostream>
#include<fstream>
using namespace std;

int main(){
    int n_loop;
    cout<<"Input n_loop:";
    cin>>n_loop;

    fstream file;
    file.open("execute",ios::out);
     if(!file){
        cerr << "Can't open file!\n";
        exit(1);
    }

    int* n=new int[6];
    int* seed=new int[3];
    int* c_max=new int[3];
    int* c_min=new int[3];
	int* cost_type=new int[3];
	cost_type[0]=1;
	cost_type[1]=2;
	cost_type[2]=3;

    n[0] =100;
    n[1]=400;
    n[2]=800;
    n[3]=1600;
    n[4]=3200;
    n[5]=6400;

    seed[0]=1;
    seed[1]=10;
    seed[2]=100;

    c_max[0]=1000;
    c_max[1]=10000;
    c_max[2]=1000000;

    c_min[0]=1;
    c_min[1]=1000;
    c_min[2]=1;


    for(int i=0;i<6;i++){
        int* m=new int[3];
        m[0]=n[i]*4;
        m[1]=n[i]*16;
        m[2]=n[i]*(n[i]-1)/4;
        for(int j=0;j<3;j++){
            for(int s=0;s<3;s++){
                for(int c=0;c<3;c++){
                    file<<"./bin/sprand "<<n[i]<<" "<<m[j]<<" "<<seed[s]<<"  -ll"<<c_max[c]<<" -lm"<<c_min[c];
                    file<<" > "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp\n";
                    file<<"./bin/dikh_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >>"<<"./results/mydikh.txt\n";
                    if(c==2){
                        file<<"./bin/dikdl_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >> "<<"./results/mydikd.txt\n";
                    }
                    else{
                        file<<"./bin/dikds_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >> "<<"./results/mydikd.txt\n";
                    }
                    file<<"./bin/bf_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >> "<<"./results/mybf.txt\n";
                    file<<"./bin/pape_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >> "<<"./results/mypape.txt\n";
                    file<<"./bin/fwa_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >> "<<"./results/myfwa.txt\n";
                    file<<"./bin/fwg_run "<<"./inputs/sprand_"<<n[i]<<"_"<<m[j]<<"_"<<seed[s]<<"_"<<c_max[c]<<"_"<<c_min[c]<<".sp "<<n_loop<<" "<<seed[s]<<" "<<cost_type[c]<<" >> "<<"./results/myfwg.txt\n\n";
                }
            }
        }
    }

}
