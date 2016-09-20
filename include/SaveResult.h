#ifndef SAVE_RESULT_H
#define SAVE_RESULT_H
#include<fstream>
#include<iostream>
#include "IDHelper.h"
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>
#include<vector>
using namespace std;
/*Example Usage:
 *
int test_SaveResult(){
	cout<<"helo"<<endl;
	SaveResult s;
	s.set("t1",123).s("t3","wtf");
	s.set("t2",123.244232);
	s.set("t3","wtf");
	s.next();
	s.set("t1",321);
	s.set("t2",520.1314);
	s.set("t3","love little fish.");
	s.next();
	cout<<"Result saved in :"<<s.getFileName()<<endl;
	return 0;
}
*/
class SaveResult{
	class AllType{
		enum {INT,DOUBLE,STRING,ARRAY,UNKNOWN};
		int type;
		union Value{int i;double d;char s[50];};
		vector<double>a;
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
		AllType(const vector<double>& v){
			type=ARRAY;
		//	value.a=v;
			a=v;
		}
		AllType(const char* v){
			type=STRING;
			strncpy(value.s,v,50);
			value.s[49]=0;
		}
		private:
		void outDouble(ostream&out,const double d){
			char buff[32];
			sprintf(buff,"%g",d);
			out<<buff;
		}
		public:
		void save(ostream&out){
			switch(type){
				case INT:
					out<<value.i;
					break;
				case DOUBLE:
					//out<<value.d;
					outDouble(out,value.d);
					break;
				case STRING:
					out<<value.s;
					break;
				case ARRAY:
					out<<"[";
					for(int i=0;i<a.size();i++){
						if(i!=0)out<<",";
						//out<<value.a[i];
						outDouble(out,a[i]);
					}
					out<<"]";
					break;
				case UNKNOWN:
				default:
					out<<"UnknownValue";
					break;
			}
		}
	};
	//Should be run once, in master node.
	//auto id generated.
	//save the result.
	//oupput the result easy to process in excel.
	char filename[100];
	ofstream file;
	int id;
	bool isRecordMod;
	vector<string>type;
	vector<AllType> vs;
	int recordID;
	/******AllType********/

	private:
	inline bool isFileExist(const char *f){
		struct stat buff;
		return (stat (f,&buff)==0);
	}
	void getNextAvaliableFile(char *filename){
		char name[50],ext[15];
		int id=0;
		if(!isFileExist(filename))return;
		//split filename into two parts, name,ext(NOT containing a dot)
		char *dot=strrchr(filename,'.');
		if(dot==0){
			strcpy(name,filename);
			strcpy(ext,"txt");
		}else{
			*dot=0;
			strcpy(name,filename);
			strcpy(ext,dot+1);
		}
		//loop from id=0 to infinite, to find a filename that do NOT exit.
		do{
			sprintf(filename,"%s_%d.%s",name,id,ext);
			id++;
		}while(isFileExist(filename));
	}
	//
	/*
	void setupID(){
		id=IDHelper::newID("SaveResult-ID.txt");
	}
	*/
	int getIndex(const char *name){
		for(int i=0;i<type.size();i++){
			if(type[i].compare(name)==0){
				return i;
			}
		}
		return -1;
	}
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
	SaveResult& _set(const char *name,AllType v){
		if(!file.is_open()){
			file.open(filename,ofstream::app|ofstream::out);
		}
		int i=getIndex(name);
		if(i==-1){
			addType(name);
			i=type.size()-1;
		}
		vs[i]=v;
		isRecordMod=true;
		return *this;
	}
	public:
	SaveResult(const char *f=0){
		//setupID();
		if(f==0){
			strcpy(filename,"DefaultResult.txt");
		}else{
			strcpy(filename,f);
		}
		getNextAvaliableFile(filename);
		recordID=0;
		isRecordMod=false;
	}
	//
	//
	void init(const char *f=0){
		if(file.is_open())file.close();
		//
		if(f==0){
			strcpy(filename,"DefaultResult.txt");
		}else{
			strcpy(filename,f);
		}
		getNextAvaliableFile(filename);
		recordID=0;
		isRecordMod=false;
	}
	//Notice::end with ""
	inline SaveResult& s(const char *name,AllType v){
		return _set(name,v);
	}
	inline SaveResult& set(const char *name,AllType v){
		return _set(name,v);
	}
	//This method fails, as far as i know, what the variable arguments are passed are 
	//just the address. That means, the passing in arguments are NOT auto-converted to AllType.
	/*
	SaveResult& sets(const char *name,AllType value,...){
		const char *n;
		AllType v;
		//
		va_list arg;
		va_start(arg,value);
		//
		_set(name,value);
		n=va_arg(arg,const char *);
		cout<<"paring n:"<<n<<endl;
		v=va_arg(arg,AllType);
		cout<<"paring v ok:";
		v.save(cout);
		cout<<endl;
		while(true){
			cout<<"try par"<<endl;
			//Error occurs.
			n=va_arg(arg,const char *);
			cout<<"paring n:"<<n<<endl;
			if(n[0]=='e'){
				cout<<"breaking"<<endl;
				break;
			}
			//if(strcmp(n,"")==0)break;
			v=va_arg(arg,AllType);
			cout<<"paring v ok:";
			v.save(cout);
			cout<<endl;
			_set(n,v);
			cout<<"end set"<<endl;
		}
		va_end(arg);
		return *this;
	}
	*/
	public:
	void next(){
		if(!isRecordMod){
			return ;
		}
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
	const char *getFileName()const{
		return filename;
	}
	void end(){
		if(isRecordMod){
			next();
		}
		if(file.is_open()){
			file.close();
		}
	}
	~SaveResult(){
		end();
	}
};
#else
#endif
