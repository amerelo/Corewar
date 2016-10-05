#!/bin/sh

# Options are :
# -a to see the result on all tests and not only the ones who fail
# -e to see the error messages of our vm
# -l to see the output logs of our asm NOT IMPLEMENTED
# -v to see the file content of the files as shown with xxd
# -h to see this NOT IMPLEMENTED YET
# -w to see the winner

cat_file=FALSE;
perso_logs=FALSE;
error_logs=FALSE;
show_all=FALSE
winner_info=FALSE

while getopts ":vleaw" opt; do
	case $opt in
		v)
			#echo "-v was triggered!" >&2;
			cat_file=TRUE;
			;;
		l)
			#echo "-l was triggered!" >&2;
			perso_logs=TRUE;
			;;
		e)
			#echo "-l was triggered!" >&2;
			error_logs=TRUE;
			;;
		a)
			#echo "-l was triggered!" >&2;
			show_all=TRUE;
			;;
		w)
			#echo "-w was triggered!" >&2;
			winner_info=TRUE;
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			;;
  esac
done

# this resets the $n arg to after opt args
shift $(($OPTIND - 1))

#$1 winner
#$2 last_cycle
#$3 output_file
function find_winner ()
{
	local  __winner=$1
	local  __last_cycle=$2
	local  winner=""
	local  our_winner=""
	local  last_cycle=""

	while read winner_line
	do
		if [[ "${winner_line}" == *"Contestant"* ]]; then
			# extracting the contestant number
			winner=$(expr "$winner_line" : 'Contestant [0-9], \([^ ,]*\).*')
			our_winner=$(expr "$winner_line" : 'Contestant [0-9] \([^ ,]*\).*')
			# if [[ $our_winner != "" ]]; then
			# 	winner="$our_winner"
			# fi
			# echo "winner in find : "$winner" in file : "$3
		fi
		if [[ "${winner_line}" == *"has won,"* ]]; then
			last_cycle=$(expr "$winner_line" : '.*last was in cycle .* / \([^)]*\).*')
		elif [[ "${winner_line}" == *"now cycle"* ]]; then
			last_cycle=$(expr "$winner_line" : '.*now cycle \(.*\)')
		fi

	done < $3

	eval "$__winner="'$winner'""
    eval "$__last_cycle="'$last_cycle'""
}

# $1 result
# $2 test_content
# $3 test_champ
function test_winner ()
{
	local  __resultvar=$1
	local __test_content=$2
	local __test_champ=$3

	#file names creation
	local ok_file=$(echo "$entry" | sed "s/\.test/\.test_out_ok/");
	local our_file=$(echo "$entry" | sed "s/\.test/\.test_out_our/");

	#rm before recompiling to see if a new one appears
	$(rm $ok_file 2> /dev/null);
	$(rm $our_file 2> /dev/null);

	local ok_output=$(eval "./test_files/"$test_content $__test_champ -a -v 2  | tail -3 > $ok_file 2> /dev/null);
	local our_output=$(eval "$test_content $__test_champ -h" > $our_file 2> /dev/null);

	find_winner ok_winner ok_last_cycle "$ok_file"
	find_winner our_winner our_last_cycle "$our_file"

	# echo $ok_winner
	# echo $our_winner

	local res="";
	res="$ok_winner"
	# if [[ $ok_winner != $our_winner ]]; then
	# 	res="Contestant $ok_winner won in original, while we got Contestant $our_winner"
	# fi

	#rm to not keep garbage files
	$(rm $ok_file 2> /dev/null);
	$(rm $our_file 2> /dev/null);

    local  myresult=$res
    eval "$__resultvar="'$myresult'""
}


# for entry in ./test_files/*.test
# do
entry=$1
echo "$entry"

	#echo "$entry"
	while read line
	do
		#echo "$line"
		test_content=$(echo "$line")

		test_winner winner_result "$test_content" $2

		echo "$line $2"
		printf "\033[33m";
		echo "Winner is $winner_result"
		printf "\033[0m";

	done < $entry
# done
