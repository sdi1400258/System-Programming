#! /bin/bash

# inputFile=$1

inputDir=$2

numFilesPerDirectory=$3

#Read Input File 

declare -a array[0]=""
declare -a carray[0]=""

echo -n > temp


#Check inputs

if [[ $numFilesPerDirectory -lt 1 ]];
then
	echo "Wrong input, try again later"
	exit 0
fi

#Read inputFile

while read line;
do
	echo -n
done < $1

i=0
while read line;
do
	echo "$line" > temp

	if  [[ " ${array[@]} " =~ " $(cut -d" " -f4 temp) " ]]
	then
		continue
	elif [[ " ${array[@]} " != " $(cut -d" " -f4 temp) " ]]
	then	
		declare -a array[i]=$(cut -d" " -f4 temp)
		i=$(($i+1))
	fi
 
done < $1

#Make Input Directory

if [ ! -d "$inputDir" ]
then
	mkdir -p "$inputDir"
else
	echo "Folder already exists"
	exit 0
fi

#Make Sub-Directories

i=$(($i-1))

for (( a = 0; a <= i; a++ ))
do

	mkdir -p "$inputDir"/"${array[a]}"
done

for (( x = 1; x <= $numFilesPerDirectory; x++ ))
do
	for (( y = 0; y<= i; y++))
	do
		touch "$inputDir"/"${array[y]}"/"${array[y]}"-"$x".txt
	done
done	

c=0
while read line;
do
	echo "$line" > temp
	for (( q = 0; q <= i; q++ ))
	do
		if [[ "${array[q]}" != " $(cut -d" " -f4 temp )" ]]
		then
			declare -a carray[c]="$(cat temp)"
			c=$(($c+1))
			break			
		fi
	done

done < $1

#Make temporary Country Files

for (( e = 0; e <= i; e++ ))
do 
	echo -n > Filecountry-"${array[e]}".txt
done


for (( z = 0; z <= c; z++ ))
do
	echo "${carray[z]}" > temp
	for (( v = 0; v <= i; v++ ))
	do
		if [[ " $(cut -d" " -f4 temp) "  == " ${array[v]} " ]]
		then
			echo "${carray[z]}" >> Filecountry-"${array[v]}".txt
			break
		fi
	done
done

#Splitting lines from country files to special files, using round robin

d=1

for (( v = 0; v <= i; v++))
do
	while read line;
	do		
		echo "$line" >> "$inputDir"/"${array[v]}"/"${array[v]}"-"$d".txt
		d=$(($d+1))
		if [[ $d -gt $numFilesPerDirectory ]]
		then
			d=1
		fi

	done <  Filecountry-"${array[v]}".txt
	rm -r Filecountry-"${array[v]}".txt
done


