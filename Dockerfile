FROM intersystemsdc/iris-community:latest

USER root
RUN apt-get update && apt-get install -y gcc

COPY fast_lookup.c /opt/fast_lookup.c
RUN gcc -fPIC -shared -o /usr/lib/libfastlookup.so /opt/fast_lookup.c
RUN chmod 755 /usr/lib/libfastlookup.so

USER irisowner
COPY iris.script /tmp/iris.script
RUN iris session iris < /tmp/iris.script
