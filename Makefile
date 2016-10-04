
HADOOP_INSTALL = /usr/usc/hadoop/default
HADOOP_C_LIB = /home/rcf-40/renchen/Hadoop-1.1.2-on-USC-HPCC-Cluster/hadoop_c_libs
CC = gcc 
CXX = g++

PLATFORM = Linux-amd64-64
LIBS = -lhadooppipes -lhadooputils -lssl -lpthread

CPPFLAGS = -Wall -g -O2 -I$(HADOOP_C_LIB)/include
LDFLAGS = -L$(HADOOP_C_LIB)/lib $(LIBS)

all: wordcount karma_counter

wordcount: wordcount.cc
	$(CXX) $(CPPFLAGS) $< -o $@ $(LDFLAGS)

karma_counter: karma_counter.cc
	$(CXX) $(CPPFLAGS) $< -o $@ $(LDFLAGS)

clean:
	/bin/rm -f wordcount karma_counter

squeaky: clean
	/bin/rm -rf zarathustra-out
