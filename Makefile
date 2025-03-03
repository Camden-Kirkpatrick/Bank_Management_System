CPPFLAGS = -std=c++20
OBJDIR = bin

all: main

main: $(OBJDIR)/main.o $(OBJDIR)/bank.o $(OBJDIR)/customer.o $(OBJDIR)/bank_account.o $(OBJDIR)/transaction.o $(OBJDIR)/utilities.o
	g++ $(CPPFLAGS) $(OBJDIR)/main.o $(OBJDIR)/bank.o $(OBJDIR)/customer.o $(OBJDIR)/bank_account.o $(OBJDIR)/transaction.o $(OBJDIR)/utilities.o -o main

$(OBJDIR)/main.o: src/main.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c src/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/bank.o: src/bank.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c src/bank.cpp -o $(OBJDIR)/bank.o

$(OBJDIR)/customer.o: src/customer.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c src/customer.cpp -o $(OBJDIR)/customer.o

$(OBJDIR)/bank_account.o: src/bank_account.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c src/bank_account.cpp -o $(OBJDIR)/bank_account.o

$(OBJDIR)/transaction.o: src/transaction.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c src/transaction.cpp -o $(OBJDIR)/transaction.o

$(OBJDIR)/utilities.o: src/utilities.cpp | $(OBJDIR)
	g++ $(CPPFLAGS) -c src/utilities.cpp -o $(OBJDIR)/utilities.o

# Ensure bin/ directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) main

