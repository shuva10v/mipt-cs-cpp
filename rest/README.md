## Build docker image

### Simple version

It works only on Linux:

1. Build app (cmake --build ...)
2. Build docker image:
```
docker build . -t simple_rest -f simple.Dockerfile 
```

### Builder image approach

Note: currently restbed has [a bug](https://github.com/Corvusoft/restbed/pull/484) in ARM build, works only on x86.

```
docker build . -t simple_rest -f builder.Dockerfile 
```

If you have ARM platform, use buildx:
```
docker buildx build --platform=linux/amd64  . -t simple_rest -f builder.Dockerfile 
```
