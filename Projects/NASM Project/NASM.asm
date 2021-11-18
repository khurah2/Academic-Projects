%include "simple_io.inc"

global  asm_main

segment .data
    msg: db    "border array: ",0    ; a C-string with message
    msg1: db    "Incorrect number of command line argumemts",10,0    ;; a C-string with error message
    msg2: db    "input string too long" ,10,0    ;; a C-string with error message
    msg3: db    "input string: " ,0    ;; a C-string with a message
    str1: db    "+++ ",0    ; a C-string with message for maxbord 
    str2: db    "... ",0    ; a C-string with message for maxbord
    str3: db    "    ",0    ; a C-string with message for maxbord
    bordar: dq 0,0,0,0,0,0,0,0,0,0,0,0  ; array of 12 qwords, all 12 contains 0.

segment .text

maxbord:

        enter   0,0
        saveregs

        mov r10, [rbp+24] ; length of string passed

        mov r12, qword 1  ; r = 1
        mov r14, qword 0  ; max = 0

        Loop1:

            cmp r12, r10
            je end_maxbord

            mov r15, qword 1  ; isborder = 1
            mov r13, qword 0  ; i = 0

            Loop2:
                cmp r13, r12
                je set_max
                 mov rbx, [rbp+32] ; base address of string passed

                ;; if statment
                add rbx, r13  ; string[i]
                mov rcx, rbx
                add rcx, r10
                sub rcx, r12  ; string[L-r+i]
                mov al, byte[rbx]
                mov dl, byte[rcx]

                cmp al, dl  ; check string[i] == string [L-r+i]
                je step_2
                mov r15, qword 0
                jmp set_max


                step_2:
                inc r13
                jmp Loop2

            set_max:
                cmp r15, qword 1
                jne step_1
                cmp r14, r12
                jnb step_1
                mov r14, r12

            step_1:
                inc r12
                jmp Loop1

        end_maxbord:
            mov rax,r14
            restoregs
            leave
            ret

simple_display:

        enter   0,0
        saveregs

        mov rax, msg
        call print_string
        mov r14, [rbp+24]  ; Array adress
        mov r15, [rbp+32]  ; length of string passed as argument

        ;;;;;  Display of array till len
        mov r13, qword 1 ;; counter

        mov rax, [r14]  ;; printing array[0]
        call print_int
        add r14, qword 8       ;; array index = 1

        display_L1:

            cmp r13, r15       ;; If i == len
            je s_end

            mov al, ','
            call print_char
            mov rax, [r14]
            call print_int

            add r14, qword 8  ;; incrementation of array index by 1
            inc r13           ;; incrementation of counter variable by 1 (i.e i+=1) 
            jmp display_L1

       s_end:
        restoregs
        leave
        ret


fancy_display:

        enter   0,0
        saveregs

         
        mov r15, [rbp+32]  ; length of string passed as argument.
        mov r12, r15       ; initializing level to len of string passed.

        loop1:
            mov r13, qword 0   ; count == 0
            mov r14, [rbp+24]  ; Array address.

        ;;;;;;;;;;;;;;;;;;;;;;;;;;

            loop2:
                inc r13            ; incrementing count variable
                mov rbx, [r14]

                cmp r13, r15       ; if count > L
                ja process_L1

                cmp r12, qword 1   ; if level == 1
                je step

                cmp r12, rbx     ; level < x
                ja pstep

                mov rax, str1
                call print_string
                call process_L2

            pstep:
                mov rax, str3
                call print_string
                call process_L2

            ;; level == 1 is true
            step:
                cmp rbx, qword 0     ; x > 0
                ja pstep1

                mov rax, str2
                call print_string
                call process_L2

            pstep1:
                mov rax, str1
                call print_string
                call process_L2

            ; handles increment and decrement for Loop2
            process_L2 :     
                add r14, qword 8       ; array[i] = array[i+1]
                jmp loop2

        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

            ;; handles increment and decrement for Loop1
            process_L1 :
                call print_nl
                dec r12
                cmp r12, qword 0  ; level == 0
                je f_end
                jmp loop1


        f_end:
            restoregs
            leave
            ret

wrong_args: ; this is called when number of arguments are wrong

        mov rax, msg1
        call print_string
        jmp end_asm_main

wrong_len:  ; this is called when string paased as argument has length above 12

        mov rax, msg2
        call print_string
        jmp end_asm_main


asm_main:
        enter   0,0
        saveregs
        ;;;;;;;;;;;;;;;;;;;;

        mov r12, qword 0
        mov r13, qword 0

        ;;;;;;;;;;;;;;;;;;;;

        cmp rdi, qword 2    ; cheking for number of arguments
        jne wrong_args      ; if number of arguments is not equal to 2 wrong_args is called

        mov rbx, [rsi+8]    ; address of string passed as argument is in rbx , rbx = agrs[1]

        len_cal:    ;;;; To calculate the lenght of string passed as argument
            mov r12b, byte[rbx]
            cmp r12b, 0
            je len_check

            inc rbx  ; shifting the pointer to next variable of the string passed as argument
            inc r13  ; incrementing to calculate len of string passed as argument
            jmp len_cal  ; unconditional jump to len_cal

        len_check:   ; checks if the lenght of string passed as arugument is not above 12
            cmp r13, qword 12
            ja wrong_len


        ;; printing the input string passed as argument
        mov rax, msg3
        call print_string
        mov rax, [rsi+8]
        call print_string
        call print_nl
        

        maxbord_call:  ;; calling maxbord with two actual paremeters and a fake parameter on stack, using loop.

            mov rbx, bordar  ;; base address of array is stored in rbx 

            mov rcx, [rsi+8]  ;; base address of string passed as argument is stored in rcx
            mov r12, qword 0 ; iterator for loop
            mov r15, r13     ; len of string passed
            mov r14, r13     ; temp variable for len namely L1
            sub r15, qword 1 ; for range part of the loop

            L1:
                cmp r12, r15
                je s_display
                push rcx 
                push r14 
                sub rsp, 8   ;; fake parameter
                call maxbord
                mov qword[rbx], rax ; the max value returned from maxbord is saved in bordar array
                add rsp, 24

                add rbx, qword 8  ; shifting the pointer to next address of bordar array
                inc rcx ; shifting the pointer to next variable of the string passed as argument
                inc r12 ; incrementing iterator of loop
                dec r14 ; decrementing L1
                jmp L1  ; unconditional jump to L1


        s_display:  ;; calling simple display with two actual paremeters and a fake parameter on stack.

            mov rcx, r13  ;; length of string passed as argument is stored in rcx
            mov rbx, bordar ;; base address of array is stored in rbx
            push rcx
            push rbx
            sub rsp, 8   ;; fake parameter
            call simple_display
            add rsp,24  ;; stack is closed here
            call print_nl

         f_display:   ;; calling fancy display with two actual paremeters and a fake parameter on stack.

            mov rcx, r13  ;; length of string passed as argument is stored in rcx
            mov rbx, bordar ;; base address of array is stored in rbx
            push rcx
            push rbx
            sub rsp, 8   ;; fake parameter
            call fancy_display
            add rsp,24  ;; stack is closed here


end_asm_main:
        restoregs
        leave
         ret