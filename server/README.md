#server


make build-release
make start-release


wscat --connect ws://localhost:8080/chat
