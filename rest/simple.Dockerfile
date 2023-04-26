FROM ubuntu:20.04

ADD build/rest_server /opt/rest/rest_server

CMD ["/opt/rest/rest_server"]