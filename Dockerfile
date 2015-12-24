FROM gcc:5.3

RUN apt-get update && apt-get install -y \
    curl \
    unzip \
    cmake \
    qtbase5-dev \
    qtmultimedia5-dev \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    libxcb-image0-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev

# Boost
RUN curl -L \
    -o /boost.tar.bz2 \
    http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.bz2/download
RUN tar xf /boost.tar.bz2
RUN rm /boost.tar.bz2
WORKDIR boost_1_58_0/
RUN apt-get update && apt-get install -y \
    python-dev
RUN ./bootstrap.sh --with-libraries=program_options --with-libraries=python
RUN ./b2 -j4 --link=static --runtime-link=static
RUN ln -s /boost_1_58_0/stage/lib/libboost_program_options.a /usr/lib/x86_64-linux-gnu/
RUN ln -s /boost_1_58_0/stage/lib/libboost_python.a /usr/lib/x86_64-linux-gnu/
RUN ln -s /boost_1_58_0/boost/ /usr/include/x86_64-linux-gnu/

ENV BOOST_DIR /boost_1_58_0

# SFML
RUN curl -L http://www.sfml-dev.org/files/SFML-2.3.2-sources.zip > /tmp/sfml.zip
WORKDIR /tmp
RUN unzip sfml.zip
WORKDIR SFML-2.3.2
RUN cmake .
RUN make -j4
RUN mv include/SFML/ /usr/include/
RUN mv lib/* /usr/lib/x86_64-linux-gnu/
