size_t maxSeq(int * array, size_t n){
  if (n <= 1){
    return n;
  }
  else{
    int count = 1;
    int best = 1;
    for (int i = 1; i < n; i++){
      if (array[i]>array[i-1]){
	count++;
      }
      else{
	if (count>best){
	  best = count;
	  count = 1;
	}
	else{
	  count = 1;
	}
      }
    }
  }
}
