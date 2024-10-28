sw $fp, ($sp)
move $fp, $sp
sub $sp, $sp, 16
.text
.globl main
main:   nop
li $v0, 10
syscall