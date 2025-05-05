FROM intersystemsdc/iris-community:latest

# Switch to root for software installation
USER root

# Install GCC to compile shared object
RUN apt-get update && \
    apt-get install -y gcc && \
    rm -rf /var/lib/apt/lists/*

# Copy C source and compile shared object
COPY fastlookup.c /opt/fastlookup.c
RUN gcc -Wall -fPIC -shared -o /usr/lib/libfastlookup.so /opt/fastlookup.c && \
    chmod 755 /usr/lib/libfastlookup.so && \
    rm /opt/fastlookup.c

# Ensure shared library is discoverable
ENV LD_LIBRARY_PATH="/usr/lib:$LD_LIBRARY_PATH"

# Return to irisowner user
USER irisowner

# Copy your ObjectScript source and initialization script
COPY PrefixTrie /irisdev/app/PrefixTrie
COPY test /irisdev/app/test
COPY iris.script /tmp/iris.script

# Run ObjectScript compilation
RUN iris start iris && \
    iris session iris < /tmp/iris.script && \
    iris stop iris quietly
