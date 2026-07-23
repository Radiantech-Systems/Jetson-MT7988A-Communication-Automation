# Jetson–MT7988A TCP Communication

A TCP socket-based communication project between an NVIDIA Jetson AGX Orin and a Banana Pi BPI-R4 Pro (MediaTek MT7988A).

---

## Overview

This project demonstrates reliable TCP communication between two embedded Linux platforms.

- **Jetson AGX Orin** acts as the **TCP Server**
- **Banana Pi BPI-R4 Pro (MT7988A)** acts as the **TCP Client**

The MT7988A automatically connects to the Jetson when it boots, sends a boot notification, receives an acknowledgment from the Jetson, and continues communicating using heartbeat messages.

---

## Features

- TCP Server (Jetson)
- TCP Client (MT7988A)
- Automatic client connection
- Boot notification
- Automatic acknowledgment
- Heartbeat communication
- Automatic reconnection
- Automatic startup after boot
- POSIX Socket Programming
- C Language Implementation

---

## Project Structure

```
Jetson-MT7988A-TCP-Communication
│
├── README.md
├── LICENSE
├── .gitignore
│
├── jetson
│   ├── main.c
│   ├── Makefile
│   ├── run_server.sh
│   └── jetson.service
│
└── mt7988a
    ├── tcp_client.c
    ├── Makefile
    ├── run_client.sh
    └── tcp_client.init
```

---

## Communication Flow

```
                Ethernet

+-----------------------------+
|        MT7988A Client       |
+-------------+---------------+
              |
              | Connect
              |
              v
+-------------+---------------+
|      Jetson TCP Server      |
+-----------------------------+

MT7988A -----------------> Jetson
 MT7988A_BOOT

Jetson ------------------> MT7988A
 JETSON_ACK

MT7988A -----------------> Jetson
 PING

Jetson ------------------> MT7988A
 PONG
```

---

## Build

### Jetson

```
cd jetson
make
```

Output:

```
server
```

---

### MT7988A

```
cd mt7988a
make
```

Output:

```
tcp_client
```

---

## Run

### Jetson

```
./run_server.sh
```

---

### MT7988A

```
./run_client.sh
```

---

## Automatic Startup

### Jetson

```
sudo cp jetson.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable jetson.service
sudo systemctl start jetson.service
```

---

### MT7988A (OpenWrt)

```
cp tcp_client.init /etc/init.d/tcp_client
chmod +x /etc/init.d/tcp_client
/etc/init.d/tcp_client enable
/etc/init.d/tcp_client start
```

---

## Communication Messages

| MT7988A | Jetson |
|----------|---------|
| MT7988A_BOOT | JETSON_ACK |
| PING | PONG |
| STATUS | MESSAGE_RECEIVED |

---

## Future Improvements

- Command-based communication
- AI inference requests
- Image transfer
- Video streaming
- Camera control
- JSON message format
- Multi-client support
- Secure TCP communication
- Logging and diagnostics

---

## Author

Harshavardhan Yanadi

Hardware Design & Embedded Systems Intern

---

## License

This project is licensed under the MIT License.
