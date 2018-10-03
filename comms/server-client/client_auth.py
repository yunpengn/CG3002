#Author: Zhi Yuan

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from base64 import b64encode

BLOCK_SIZE_BYTES = 16

def encryptText(keyStr, action, voltage, current, power, cumpower):
    """
    Encrypts a set of data that conforms to the server
    Arguments:
        keyStr:   16, 24 or 32 bytes long key as a UTF-8 String
        action:   UTF-8 String
        voltage:  UTF-8 String
        current:  UTF-8 String
        power:    UTF-8 String
        cumpower: UTF-8 String
    Returns:
        (IV + cipherText) encoded in base64 as a UTF-8 String
    """
    plaintext = '|'.join([action, voltage, current, power, cumpower])
    plaintext = "#" + plaintext
    paddingRequired = BLOCK_SIZE_BYTES - (len(plaintext)%BLOCK_SIZE_BYTES)
    if paddingRequired != BLOCK_SIZE_BYTES:
        padding = ' ' * paddingRequired
        plaintext = plaintext + padding
    iv = get_random_bytes(16)
    aesKey = bytes(str(keyStr), encoding = "utf8")

    cipher = AES.new(aesKey,AES.MODE_CBC,iv)
    cipherText = iv + cipher.encrypt(bytes(plaintext, "utf8"))
    return b64encode(cipherText).decode("utf8")

def testAuthentication(action, voltage, current, power, cumpower):
    from server_auth import server_auth
    server = server_auth()
    aesKey = "abcdef1234_12345"
    cipherText = encryptText(aesKey, action, voltage, current, power, cumpower)
    plainText = server.decryptText(cipherText, aesKey)
    for k in plainText:
        print("{0}: {1}".format(k, plainText[k]))

if __name__ == "__main__":
    testAuthentication("action","voltage","current","power","cumpower")
