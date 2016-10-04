##Steps to compile the source file and test:
1. Make sure WORK_HOME=/auto/rcf-40/renchen/Hadoop-1.1.2-on-USC-HPCC-Cluster
2. cd $WORK_HOME
3. chmod 777 setup-and-start-hadoop-on-hpcc
##Run wordcount
4. make wordcount
5. qsub wordcount.pbs
##Run karmacount
6. make karma_counter
7. qsub karma_counter.pbs