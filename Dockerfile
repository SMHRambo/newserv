# syntax=docker/dockerfile:1

ARG ALPINE_VERSION=3.20

FROM alpine:${ALPINE_VERSION} AS builder
WORKDIR /build
COPY . /build
RUN \
  echo "**** install dependencies ****" && \
  apk upgrade && \
  apk add --no-cache \
    git \
    libevent-dev \
    zlib-dev \
#    libc-dev \
    build-base \
    python3 \
#    make \
#    gcc \
#    g++ \
    cmake && \
  echo "**** cleanup ****" && \
  rm -rf \
    /tmp/*
 WORKDIR /build
 RUN \
   echo "**** clone, build and install PHOSG ****" && \
   git clone https://github.com/fuzziqersoftware/phosg.git && \
   cd phosg && \
   cmake . && \
   make && \
   make install
 WORKDIR /build
 RUN \
   echo "**** clone, build and install resource_dasm ****" && \
   git clone https://github.com/fuzziqersoftware/resource_dasm.git && \
   cd resource_dasm && \
   cmake . && \
   make && \
   make install
 WORKDIR /build
 RUN \
   echo "**** build and install newserv ****" && \
   cmake . && \
   make


########### Linuxserver.io alpinebase ###########
FROM ghcr.io/linuxserver/baseimage-alpine:${ALPINE_VERSION}

# set version label
ARG BUILD_DATE
ARG VERSION
LABEL build_version="Linuxserver.io version:- ${VERSION} Build-date:- ${BUILD_DATE}"
LABEL maintainer="smhrambo"

RUN \
  echo "**** install dependencies ****" && \
  apk upgrade && \
  apk add --no-cache \
    libevent \
    zlib && \
  echo "**** cleanup ****" && \
  rm -rf \
    /tmp/*

# add bin files
COPY --from=builder /build/newserv /app/newserv

# add system files
COPY --from=builder /build/system /default

RUN \
  mkdir -p /{config,data} && \
  ln -s /data /app/system

# add local files
COPY root/ /

WORKDIR /app
