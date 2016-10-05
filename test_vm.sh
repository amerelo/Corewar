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

#$1 result
#$2 test_content
#$3 dump_cycles
function test_dump ()
{
	local  __resultvar=$1
	local __test_content=$2
	local  __dump_cycles=$3

	#file names creation
	local ok_file=$(echo "$entry" | sed "s/\.test/\.test_out_ok/");
	local our_file=$(echo "$entry" | sed "s/\.test/\.test_out_our/");

	#rm before recompiling to see if a new one appears
	$(rm $ok_file 2> /dev/null);
	$(rm $our_file 2> /dev/null);

	if [[ $error_logs == TRUE ]]; then
		local ok_output=$(eval "./test_files/"$test_content -d $__dump_cycles -a > $ok_file);
		local our_output=$(eval $test_content -dump $__dump_cycles -h -64 > $our_file);
	else
		local ok_output=$(eval "./test_files/"$test_content -d $__dump_cycles -a > $ok_file 2> /dev/null);
		local our_output=$(eval $test_content -dump $__dump_cycles -h -64 > $our_file 2> /dev/null);
	fi

	local diff_output=$(diff $ok_file $our_file);

	#rm before recompiling to see if a new one appears
	$(rm $ok_file 2> /dev/null);
	$(rm $our_file 2> /dev/null);

    local  myresult=$diff_output
    eval "$__resultvar="'$myresult'""
}

#$1 winner
#$2 last_cycle
#$3 output_file
function find_winner ()
{
	local  __winner=$1
	local  __last_cycle=$2
	local  winner=""
	local  last_cycle=""

	while read winner_line
	do
		if [[ "${winner_line}" == *"Contestant"* ]]; then
			# extracting the contestant number
			winner=$(expr "$winner_line" : '.*Contestant \([^ ,]*\).*')
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

#$1 result
#$2 test_content
function test_winner ()
{
	local  __resultvar=$1
	local __test_content=$2

	#file names creation
	local ok_file=$(echo "$entry" | sed "s/\.test/\.test_out_ok/");
	local our_file=$(echo "$entry" | sed "s/\.test/\.test_out_our/");

	#rm before recompiling to see if a new one appears
	$(rm $ok_file 2> /dev/null);
	$(rm $our_file 2> /dev/null);

	local ok_output=$(eval "./test_files/"$test_content -a -v 2  | tail -3 > $ok_file 2> /dev/null);
	local our_output=$(eval $test_content -h -64 > $our_file 2> /dev/null);

	find_winner ok_winner ok_last_cycle "$ok_file"
	find_winner our_winner our_last_cycle "$our_file"

	local res="";
	if [[ $ok_winner != $our_winner ]]; then
		res="Contestant $ok_winner won in original, while we got Contestant $our_winner"
	fi
	if [[ $ok_last_cycle != $our_last_cycle ]]; then
		res+="Got $ok_last_cycle in original, while we got $our_last_cycle"
	fi

	#rm to not keep garbage files
	$(rm $ok_file 2> /dev/null);
	$(rm $our_file 2> /dev/null);

    local  myresult=$res
    eval "$__resultvar="'$myresult'""
}


# for entry in ./test_files/*.test
# do
entry=$1
	#echo "$entry"
	while read line
	do
		#echo "$line"
		test_content=$(echo "$line")

		test_dump dump_result "$test_content" 15000
		test_winner winner_result "$test_content"

		if [[ $dump_result != "" ]]; then
			echo "$entry"
			echo "$line"
			printf "\033[33m";
			echo "$dump_result";
			printf "\033[0m";
			if [[ $cat_file == TRUE ]]; then
				cat -e $entry;
			fi
		elif [[ $winner_result != "" ]]; then
			echo "$entry"
			echo "$line"
			printf "\033[33m";
			echo "Winner difference";
			echo "$winner_result";
			printf "\033[0m";
			if [[ $cat_file == TRUE ]]; then
				cat -e $entry;
			fi
		elif [[ $show_all == TRUE ]]; then
			# echo "$entry"
			echo "$line"
			printf "\033[32m";
			echo "ok";
			printf "\033[0m";
			if [[ $cat_file == TRUE ]]; then
				cat -e $entry;
			fi
		fi
	done < $entry
# done
