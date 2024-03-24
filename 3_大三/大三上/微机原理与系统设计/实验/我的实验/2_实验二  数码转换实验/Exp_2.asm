_STACK SEGMENT PARA STACK'_STACK'
DB 128 DUP(0)
_STACK ENDS

DATA SEGMENT 
hello_1 DB 'Input your character, Q or q: EXIT, c: count the number of input string',0AH,0DH,'$' 
error_1 DB 0AH,0DH,'Wrong input!',0AH,0DH,'$'
error_2 DB 0AH,0DH,'Too more characters! Please input 4 characters at most!',0AH,0DH,'$'
finish_1 DB 0AH,0DH,'OK!',0AH,0DH,'$'
hello_2 DB 0AH,0DH,'Count the number',0AH,0DH,'Input string:',0AH,0DH,'$'
finish_2 DB 0AH,0DH,'Finished!',0AH,0DH,'There are ','$'
finish_3 DB ' numbers',0AH,0DH,'$'
got DB 5 DUP(0) 
DATA ENDS 

CODE SEGMENT
assume cs:CODE, ds:DATA, ss:_STACK
start:
    begin_read: ;开始读入
        mov ax,DATA 
        mov ds,ax
        mov dx,offset hello_1
        mov ah,09H
        int 21H 
        mov bx,0H 
        mov di,offset got 
        mov cx,0H 

    read_char: ;读入字符
        mov ah,01H
        int 21H 
        cmp bx,0H
        jne notfirst 
        cmp al,'Q'
        je exit_close
        cmp al,'q'
        je exit_close 
        cmp al,'c'
        je count_number_close 

    notfirst:
        mov bx,01H
        call check_legal 
        cmp bx,02H
        je begin_read 
        cmp bx,04H
        je end_input 
        jmp load

    load: ;加载
        mov [di],al 
        inc cx 
        inc di 
        jmp read_char 

    end_input: ;结束输入
        mov dx,0H 
        mov di,offset got 

    begin_convert: ;开始将十进制数转换成二进制数
    mov bx,0H
    mov bl,[di] 
    sub bx,30H 
    add dx,bx 
    cmp cx,1H 
    je end_convert
    call multiply 
    dec cx 
    inc di 
    jmp begin_convert

    end_convert: ;结束转换
        call binary_output
        jmp begin_read

    count_number_close: ;结束计数
        jmp count_number

    exit_close: ;结束后退出
        jmp exit

    binary_output: ;输出二进制数
        mov bx,dx 
        mov dx,0H
        mov cx,10H

    begin_outputloop:
        shl bx,1 
        jnc out_0 
        mov dl,'1'
        jmp outputdl
        out_0:
            mov dl,'0'
            outputdl:
            mov ah,02H
            int 21H 
            dec cx
            cmp cx,0H
            jne begin_outputloop
            mov dx,offset finish_1
            mov ah,09H
            int 21H 
            ret

    check_legal: ;检查输入合法性
        cmp al,0DH
        je end_legal_nextline
        cmp al,30H
        jb end_legal_false
        cmp al,39H
        ja end_legal_false

    end_legal_true: ;输入合法时的处理
        mov bx,03H
        ret 

    end_legal_nextline: ;换行时的处理
        mov bx,04H
        ret

    end_legal_false: ;输入非法时的处理
        mov dx,offset error_1
        mov ah,09H
        int 21H
        mov bx,02H
        ret

    multiply: ;乘10
        mov bx,0H
        mov ax,0H

    loop_mul:
        add ax,dx
        inc bx
        cmp bx,0AH
        jb loop_mul
        mov dx,ax
        ret

    count_number: ;计数
        mov dx,offset hello_2
        mov ah,09H
        int 21H 
        mov cx,0H

    begin_count:
        mov ah,01H
        int 21H 
        cmp al,20H
        je end_count 
        cmp al,30H
        jb notnum 
        cmp al,39H
        ja notnum

    isnum: ;是数字字符时的处理
        inc cx
        jmp begin_count

    notnum: ;非数字字符时的处理
        jmp begin_count

    end_count: ;结束计数
        add cx,30H 
        mov dx,offset finish_2
        mov ah,09H
        int 21H 
        mov dx,0H
        mov dl,cl
        mov ah,02H
        int 21H 
        mov dx,offset finish_3
        mov ah,09H
        int 21H 
        jmp begin_read
        exit: 
        mov ah,4CH 
        int 21H
    CODE ENDS
END START