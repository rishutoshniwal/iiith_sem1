#!/bin/bash



#-printf "%s\t%f\n"
du -h -d 1 | sort -r -h | awk '!($2 == ".")' | awk -F ./ '{print $NF "\t" $1}'
#awk '{print $9 "\t" $5}'
