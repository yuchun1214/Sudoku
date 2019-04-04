

# Define c++ compiler
# The Compiler which allow to compile program : g++ icpc

COMPILER = g++ --std=c++14



# library : 

all : generate solve transform

generate : 
	$(COMPILER) -o generate generate.cpp

solve : 
	$(COMPILER) -o solve solve.cpp

transform : 
	$(COMPILER) -o transform transform.cpp


