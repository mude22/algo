#!/bin/bash

PRINT="0"
TIME="0"
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -e|--ex_path)
    EX_PATH="$2"
    shift
    ;;
    -p|--print)
    PRINT="1"
    ;;
    -t|--time)
    TIME="1"
    ;;
    *)
        echo "Argument inconnu: ${1}"
        exit
    ;;
esac
shift
done

printf '%s\n' $(./main $ALGO $EX_PATH $PRINT $TIME)
