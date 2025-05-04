FROM intersystemsdc/iris-community:latest

# Switch to root to install build tools
USER root

# Install gcc, compile shared object, and clean up
RUN apt-get update && \
    apt-get install -y gcc && \
    rm -rf /var/lib/apt/lists/*

# Copy and compile C source code
COPY fastlookup.c /opt/fastlookup.c
RUN gcc -Wall -fPIC -shared -o /usr/lib/libfastlookup.so /opt/fastlookup.c && \
    chmod 755 /usr/lib/libfastlookup.so && \
    rm /opt/fastlookup.c

# Set library path
ENV LD_LIBRARY_PATH="/usr/lib:$LD_LIBRARY_PATH"

# Switch back to irisowner
USER irisowner

# Copy ObjectScript source and script
COPY PrefixTrie /irisdev/app/PrefixTrie
COPY test /irisdev/app/test
COPY iris.script /tmp/iris.script

# Compile ObjectScript during build
RUN iris start iris && \
    iris session iris < /tmp/iris.script && \
    iris stop iris quietly
