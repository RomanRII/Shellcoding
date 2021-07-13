; Name: Basic calc pop
; Author: RomanRII
; Date: 07/13/21

BITS 32
section .text
global _start
_start:
 xor eax, eax
 push eax
 push ".exe"
 push "calc"
 mov eax, esp
 push 1
 push eax
 mov ebx, 0x775dcd30
 call ebx
