# script akin to ps using /proc
# Michał Waluś 2024

# ------------------------
# PPID - parent process ID
# PID - process ID
# COMM - command name
# STATE - state of the process (R: running, S: sleeping, D: uninterruptible sleep, Z: zombie, T: traced or stopped)
# TTY - number of controlling terminal
# RSS - resident set size, number of pages program has in memory
# PGID - progress group ID
# SID - session ID
# NOOF - number of open files
# WARNING: to see number of open files of processes like 1 root permissions are needed
# ------------------------


filesno=$(ls /proc | grep -E ^[0-9]+$ | wc -l) # count the number of files in /proc``
secondlast=$(($(tput lines) - 2)) # save the location of 2nd lines from the bottom of the terminal

# because the method isn't particularly fast I've made a progress counter
declare -i i=0 # declare i as int
echo # write a new line

# we loop over all processes in /proc
for pid in $(ls /proc | grep -E ^[0-9]+$); do
    tput cup $secondlast 0 && echo "$i/$filesno"

    if [ -f /proc/$pid/stat ]; then
        comm=$(cut -d ")" -f 1 /proc/$pid/stat  | cut -d "(" -f 2) # comm is 2nd in /proc/pid/stat and is the only part that can have spaces
        rest=$(cut -d ")" -f 2 /proc/$pid/stat  | xargs) # before the comm is only pid, so we save the rest
        # because of that we will subtract 2 from block number in remaining fields 

        output="$output$(echo $rest | cut -d " " -f 2)|" # ppid - 4th in /proc/pid/stat
        output="$output$pid|" # pid
        output="$output$comm|" # comm
        output="$output$(echo $rest | cut -d " " -f 1)|" # state - 3rd in /proc/pid/stat
        output="$output$(echo $rest | cut -d " " -f 5)|" # tty - 7th in /proc/pid/stat
        output="$output$(echo $rest | cut -d " " -f 22)|" # rss - 24th in /proc/pid/stat
        output="$output$(echo $rest | cut -d " " -f 3)|" # pgid - 5th in /proc/pid/stat, there called pgrp
        output="$output$(echo $rest | cut -d " " -f 4)|" # sid - 6th in /proc/pid/stat
        output="$output$(ls /proc/$pid/fd 2> /dev/null | wc -l)" # number of open files - number of files in /proc/pid/fd

        output="$output\n" # new line for table to properly format
    fi
    i+=1 # increace i by 1 for the counter
done

echo -e $output | column -t -s "|" -N PPID,PID,COMM,STATE,TTY,RSS,PGID,SID,NOOF # we set the headers and print table
