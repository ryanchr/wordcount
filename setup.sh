if [ ! "${USCENV_HADOOP}" ] ; then
  USCENV_HADOOP=1 ; export USCENV_HADOOP

  HADOOP_VERSION=1.1.2
  JAVA_PATH=/usr/lib/jvm/java-1.6.0-openjdk-1.6.0.34.x86_64/jre/bin
  JAVA_HOME=/usr/lib/jvm/java-1.6.0-openjdk-1.6.0.34.x86_64/jre

  prefix=/usr/usc/hadoop/$HADOOP_VERSION
  _bindir=$prefix/bin

  export HADOOP_VERSION
  export JAVA_HOME
  if [ -n "$PATH" ]; then
    PATH=$_bindir:$JAVA_PATH:$PATH
  else
    PATH=$_bindir:$JAVA_PATH
  fi
  export PATH

fi
