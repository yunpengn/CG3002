import socket
from .client_auth import encryptText


class ResultClient():
    def __init__(self, server_ip, server_port, aesKeyStr):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.keyStr = aesKeyStr
        self.socket.connect((server_ip, server_port))
        print("Client connected")

    def sendData(self, action, voltage, current, power, cumpower):
        dataStr = encryptText(self.keyStr, action, voltage, current, power, cumpower)
        dataBytes = dataStr.encode("UTF-8")
        numSent = self.socket.send(dataBytes)
        if numSent < len(dataBytes):
            print("Warning: Sent less bytes than what was meant to be sent")
