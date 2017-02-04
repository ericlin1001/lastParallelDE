# Get the last program's Result
	This project is to get last program's  result on the current experimental settings.

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




## Experimental Setting

1. When computers are different:

	Purpose: Keep each core processes more data, such that the differences in cpu can be realized.

~~~~
			Exp5	Exp6
			cores	cores
	i3		2		10
	i5		2		10
	i7		2		10
	total	6		30
	computer1,1,1	5,3,3

	i3 no:17~19 22~23
	i5 no:
~~~~

2. When computers are the same:

```
			Exp1	Exp2	Exp3	Exp4
			cores	cores	cores	cores
	i5		5		6		30		31
	computer2		2		8		8
	no. 70~78
```

## What's next?
1. Generate a machine file.
	1. Exp1(5 cores)

	```
	chen-510130:4
	chen-510131:1
	```

	2. Exp2(6 cores)
	
	```
	chen-510130:4
	chen-510131:2
	```

	3. Exp3(30 cores)

	```
	chen-510130:4
	chen-510131:2
	```

	3. Exp4(31 cores)

2. Using a script to run all Exps.


