## Build docker image

### Simple version

It works only on Linux:

1. Build app (cmake --build ...)
2. Build docker image:
```
docker build . -t simple_rest -f simple.Dockerfile 
```

### Builder image approach

```
docker build . -t simple_rest -f builder.Dockerfile 
```
