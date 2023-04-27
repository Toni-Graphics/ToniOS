[bits 16]
[extern _main]

start:
    call _main
    hlt

times 510 -( $ - $$ ) db 0
dw 0xAA55