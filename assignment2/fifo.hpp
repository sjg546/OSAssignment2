void FIFO(std::vector<std::string> traces,int pagecount,int pageSize){
  Timing *timer = new Timing();
  int count = 0;
  Printer *printer = new Printer();
  std::vector<MemoryItem*> memory;
  int curr = 0;
  int i = 0;
  int recTime = 1;
  while(i<traces.size()){
    std::string temp = traces[i];
    std::string value = hexConverter(temp.erase(0,2),pageSize);

    if(traces[i][0] != '#'){
    printer->pushBackEmpty();
    curr = printer->times.size()-1;
    // std::cout<<curr<<std::endl;
    timer->events++;
    printer->times[curr] = "Time:  ";
    recTime++;

    if(checkIsInMemory(memory,pagecount,value) == -1){
      timer->diskReads++;
      timer->pageFaults++;
      printer->hit_miss[curr] = " MISS:  ";
    }else{
      printer->hit_miss[curr] = " HIT:  ";
    }
    printer->page[curr] = printer->page[curr] + "page   " + value;
    MemoryItem *tempMemoryItem = new MemoryItem(value);
    if(memory.size() < pagecount){
      if(checkIsInMemory(memory,pagecount,traces[i]) == -1){
        if(traces[i][0] == 'W'){
          tempMemoryItem->memoryBit = 1;
        }
        memory.push_back(tempMemoryItem);
      }
    }else{
      int inMemory = checkIsInMemory(memory,pagecount,tempMemoryItem->value);
      if(inMemory != -1){
        if(traces[i][0] == 'W'){
          memory[inMemory]->memoryBit = 1;
        }
      }else{
        int oldestItem = getOldest(memory);
        printer->page[curr] = printer->page[curr] + "    REPLACE:  page  " + memory[oldestItem]->value;
        if(traces[i][0] == 'W'){
          tempMemoryItem->memoryBit = 1;
        }
        if(memory[oldestItem]->memoryBit == 1){
          timer->diskWrites++;
          printer->page[curr] = printer->page[curr] + " (DIRTY)";
        }
        memory[oldestItem] = tempMemoryItem;
      }
    }
    printer->frames[curr] = " Frames: ";

    for(int j = 0 ; j<memory.size();j++){
      printer->frames[curr] = printer->frames[curr] + " " +memory[j]->value + " ";
    }
    incrementAge(memory);
  }
  else{
  }
  i++;

}
  // printer->printTiming();
  timer->printOutput();
}
