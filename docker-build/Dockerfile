FROM ubuntu:20.04
RUN apt-get update && \
    apt-get -y install sudo qpdf && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
COPY entrypoint /entrypoint
RUN chmod +x /entrypoint
ENTRYPOINT [ "/entrypoint" ]
