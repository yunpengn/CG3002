import socket

from client_auth import encryptText

class Client():

    def __init__(self, server_ip, server_port, aesKeyStr):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.keyStr = aesKeyStr
        self.socket.connect((server_ip, server_port))
        print("Client connected")

    def sendData(self, action, voltage, current, power, cumpower):
        dataStr = encryptText(self.keyStr, action, voltage, current, power, cumpower)
        dataBytes = dataStr.encode("UTF-8")
        numSent = self.socket.send(dataBytes)
        if numSent<len(dataBytes):
            print("Warning: Sent less bytes than what was meant to be sent")

def testClient():
    ip_addr = "127.0.0.1"
    portNum = 1337
    key = "abcdef1234012345"
    c = Client(ip_addr, portNum, key)
    i = 1
    action = None
    while action!="logout":
        action = input("Action: ")
        c.sendData(action, "voltage"+str(i), "curremt"+str(i), "power"+str(i),
                   "cumpower"+str(i))
        i+=1
    
    
if __name__ == '__main__':
    testClient()
