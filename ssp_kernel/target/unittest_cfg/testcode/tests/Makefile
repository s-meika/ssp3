#
#  コンフィギュレータ単体テスト用の Makefile
#
-include Makefile.depend
include ../cfgs/Makefile

# 変数宣言
INCLUDES := $(INCLUDES) -I/opt/local/include/ -I../cfgs -I$(SRCDIR)/kernel -I$(EXTPKG_DIR)

#CC = gcc
CFLAGS := $(CFLAGS) -DNDEBUG
#LDFLAGS := $(LDFLAGS)
LIB = -L/opt/local/lib -lcunit -lncurses
#COPTS := $(COPTS)

TEST_C = $(wildcard test_*.c)
TEST_OBJ = $(TEST_C:.c=.o)
TEST_EXE = $(TEST_C:.c=.exe)
MAIN_OBJ = main.o
KERNEL_CFG_OBJ = $(TEST_C:.c=_kernel_cfg.o)
KERNEL_OBJ = task.o task_manage.o interrupt.o exception.o sys_manage.o  \
                                startup.o time_event.o alarm.o cyclic.o \
				eventflag.o dataqueue.o \
								target_config.o

vpath %.c  ../cfgs $(SRCDIR)/kernel $(SRCDIR)/extenstion $(SRCDIR)/target/$(TARGETDIR)
vpath %.cpp ../cfgs

$(TEST_EXE): $(@:.exe=.o) $(MAIN_OBJ) $(@:.exe=_kernel_cfg.o) $(KERNEL_OBJ)
	$(CC) -o ../bins/$@ $(CFLAGS) $(COPTS) $(LDFLAGS) $(@:.exe=.o) $(MAIN_OBJ) $(@:.exe=_kernel_cfg.o) $(KERNEL_OBJ) $(LIB)

clean_codes :
	@rm -rf $(KERNEL_OBJ) $(TEST_OBJ) $(TEST_EXE) $(MAIN_OBJ) $(KERNEL_CFG_OBJ) 
	@rm -rf *~
	@rm -rf cfg1_out*

.PHONY: $(MAIN_OBJ) $(TEST_OBJ) $(KERNEL_CFG_OBJ)
$(MAIN_OBJ) $(TEST_OBJ) $(KERNEL_CFG_OBJ): %.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $<

depend : $(TEST_OBJ:.o=.c) $(TEST_MAIN:.o=.cpp)
	touch Makefile.depend
	makedepend $(INCLUDES) $? -f Makefile.depend 2> /dev/null

