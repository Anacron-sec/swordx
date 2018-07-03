FROM gcc:8
COPY . /usr/src/swordx
WORKDIR /usr/src/swordx
RUN make

FROM alpine:latest
RUN mkdir /data
VOLUME [ "/data" ]
WORKDIR /root/
COPY --from=0 /usr/src/swordx/bin/swordx .
CMD [ "./swordx" ]