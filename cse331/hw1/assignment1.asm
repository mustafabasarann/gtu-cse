.data

prompt_message: .asciiz "Enter text: "

chars_label: .asciiz "\nCharacters "
vowels_label: .asciiz "\nVowels: "
consonants_label: .asciiz "\nConsonants: "
digits_label: .asciiz "\nDigits: "
spaces_label: .asciiz "\nSpaces: "

input_buffer:  .space 200

.text

main:

	li $v0, 4
	la $a0, prompt_message
	syscall
	
	li $v0, 8
	la $a0, input_buffer
	li $a1, 200
	syscall
	
	la $s0, input_buffer
	
	li $s1, 0
	li $s2, 0
	li $s3, 0
	li $s4, 0
	li $s5, 0
	
loop_start:
	lb $t0, 0($s0)
	
	beq $t0, 0, loop_end
	beq $t0, 10, loop_end
	
	addi $s1, $s1, 1 
	
	li $t1, 32
	beq $t0, $t1, is_space
	
	li $t1, '0'
	blt $t0, $t1, check_letter
	li $t1, '9'
	bgt $t0, $t1, check_letter
	j is_digit
	
check_letter:
	move $a0, $t0
	jal checkVowel
	
	beq $v0, 1, is_vowel

	li $t1, 'a'
	blt $t0, $t1, check_uppercase_consonant
	li $t1, 'z'
	bgt $t0, $t1, check_uppercase_consonant
	
	j is_consonant 

check_uppercase_consonant:
	li $t1, 'A'
	blt $t0, $t1, continue_loop
	li $t1, 'Z'
	bgt $t0, $t1, continue_loop
	
	j is_consonant
	
is_space:
	addi $s5, $s5, 1
	j continue_loop	

is_digit:
	addi $s4, $s4, 1
	j continue_loop
	
is_vowel:
	addi $s2, $s2, 1
	j continue_loop	
	
is_consonant:
	addi $s3, $s3, 1 
	j continue_loop	
	
continue_loop:
	addi $s0, $s0, 1
	j loop_start	
	
	
loop_end:

	li $v0, 4
	la $a0, chars_label
	syscall
	li $v0, 1
	move $a0, $s1
	syscall
	
	li $v0, 4
	la $a0, vowels_label
	syscall 
	li $v0, 1
	move $a0, $s2
	syscall 
	
	li $v0, 4
	la $a0, consonants_label
	syscall
	li $v0, 1 
	move $a0, $s3
	syscall
	
	li $v0, 4
	la $a0, digits_label
	syscall
	li $v0, 1
	move $a0, $s4
	syscall
	
	li $v0, 4
	la $a0, spaces_label
	syscall
	li $v0, 1 
	move $a0, $s5
	syscall

	li $v0, 10
	syscall 
	
checkVowel:
	beq $a0, 'a', return_vowel_true
	beq $a0, 'e', return_vowel_true
    beq $a0, 'i', return_vowel_true
    beq $a0, 'o', return_vowel_true
    beq $a0, 'u', return_vowel_true
    beq $a0, 'A', return_vowel_true
    beq $a0, 'E', return_vowel_true
    beq $a0, 'I', return_vowel_true
    beq $a0, 'O', return_vowel_true
    beq $a0, 'U', return_vowel_true
    
    li $v0, 0
    jr $ra
  
return_vowel_true:
	li $v0, 1
	jr $ra