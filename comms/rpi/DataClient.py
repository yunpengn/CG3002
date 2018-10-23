import socket
import struct

from client_auth import encryptText

localAddr = "127.0.0.1"
server_port = 3002
featurePrefixes = ("mean_", "var_", "min_", "max_")
dataPointNames = ("BodyX", "BodyY" "BodyZ",
                  "handAcclX", "handAcclY", "handAcclZ",
                  "handGyroX", "handGyroY", "handGyroZ",
                  "legAcclX", "legAcclY", "legAcclZ",
                  "legGyroX", "legGyroY", "legGyroZ")
headerNames = []
for prefix in featurePrefixes:
    for dataName in dataPointNames:
        headerNames.append(prefix+dataName)
headerNames = tuple(headerNames)

class DataClient():

    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((localAddr, server_port))

    def start():
        self.socket.send('s')

    def stop():
        self.socket.send('q')

    def getMlData():
        '''
        Queries the C program for data.
        Returns the data as a dictionary
        '''
        self.socket.send('m')
        receivedData = self.socket.recv(4*30)
        #Received data is of the following format: Mean, variance, max, min
        #Each category has 15 points corresponding to body, handAccl, handGyro, legAccl, legGyro
        return dict(zip(headerNames,struct.unpack("30f", receivedData)))
