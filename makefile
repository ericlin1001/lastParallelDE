cc=mpic++.mpich2
exe=mpirun.mpich2
out=lastParallelDE-linjunhao

all:build
#all:simpleTest

build:main.cpp
	$(cc) -o $(out) -DUSE_MPI main.cpp

simpleTest:main.cpp
	g++ main.cpp
	make rmdata
	./a.out
	cat SaveResult-0.txt

test5:main.cpp
	$(cc) -o $(out) -DUSE_MPI main.cpp
	$(exe) -f machinefile -n 4 ./$(out)
	echo OK!

parallel1:main.cpp
	$(cc) -DUSE_MPI main.cpp
	$(exe) -f machinefile -n 4 ./a.out


clean:rmdata

rmdata:
	rm -f ./Data*.txt
	rm -f ./Run-conf*.txt
	rm -f ./SaveResult-*.txt
	rm -f ./Result.txt
	rm -f ./Result-*.txt
	rm -f ./Result_*.txt
	rm -f ./DefaultResult.txt
	rm -f ID.txt

txt:
	ls|grep .txt

	
	
