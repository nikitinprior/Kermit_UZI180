########################################################################
#
#  Use this Makefile to build the ZAS for HiTech C v3.09 under Linux
#  using John Elliott's zxcc emulator.
#
########################################################################
TARGET = kermit
CSRCS = uxkermit.c uxconu.c uxkerunx.c sleep.c
HDRS  = sgtty.h uxkermit.h

OBJS = $(CSRCS:.c=.obj)


ifeq ($(OS),Windows_NT)
RM = del /q
else
RM = rm -f
endif

all:	$(TARGET)

.SUFFIXES:		# delete the default suffixes
.SUFFIXES: .c .obj

%.obj: %.c
	zxc -c -O  $<


$(TARGET): $(OBJS)
	$(file >$@.in,-Z -Dkermit.sym -N -C -Mkermit.map -Ptext=0,data,bss -C100H -OP:$@ crtuzi.obj \)
	$(foreach O,$(OBJS),$(file >>$@.in,P:$O \))
	$(file >>$@.in,LIBCUZI.LIB)
	zxcc linq <$@.in
	$(RM) $@.in

$(OBJS) : $(HDRS)

clean:
	$(RM) $(OBJS) *.map *.sym *.sym.sorted

compress:
	enhuff -a KERMIT.HUF makefile $(CSRCS) $(HDRS)

