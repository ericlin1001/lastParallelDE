# Adpative Parallel Differential Evolution for PEC
Well, this is a basic project plan.

## What's purpose of the paper? Why do i want to write it?
1. It features on adaptive assgining task.
2. Achieving the theoretical limit of speedup ratio.
3. On different setting cpu, we achive the best time.

## Why I need to write this paper?
Because, it's a leading action for me to publish a trans paper. 
Publishing a trans paper, means I can get the money I need, that I do sth I want to do.


## Cluster Setting&Info:  
```
All the computers:
	ComputerNo.	Note	hasChecked  
	1			MainHost   
	2~23		i3CPU	2cores,8G(No2)  
	55~58		i5CPU  
	59~95		i7CPU	4cores,4G(No59)  
	96~200		i5CPU	4cores,12G(No96)  
```

```
	i3: 40cores
	i5: 400cores
	i7: 140cores
```

```
	No.		Memory  
	96~104	16G  
	145~131	32G  
	others	unknow
```

```
	No.				InTheSameSwitch
	2~18			1
	19~23,96~108	2
	146~163			3
	128~145			4
	183~200			5
	164~182			6
	109~127			7
```

### Run one serial program on each computer:  
one core's performance: i7>i5>i3



## What's the result i want?(Vision)
* If the computers are different, my algorithm is better.
* If the computers are all the same, my algorithm is not worser.

I want prove that my version is better, over all cases.





## Experimental Setting
### In last paper
Runing in 1,2,6,26,51,101 cores i5.

### In current paper
Notice: Always land the master node in high-performance computer(i7).

1. When computers are different:

	Purpose: Keep each core processes more data, such that the differences in cpu can be realized.
```
			Exp1	Exp2
			cores	cores
	i3		2		10
	i5		2		10
	i7		2		10
	total	6		30
```

2. When computers are the same:
```
			Exp1	Exp2	Exp3	Exp4
			cores	cores	cores	cores
	i5		5		6		30		31
```

## How to do that:
Compare serial version with my version over the above 2 experimental settings.
That means, get the last version program and get its result over the settings, and implement my version and get my results. And finally, analyse two results, and get the conclusion.

### Steps
1. Get the last version program.
2. Run the program and get result.
3. Implement my version
	1. Identify some technical problems.
	2. Tackle some technical problems.
4. Run my program.
5. Analyse results.


## Next actions
Get the last version program, and get it run.

## What to do now?
9.10 Goal: Get & Run it.

