######################################
# makefile for programs and generators
######################################

CCOMP1 = gcc
CCOMP2 = g++

all: progs gens

# problem generators
gens: bin/sprand 

bin/sprand: src/sprand.c src/random.c
	$(CCOMP1) -o bin/sprand src/sprand.c
	
# shortest paths programs
progs:bin/dikh_run bin/dikdl_run bin/dikds_run bin/bf_run bin/pape_run bin/fwa_run bin/fwg_run

bin/dikh_run: src/dikh_run.cpp 
	$(CCOMP2) -o bin/dikh_run src/dikh_run.cpp
	
bin/dikds_run: src/dikds_run.cpp 
	$(CCOMP2) -o bin/dikds_run src/dikds_run.cpp

bin/dikdl_run: src/dikdl_run.cpp 
	$(CCOMP2) -o bin/dikdl_run src/dikdl_run.cpp

bin/bf_run: src/bf_run.cpp 
	$(CCOMP2) -o bin/bf_run src/bf_run.cpp

bin/pape_run: src/pape_run.cpp 
	$(CCOMP2) -o bin/pape_run src/pape_run.cpp

bin/fwa_run: src/fwa_run.cpp 
	$(CCOMP2) -o bin/fwa_run src/fwa_run.cpp

bin/fwg_run: src/fwg_run.cpp 
	$(CCOMP2) -o bin/fwg_run src/fwg_run.cpp

