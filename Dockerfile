FROM gcc:6.4.0 as builder
WORKDIR /tmp/
COPY . .
RUN make clean
RUN make

FROM ubuntu:bionic
WORKDIR /root/
COPY --from=builder /tmp/bin/swordx .
RUN mkdir /files
RUN mkdir /output
ENTRYPOINT [ "/root/swordx" , "/files", "-o", "/output/swordx.out"]
