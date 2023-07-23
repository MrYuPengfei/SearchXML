# g++ src/server/*.cpp src/server/net/*.cpp src/server/threadpool/*.cpp src/common/*.cpp -o bin/server -lpthread -L /usr/local/lib /usr/local/lib/libjsoncpp.a  -Wall
# g++ src/prepare/*.cpp src/common/*.cpp -o bin/prepare -Wall
# g++ src/client/client.cpp -o bin/client -Wall -L /usr/local/lib /usr/local/lib/libjsoncpp.a
CC:=g++
prepare:=./bin/prepare
server:=./bin/server
client:=./bin/client
all_target:=$(prepare) $(server) $(client)
CCFLAGS:=-g -Wall 
#RELESE CCFLAGS=-Wall -std=c++17
common_src:=$(wildcard ./src/common/*.cpp) 
prepare_src:=$(wildcard ./src/prepare/*.cpp) 
server_src:=$(wildcard ./src/server/*.cpp) $(wildcard ./src/server/net/*.cpp) $(wildcard ./src/server/threadpool/*.cpp)
client_src:=$(wildcard ./src/client/*.cpp)
jsoncpp_src:=$(wildcard ./src/json/*.cpp)
common_obj:=$(patsubst %.cpp, %.o, $(common_src))
prepare_obj:=$(patsubst %.cpp, %.o, $(prepare_src))
server_obj:=$(patsubst %.cpp, %.o, $(server_src))
client_obj:=$(patsubst %.cpp, %.o, $(client_src))
jsoncpp_obj:=$(patsubst %.cpp, %.o, $(jsoncpp_src))
all_obj:=$(common_obj) $(prepare_obj) $(server_obj) $(client_obj) $(jsoncpp_obj) 
server_link:=-lpthread #  -L /usr/local/lib /usr/local/lib/libjsoncpp.a
all:$(all_target)
$(prepare):$(prepare_obj) $(common_obj) $(jsoncpp_obj)
	$(CC) $(CCFLAGS) $(common_obj) $(prepare_obj) $(jsoncpp_obj) -o $@ 
# %.o:%.cpp
# 	$(CC) -c $^ -o $@ $(CCFLAGS)
$(server):$(server_obj) $(common_obj) $(jsoncpp_obj)
	$(CC) $(CCFLAGS) $(common_obj) $(jsoncpp_obj)  $(server_obj) -o $@ $(server_link) 
# %.o:%.cpp
# 	$(CC) -c $^ -o $@ $(CCFLAGS)
$(client):$(client_obj) $(jsoncpp_obj) 
	$(CC) $(CCFLAGS) $(client_obj) $(jsoncpp_obj) -o $@ $(server_link)
#$(client_obj):$(client_src)
#	$(CC) $(CCFLAGS) -c $< -o $@ 
%.o:%.cpp
	$(CC) -c $^ -o $@ $(CCFLAGS)
clean:
	rm -rf $(all_target) $(all_obj)
