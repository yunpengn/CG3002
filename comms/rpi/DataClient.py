import socket
import struct

from client_auth import encryptText

localAddr = "127.0.0.1"

class DataClient():

    def __init__(self, server_port):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((localAddr, server_port))

    def start():
        self.socket.send('s')

    def stop():
        self.socket.send('q')

    def getMeanVariance():
        '''
        Returns the mean and variance of the past 0.2s of data as a tuple
        (HandAcclXMean, HandAcclXVar, HandAcclYMean, HandAcclYVar,
        HandAcclZMean, HandAcclZVar, HandGyroXMean, HandGyroXVar,
        HandGyroYMean, HandGyroYVar, HandGyroZMean, HandGyroZVar,
        LegAcclXMean, LegAcclXVar, LegAcclYMean, LegAcclYVar,
        LegAcclZMean, LegAcclZVar, LegGyroXMean, LegGyroXVar,
        LegGyroYMean, LegGyroYVar, LegGyroZMean, LegGyroZVar)
        '''
        self.socket.send('m')
        receivedData = self.socket.recv(4*24)
        return struct.unpack("24f", receivedData)
