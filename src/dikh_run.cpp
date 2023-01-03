/*
  This code can be compiled and run ok.

   use Dijkstra's binary heap implementation to output a shortest path with its length from s to all the other nodes.

  input file:
    test1.sp

  compile:
    gcc -o spheap1 spheap1.cpp

  pseudocode:
    min_heapify(A,i,n)
        left=2*i
        right=2*i+1
        if l<n and A[l]<A[i]
            lowest=l
        else
            lowest=i
        if r<n and A[r]<A[lowest]
            lowest=r
        if lowest!=i
            exchange A[i] with A[lowest]
            min_heapify(A,lowest,n)
    ----------------------------------------------------------------
    build_min_heap(A,n)
        for i=n/2 to 1
            min_heapify(A,i,n)
    -----------------------------------------------------------------
    insertion(A,node)
        A[n+1]=new node
        build_min_heap(A,A.size)
    ------------------------------------------------------------------
    delete_min(A)
        delete(A[0])
        build_min_heap(A,A.size)
    ----------------------------------------------------------------
    int main()
        create heap
        initialization
        insert(H,source)
        while H!=0
            delete_min(H)
            scan all arc with tail i
                if d(j)>d(i)+Cij
                    if distance(j)=infinite
                        insertion(H,j)
                    else
                        adjust heap
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
#include "type_dikh.h"
#include "IO_dikh.h"
#include "check_time.c"

using namespace std;

void min_heapify(vector<Node>& A,int i,int n){
	int lowest;
	int temp_label;
	double temp_dis;
	int l=2*i;
	int r=2*i+1;
	if(l<=n&&A[l-1].distance<A[i-1].distance){
		lowest=l;
	}
	else{
		lowest=i;
	}
	if(r<=n&&A[r-1].distance<A[lowest-1].distance){
		lowest=r;
	}
	if(lowest!=i){
		temp_dis=A[i-1].distance;
		temp_label=A[i-1].name;
		A[i-1].distance=A[lowest-1].distance;
        A[i-1].name=A[lowest-1].name;
		A[lowest-1].distance=temp_dis;
		A[lowest-1].name=temp_label;
		min_heapify(A,lowest,n);
	}
}

void decrease_key(vector<Node> &A,int position){
    int parent_index=position/2;
    if(A[parent_index].distance>A[position].distance){
        Node temp=A[parent_index];
        A[parent_index]=A[position];
        A[position]=temp;
        decrease_key(A,parent_index);
    }
}

void insertion(vector<Node> &A,Node node){
    A.push_back(Node(node.name,node.distance));
    decrease_key(A,A.size()-1);
}

void delete_min(vector<Node> &A){
    A.erase(A.begin());
    min_heapify(A,1,A.size()-1);
}

int main(int argc,char* argv[]){
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
    t1=mytimer();
    for(int r=0;r<n_loop;r++){
       for(int k=0;k<node_num;k++){
            source_node=k+1;
            //initialize
            vector<Node> H;

            for(int i=0;i<node_num;i++){
                distance[i]=INT_MAX;
                pred[i]=-1;
            }
            distance[source_node-1]=0;
            pred[source_node-1]=0;
            Node start=Node(source_node,0);
            insertion(H,start);

            //begin
            while(H.size()!=0){
                Node minimum=H[0];
                int tail=minimum.name;
                delete_min(H);
                Arc* current=linkedlist[tail-1].first;

                while(current!=0){
                    int head=current->head;
                    double original_distance=distance[head-1];
                    double new_distance=distance[tail-1]+current->cost;
                    comparison=comparison+1;
                    if(distance[head-1]>new_distance){
                        if(distance[head-1]==INT_MAX){
                            Node* to_insert=new Node(head,new_distance);
                            insertion(H,*to_insert);
                        }
                        else{
                                for(int i=0;i<H.size();i++){
                                    if(H[i].name==head){
                                        H[i].distance=new_distance;
                                    }
                                }
                        }
                        distance[head-1]=new_distance;
                        pred[head-1]=tail;
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

}
