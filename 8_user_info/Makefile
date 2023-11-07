# server:
# 	g++ server.cc -o server -lworkflow -lwfrest -lssl -lcrypto -lcrypt

# clean:
# 	rm -rf server


INCLUDES:=./
SRCS:=$(wildcard *.cc)
LIBS:=  -lwfrest -lworkflow -lssl -lcrypto -lcrypt
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
SERVER:=server

$(SERVER): server.o token.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

%.o:%.cc
	g++ -c $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

TOKEN:=token

$(TOKEN): token.o testToken.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

clean:
	rm -rf $(OBJS) $(SERVER) $(TOKEN)
