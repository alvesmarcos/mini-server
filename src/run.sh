# Created By: Marcos alves
# Created Date: Jun 10th, 2016	  
# Last Modified: Jun 11th, 2016	

#initial information
echo "Mini-Server-HTTP 1.0 (default, Jun 10 2016, 01:00:29)
[GCC 5.3.1 20160413] on Ubuntu 16.04Lts"

#variables
comd=0
count=1
zero=00

#program
while [ $comd != "quit" ]
do
	echo -e "iam(ssh):$zero$count:> \c"
	read comd
	case "$comd" in
   		"start") echo "=> running server"  
				 gnome-terminal -x make ;;
   		"clean") echo "=> clean *.o generated"
   				 make clean ;;
   		"kill") echo "=> kill server"
		 		pkill main ;;
   		*) comd="whatever";;
	esac
	count=$(($count+1))
	if [ "$count" -gt 9 ];
		then
		zero=0
	elif [ "$count" -gt 100 ];
		then
		zero=""
	fi
done