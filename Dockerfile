FROM intersystemsdc/iris-community:latest

USER root

RUN apt-get update && \
    apt-get install -y gcc && \
    rm -rf /var/lib/apt/lists/*

COPY fastlookup.c /opt/fastlookup.c
RUN gcc -Wall -fPIC -shared -o /usr/lib/libfastlookup.so /opt/fastlookup.c && \
    chmod 755 /usr/lib/libfastlookup.so && \
    rm /opt/fastlookup.c

ENV LD_LIBRARY_PATH="/usr/lib:$LD_LIBRARY_PATH"

USER irisowner

COPY PrefixTrie /irisdev/app/PrefixTrie
COPY test /irisdev/app/test
COPY iris.script /tmp/iris.script

RUN iris start iris && \
    iris session iris < /tmp/iris.script && \
    iris stop iris quietly
