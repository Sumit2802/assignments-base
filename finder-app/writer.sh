#!/bin/bash
writefile=$1
writestr=$2

if [ $# -lt 2 ] || [ ! -n $writestr ]
then
        echo "Incorrect arguments"
        exit 1
fi

dir_path=$(dirname "$writefile")
echo "Path is $dir_path"
if [ ! -d $dir_path ]
then
	mkdir -p "$dir_path"
fi
if [ ! -f $writefile ]
then
        touch $writefile
fi
        echo "$writestr" > $writefile
