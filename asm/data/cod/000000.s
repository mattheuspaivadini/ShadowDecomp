.include "macro.inc"

.section .text, "ax"

nonmatching __cod_000000_textbin

glabel __cod_000000_textbin
.incbin "build/assets/cod/000000.textbin.bin"
endlabel __cod_000000_textbin
