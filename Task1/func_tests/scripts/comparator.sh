#!/bin/bash

n=0
function find_after_string {
    sep=""
    found=0
    while read -r line; do
        if [[ "$line" == *"$sep"* ]] && [[ $found -eq 0 ]]; then
            found=1
            before1=${line%%"$sep"*}
            ind1=${#before1}
            after1=${line:$((ind1))}
            if [[ -z $after1 ]]; then
                line=$before1
            else
                line=$after1
            fi
            echo "$line" > "$2"
        else
            echo "$line" >> "$2"
        fi
   done < "$1"
}

while [[ $n -lt 3 ]] && [[ -n $1 ]]; do
    if [[ $1 == "-v" ]]; then 
    	verbose=1
    else 
    	if [[ -z $file1 ]]; then
    	    file1=$1
    	else 
    	    file2=$1
    	fi
    fi
    shift
    n=$((n + 1))
done

if [[ -z $file1 ]] || [[ -z $file2 ]]; then
    if [[ -n $verbose ]]; then
        echo "Incorrect input"
    fi
    exit 2
fi

if [[ ! -f $file1 ]] || [[ ! -f $file2 ]]; then
    if [[ -n $verbose ]]; then
        echo "One of files is not a file or not exists"
    fi
    exit 3
fi

if [[ ! -r $file1 ]] || [[ ! -r $file2 ]]; then
    if [[ -n $verbose ]]; then
        echo "One of files are not available for reading"
    fi
    exit 4
fi


if [[ -n $verbose ]]; then
    echo "Correct input"
fi

after_text_file1=$(mktemp)
after_text_file2=$(mktemp)

find_after_string "$file1" "$after_text_file1"
find_after_string "$file2" "$after_text_file2"

exec 3<"$after_text_file1"
exec 4<"$after_text_file2"

end_f1=1
end_f2=1

while [[ $end_f1 -gt 0 ]] && [[ $end_f2 -gt 0 ]]; do
    if ! read -r line1 <&3; then
        end_f1=0
    fi
    if ! read -r line2 <&4; then
        end_f2=0
    fi
    if [[ -n $verbose ]]; then
        echo "Line from file 1: ""$line1"
        echo "Line from file 2: ""$line2"
    fi 
    if [[ "$line1" != "$line2" ]]; then
        break
    fi   
done

if [[ $end_f2 -eq 0 ]] && [[ $end_f1 -eq 0 ]]; then
    if [[ -n $verbose ]]; then
        echo "Files have the same content"
    fi
  exit 0
else
    if [[ -n $verbose ]]; then
        echo "Files does not have the same content"
    fi
  exit 1
fi
