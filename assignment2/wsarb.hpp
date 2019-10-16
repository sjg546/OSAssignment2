void WSARB(std::vector<std::string> traces,int pageSize,int pagecount,int shiftbitnumber,int length, int size){
      Timing *timer = new Timing();
      int count = -1;
      Printer *printer = new Printer();
      std::vector<MemoryItem*> memory;
      std::vector<MemoryItem*> workingset;
      int curr = 0;
      int i = 0;
      int recTime = 1;
      while(i<traces.size()){
        wsarbShiftBits(workingset);
        if((recTime-1)%(length) == 0){
          shiftBits(memory);
          count++;
        }

        std::string temp = traces[i];
        std::string value = hexConverter(temp.erase(0,2),pageSize);

        if(traces[i][0] != '#'){
        printer->pushBackEmpty();
        curr = printer->times.size()-1;
        // std::cout<<curr<<std::endl;
        timer->events++;
        printer->times[curr] = "Time:  ";

        if(checkIsInMemory(memory,pagecount,value) == -1){
          timer->diskReads++;
          timer->pageFaults++;
          printer->hit_miss[curr] = " MISS:  ";
        }else{
          printer->hit_miss[curr] = " HIT:  ";
        }
        printer->page[curr] = printer->page[curr] + "page   " + value;
        MemoryItem *tempMemoryItem = new MemoryItem(value,shiftbitnumber);

        tempMemoryItem->arbBits[0] = '1';

        if(checkIsInMemory(workingset,pageSize,value) != -1){
          workingset[checkIsInMemory(workingset,pageSize,value)]->wsarbBits[0] = '1';
        }


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
            memory[inMemory]->arbBits[0] = '1';
            if(traces[i][0] == 'W'){
              memory[inMemory]->memoryBit = 1;
            }
          }else{

            int oldestItem = wsarbReplacementFind(memory,workingset);

            printer->page[curr] = printer->page[curr] + "    REPLACE:  page  " + memory[oldestItem]->value ;
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
          printer->frames[curr] = printer->frames[curr] + " " +memory[j]->value + " " + "(" + memory[j]->arbBits +")";
        }


        // std::cout<<recTime<<" "<<((size*count)-size)<<" "<<std::endl;

        if(recTime > ((size*count)-size)){
          if(checkIsInMemory(workingset,pageSize,value) == -1){
            // std::cout<<"hit";
            workingset.push_back(tempMemoryItem);
          }
        }
        std::cout<<"Time: "<<recTime<<" "<<value<<" "<<std::endl;
        for(int i = 0; i <workingset.size();i++){
          std::cout<<workingset[i]->value<<" ";
        }
        if((recTime+1)%length == 0){
          workingset.clear();
        }
        recTime++;

        incrementAge(memory);
      }
      else{
      }
      i++;

    }
      printer->printTiming();
      // timer->printOutput();


}
