if [ ! "${USCENV_HADOOP}" ] ; then
  USCENV_HADOOP=1 ; export USCENV_HADOOP

  HADOOP_VERSION=default
  JAVA_PATH=/usr/lib/jvm/java-1.6.0-openjdk.x86_64/jre/bin
  JAVA_HOME=/usr/lib/jvm/java-1.6.0-openjdk.x86_64/jre

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
