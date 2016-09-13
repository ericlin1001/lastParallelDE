#include "include/MPIHelper.h"
#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
	MPIHelper *mpi=new MPIHelper(argc,argv);
	int configID;//Should be run once, in master node.

	cout<<"I'm id:"<<mpi->getID()<<endl;
	if(mpi->isMaster()){
		int tmp=0;
		for(int i=0;i<mpi->getNumProcesses()-1;i++){

			mpi->recv(tmp,MPI_ANY_SOURCE);
			cout<<"recv :"<<tmp<<endl;
		}
	}else{
		mpi->send(mpi->getID()+10,0);
	}

	delete mpi;

	return 0;
}
