#!/bin/bash
n=$(wc -l cities.txt | cut -d' ' -f1)
ih=$(cat cities.txt | head -n$n | cut -d',' -f1 | sed 's/ /_/g' | sed 's/^/ih /g')
it=$(cat cities.txt | head -n$n | cut -d',' -f2 | sed 's/ /_/g' | sed 's/^/it /g')
rh=$(for (( i=0; i<$n; i++ )); do echo rh; done)

SECONDS=0

cat <<EOF | ./qtest &> /dev/null
option fail 0
option malloc 0
new
$ih
$it
size
reverse
size
$rh
show
free
quit
EOF

echo "echo \$? = $(echo $?)"
echo "Elapsed $SECONDS seconds."