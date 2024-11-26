### Zad.1

We compile the file to `fakesudo.out` and change its owner to root and give everyone SUID permission.
```sh
sudo chown root fakesudo.out
sudo chmod +s fakesudo.out
```

