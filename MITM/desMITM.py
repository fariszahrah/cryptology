from Crypto.Cipher import DES
import binascii
import random

randKey1 = hex(random.randint(0,1048576))[2:]
randKey2 = hex(random.randint(0,1048576))[2:]

print('randkey1 decimal:', int(randKey1,16))
print('randkey2 decimal:', int(randKey2,16))
while len(randKey1) < 16:
    randKey1 = '0' + randKey1 
while len(randKey2) < 16:
    randKey2 = '0' + randKey2 
    
#setting the stage to test against predetermined keys
key1 = binascii.unhexlify(randKey1)
key2 = binascii.unhexlify(randKey2)
des0 = DES.new(key1, DES.MODE_ECB)
des1 = DES.new(key2, DES.MODE_ECB)

#sample plaintext
plaintext = 'sona si latine loqueris '
ciphertext = des0.encrypt(plaintext)
finalCipher = des1.encrypt(ciphertext)



blocksToCompare = {}
collisionBlocks = {}
potentialKey1=[]
potentialKey2=[]

#now the first forloop which encrypts the plain text with all potential key0 values
counter =0
for num in range(0,1048576):
    hexOfNum = hex(num)[2:]
    while len(hexOfNum) < 16:
        hexOfNum = '0' + hexOfNum
    tempKey = binascii.unhexlify(hexOfNum)
    des = DES.new(tempKey, DES.MODE_ECB)
    tempBlock = des.encrypt(plaintext)

    if binascii.hexlify(tempBlock) in blocksToCompare:
        collisionBlocks[binascii.hexlify(tempBlock)]=num

    elif binascii.hexlify(tempBlock) in collisionBlocks:
        counter+=1

    else:
        blocksToCompare[binascii.hexlify(tempBlock)] = num



print('done with part 1')    
print('Number of collions in the collision dict:',counter)
#now I have a list of all partially encrypted blocks

for num1 in range(1048576):
    hexOf = hex(num1)[2:]
    while len(hexOf) < 16:
        hexOf = '0' + hexOf
    tempKey1=binascii.unhexlify(hexOf)
    des2= DES.new(tempKey1, DES.MODE_ECB)
    tempBlock1 = des2.decrypt(finalCipher)

    if binascii.hexlify(tempBlock1) in blocksToCompare:
        
        potentialKey1.append(blocksToCompare[binascii.hexlify(tempBlock1)])
        potentialKey2.append(num1)

        if binascii.hexlify(tempBlock1) in collisionBlocks:
            potentialKey1.append(collisionBlocks[binascii.hexlify(tempBlock1)])

    if binascii.hexlify(tempKey1) in collisionBlocks:
        potentialKey1.append(collisionBlocks[binascii.hexlify(tempKey1)])




for num in range(len(potentialKey1)):
    hexOf = hex(potentialKey1[num])[2:]
    while len(hexOf) < 16:
        hexOf = '0' + hexOf 
        num = hexOf
    des = DES.new(binascii.unhexlify(hexOf), DES.MODE_ECB)


for num in range(len(potentialKey2)):
    hexOf = hex(potentialKey2[num])[2:]
    while len(hexOf) < 16:
        hexOf = '0' + hexOf 
        num = hexOf
    des = DES.new(binascii.unhexlify(hexOf), DES.MODE_ECB)

   
    
    
print('potentialKey1:', list(set(potentialKey1)))
print('potentialKey2:', list(set(potentialKey2)))
'''
for i in list(set(potentialKey1)):
    for j in list(set(potentialKey2)):
        if i == j:
'''            






