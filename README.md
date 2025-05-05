# Network chat (userver)

## Building using a MakeFile

```bash
make all            #  Build and test in debug and release modes
make cmake-<preset> #  Run CMake with the specified preset (debug/release)
make build-<preset> #  Build a project with the specified preset
make test-<preset>  #  Run tests for the specified preset
```
## Starting the server

```bash
make start-<preset> #  Run server
```

## Client connections

```bash
wscat --connect ws://localhost:8080/chat
```


## Additional dependencies

```bash
sudo apt install node-ws   # wscat
```