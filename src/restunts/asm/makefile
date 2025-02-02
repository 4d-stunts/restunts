!ifndef TARGET
TARGET=dos
!endif

OBJDIR = build

!if ($(TARGET)!=dos)
!error Unsupported ASM target: $(TARGET)
!endif

ASM = tasmbox /m2 /s /zi

INCLUDES = structs.inc

all: $(OBJDIR)\segments.obj $(OBJDIR)\seg000.obj $(OBJDIR)\seg001.obj $(OBJDIR)\seg002.obj $(OBJDIR)\seg003.obj $(OBJDIR)\seg004.obj $(OBJDIR)\seg005.obj $(OBJDIR)\seg006.obj $(OBJDIR)\seg007.obj $(OBJDIR)\seg008.obj $(OBJDIR)\seg009.obj $(OBJDIR)\seg010.obj $(OBJDIR)\seg011.obj $(OBJDIR)\seg012.obj $(OBJDIR)\seg013.obj $(OBJDIR)\seg014.obj $(OBJDIR)\seg015.obj $(OBJDIR)\seg016.obj $(OBJDIR)\seg017.obj $(OBJDIR)\seg018.obj $(OBJDIR)\seg019.obj $(OBJDIR)\seg020.obj $(OBJDIR)\seg021.obj $(OBJDIR)\seg022.obj $(OBJDIR)\seg023.obj $(OBJDIR)\seg024.obj $(OBJDIR)\seg025.obj $(OBJDIR)\seg026.obj $(OBJDIR)\seg027.obj $(OBJDIR)\seg028.obj $(OBJDIR)\seg029.obj $(OBJDIR)\seg030.obj $(OBJDIR)\seg031.obj $(OBJDIR)\seg032.obj $(OBJDIR)\seg033.obj $(OBJDIR)\seg034.obj $(OBJDIR)\seg035.obj $(OBJDIR)\seg036.obj $(OBJDIR)\seg037.obj $(OBJDIR)\seg038.obj $(OBJDIR)\seg039.obj $(OBJDIR)\seg041.obj $(OBJDIR)\dseg.obj

$(OBJDIR)\segments.obj: segments.asm
	$(ASM) segments.asm , $<

$(OBJDIR)\seg000.obj: seg000.asm $(INCLUDES)
	$(ASM) seg000.asm , $<

$(OBJDIR)\seg001.obj: seg001.asm $(INCLUDES)
	$(ASM) seg001.asm , $<

$(OBJDIR)\seg002.obj: seg002.asm $(INCLUDES)
	$(ASM) seg002.asm , $<

$(OBJDIR)\seg003.obj: seg003.asm $(INCLUDES)
	$(ASM) seg003.asm , $<

$(OBJDIR)\seg004.obj: seg004.asm $(INCLUDES)
	$(ASM) seg004.asm , $<

$(OBJDIR)\seg005.obj: seg005.asm $(INCLUDES)
	$(ASM) seg005.asm , $<

$(OBJDIR)\seg006.obj: seg006.asm $(INCLUDES)
	$(ASM) seg006.asm , $<

$(OBJDIR)\seg007.obj: seg007.asm $(INCLUDES)
	$(ASM) seg007.asm , $<

$(OBJDIR)\seg008.obj: seg008.asm $(INCLUDES)
	$(ASM) seg008.asm , $<

$(OBJDIR)\seg009.obj: seg009.asm $(INCLUDES)
	$(ASM) seg009.asm , $<

$(OBJDIR)\seg010.obj: seg010.asm $(INCLUDES)
	$(ASM) seg010.asm , $<

$(OBJDIR)\seg011.obj: seg011.asm $(INCLUDES)
	$(ASM) seg011.asm , $<

$(OBJDIR)\seg012.obj: seg012.asm $(INCLUDES)
	$(ASM) seg012.asm , $<

$(OBJDIR)\seg013.obj: seg013.asm $(INCLUDES)
	$(ASM) seg013.asm , $<

$(OBJDIR)\seg014.obj: seg014.asm $(INCLUDES)
	$(ASM) seg014.asm , $<

$(OBJDIR)\seg015.obj: seg015.asm $(INCLUDES)
	$(ASM) seg015.asm , $<

$(OBJDIR)\seg016.obj: seg016.asm $(INCLUDES)
	$(ASM) seg016.asm , $<

$(OBJDIR)\seg017.obj: seg017.asm $(INCLUDES)
	$(ASM) seg017.asm , $<

$(OBJDIR)\seg018.obj: seg018.asm $(INCLUDES)
	$(ASM) seg018.asm , $<

$(OBJDIR)\seg019.obj: seg019.asm $(INCLUDES)
	$(ASM) seg019.asm , $<

$(OBJDIR)\seg020.obj: seg020.asm $(INCLUDES)
	$(ASM) seg020.asm , $<

$(OBJDIR)\seg021.obj: seg021.asm $(INCLUDES)
	$(ASM) seg021.asm , $<

$(OBJDIR)\seg022.obj: seg022.asm $(INCLUDES)
	$(ASM) seg022.asm , $<

$(OBJDIR)\seg023.obj: seg023.asm $(INCLUDES)
	$(ASM) seg023.asm , $<

$(OBJDIR)\seg024.obj: seg024.asm $(INCLUDES)
	$(ASM) seg024.asm , $<

$(OBJDIR)\seg025.obj: seg025.asm $(INCLUDES)
	$(ASM) seg025.asm , $<

$(OBJDIR)\seg026.obj: seg026.asm $(INCLUDES)
	$(ASM) seg026.asm , $<

$(OBJDIR)\seg027.obj: seg027.asm $(INCLUDES)
	$(ASM) seg027.asm , $<

$(OBJDIR)\seg028.obj: seg028.asm $(INCLUDES)
	$(ASM) seg028.asm , $<

$(OBJDIR)\seg029.obj: seg029.asm $(INCLUDES)
	$(ASM) seg029.asm , $<

$(OBJDIR)\seg030.obj: seg030.asm $(INCLUDES)
	$(ASM) seg030.asm , $<

$(OBJDIR)\seg031.obj: seg031.asm $(INCLUDES)
	$(ASM) seg031.asm , $<

$(OBJDIR)\seg032.obj: seg032.asm $(INCLUDES)
	$(ASM) seg032.asm , $<

$(OBJDIR)\seg033.obj: seg033.asm $(INCLUDES)
	$(ASM) seg033.asm , $<

$(OBJDIR)\seg034.obj: seg034.asm $(INCLUDES)
	$(ASM) seg034.asm , $<

$(OBJDIR)\seg035.obj: seg035.asm $(INCLUDES)
	$(ASM) seg035.asm , $<

$(OBJDIR)\seg036.obj: seg036.asm $(INCLUDES)
	$(ASM) seg036.asm , $<

$(OBJDIR)\seg037.obj: seg037.asm $(INCLUDES)
	$(ASM) seg037.asm , $<

$(OBJDIR)\seg038.obj: seg038.asm $(INCLUDES)
	$(ASM) seg038.asm , $<

$(OBJDIR)\seg039.obj: seg039.asm $(INCLUDES)
	$(ASM) seg039.asm , $<

$(OBJDIR)\seg041.obj: seg041.asm $(INCLUDES)
	$(ASM) seg041.asm , $<

$(OBJDIR)\dseg.obj dseg.inc: dseg.asm
	$(ASM) dseg.asm, $<

clean:
	del $(OBJDIR)\seg*.obj
	del $(OBJDIR)\dseg*.obj
