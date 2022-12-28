#!/bin/bash
tgtname="bash"
cmdname=`basename $0"
if [ "$rootname" != "$tgtname" ]; then
   echo "This file must run under source"
   echo "usage: source setmsseenv.sh"
else
   echo "setting the environment"
   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/cray/pe/libsci/22.06.1.3/GNU/9.1/x86_64/lib/
   export OMP_NUM_THREADS=4
fi
