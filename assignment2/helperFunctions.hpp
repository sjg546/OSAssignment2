std::string hexConverter(std::string in, int pagesize){
  int y;
  std::stringstream stream;
  stream << in;
  stream >> std::hex >> y;
  return std::to_string(y/pagesize);
}

void incrementAge(std::vector<MemoryItem*> memory){
  for(int i = 0; i < memory.size();i++){
    memory[i]->age++;
  }
}

void incrementWorked(std::vector<MemoryItem*> memory){
  for(int i = 0; i < memory.size();i++){
    memory[i]->worked++;
  }
}

int getOldest(std::vector<MemoryItem*> memory){
  int max = 0;
  int ret = 0;
  for(int i = 0; i < memory.size();i++){
    if(memory[i]->age > max){
      max = memory[i]->age;
      ret = i;
    }
  }
  return ret;
}

int getOldestWorked(std::vector<MemoryItem*> memory){
  int max = 0;
  int ret = 0;
  for(int i = 0; i < memory.size();i++){
    if(memory[i]->worked > max){
      max = memory[i]->worked;
      ret = i;
    }
  }
  return ret;
}

int checkIsInMemory(std::vector<MemoryItem*> memory,int pageSize, std::string trace){
  for(int i = 0; i < memory.size();i++){
    if(memory[i]->value == trace){
      return i;
    }
  }
  return -1;
}

void shiftBits(std::vector<MemoryItem*> memory){
  for(int i = 0; i < memory.size();i++){
    for(int j = memory[0]->arbBits.size()-1; j > 0 ; j-- ){
      memory[i]->arbBits[j] = memory[i]->arbBits[j-1];
    }
    memory[i]->arbBits[0] = '0';
  }
}
void wsarbShiftBits(std::vector<MemoryItem*> memory){
  for(int i = 0; i < memory.size();i++){
    for(int j = memory[0]->wsarbBits.size()-1; j > 0 ; j-- ){
      memory[i]->wsarbBits[j] = memory[i]->wsarbBits[j-1];
    }
    memory[i]->wsarbBits[0] = '0';
  }
}

int arbReplacementFind(std::vector<MemoryItem*> memory){
  std::vector<int> references = {};
  std::vector<MemoryItem*> item;

  unsigned long long int min = 1000000000000000;
  unsigned long long output;
  for(int i = 0; i<memory.size();i++){
     output = std::stoull(memory[i]->arbBits, 0, 2);
     // std::cerr<<output<<" ";

    if(output < min){
      min = output;
      item.clear();
      references.clear();
      item.push_back(memory[i]);
      references.push_back(i);
    }else if(output == min){
      item.push_back(memory[i]);
      references.push_back(i);
    }
  }


  if(references.size() == 1){
    return references[0];
  }else{
    int oldref = 0;
    int oldest = 0;
    for(int i = 0; i < item.size();i++){
      if(memory[references[i]]->age > oldest){
        oldest = memory[references[i]]->age;
        oldref = references[i];
      }

    }
    return oldref;
  }

}
int wsarbReplacementFind(std::vector<MemoryItem*> memory,std::vector<MemoryItem*> workingset){


  std::cout<<"hit";
  for(int i = 0; i<workingset.size();i++){
    std::cout<<workingset[i]->value<<" "<<workingset[i]->wsarbBits<<" ";
  }
  std::cout<<std::endl;

  return 1;
}
