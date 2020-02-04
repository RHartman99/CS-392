###############################################################################
# Author: Ryan Hartman
# Date: 1/7/20
# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Description: Creates a recycling bin that can be purged and listed.
###############################################################################
#!/bin/bash

readonly JUNK_DIRECTORY="$HOME/.junk"
help_flag=0
list_flag=0
purge_flag=0


help_msg() {
    cat << EOF
Usage: $(basename "${0}") [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
EOF
}

while getopts ":hlp" option; do
    case "$option" in
        h)  help_flag=1
            ;;
        l)  list_flag=1
            ;;
        p)  purge_flag=1
            ;;
        ?)  printf "Error: Unknown option '-%s'.\n" $OPTARG >&2 #Print to standard error the unknown arg
            exit 1
            ;;
    esac
done

flags_sum=$((help_flag + list_flag + purge_flag))

if [ $flags_sum -gt 1 ]; then
     printf "Error: Too many options enabled.\n" >&2
     help_msg
     exit 1
fi

declare -a file_array
index=0
shift "$((OPTIND-1))" # Shift back one because we need the first argument.
for f in $@; do
    file_array[$index]=$f
    (( ++index ))
done

# Make ~/.junk if it doesn't exist
if [ ! -d "$JUNK_DIRECTORY" ]; then
    mkdir "$JUNK_DIRECTORY"
fi

# Check flags to error check and apply operations
if [ $flags_sum -eq 1 ] && [ $index -gt 0 ]; then
    printf "Error: Too many options.\n">&2
    help_msg
    exit 1
elif [ $flags_sum -eq 0 ] && [ $index -eq 0 ]; then
    help_msg
    exit 0
elif [ $help_flag -eq 1 ]; then
    help_msg
    exit 0
elif [ $list_flag -eq 1 ]; then
    ls -l "$JUNK_DIRECTORY"
    exit 0
elif [ $purge_flag -eq 1 ]; then
    rm -R "$JUNK_DIRECTORY"
    mkdir "$JUNK_DIRECTORY"
    exit 0
fi

for f in $file_array; do
    cp "$f" "$JUNK_DIRECTORY"
    rm "$f"
done

exit 0


# Should it error and go to standard error if no arguments are provided?
# What error message if we try to recycle but provide arguments?
# What if the file is not found?
# The permissions are different. Does that matter?