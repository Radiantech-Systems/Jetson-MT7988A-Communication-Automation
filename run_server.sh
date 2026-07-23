#!/bin/bash

SERVER_EXEC="./server"

echo "====================================="
echo " Starting Jetson TCP Server..."
echo "====================================="

while true
do
    if [ -x "$SERVER_EXEC" ]; then
        $SERVER_EXEC
    else
        echo "Error: server executable not found!"
        exit 1
    fi

    echo ""
    echo "Server stopped."
    echo "Restarting in 2 seconds..."
    sleep 2
done
