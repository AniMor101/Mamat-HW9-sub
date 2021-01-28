#!/bin/bash

# exit if the number of arguments different from 1
if [ "$#" -ne 1 ]; then
exit
fi

#insert stdin into txt file
cat > stdin.txt

# remove space, comments and empty lines 
cat $1 | grep -o '^[^#]*' | sort | uniq > new_rules.txt

while read line; 
do
	IFS=',' read -r -a subrules <<< "$line"
	the_rules=$(cat stdin.txt | \
       ./firewall.exe "${subrules[0]}" 2>/dev/null | \
       ./firewall.exe "${subrules[1]}" 2>/dev/null| \
       ./firewall.exe "${subrules[2]}" 2>/dev/null| \
       ./firewall.exe "${subrules[3]}" 2>/dev/null)
	echo "$the_rules" >> bin.txt

done < new_rules.txt

cat bin.txt | sort | uniq | tr -d " \t" 

rm -f bin.txt stdin.txt new_rules.txt
