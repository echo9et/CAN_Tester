#/bin/sh
INTERFACES=$( ip link | egrep can | /usr/bin/awk '{ print $2}' )

for INTERFACE in ${INTERFACES}; 
    do echo ${INTERFACE%:*};
    done
