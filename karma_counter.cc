/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <algorithm>
#include <limits>
#include <string>
#include <iostream>
 
#include  "stdint.h"  
 
#include "hadoop/Pipes.hh"
#include "hadoop/TemplateFactory.hh"
#include "hadoop/StringUtils.hh"

const std::string USCID = "4844077297";
const std::string WORDCOUNT = "WORDCOUNT";
const std::string INPUT_WORDS = "INPUT_WORDS";
const std::string OUTPUT_WORDS = "OUTPUT_WORDS";
std::vector<std::string> hostnames;
static int index = 0;

class WordCountMap: public HadoopPipes::Mapper {
public:
  HadoopPipes::TaskContext::Counter* inputWords;
  
  WordCountMap(HadoopPipes::TaskContext& context) {
    inputWords = context.getCounter(WORDCOUNT, INPUT_WORDS);
	//std::cout<<"Get inputWords counter id"<<inputWords->getId()<<std::endl;
  }
  
  void map(HadoopPipes::MapContext& context) {
    char hostname[128];
    gethostname(hostname, sizeof(hostname));
	
    std::vector<std::string> words = 
      HadoopUtils::splitString(context.getInputValue(), " ");
    for(unsigned int i=0; i < words.size(); ++i) {
	  if(words[i] == USCID)
        context.emit(hostname, "1");
    }
    //context.incrementCounter(inputWords, 1);
	//HadoopPipes::TaskContext* cp_context = dynamic_cast<HadoopPipes::TaskContext *> (context);
	//context.emit(HadoopUtils::toString(inputWords->getId()), "1");
  }
};

class WordCountReduce: public HadoopPipes::Reducer {
public:
  HadoopPipes::TaskContext::Counter* outputWords;

  WordCountReduce(HadoopPipes::TaskContext& context) {
    outputWords = context.getCounter(WORDCOUNT, OUTPUT_WORDS);
	//std::cout<<"Get outputWords counter id"<<outputWords->getId()<<std::endl;
  }

  void reduce(HadoopPipes::ReduceContext& context) {
    //const HadoopPipes::JobConf* job = context.getJobConf();
	//int part = job->getInt("mapred.task.partition");
	//std::string outDir = job->get("mapred.work.output.dir");
	
	if(hostnames.size()!=0){
	  if(hostnames[index] != context.getInputKey()){
	    hostnames.push_back(context.getInputKey());
		index++;
	  }	    
	}
	else
	  hostnames.push_back(context.getInputKey());
	  
    int sum = 0;
    while (context.nextValue()) {
      sum += HadoopUtils::toInt(context.getInputValue());
	  //context.emit(HadoopUtils::toString(outputWords->getId()), HadoopUtils::toString(sum));
    }
	//if(context.getInputKey() == "4844077297")
    
	context.incrementCounter(outputWords, 1); 
	std::string pre_key = "id = ";
	std::string key = pre_key + USCID;
	std::string value = "node"+ HadoopUtils::toString(index) + ": "+ HadoopUtils::toString(sum);
	context.emit(key, value);
    //context.incrementCounter(outputWords, 1); 
	//HadoopPipes::TaskContext* cp_context = dynamic_cast<HadoopPipes::TaskContext *>(context);
	//context.emit(HadoopUtils::toString(outputWords->getId()), "2");
	//context.emit(outDir, "3");
	//context.emit(HadoopUtils::toString(part), "4");
	//std::cout<<"Get input key"<<context.getInputKey()<<std::endl;	
  }
};

int main(int argc, char *argv[]) {
  return HadoopPipes::runTask(HadoopPipes::TemplateFactory<WordCountMap, 
                              WordCountReduce>());
}