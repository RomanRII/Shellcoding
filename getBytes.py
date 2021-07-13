#!/bin/python3

# Supply the bin file that was created to get hex bytes + total size
import binascii

file = input("Input the bin file you want to get the bytes from: ")
with open(file, 'rb') as f:
    hexdata = f.read().hex()

outBytes = ',0x'.join(hexdata[i:i+2] for i in range(0, len(hexdata), 2))
outBytes = "0x" + outBytes
count = outBytes.count("0x")
print("Bytes:",outBytes,"\nByte Count:",count)
