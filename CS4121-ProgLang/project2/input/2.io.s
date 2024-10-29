.data
.newLine: .asciiz "\n"
.string2: .asciiz "input an integer:"
.text
.globl main
main:	nop
sw $gp, ($sp)
move $gp, $sp
add $sp, $sp, 4
la $a0, .string2
li $v0, 4
syscall
la $a0, .newLine
li $v0, 4
syscall
li $v0, 5
syscall
move $s0, $v0
add $s1, $gp, 0
sw $s0, 0($s1)
add $s1, $gp, 0
lw $s0, 0($s1)
move $a0, $s0
li $v0, 1
syscall
la $a0, .newLine
li $v0, 4
syscall
li $s0, 1
move $a0, $s0
li $v0, 1
syscall
la $a0, .newLine
li $v0, 4
syscall
li $s0, 1
li $s1, 2
add $s2, $s0, $s1
move $a0, $s2
li $v0, 1
syscall
la $a0, .newLine
li $v0, 4
syscall
li $v0, 10
syscall
