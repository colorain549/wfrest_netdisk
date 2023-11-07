all:server client

server:
	g++ server.pb_skeleton.cc user.pb.cc -o $@ -lsrpc -lprotobuf -lworkflow

client:
	g++ client.pb_skeleton.cc user.pb.cc -o $@ -lsrpc -lprotobuf -lworkflow
user:
	g++ user.pb.cc testUser.cc -o testUser -lsrpc -lprotobuf -lworkflow

clean:
	rm -rf server client
