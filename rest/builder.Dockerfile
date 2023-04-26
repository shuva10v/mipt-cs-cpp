FROM ubuntu:22.04 as builder

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install git -y build-essential cmake make g++ curl zip unzip tar ninja-build
ADD server.cpp /sources/
ADD CMakeLists.txt /sources/
ADD vcpkg.json /sources/

WORKDIR /sources/
RUN git clone https://github.com/microsoft/vcpkg.git
WORKDIR /sources/vcpkg
ENV VCPKG_FORCE_SYSTEM_BINARIES=1
RUN ./bootstrap-vcpkg.sh

WORKDIR /build
RUN cmake /sources
RUN cmake --build .

FROM ubuntu:22.04
COPY --from=builder /build/target/rest_server  /opt/rest/rest_server

CMD ["/opt/rest/rest_server"]
# CMD ["bash"]