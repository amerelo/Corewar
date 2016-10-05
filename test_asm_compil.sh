#!/bin/sh

# Options are :
# -a to see the result on all tests and not only the ones who fail
# -e to see the error messages of our asm
# -l to see the output logs of our asm NOT IMPLEMENTED
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
	original_cor_created=FALSE;
	perso_cor_created=FALSE;
	cor_file=$(echo "$entry" | sed "s/\.s/\.cor/");

	#rm before recompiling to see if a new one appears
	$(rm $cor_file 2> /dev/null);

	if [[ $error_logs == TRUE ]]; then
		perso_output=$(./asm -e -i $entry);
	else
		perso_output=$(./asm -i $entry 2> /dev/null);
	fi

	if [ -f $cor_file ]; then
		perso_cor_created=TRUE;
		perso_file=$cor_file"2";
		mv $cor_file $perso_file;
	fi

	#rm before recompiling to see if a new one appears
	$(rm $cor_file 2> /dev/null);

	original_output=$(./test_files/asm $entry);
	if [ -f $cor_file ]; then
		original_cor_created=TRUE;
	fi

	if [[ $perso_cor_created != $original_cor_created ]]; then
		echo "$entry"
		printf "\033[31m";
		if [[ $perso_cor_created == TRUE ]]; then
			echo "we created a .cor while the original failed!"
		fi
		if [ $original_cor_created == TRUE ]; then
			echo "original created a .cor while we failed!"
		fi
		printf "\033[0m";

		if [[ $cat_file == TRUE ]]; then
			cat -e $entry;
		fi
	fi

	if [[ $perso_cor_created == TRUE && $original_cor_created == TRUE ]]; then
		perso_file_hex=$perso_file"hex";
		cor_file_hex=$cor_file"hex";


		xxd $perso_file > $perso_file_hex
		xxd $cor_file > $cor_file_hex

		diff_output=$(diff $cor_file_hex $perso_file_hex);
		if [[ $diff_output != "" ]]; then
			echo "$entry"
			printf "\033[33m";
			echo "$diff_output";
			printf "\033[0m";
			if [[ $cat_file == TRUE ]]; then
				cat -e $entry;
			fi
		elif [[ $show_all == TRUE ]]; then
			echo "$entry"
			printf "\033[32m";
			echo "ok";
			printf "\033[0m";
			if [[ $cat_file == TRUE ]]; then
				cat -e $entry;
			fi
		fi
	elif [[ $show_all == TRUE ]]; then
		echo "$entry"
		printf "\033[32m";
		echo "ok";
		printf "\033[0m";
	fi
done
