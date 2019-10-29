FROM ubuntu:18.04 as builder

RUN apt update \
   && apt install -y build-essential curl git g++ libncurses5-dev cmake

RUN    mkdir -p ~/opt/src \
    && cd ~/opt/src \
    && git clone https://github.com/Boskim0n0/lte-gtp-simulator.git

RUN    cd ~/opt/src/lte-gtp-simulator \
    && mkdir build \
	&& cd build \
	&& cmake .. \
	&& make
	
RUN    tar czf /root/bin.tgz ~/opt/src/lte-gtp-simulator/build/gsim \
    && tar czf /root/scenarios.tgz ~/opt/src/lte-gtp-simulator/scenario/* \
    && tar czf /root/pkg.tgz /root/scenarios.tgz /root/bin.tgz

FROM ubuntu:18.04 as distro

RUN    apt update \
	&& apt install -y ksh locales \
    && apt upgrade -y \	
	&& apt install -y vim \	
	&& apt-get install -y tcpdump \
    && locale-gen en_US.UTF-8 \
    && dpkg-reconfigure --frontend noninteractive locales \
    && rm -rf /var/lib/apt/lists/*
	
COPY --from=builder /root/pkg.tgz /root/pkg.tgz

RUN    tar xzf /root/pkg.tgz -C /root --strip=1 \
	&& mkdir -p /opt/LTE-GTP-Simulator \
	&& mkdir -p /opt/LTE-GTP-Simulator/scenarios \
    && tar xzf /root/bin.tgz -C /opt/LTE-GTP-Simulator --strip=5 \    
    && tar xzf /root/scenarios.tgz -C /opt/LTE-GTP-Simulator/scenarios --strip=5	
