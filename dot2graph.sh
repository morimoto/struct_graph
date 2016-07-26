#! /bin/sh
#===============================
#
# dot2graph
#
# 2016/07/26 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
#===============================

FILE=$1
[ ! -f $1 ] && echo "no such file" && exit

dot -Tps $FILE -o $FILE.ps
