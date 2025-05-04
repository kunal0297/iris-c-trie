FROM intersystemsdc/iris-community:latest

# Switch to root to install build tools
USER root

# Install gcc and clean up to reduce image size
RUN apt-get update && apt-get install -y gcc && rm -rf /var/lib/apt/lists/*

# Copy C source code
COPY fastlookup.c /opt/fastlookup.c

# Compile to a shared object and set appropriate permissions
RUN gcc -fPIC -shared -o /usr/lib/libfastlookup.so /opt/fastlookup.c && \
    chmod 755 /usr/lib/libfastlookup.so

# Optional: Set library path (IRIS already uses standard paths like /usr/lib, but just in case)
ENV LD_LIBRARY_PATH="/usr/lib:$LD_LIBRARY_PATH"

# Switch back to irisowner
USER irisowner

# Copy your ObjectScript and support files
COPY PrefixTrie /irisdev/app/PrefixTrie
COPY test /irisdev/app/test
COPY iris.script /tmp/iris.script

# Pre-load and run the script during image build
RUN iris start iris && \
    iris session iris < /tmp/iris.script && \
    iris stop iris quietly
