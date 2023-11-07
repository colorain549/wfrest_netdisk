LIBS:= -lsrpc -lprotobuf -lworkflow -lcrypt -lppconsul -lcurl

all: rpc_server client

rpc_server: user.pb.o server.pb_skeleton.o
	g++ $^ -o $@ $(LIBS)

client: user.pb.o client.pb_skeleton.o
	g++ $^ -o $@ $(LIBS)

%.o:%.cc
	g++ -c $^ -o $@ $(LIBS)

clean:
	rm -rf *.o rpc_server client

