.text
.globl main
main: 
# ==================================

li $t0, 10
li $t1, 11
li $t2, 5
jal print
print:
  # print function body
  # function changed so previous version lost
  jr $ra

li $v0,10


syscall
.end main
