function generate(){
	y=0
	a=$3
	b=$4
	while [ $y -lt $1 ]
	do
		x=0
		((y++))
		while [ $x -lt $2 ]
		do
			((x++))
			echo -n $((RANDOM%(b-a+1)+a))
			if [ $x -ne $2 ]
			then
			echo -ne "\t"
			else
				echo
			fi
		done
	done
}

generate $1 $2 $3 $4
