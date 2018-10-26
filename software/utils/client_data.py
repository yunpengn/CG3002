import socket
import struct

localAddr = "localhost"
server_port = 3002
featurePrefixes = ("mean_", "var_", "min_", "max_")
dataPointNames = ("BodyX", "BodyY", "BodyZ",
                  "handAcclX", "handAcclY", "handAcclZ",
                  "handGyroX", "handGyroY", "handGyroZ",
                  "legAcclX", "legAcclY", "legAcclZ",
                  "legGyroX", "legGyroY", "legGyroZ")
headerNames = []
for prefix in featurePrefixes:
    for dataName in dataPointNames:
        headerNames.append(prefix + dataName)
headerNames = tuple(headerNames)


class DataClient:
    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((localAddr, server_port))

    def start(self):
        self.socket.send('s'.encode())

    def stop(self):
        self.socket.send('q'.encode())

    def getMlData(self):
        '''
        Queries the C program for data.
        Returns the data as a dictionary
        '''
        self.socket.send('m'.encode())
        receivedData = self.socket.recv(4 * 60)
        # Received data is of the following format: Mean, variance, max, min
        # Each category has 15 points corresponding to body, handAccl, handGyro, legAccl, legGyro
        return dict(zip(headerNames, struct.unpack("60f", receivedData)))

    def getPowerData(self):
        self.socket.send('p'.encode())
        energy, voltage, current = struct.unpack("3f", self.socket.recv(4 * 3))
        power = voltage * current
        return {'cumpower': energy, 'voltage': voltage, 'current': current, 'power': power}
