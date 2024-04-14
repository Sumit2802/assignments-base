#!/bin/sh
filesdir=$1
searchstr=$2

#if [ $# -ge 2 ] && [ -d $filesdir ] && [ -n $searchstr ]

if [ $# -lt 2 ]
then
   echo "Few arguments are passed"
   exit 1
fi

if [ ! -d $filesdir ]
then
   echo "1st argument is not a directory"
   exit 1
fi
echo "$(ls -1 $filesdir)"
num_of_files=$(ls -1 $filesdir | wc -l)
echo "$num_of_files"
num_of_matches=$(grep -nri $searchstr $filesdir | wc -l)
echo "The number of files are $num_of_files and the number of matching lines are $num_of_matches"
