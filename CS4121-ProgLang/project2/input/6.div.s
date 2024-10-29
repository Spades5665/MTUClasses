.data
.newLine: .asciiz "\n"
.text
.globl main
main:	nop
sw $gp, ($sp)
move $gp, $sp
add $sp, $sp, 16
li $s0, 51
li $s1, 17
div $s2, $s0, $s1
move $a0, $s2
li $v0, 1
syscall
la $a0, .newLine
li $v0, 4
syscall
li $s0, 100
add $s1, $gp, 0
sw $s0, 0($s1)
li $s0, 2
add $s1, $gp, 8
sw $s0, 0($s1)
li $s0, 5
add $s1, $gp, 12
sw $s0, 0($s1)
add $s1, $gp, 0
lw $s0, 0($s1)
add $s2, $gp, 8
lw $s1, 0($s2)
div $s2, $s0, $s1
add $s1, $gp, 12
lw $s0, 0($s1)
div $s1, $s2, $s0
add $s0, $gp, 4
sw $s1, 0($s0)
add $s1, $gp, 4
lw $s0, 0($s1)
move $a0, $s0
li $v0, 1
syscall
la $a0, .newLine
li $v0, 4
syscall
li $v0, 10
syscall
