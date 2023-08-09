.text
.globl main
main: 
# ==================================

li $t0,10

li $t1,11

li $t2,5

move $a0,$t4
li $v0,1
syscall
li $a0, 10
li $v0, 11
syscall

jal print

print:
	lw $a0, 
	li $v0, 1
	syscall
	
