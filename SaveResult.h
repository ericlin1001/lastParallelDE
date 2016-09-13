#ifndef SAVE_RESULT_H
#define SAVE_RESULT_H
#include<fstream>
#include<iostream>
using namespace std;
class SaveResult{
//Should be run once, in master node.
	//auto id generated.
	//save the result.
	//oupput the result easy to process in excel.
	char filename[100];
	int id;
	bool isRecordMod;
	class AllType{
		enum {INT,DOUBLE,STRING,UNKNOWN};
		int type;
		union Value{int i;double d;char s[50];};
		Value value;
		public:
			AllType(){
				//Unknow(value)
				type=UNKNOWN;
			}
			AllType(int v){
				type=INT;
				value.i=v;
			}
			AllType(double v){
				type=DOUBLE;
				value.d=v;
			}
			AllType(const char* v){
				type=STRING;
				strncpy(value.s,v,50);
				value.s[49]=0;
			}
			void save(ofstream&out){
				switch(type){
					case INT:
						out<<value.i;
						break;
					case DOUBLE:
						out<<value.d;
						break;
					case STRING:
						out<<value.s;
						break;
					case UNKNOWN:
					default:
						out<<"UnknownValue";
						break;
				}
			}
	};
	vector<string>type;
	vector<AllType> vs;
	int recordID;
	void setupID(){
		id=IDHelper::newID();
	}
	int getIndex(const char *name){
		for(int i=0;i<type.size();i++){
			if(type[i].compare(name)==0){
				return i;
			}
		}
		return -1;
	}
		ofstream file;
	void addType(const char *name){
		type.push_back(name);
		vs.resize(type.size());
	}
	void outputTypeNames(){
		for(int i=0;i<type.size();i++){
			if(i!=0)file<<"\t";
			file<<type[i];
		}
		file<<endl;
	}
	public:
	const char *getFileName()const{
		return filename;
	}
	SaveResult(const char *f=0){
		setupID();
		if(f==0){
			sprintf(filename,"SaveResult-%d.txt",id);
		}else{
			sprintf(filename,"%s-%d.txt",f,id);
		}
		file.open(filename,ofstream::app|ofstream::out);
		recordID=0;
		isRecordMod=false;
	}
	//
	//
	void set(const char *name,AllType v){
		int i=getIndex(name);
		if(i==-1){
			addType(name);
			i=type.size()-1;
		}
		vs[i]=v;
		isRecordMod=true;
	}
	void next(){
		if(recordID==0){
			outputTypeNames();
		}
		for(int i=0;i<vs.size();i++){
			if(i!=0)file<<"\t";
			vs[i].save(file);
		}
		file<<endl;
		file.flush();
		//
		recordID++;
		isRecordMod=false;
	}
	//
	/*void save(){
		if(isRecordMod){
			next();
		}
		file.flush();
	}*/
	~SaveResult(){
		if(isRecordMod){
			next();
		}
		file.close();
	}
};
#else
#endif
