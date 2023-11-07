INCLUDES:=./
SRCS:=$(wildcard *.cc)
LIBS:=  -lwfrest -lworkflow -lssl -lcrypto -lcrypt -std=c++11 -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl -lpthread -lSimpleAmqpClient 
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
SERVER:=server

$(SERVER): server.o token.o hash.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

%.o:%.cc
	g++ -c $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

HASH:=hash
TOKEN:=token

$(HASH): hash.o testhash.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

$(TOKEN): token.o testToken.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g


clean:
	rm -rf $(OBJS) $(SERVER) $(HASH) $(TOKEN)

