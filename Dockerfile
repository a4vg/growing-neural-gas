FROM m03geek/ffmpeg-opencv:alpine-3.4.1

# Install dependencies
RUN apk update && apk add \
    cmake \
    make \
    g++

# Create and set working directory
WORKDIR /gng

# Copy project
COPY main.cpp CMakeLists.txt /gng/
ADD src /gng/src
ADD include /gng/include
ADD sample-imgs /gng/sample-imgs
RUN mkdir build output && \
    cd build && \
    cmake .. && \
    make

# Default command
CMD ["/bin/sh"]