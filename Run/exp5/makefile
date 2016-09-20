cc=mpic++.mpich2
exe=mpirun.mpich2
out=lastParallelDE-linjunhao

all:run

run:./$(out)
	$(exe) -f machinefile -n 6 ./$(out) |tee log.txt
	echo OK!

genMachinefile:exp.setting
	cp exp.setting ~/linjunhao/Projects/getInfo/
	cd ~/linjunhao/Projects/getInfo/ && ./genMachinefile.sh exp.setting  
	cp ~/linjunhao/Projects/getInfo/exp.setting.machinefile machinefile
	cat machinefile


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
	rm -f log.txt

	
	
	
