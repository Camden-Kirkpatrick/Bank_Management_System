ifeq ($(OS), Windows_NT)
    SHELL := cmd.exe

    RM_DIR  = rmdir /S /Q
    RM_FILE = del
    MKDIR   = mkdir
    EXE     = main.exe
else
    RM_DIR  = rm -rf
    RM_FILE = rm -f
    MKDIR   = mkdir -p
    EXE     = main
endif

CPPFLAGS := -std=c++20
OBJDIR   := bin

SOURCES  := main bank customer bank_account transaction utilities
OBJECTS  := $(SOURCES:%=$(OBJDIR)/%.o)

all: $(EXE)

$(EXE): $(OBJECTS)
	g++ $(CPPFLAGS) $^ -o $@

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c $< -o $@

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	$(RM_DIR) $(OBJDIR)
	$(RM_FILE) $(EXE)
