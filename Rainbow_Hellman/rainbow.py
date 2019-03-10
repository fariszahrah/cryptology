from Crypto.Cipher import AES
import binascii
import os


key = binascii.unhexlify('2AF453B6000000000000000000000000')
encryptor = AES.new(key, AES.MODE_ECB)
coverageSet = {0}

os.system('clear')

for table in range(1):
     
    for row in range(80000):
        tempp = os.urandom(16)
        for column in range(316):
            tempp = encryptor.encrypt(tempp)
            tempp = hex(int(binascii.hexlify(tempp),16)+table)[2:]
            if len(tempp) < 32:
                tempp = tempp[2:]
                while len(tempp) < 32:
                    tempp = '0' + tempp
            tempp = binascii.unhexlify(tempp)
            toAdd = int(int(binascii.hexlify(tempp),16)/(10**31))    
            coverageSet.add(toAdd)             
            if len(coverageSet) % 50000 == 0:
                print(len(coverageSet), end='\r')
print('set coverage: ',len(coverageSet))

