# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall

# Executable name
EXEC = mainMenu

# Source files
SOURCES = menuItem.cpp foodItem.cpp veganItem.cpp \
          drinkItem.cpp alcoholDrink.cpp order.cpp alcFreeDrink.cpp \
          nonVeganItem.cpp customer.cpp cashPayment.cpp cardPayment.cpp table.cpp \
          payment.cpp reservation.cpp main.cpp UI.cpp takeaway.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = menuItem.h foodItem.h veganItem.h drinkItem.h alcoholDrink.h \
          order.h alcFreeDrink.h nonVeganItem.h customer.h \
          cashPayment.h cardPayment.h table.h payment.h reservation.h UI.h takeaway.h

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

# Compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(EXEC) $(OBJECTS)