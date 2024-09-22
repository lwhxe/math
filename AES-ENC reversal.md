```assembly
# MOVE 6 DOUBLE QUADWORDS (96 Bytes) from 0x7e00 into xmm0-xmm2 then call 0x57
# AKA do 48 AES passes
0000002B  F30F6F06007E      movdqu xmm0,oword [0x7e00]
00000031  F30F6F0E107E      movdqu xmm1,oword [0x7e10]
00000037  F30F6F16207E      movdqu xmm2,oword [0x7e20]

0000003D  E81700            call 0x57

# Set cl to 20, XOR xmm1 and xmm2 with each other into xmm3
00000057  B130              mov cl,0x30
00000059  0F28D9            movaps xmm3,xmm1
0000005C  0F57DA            xorps xmm3,xmm2

# AES ENCRYPT xmm3 with WITH KEY xmm0 
# Then rotate registers (0 to 3, 1 to 0, etc.)
0000005F  660F38DCD8        aesenc xmm3,xmm0
00000064  0F28C1            movaps xmm0,xmm1
00000067  0F28CA            movaps xmm1,xmm2
0000006A  0F28D3            movaps xmm2,xmm3

0000006D  FEC9              dec cl
0000006F  75E8              jnz 0x59

# Rotate again except for the 1 to 0
00000071  0F28D8            movaps xmm3,xmm0
00000074  0F28C2            movaps xmm0,xmm2
00000077  0F28D3            movaps xmm2,xmm3
0000007A  C3                ret
```
### Final Values:

XMM0 6e1d 7130 af40 3aac b49a ed58 e463 2994; 
XMM1: a4ed b66c 74f6 9b01 ae91 a486 0204 32cd;  
XMM2: afe1 631d 459b e1bd 8714 e352 60f7 ed9d; 
XMM3: afe1 631d 459b e1bd 8714 e352 60f7 ed9d; 

## Manual Reversing until AES is figured out:

XMM0 afe1 631d 459b e1bd 8714 e352 60f7 ed9d; 
XMM1: a4ed b66c 74f6 9b01 ae91 a486 0204 32cd;  
XMM2: 6e1d 7130 af40 3aac b49a ed58 e463 2994; 
XMM3: 6e1d 7130 af40 3aac b49a ed58 e463 2994; 

Backwards loop starts here:

XMM0: ? 
XMM1: afe1 631d 459b e1bd 8714 e352 60f7 ed9d;  
XMM2: a4ed b66c 74f6 9b01 ae91 a486 0204 32cd;  
XMM3: 6e1d 7130 af40 3aac b49a ed58 e463 2994; 

XMM0: ? 
XMM1: afe1 631d 459b e1bd 8714 e352 60f7 ed9d;  
XMM2: a4ed b66c 74f6 9b01 ae91 a486 0204 32cd;  
XMM3: 6e1d 7130 af40 3aac b49a ed58 e463 2994; Known After XMM3 Encrypted DATA

XMM0: ? 
XMM1: afe1 631d 459b e1bd 8714 e352 60f7 ed9d;  
XMM2: a4ed b66c 74f6 9b01 ae91 a486 0204 32cd;  
XMM3: afe1 631d 459b e1bd 8714 e352 60f7 ed9d;  Copied from XMM1

XMM0: ? 
XMM1: afe1 631d 459b e1bd 8714 e352 60f7 ed9d;  
XMM2: a4ed b66c 74f6 9b01 ae91 a486 0204 32cd;  
XMM3: 0b0c d571 316d 7abc 2985 47d4 62f3 df50; Known Before XMM3 Encrypted DATA

And here we figure out that XMM0:
8fe6 c877 a5a8 b3aa 9445 ec68 2013 ac05