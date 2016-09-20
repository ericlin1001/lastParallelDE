//Warning:: EvaluationFunction(e.g. F1~F30) must fit in concurrency-safety, i.e. DO NOT use global variables.
//Warning::if task.isFinished in master return =-1;
//Notice:: vector will reallocate space, when the capacity is not enough.

#include "include/template.h"
#include "include/BasicDE.h"
#include "include/SignalHandleHelper.h"
#include "include/IDHelper.h"
#include "pecFunction.h"
#include "include/SaveResult.h"
#include<pthread.h>
#include<algorithm>
#include<map>
#include<iostream>
#include<fstream>
#undef DEBUG
#define NOT_USED {cerr<<"Error::UNUSED."<<endl;}
//#define INFO
//#define DEBUG
//#define DEBUG1
using namespace std;
#include "ParallelDE.h"
DefFunction(TestF,-100,100,100)
	return xs[0];
EndDef

///////////////////////

EA *de=0;
void IntHandler(int s){
	if(de!=NULL){
		delete de;
		de=NULL;
	}
	cout<<"My:Caught signal SIGINT"<<endl;
	exit(1);
}
int MainProgram(MPIHelper*mpi,SaveResult&saveResult,int run,int MaxRun,int configID,EA *de,Function*f,SearchParam*param,bool isFindMin=true){
	/*************Shared Data*************/
	vector<double>x;
	double fx=-1;
	//srand(time(NULL));
	Save save;
	/**************end Shared Data***********/

	/********Master data*************/
	char state[50]="start";
	double usedTime;
	double absError;
	char saveFileName[100];
	/**********end Master data*************/

	//
#ifdef INFO 
	printf("client(%s) starts computing...\n",mpi->getName());
#endif
	if(mpi->isMaster()){
		printf("Runing %s \n",de->getName());
		printf("%cFunName(MyBestF,Optima)\n",isFindMin?'-':'+');
		//
		usedTime=-1;
		absError=-1;
		//
		sprintf(saveFileName,"Data-%d-%d.txt",configID,run);
		save.init(saveFileName);
		de->addSave(&save);
		Tic::tic("begin");
	}
	if(isFindMin){
		de->getMin(f,param->getInt("MaxFEs"),x,fx);
	}else{
		de->getMax(f,param->getInt("MaxFEs"),x,fx);
	}
	if(mpi->isMaster()){
		usedTime=Tic::tic("end");
		absError=fabs(fx-(f->getFBest()));
		strcpy(state,"end");

		//saving the result:
		saveResult.s("ID(ExecutionOfProgram)",configID).s("Run",run).s("MaxRun",MaxRun)
			.s("Function",f->getName()).s("Algorithm",de->getName()).s("ParamemterFile",param->getName())
			.s("NumOfProcesses",mpi->getNumProcesses()).s("MaxFEs",param->getInt("MaxFEs"))
			.s("PopSize",param->getInt("PopSize")).s("NumDim",param->getInt("NumDim")).s("F-parameter",param->getDouble("F"))
			.s("CR-paramter",param->getDouble("CR"))
			.s("State",state).s("DataFile",saveFileName).s("UsedTime",usedTime).s("AbsError",absError).s("X",x).s("Fx",fx);
		saveResult.next();
		//end save result.
		printf("%c%s(%g,%g)\n",isFindMin?'-':'+',f->getName(),fx,f->getFBest());
		cout<<"ends successfully!"<<endl;
		cout<<endl;
	}
	return 0;
}

int main(int argc,char *argv[]){
	//test_SaveResult();
	//return 0;
	SignalHandleHelper::registerSignalHandler(IntHandler);
	MPIHelper mpi(argc,argv);
	int configID;//Should be run once, in master node.
	SaveResult saveResult;
	if(mpi.isMaster()){
		saveResult.init("Result.txt");
		cout<<"Results are saving in file: "<<saveResult.getFileName()<<endl;
		configID=IDHelper::newID();//Should be run once, in master node.
	}else{
		configID=-1;//unused in slavery process.
	}
	//
	//Function*f=new TestF();
	//SearchParam param("TestF.json");
	Function*f=new PECFunction();
	SearchParam param("PEC.json");
	de=new ParallelDE();
	//
	de->setParam(&mpi,&param);
	f->setNumDim(param.getInt("NumDim"));
	const int MaxRun=param.getInt("MaxRun");
	int run=0;
	bool isFindMin=false;

	for(run=1;run<=MaxRun;run++){
		MainProgram(&mpi,saveResult,run,MaxRun,configID,de,f,&param,isFindMin);
	}
	if(mpi.isMaster()){
		cout<<"Results have saved in file: "<<saveResult.getFileName()<<endl;
	}
	delete de;
	delete f;
	cout<<"end of program."<<endl;
	return 0;
}
