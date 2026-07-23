#!/bin/sh

CLIENT_EXEC="./tcp_client"

echo "====================================="
echo " Starting MT7988A TCP Client..."
echo "====================================="

while true
do
    if [ -x "$CLIENT_EXEC" ]; then
        $CLIENT_EXEC
    else
        echo "Error: tcp_client executable not found!"
        exit 1
    fi

    echo ""
    echo "TCP Client stopped."
    echo "Restarting in 2 seconds..."
    sleep 2
done
