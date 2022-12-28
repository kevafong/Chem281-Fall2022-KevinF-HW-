// Create a parallel region. Make all the predefined variables shared
  int i, threadno, numthread, chunkstart, chunkend, chunksize = 0;
  
  // by default - hint: use the clause default(shared)
  #pragma omp parallel default(shared)
  {
    // partition the array into as many subarray chunks as number_of_threads

    // compute the chunk size to be assigned to each thread
    threadno = omp_get_thread_num();
    numthread = omp_get_num_threads();
    chunksize = l/numthread;
    
    // For each threads
    
    // compute the beginning and end (length) of the corresponding
    chunkstart = threadno * chunksize;
    if (threadno == numthread-1)
      chunksize = l - chunkstart;
    chunkend = chunkstart + chunksize;
    // partition of the array. hint: You can use the thread number to
    // compute the corresponding chunk.
    // Caution: the length of the last chunk may be different from the
    // length of the other chunks if the size of the data is not a multiple
    // of the number of threads

    // for each thread serially accumulate the entries on its subarray/partition
    // as has been done in the serial loop for s above
    for (i = chunkstart+1; i < chunkend; i++) {
      v[i] += v[i-1];
    }
    // when done, store the accumulated value in the last entry of the thread's
    // into the corresponding entry of *locallast* array.
    // The location of this local maximum in the *locallast* array is
    // the thread number plus 1

    locallast[threadno+1] = v[chunkend-1];
    
    // Next, you need to synchronize to ensure that all threads have completed
    // their task before moving to next step
    #pragma omp barrier
    // Next, create a serial region (single thread). You can use the master
    // thread to execute this region
    #pragma omp master
    {
    // in the serial region, accumulate all the values in *locallast* array
 
      for (i = 1; i < number_of_threads+1; i++) {
        locallast[i] += locallast[i-1];
      }
    }
    // All other threads must wait until the serial region finishes accumulating
    // the entries in *locallast* array. Synchronize again before proceeding
    // to the next step
    #pragma omp barrier
    // Now you need each thread has to loop over its array partition
    // to add to each entry in its local subarray the value of the
    // accumulated entry in the global array v corresponding to the entry
    // in v that immediately preceeds the first entry in the subarray of
    // v that the thread is processing.
    // This value to add is the value in *locallast* computed previously in the
    // preceeding serial region. The corresponding entry is equal to the
    // loop index assigned to the thread by the for loop
    for (i = chunkstart; i < chunkend; i++) {
      v[i] += locallast[threadno];
    }
    
  }