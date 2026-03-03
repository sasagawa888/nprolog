;INCLUDE plmbase.asm
    JP START
SUMSQUARE:
    PUSH ix
    LD ix,4096
    ADD ix,sp
    LD l,(ix+4)
    LD h,(ix+5)
    PUSH hl
    LD l,(ix+4)
    LD h,(ix+5)
    POP de
    CALL MUL16
    PUSH hl
    LD l,(ix+6)
    LD h,(ix+7)
    PUSH hl
    LD l,(ix+6)
    LD h,(ix+7)
    POP de
    CALL MUL16
    POP de
    ADD hl,de
    POP ix
    RET
START:
    LD hl,4
    PUSH hl
    LD hl,3
    PUSH hl
    CALL SUMSQUARE
    ADD sp,4
    LD (C),hl
HALT_LABEL:
    HALT
    JP HALT_LABEL
