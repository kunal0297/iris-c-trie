FROM intersystemsdc/iris-community:latest

USER root
RUN apt-get update && apt-get install -y gcc

COPY fastlookup.c /opt/fastlookup.c
RUN gcc -fPIC -shared -o /usr/lib/libfastlookup.so /opt/fastlookup.c
RUN chmod 755 /usr/lib/libfastlookup.so

USER irisowner
COPY iris.script /tmp/iris.script
RUN iris start iris && iris session iris < /tmp/iris.script && iris stop iris quietly
