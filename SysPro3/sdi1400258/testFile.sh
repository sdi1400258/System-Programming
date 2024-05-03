#! /bin/bash

virusesFile=$1  
countriesFile=$2
numlines=$3
dub=$4


#Check input numbers

if [[ $numlines -lt 1 || $numlines -gt 10001 ]];
then
	echo "Wrong input, try again later"
	exit 0
fi

if [[ $dub < 0 || $dub > 1 ]];
then
	echo "Wrong input, try again later"
	exit 0
fi

#Read virus File & country file


while read line;
do
	echo -n
done < virusesFile 

while read line;
do
	echo -n
done < countriesFile

echo "YES" > yesno
echo "NO" >> yesno

#Input File

echo -n > inputFile
	
id=$(( RANDOM % 9999 + 1 ))
declare -a array[0]=$id

for (( a = 1; a <= $numlines; a++ )) 
do

	#ID
	
	
	id=$(( RANDOM % 9999 + 1 ))

	flag=0

	if [[ " ${array[@]} " =~ " ${id} " ]]; 
	then
  		while :
  		do
  			id=$(( RANDOM % 9999 + 1 ))
   			if [[ " ${array[@]} " != " ${id} " ]];
   			then
   				echo -n "$id" >> inputFile
   				flag=1
   				break
   			fi

   		done
	fi
	if [[ "$flag" == 0 ]];
	then
		echo -n "$id" >> inputFile
	fi

	declare -a array[a]=$id


	#First name

	letters='abcdefghijklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVYXWZ' 
	count_letters=${#letters}
	(( length = RANDOM % 10 + 3 ))
	firstname=""
	for k in $(seq 1 $length) ; do
	    firstname+=${letters:RANDOM % count_letters:1}
	done
	echo -n " " >> inputFile
	echo -n "$firstname" >> inputFile

	#Last name

	letters='abcdefghijklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVYXWZ' 
	count_letters=${#letters}
	(( length = RANDOM % 10 + 3 ))
	lastname=""
	for x in $(seq 1 $length) ; do
	    lastname+=${letters:RANDOM % count_letters:1}
	done
	echo -n " " >> inputFile
	echo -n "$lastname" >> inputFile

	#Country

	echo -n " " >> inputFile
	shuf -n 1 countriesFile -r | xargs -i echo -n "{}" > country
	cat country >> inputFile


	#Age

	age=""
	echo -n " " >> inputFile
	age=$(( $RANDOM % 120 + 1))
	echo -n "$age" >> inputFile

	#Virus

	echo -n " " >> inputFile
	shuf -n 1 virusesFile | xargs -i echo -n "{}" >> inputFile

	#Yes/No

	echo -n " " >> inputFile
	shuf -n 1 yesno -r > yn
	cat yn | tr '\n' ' ' >> inputFile
	ynyn=$(head -n 1 yn)


	randomno=$(( RANDOM % 10 + 1 ))


	if [[ $ynyn == "YES" ]];
	then
		#Date

		day=$(( $RANDOM % 30 + 1 ))
		if [[ $day -lt 10 ]];
		then 
			echo -n "0$day-" >> inputFile
		else
			echo -n "$day-" >> inputFile
		fi
		month=$(( $RANDOM % 12 + 1 ))
		if [[ $month -lt 10 ]];
		then 
			echo -n "0$month-" >> inputFile
		else
			echo -n "$month-" >> inputFile
		fi
		year=$(( $RANDOM % 80 + 1950 ))
		echo -n "$year" >> inputFile
		printf "\n" >> inputFile
	elif [[ $ynyn == "NO" ]];
	then
		if [[ $randomno == 2  ]];
		then
			day=$(( $RANDOM % 30 + 1 ))
			if [[ $day -lt 10 ]];
			then 
				echo -n "0$day-" >> inputFile
			else
				echo -n "$day-" >> inputFile
			fi
			month=$(( $RANDOM % 12 + 1 ))
			if [[ $month -lt 10 ]];
			then 
				echo -n "0$month-" >> inputFile
			else
				echo -n "$month-" >> inputFile
			fi
			year=$(( $RANDOM % 80 + 1950 ))
			echo -n "$year" >> inputFile
			printf "\n" >> inputFile
		else
			printf "\n" >> inputFile
		fi
	fi


	#Dublicates Allowed

	if [[ $dub == 1 ]];
	then
		r=1
		p=$(( $RANDOM % 4 + 0 ))
		while [ $r -le $p ]
		do
			echo -n "$id" >> inputFile
			echo -n " " >> inputFile
			echo -n "$firstname" >> inputFile
			echo -n " " >> inputFile
			echo -n "$lastname" >> inputFile
			echo -n " " >> inputFile
			cat country >> inputFile
			echo -n " " >> inputFile
			echo -n "$age" >> inputFile
			echo -n " " >> inputFile
			shuf -n 1 virusesFile -r | xargs -i echo -n "{}" >> inputFile
			echo -n " " >> inputFile
			shuf -n 1 yesno -r > yn
			cat yn | tr '\n' ' ' >> inputFile
			ynyn=$(head -n 1 yn)
			if [[ $ynyn == "YES" ]];
			then
				day=$(( $RANDOM % 30 + 1 ))
				if [[ $day -lt 10 ]];
				then 
					echo -n "0$day-" >> inputFile
				else
					echo -n "$day-" >> inputFile
				fi
				month=$(( $RANDOM % 12 + 1 ))
				if [[ $month -lt 10 ]];
				then 
					echo -n "0$month-" >> inputFile
				else
					echo -n "$month-" >> inputFile
				fi
				year=$(( $RANDOM % 80 + 1950 ))
				echo -n "$year" >> inputFile
				printf "\n" >> inputFile
			elif [[ $ynyn == "NO" ]];
			then
				if [[ $randomno == 2  ]];
				then
				day=$(( $RANDOM % 30 + 1 ))
				if [[ $day -lt 10 ]];
				then 
					echo -n "0$day-" >> inputFile
				else
					echo -n "$day-" >> inputFile
				fi
				month=$(( $RANDOM % 12 + 1 ))
				if [[ $month -lt 10 ]];
				then 
					echo -n "0$month-" >> inputFile
				else
					echo -n "$month-" >> inputFile
				fi
				year=$(( $RANDOM % 80 + 1950 ))
				echo -n "$year" >> inputFile
				printf "\n" >> inputFile
				else
					printf "\n" >> inputFile
				fi
			fi
			r=$(( $r + 1 ))
			a=$(( $a + 1))
			if [ $a -eq $numlines ]
			then
				exit 0
			fi

		done
	fi

done

 

exit 0
