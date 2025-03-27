```sh
Welcome to Scapy (2.6.1) using IPython 9.0.2
Tip: Use `--theme`, or the `%colors` magic to change ipython themes and colors.
>>> a=IP(ttl=10)
>>> a
<IP  ttl=10 |>
>>> a.src
'127.0.0.1'
>>> a.dst="192.168.1.1"
>>> a
<IP  ttl=10 dst=192.168.1.1 |>
>>> a.src
'10.182.15.233'
>>> del(a.ttl)
>>> a
<IP  dst=192.168.1.1 |>
>>> a.ttl
64

>>> IP()
<IP  |>
>>> IP()/TCP()
<IP  frag=0 proto=tcp |<TCP  |>>
>>> Ether()/IP()/TCP()
<Ether  type=IPv4 |<IP  frag=0 proto=tcp |<TCP  |>>>
>>> IP()/TCP()/"GET / HTTP/1.0\r\n\r\n"
<IP  frag=0 proto=tcp |<TCP  |<Raw  load=b'GET / HTTP/1.0\r\n\r\n' |>>>
>>> Ether()/IP()/IP()/UDP()
<Ether  type=IPv4 |<IP  frag=0 proto=ipv4 |<IP  frag=0 proto=udp |<UDP  |>>>>
>>> IP(proto=55)/TCP()
<IP  frag=0 proto=min_ipv4 |<TCP  |>>

>>> raw(IP())
b'E\x00\x00\x14\x00\x01\x00\x00@\x00|\xe7\x7f\x00\x00\x01\x7f\x00\x00\x01'
>>> IP(_)
<IP  version=4 ihl=5 tos=0x0 len=20 id=1 flags= frag=0 ttl=64 proto=hopopt chksum=0x7ce7 src=127.0.0.1 dst=127.0.0.1 |>
>>> a=Ether()/IP(dst="www.slashdot.org")/TCP()/"GET /index.html HTTP/1.0 \n\n"
>>> hexdump(a)
0000  B4 0C 25 E3 40 10 30 89 4A 74 16 BB 08 00 45 00  ..%.@.0.Jt....E.
0010  00 43 00 01 00 00 40 06 F2 2C 0A B6 0F E9 68 12  .C....@..,....h.
0020  05 D7 00 14 00 50 00 00 00 00 00 00 00 00 50 02  .....P........P.
0030  20 00 35 2A 00 00 47 45 54 20 2F 69 6E 64 65 78   .5*..GET /index
0040  2E 68 74 6D 6C 20 48 54 54 50 2F 31 2E 30 20 0A  .html HTTP/1.0 .
0050  0A                                               .
>>> b=raw(a)
>>> b
b'\xb4\x0c%\xe3@\x100\x89Jt\x16\xbb\x08\x00E\x00\x00C\x00\x01\x00\x00@\x06\xf2,\n\xb6\x0f\xe9h\x12\x05\xd7\x00\x14\x00P\x00\x00\x00\x00\x00\x00\x00\x00P\x02 \x005*\x00\x00GET /index.html HTTP/1.0 \n\n'
>>> c=Ether(b)
>>> c
<Ether  dst=b4:0c:25:e3:40:10 src=30:89:4a:74:16:bb type=IPv4 |<IP  version=4 ihl=5 tos=0x0 len=67 id=1 flags= frag=0 ttl=64 proto=tcp chksum=0xf22c src=10.182.15.233 dst=104.18.5.215 |<TCP  sport=ftp_data dport=www_http seq=0 ack=0 dataofs=5 reserved=0 flags=S window=8192 chksum=0x352a urgptr=0 |<Raw  load=b'GET /index.html HTTP/1.0 \n\n' |>>>>
>>> c.hide_defaults()
>>> c
<Ether  dst=b4:0c:25:e3:40:10 src=30:89:4a:74:16:bb type=IPv4 |<IP  ihl=5 len=67 frag=0 proto=tcp chksum=0xf22c src=10.182.15.233 dst=104.18.5.215 |<TCP  dataofs=5 chksum=0x352a |<Raw  load=b'GET /index.html HTTP/1.0 \n\n' |>>>>

# Nie mamy dostępu do zapisanego pliku więc sam stworzyłem
>>> a=IP()
>>> wrpcap("./cap.cap", a)
>>> b=rdpcap("./cap.cap")
>>> b
<cap.cap: TCP:0 UDP:0 ICMP:0 Other:1>

>>> a=IP(dst="www.slashdot.org/30")
>>> a
<IP  dst=Net("www.slashdot.org/30") |>
>>> [p for p in a]
[<IP  dst=104.18.5.212 |>,
 <IP  dst=104.18.5.213 |>,
 <IP  dst=104.18.5.214 |>,
 <IP  dst=104.18.5.215 |>]
>>> b=IP(ttl=[1,2,(5,9)])
>>> b
<IP  ttl=[1, 2, (5, 9)] |>
>>> [p for p in b]
[<IP  ttl=1 |>,
 <IP  ttl=2 |>,
 <IP  ttl=5 |>,
 <IP  ttl=6 |>,
 <IP  ttl=7 |>,
 <IP  ttl=8 |>,
 <IP  ttl=9 |>]
>>> c=TCP(dport=[80,443])
>>> [p for p in a/c]
[<IP  frag=0 proto=tcp dst=104.18.5.212 |<TCP  dport=www_http |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.212 |<TCP  dport=https |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.213 |<TCP  dport=www_http |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.213 |<TCP  dport=https |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.214 |<TCP  dport=www_http |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.214 |<TCP  dport=https |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.215 |<TCP  dport=www_http |>>,
 <IP  frag=0 proto=tcp dst=104.18.5.215 |<TCP  dport=https |>>]
>>> p=PacketList(a)
>>> p
<PacketList: TCP:0 UDP:0 ICMP:0 Other:4>
>>> p = PacketList([p for p in a/c])
>>> p
<PacketList: TCP:8 UDP:0 ICMP:0 Other:0>

>>> send(IP(dst="1.2.3.4")/ICMP())
.
Sent 1 packets.
>>> sendp(Ether()/IP(dst="1.2.3.4",ttl=(1,4)), iface="enp0s31f6")
....
Sent 4 packets.
>>> sendp("I'm travelling on Ethernet", iface="enp0s31f6", loop=1, inter=0.2)
.............................^C
Sent 29 packets.
>>> sendp(rdpcap("cap.cap"))
.
Sent 1 packets.
>>> send(IP(dst='127.0.0.1'), return_packets=True)
...: 
.
Sent 1 packets.
<PacketList: TCP:0 UDP:0 ICMP:0 Other:1>

```