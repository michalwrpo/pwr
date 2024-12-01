### Zad.1

We compile the file to `fakesudo.out` and change its owner to root and give everyone SUID permission.
```sh
sudo chown root fakesudo.out
sudo chmod +s fakesudo.out
```

### Zad.2 

Linux:
    - It's impossible to catch signals 9 and 19 (`SIGKILL` and `SIGSTOP`)  
    - Normal users cannot send any signals to process 1. Root can send signals normally, but `SIGKILL` gets ignored.
    - Process ignores multiple signals - `multiplesignals.c` and `receivesignals.c`