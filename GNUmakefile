# GNUmakefile
#		(c) S.Suzuki 2017.1.16 ————— patch 2017.9.14

NAME    := GraCraft

SUFFIX  := .cpp

SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./obj
EXE_DIR := ./bin

COMPILER:= g++

#==============================================#

# cross platform make
UNAME   := $(shell uname)
ifeq ($(UNAME), Darwin)
CFLAGS  += -Wall -O2 #-mmacosx-version-min=10.8
FRAME   := -framework GLUT -framework OpenGL 
endif
ifeq ($(UNAME), Linux)
CFLAGS  += -w -O2 -I/usr/X11R6/include -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lpthread
endif

OPTIONS := -I$(INC_DIR) $(CFLAGS) $(FRAME)

SOURCES := $(wildcard $(SRC_DIR)/*$(SUFFIX))
HEADERS := $(wildcard $(INC_DIR)/*.h)
OBJECTS := $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:%$(SUFFIX)=%.o)))
TARGETS := $(notdir $(basename $(SOURCES)))

TAR     := 0
TARNUM  := $(words $(TARGETS))

# make commands
.PHONY:all info build run clean
all: build 

build: info  $(NAME)
	@echo "\t————————————————————————————————————————————— "
	@echo "\t  Complete to create $(NAME) into $(EXE_DIR)  "
	@echo "\t     Let's try doing $(EXE_DIR)/$(NAME) !     "
	@echo "\t————————————————————————————————————————————— "

run:
	@echo " —— running $(NAME)"
	@$(EXE_DIR)/$(NAME)

info:
	@echo " Project : $(NAME)"
	@echo " Targets : $(TARGETS)"
	@echo

clean: 
	@echo " —— clean up objects"
	@$(RM) $(OBJECTS)

# create execute file 
$(NAME): $(OBJECTS)
	@echo " —— linking objects & create $(NAME)"
	@$(COMPILER) $(OPTIONS) -o $(EXE_DIR)/$@ $?

# compile objects (Pattern Rule)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(SUFFIX) $(HEADERS)
	$(eval TAR := $(shell python -c "print($(TAR)+1)"))
	@echo "[$(TAR)/$(TARNUM)]\t$(notdir $(basename $@))"
	@$(COMPILER) $(OPTIONS) -o $@ -c $<


