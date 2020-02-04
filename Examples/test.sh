#!/bin/bash

size_flag=0

while getopts ":s" option; do
    case "$option" in
        s)  size_flag=1
            ;;
        ?)  printf "Error: Unknown option '-%s'.\n" $OPTARG >&2 #Print to standard error the unknown arg
            exit 1
            ;;
    esac
done

if [ $size_flag -eq 1 ]; then
    echo "Yay, size flag"
fi

declare -a file_array
index=0
shift "$((OPTIND-1))" # Shift back one because we need the first argument.
for f in $@; d    file_array[$index]=$f
    (( ++index ))
done

echo "${file_array[*]}"
exit 0