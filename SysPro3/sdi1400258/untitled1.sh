#! /bin/bash

echo -n > inputFile


id=$(( RANDOM % 9999 + 1 ))
declare -a array[0]=$id


for o in {1..999}
do
	id=$(( RANDOM % 9999 + 1 ))
	#declare -a array[o]=$id

	flag=0
	# echo "something"

	if [[ " ${array[@]} " =~ " ${id} " ]]; 
	then

		# echo "$id ${array[@]}"

		# for ((i=0; i<10000; i++)); do
  		while :
  		do
  			id=$(( RANDOM % 9999 + 1 ))
   			# declare -a array[o]=$id

   			if [[ " ${array[@]} " != " ${id} " ]];
   			then
   				echo "$id" >> inputFile
   				flag=1
   				# echo "$id"
   				break
   			fi

   		done

 		# declare -a array[o]=$id
  	  		
		# done
		
	fi
	if [[ "$flag" == 0 ]];
	then
		echo "$id" >> inputFile
	fi

	declare -a array[o]=$id

	# echo "$id" >> inputFile

done




# counter=0

# while :
# do
# 	id=$(( RANDOM % 9999 + 1 ))
# 	if [[ " ${array[@]} " != " ${id} " ]];
# 	then
# 		echo "$id" >> inputFile
# 	fi
# 	let counter=counter+1
# 	array[counter]="$id"
# 	if [[ $counter == 1000 ]]
# 	then
# 		break
# 	fi
# done
