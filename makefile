all:simpleTest
simpleTest:main.cpp
	g++ main.cpp
	./a.out

test5:main.cpp
	mpic++.mpich -DUSE_MPI main.cpp
	mpirun.mpich -n 4 ./a.out 
	echo OK!

test4:main.cpp
	cat /dev/null >a
	cat /dev/null >b
	mpic++.mpich -DUSE_MPI main.cpp
	mpirun.mpich -n 4 ./a.out > a
	mpic++.mpich -DUSE_MPI -DORIGINAL main.cpp
	mpirun.mpich -n 4 ./a.out > c
	mpic++.mpich -DUSE_MPI -DTHREAD main.cpp
	mpirun.mpich -n 4 ./a.out > b
#	cat b
	diff b c
	echo ok~

test3:parallel2

test2:main.cpp
	mpic++.mpich -DUSE_MPI main.cpp
	mpirun.mpich -n 4 ./a.out | tee test.log
	vim test.log
	
serial:main.cpp
	g++ -pthread main.cpp
	./a.out


parallel:main.cpp
	mpic++.mpich -DUSE_MPI main.cpp
	./b.sh 4

parallel1:main.cpp
	mpic++.mpich -DUSE_MPI main.cpp
	mpirun.mpich -f machinefile -n 4 ./a.out

parallel2:main.cpp
	mpic++.mpich -DUSE_MPI main.cpp
	mpirun.mpich -n 4 ./a.out

test:test.cpp
	g++ -o test test.cpp
	./test


clean:
#	rm -f ./*.txt
	rm -f ./*.figdata
	rm -f *.out

rmdata:
	rm -f ./Data*.txt
	rm -f ./Run-conf*.txt
	rm -f ./SaveResult-*.txt
	rm -f *.out
	rm -f ID.txt

doid:idtest.cpp
	g++ -o idtest idtest.cpp
	./idtest
	
	
