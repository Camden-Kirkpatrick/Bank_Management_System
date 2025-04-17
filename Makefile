CXX      := g++
CPPFLAGS := -std=c++20
OBJDIR   := bin

SOURCES  := main bank customer bank_account transaction utilities
OBJECTS  := $(SOURCES:%=$(OBJDIR)/%.o)

RM_DIR  := rm -rf
RM_FILE := rm -f
MKDIR   := mkdir -p
EXE     := main.exe

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $^ -o $@

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

clean:
	-$(RM_DIR) $(OBJDIR)
	-$(RM_FILE) $(EXE)
