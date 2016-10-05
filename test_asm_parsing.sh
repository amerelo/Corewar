#!/bin/sh

# Options are :
# -a to see the result on all tests and not only the ones who fail
# -e to see the error messages of our asm
# -l to see the output logs of our asm
# -v to see the file content of the files
# -h to see this NOT IMPLEMENTED YET

cat_file=FALSE;
perso_logs=FALSE;
error_logs=FALSE;
show_all=FALSE

while getopts ":vlea" opt; do
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
		\?)
			echo "Invalid option: -$OPTARG" >&2
			;;
  esac
done

for entry in ./test_files/*.s
do
	#echo "$entry"
	perso_valid=FALSE;
	original_valid=FALSE;
	if [[ $error_logs == FALSE ]]; then
		perso=$(./asm -e -i $entry 2> /dev/null);
	else
		perso=$(./asm -e -i $entry);
	fi
	original=$(./test_files/asm $entry);

	if [[ "${original}" == "Writing output program"* ]]; then
		original_valid=TRUE;
		#echo "original is valid";
	fi
	if [[ "${perso}" == *"parsing successful"* ]]; then
		perso_valid=TRUE;
		#echo "perso is valid";
	fi
	if [[ $perso_valid != $original_valid ]]; then
		echo "";
		echo "$entry";
		if [[ $cat_file == TRUE ]]; then
			cat -e $entry;
		fi
		if [[ $perso_logs == TRUE ]]; then
			echo $perso;
		fi
		printf "\033[31m";
		echo "fail";
		printf "\033[0m";
		if [[ $original_valid == TRUE ]]; then
			echo "original is valid";
		fi
		if [[ $perso_valid == TRUE ]]; then
			echo "perso is valid";
		fi
	elif [[ $show_all == TRUE ]]; then
		echo "$entry";
		printf "\033[32m";
		echo "ok";
		printf "\033[0m";
	fi
done