#!/bin/bash

# Record the start time
start_time=$(date +%s)

# Run the first program in the background
./converter dna_100.txt 200000 100 100 yes &
#echo "Program 1 started."

# Wait for 500 milliseconds before starting the second program
sleep 0.5  #  500 ms delay

# Run the second program in the background
./aggregator 100 yes &
#echo "Program 2 started."

# Wait for both programs to finish
wait
#echo "Both programs completed."

# Record the end time
end_time=$(date +%s)

# Calculate the total time
total_time=$((end_time - start_time))
#echo "Total execution time: $total_time seconds"