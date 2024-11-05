# Lista 1

## Zad. 1

```sh
sudo dd if=/dev/nvme0n1p1 of=/dev/stdout bs=512 count=1 2> /dev/null | hexdump -C
```

## Zad. 2

```sh
ps -eH -o pri,pid,ppid,state,c,sz,rss,stime,tname,nice,cmd
```

## Zad. 3

`-Wall` wszystkie typowe warningi, generalnie o konstrukcjach, które są uznawane za złą praktykę
`-pedantic` sprawdza zgodność ze standardem ISO