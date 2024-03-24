STACK1 SEGMENT STACK
STACK1 ENDS

DATA SEGMENT
    buffer     DB 'Student ID:21009200758  Student Name:Mei Yuding',0ah,0dh,'$'
    buffer2    DB 'Hello World','$'
    showch     DB 'The character in the buffer: ','$'
    showasc    DB '             The ASCII is:','$'
    showinput  DB 'Please input characters:','$'
    endl       DB 0ah,0dh,'$'
    space      DB 20h,'$'
DATA ENDS

CODE SEGMENT
        assume ss:stack1,cs:code,ds:data
    START:
        mov   ax,data
        mov   ds,ax
        mov   ah,09h
        mov   dx,offset buffer
        int   21h
        mov   si,offset buffer2

    ;获取ASCII码
    ascii_show:
        cmp   byte ptr [si],'$'
        je    inputasc_show
        
        mov   ah,09h
        mov   dx,offset showch
        int   21h
        mov   al,ds:[si]
        mov   dl,al
        mov   ah,02h
        int   21h
        
        mov   ah,09h
        mov   dx,offset space
        int   21h
        
        mov   ah,09h
        mov   dx,offset inputasc_show
        int   21h
        
        mov   al,ds:[si]
        mov   dl,al
        and   al,0f0h
        mov   cl,4
        shr   al,cl
        cmp   al,0ah
        jb    high_show_1
        add   al,07h

    ;取字节高4位
    high_show_1:
        add   al,30h
        mov   dl,al
        mov   ah,02h
        int   21h
        mov   al,ds:[si]
        and   al,0fh
        cmp   al,0ah
        jb    low_show_1
        add   al,07h
    
    ;取字节低4位
    low_show_1:
        add   al,30h
        mov   dl,al
        mov   ah,02h
        int   21h
        
        mov   ah,09h
        mov   dx,offset endl
        int   21h
        
        add   si,1
        jmp   ascii_show
        
    ;从键盘读入字符并回显在屏幕上
    inputasc_show:
        mov   ah,09h
        mov   dx,offset endl
        int   21h
        
        mov   ah,09h
        mov   dx,offset showinput
        int   21h
        
        mov   ah,01h
        int   21h
        
        cmp   al,'q'
        je    proend
        cmp   al,'q'
        je    proend
        mov   bl,al
        
        mov   ah,09h
        mov   dx,offset endl
        int   21h
        mov   ah,09h
        mov   dx,offset showasc
        int   21h
        
        mov   al,bl
        and   al,0f0h
        mov   cl,4
        shr   al,cl
        cmp   al,0ah
        jb    high_show_2
        add   al,07h

    high_show_2:
        add   al,30h
        mov   dl,al
        mov   ah,02h
        int   21h
        mov   al,bl
        and   al,0ah
        jb    low_show_2
        add   al,01h

    low_show_2:
        add   al,30h
        mov   dl,al
        mov   ah,02h
        int   21h
        jmp   inputasc_show

    proend:
        mov   ah,4ch
        int   21h
        
CODE ENDS
END START

