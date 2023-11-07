# INCLUDES:=./
# SRCS:=$(wildcard *.cc)
# LIBS:=  -lwfrest -lworkflow -lssl -lcrypto -lcrypt -std=c++11 -lalibabacloud-oss-cpp-sdk -lcurl -lpthread -lSimpleAmqpClient -lsrpc -lprotobuf -lppconsul
# OBJS:=$(patsubst %.cc, %.o, $(SRCS))
# SERVER:=server

# $(SERVER): server.o token.o hash.o
# 	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

# %.o:%.cc
# 	g++ -c $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

# HASH:=hash
# TOKEN:=token

# $(HASH): hash.o testhash.o
# 	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

# $(TOKEN): token.o testToken.o
# 	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g


# clean:
# 	rm -rf $(OBJS) $(SERVER) $(HASH) $(TOKEN)

INCLUDES:=./
SRCS:=$(wildcard *.cc)
LIBS:= -lwfrest -lworkflow -lssl -lcrypto -lcrypt -lpthread -lSimpleAmqpClient -lsrpc -lprotobuf -lalibabacloud-oss-cpp-sdk -lcurl
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
ABLIBABALIBS:= -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl
SERVER:=wfrest_server.exe

$(SERVER): server.o hash.o token.o user.pb.o 
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

%.o:%.cc
	g++ -c $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

hash.exe:
	g++ hash.cc testHash.cc -o $@ -lssl -lcrypto
token.exe:
	g++ token.cc testToken.cc -o $@ -lssl -lcrypto
consumer.exe:
	g++ consumer.cc oss.cc -o $@ $(ABLIBABALIBS) $(LIBS)

clean:
	rm -rf $(OBJS) $(SERVER) hash token