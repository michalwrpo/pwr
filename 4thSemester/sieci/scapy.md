```python
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

>>> a=rdpcap("ipv4frags.pcap")
>>> a
<ipv4frags.pcap: TCP:0 UDP:0 ICMP:2 Other:1>

>>> a[0].pdfdump("scapy/ipv4frag.pdf",layer_shift=1)
>>> a[0].psdump("scapy/ipv6frag.eps",layer_shift=1)

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

>>> conf.checkIPaddr = False
>>> sr(IP(dst="224.0.0.1%enp0s31f6")/ICMP(), multi=True)
WARNING: No route found for IPv4 destination 224.0.0.1 (no default route?)
>>> sr(IPv6(dst="ff02::1%enp0s31f6")/ICMPv6EchoRequest(), multi=True)
WARNING: No route found for IPv6 destination ff02::1 (no default route?)

>>> pkt = IP(dst=ScopedIP("224.0.0.1", scope=conf.iface))/ICMP()

>>> send(IP(dst="1.2.3.4")/fuzz(UDP()/NTP(version=4)),loop=1)
.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................^C
Sent 1225 packets.

>>> pkt = IP(len=RawVal(b"NotAnInteger"), src="127.0.0.1")
>>> bytes(pkt)
b'H\x00NotAnInt\x0f\xb3er\x00\x01\x00\x00@\x00\x00\x00\x7f\x00\x00\x01\x7f\x00\x00\x01\x00\x00'

>>> p = sr1(IP(dst="www.slashdot.org")/ICMP()/"XXXXXXXXXXX")
Begin emission

Finished sending 1 packets

Received 2 packets, got 1 answers, remaining 0 packets
>>> p
<IP  version=4 ihl=5 tos=0x0 len=39 id=19846 flags= frag=0 ttl=56 proto=icmp chksum=0x74f src=104.18.4.215 dst=192.168.0.112 |<ICMP  type=echo-reply code=0 chksum=0xee45 id=0x0 seq=0x0 unused=b'' |<Raw  load=b'XXXXXXXXXXX' |>>>
>>> p.show()
###[ IP ]###
  version   = 4
  ihl       = 5
  tos       = 0x0
  len       = 39
  id        = 19846
  flags     = 
  frag      = 0
  ttl       = 56
  proto     = icmp
  chksum    = 0x74f
  src       = 104.18.4.215
  dst       = 192.168.0.112
  \options   \
###[ ICMP ]###
     type      = echo-reply
     code      = 0
     chksum    = 0xee45
     id        = 0x0
     seq       = 0x0
     unused    = b''
###[ Raw ]###
        load      = b'XXXXXXXXXXX'


>>> sr1(IP(dst="8.8.8.8")/UDP()/DNS(rd=1,qd=DNSQR(qname="www.slashdot.org")))
Begin emission

Finished sending 1 packets

Received 2 packets, got 1 answers, remaining 0 packets
<IP  version=4 ihl=5 tos=0x0 len=143 id=30299 flags= frag=0 ttl=114 proto=udp chksum=0xdb src=8.8.8.8 dst=192.168.0.112 |<UDP  sport=domain dport=domain len=123 chksum=0xe198 |<DNS  id=0 qr=1 opcode=QUERY aa=0 tc=0 rd=1 ra=1 z=0 ad=0 cd=0 rcode=ok qdcount=1 ancount=3 nscount=0 arcount=0 qd=[<DNSQR  qname=b'www.slashdot.org.' qtype=A unicastresponse=0 qclass=IN |>] an=[<DNSRR  rrname=b'www.slashdot.org.' type=CNAME cacheflush=0 rclass=IN ttl=300 rdata=b'www.slashdot.org.cdn.cloudflare.net.' |>, <DNSRR  rrname=b'www.slashdot.org.cdn.cloudflare.net.' type=A cacheflush=0 rclass=IN ttl=300 rdata=104.18.4.215 |>, <DNSRR  rrname=b'www.slashdot.org.cdn.cloudflare.net.' type=A cacheflush=0 rclass=IN ttl=300 rdata=104.18.5.215 |>] |>>>

>>> sr(IP(dst="127.0.0.1")/TCP(dport=[21,22,23]))
Begin emission

Finished sending 3 packets

Received 6 packets, got 3 answers, remaining 0 packets
(<Results: TCP:3 UDP:0 ICMP:0 Other:0>,
 <Unanswered: TCP:0 UDP:0 ICMP:0 Other:0>)
>>> ans, unans = _
>>> ans.summary()
IP / TCP 127.0.0.1:ftp_data > 127.0.0.1:ftp S ==> IP / TCP 127.0.0.1:ftp > 127.0.0.1:ftp_data RA
IP / TCP 127.0.0.1:ftp_data > 127.0.0.1:ssh S ==> IP / TCP 127.0.0.1:ssh > 127.0.0.1:ftp_data RA
IP / TCP 127.0.0.1:ftp_data > 127.0.0.1:telnet S ==> IP / TCP 127.0.0.1:telnet > 127.0.0.1:ftp_data RA

>>> sr(IP(dst="172.20.29.5/30")/TCP(dport=[21,22,23]),inter=0.5,retry=-2,timeout=1)
Begin emission

Finished sending 12 packets
Begin emission

Finished sending 12 packets
Begin emission

Finished sending 12 packets

Received 50 packets, got 0 answers, remaining 12 packets
(<Results: TCP:0 UDP:0 ICMP:0 Other:0>,
 <Unanswered: TCP:12 UDP:0 ICMP:0 Other:0>)

>>> sr1(IP(dst="127.0.0.1")/TCP(dport=80,flags="S"))
Begin emission

Finished sending 1 packets

Received 2 packets, got 1 answers, remaining 0 packets
<IP  version=4 ihl=5 tos=0x0 len=40 id=0 flags=DF frag=0 ttl=64 proto=tcp chksum=0x3cce src=127.0.0.1 dst=127.0.0.1 |<TCP  sport=www_http dport=ftp_data seq=0 ack=1 dataofs=5 reserved=0 flags=RA window=0 chksum=0xb169 urgptr=0 |>>

>>> sr(IP(dst="192.168.0.1")/TCP(sport=666,dport=(440,443),flags="S"))
Begin emission

Finished sending 4 packets

Received 4 packets, got 4 answers, remaining 0 packets
(<Results: TCP:4 UDP:0 ICMP:0 Other:0>,
 <Unanswered: TCP:0 UDP:0 ICMP:0 Other:0>)
>>> sr(IP(dst="192.168.0.1")/TCP(sport=RandShort(),dport=[440,441,442,443],flags="S"))
Begin emission

Finished sending 4 packets

Received 4 packets, got 4 answers, remaining 0 packets
(<Results: TCP:4 UDP:0 ICMP:0 Other:0>,
 <Unanswered: TCP:0 UDP:0 ICMP:0 Other:0>)
(<Results: TCP:4 UDP:0 ICMP:0 Other:0>,
 <Unanswered: TCP:0 UDP:0 ICMP:0 Other:0>)
>>> ans, unans = _
>>> ans.summary()
IP / TCP 192.168.0.112:11261 > 192.168.0.1:sgcp S ==> IP / TCP 192.168.0.1:sgcp > 192.168.0.112:11261 RA
IP / TCP 192.168.0.112:42395 > 192.168.0.1:decvms_sysmgt S ==> IP / TCP 192.168.0.1:decvms_sysmgt > 192.168.0.112:42395 RA
IP / TCP 192.168.0.112:24734 > 192.168.0.1:cvc_hostd S ==> IP / TCP 192.168.0.1:cvc_hostd > 192.168.0.112:24734 RA
IP / TCP 192.168.0.112:36304 > 192.168.0.1:https S ==> IP / TCP 192.168.0.1:https > 192.168.0.112:36304 SA

>>> ans.summary( lambda s,r: r.sprintf("%TCP.sport% \t %TCP.flags%") )
sgcp 	 RA
decvms_sysmgt 	 RA
cvc_hostd 	 RA
https 	 SA

>>> ans, unans = sr(IP(dst=["192.168.0.1","yahoo.com","slashdot.org"])/TCP(dport=[22,80,443],flags="S"))
Begin emission

Finished sending 9 packets
^C
Received 31 packets, got 6 answers, remaining 3 packets
>>> ans.make_table(
...:    lambda s,r: (s.dst, s.dport,
...:    r.sprintf("{TCP:%TCP.flags%}{ICMP:%IP.src% - %ICMP.type%}")))
    74.6.231.21 104.18.5.215 192.168.0.1 
80  SA          SA           SA          
443 SA          SA           SA          

>>> ans.nsummary(lfilter = lambda s,r: r.sprintf("%TCP.flags%") == "SA")
0000 IP / TCP 192.168.0.112:ftp_data > 192.168.0.1:www_http S ==> IP / TCP 192.168.0.1:www_http > 192.168.0.112:ftp_data SA
0001 IP / TCP 192.168.0.112:ftp_data > 192.168.0.1:https S ==> IP / TCP 192.168.0.1:https > 192.168.0.112:ftp_data SA
0002 IP / TCP 192.168.0.112:ftp_data > 104.18.5.215:www_http S ==> IP / TCP 104.18.5.215:www_http > 192.168.0.112:ftp_data SA
0003 IP / TCP 192.168.0.112:ftp_data > 104.18.5.215:https S ==> IP / TCP 104.18.5.215:https > 192.168.0.112:ftp_data SA
0004 IP / TCP 192.168.0.112:ftp_data > 74.6.231.21:https S ==> IP / TCP 74.6.231.21:https > 192.168.0.112:ftp_data SA
0005 IP / TCP 192.168.0.112:ftp_data > 74.6.231.21:www_http S ==> IP / TCP 74.6.231.21:www_http > 192.168.0.112:ftp_data SA

>>> ans.summary(lfilter = lambda s,r: r.sprintf("%TCP.flags%") == "SA",prn=lambda s,r: r.sprintf("%TCP.sport% is open"))
www_http is open
https is open
www_http is open
https is open
https is open
www_http is open

>>> ans.filter(lambda s,r: TCP in r and r[TCP].flags&2).make_table(lambda s,r:
...:             (s.dst, s.dport, "X"))
    74.6.231.21 104.18.5.215 192.168.0.1 
80  X           X            X           
443 X           X            X           

>>> report_ports("192.168.0.1",(440,443))
Begin emission

Finished sending 4 packets

Received 5 packets, got 4 answers, remaining 0 packets
'\\begin{tabular}{|r|l|l|}\n\\hline\nhttps & open & SA \\\\\n\\hline\nsgcp & closed & TCP RA \\\\\ndecvms_sysmgt & closed & TCP RA \\\\\ncvc_hostd & closed & TCP RA \\\\\n\\hline\n\\hline\n\\end{tabular}\n'

>>> ans, unans = sr(IP(dst="173.29.39.101", ttl=(4,25),id=RandShort())/TCP(flags=0x2))
Begin emission

Finished sending 22 packets
^C
Received 16 packets, got 15 answers, remaining 7 packets
>>> for snd,rcv in ans:
...:     print(snd.ttl, rcv.src, isinstance(rcv.payload, TCP))
4 80.50.119.233 False
5 194.204.175.209 False
6 193.251.249.17 False
7 193.251.133.3 False
8 184.104.196.231 False
9 184.105.223.254 False
10 184.104.188.213 False
11 68.66.72.189 False
12 209.51.171.18 False
13 173.29.39.101 False
14 173.29.39.101 False
15 173.29.39.101 False
16 173.29.39.101 False
17 173.29.39.101 False
18 173.29.39.101 False

>>> lsc()

>>> conf.use_pcap = True

>>>  sniff(count=5)
<Sniffed: TCP:0 UDP:2 ICMP:0 Other:3>
>>> a=_
>>> a.nsummary()
0000 802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
0001 802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
0002 802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
0003 Ether / IP / UDP 192.168.50.1:33045 > 239.255.255.250:ssdp / Raw
0004 Ether / IP / UDP 192.168.50.1:33045 > 239.255.255.250:ssdp / Raw
>>> a[1]
<Dot3  dst=01:80:c2:00:00:00 src=cc:28:aa:6c:8c:b4 len=38 |<LLC  dsap=0x42 ssap=0x42 ctrl=3 |<STP  proto=0 version=0 bpdutype=0 bpduflags=0 rootid=32768 rootmac=cc:28:aa:6c:8c:b0 pathcost=0 bridgeid=32768 bridgemac=cc:28:aa:6c:8c:b0 portid=32771 age=0.0 maxage=20.0 hellotime=2.0 fwddelay=2.0 |>>>

>>> sniff(iface="wlan0", prn=lambda x: x.summary())
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
Ether / ARP who has 192.168.50.105 says 192.168.50.1
Ether / ARP is at 30:89:4a:74:16:bb says 192.168.50.105
Ether / IP / UDP / NBNSHeader / NBNSQueryRequest who has '\\__MSBROWSE__'
Ether / 192.168.50.105 > 224.0.0.22 igmp / Raw
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
Ether / IP / UDP / NBNSHeader / NBNSQueryRequest who has '\\__MSBROWSE__'
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
Ether / IP / UDP / NBNSHeader / NBNSQueryRequest who has '\\__MSBROWSE__'
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:0e (0x88cc) / Raw
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:0e (0x88cc) / Raw
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
Ether / IP / TCP 192.168.50.105:49756 > 34.149.100.209:https PA / Raw
Ether / IP / TCP 192.168.50.105:49756 > 34.149.100.209:https PA / Raw
Ether / IP / TCP 192.168.50.105:49756 > 34.149.100.209:https PA / Raw
Ether / 192.168.50.1 > 224.0.0.1 igmp / Raw
Ether / IP / TCP 192.168.50.105:49756 > 34.149.100.209:https PA / Raw
Ether / IP / TCP 192.168.50.105:48722 > 34.160.144.191:https PA / Raw
Ether / IP / TCP 192.168.50.105:48722 > 34.160.144.191:https PA / Raw
Ether / IP / TCP 192.168.50.105:48722 > 34.160.144.191:https PA / Raw
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
Ether / IP / TCP 192.168.50.105:49756 > 34.149.100.209:https PA / Raw
Ether / IP / TCP 192.168.50.105:48722 > 34.160.144.191:https PA / Raw
^C<Sniffed: TCP:9 UDP:3 ICMP:0 Other:17>

>>> sniff(iface="enp0s31f6", prn=lambda x: x.show(), count=2)

>>> sniff(iface=["enp0s31f6","wlan0"], prn=lambda x: x.sniffed_on+": "+x.summary())
wlan0: Ether / IP / UDP 192.168.50.1:distinct > 255.255.255.255:distinct / Raw
wlan0: Ether / IP / UDP 192.168.50.1:distinct > 255.255.255.255:distinct / Raw
wlan0: 802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
wlan0: Ether / IP / TCP 192.168.50.105:33802 > 20.42.72.131:https A
wlan0: Ether / IP / TCP 20.42.72.131:https > 192.168.50.105:33802 A
wlan0: Ether / 192.168.50.1 > 224.0.0.1 igmp / Raw
wlan0: Ether / IP / UDP 192.168.50.1:distinct > 255.255.255.255:distinct / Raw
wlan0: Ether / IP / UDP 192.168.50.1:distinct > 255.255.255.255:distinct / Raw
wlan0: 802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
^C<Sniffed: TCP:2 UDP:4 ICMP:0 Other:3>

>>> pkts = sniff(prn=lambda x:x.sprintf("{IP:%IP.src% -> %IP.dst%\n}{Raw:%Raw.load%\n}"))
192.168.50.1 -> 224.0.0.1
b'\x11d\xec\x87\x00\x00\x00\x00\x02\x14\x00\x00'
192.168.50.105 -> 224.0.0.22
b'"\x00\t\x06\x00\x00\x00\x02\x02\x00\x00\x00\xe0\x00\x00\xfc\x02\x00\x00\x00\xef\xff\xff\xfa'
192.168.50.1 -> 239.255.255.250
b'NOTIFY * HTTP/1.1\r\nHOST: 239.255.255.250:1900\r\nCACHE-CONTROL: max-age=120\r\nLOCATION: http://192.168.50.1:43127/rootDesc.xml\r\nSERVER: AsusWRT/388 UPnP/1.1 MiniUPnPd/2.2.0\r\nNT: upnp:rootdevice\r\nUSN: uuid:3ddcd1d3-2380-45f5-b069-cc28aa6c8cb0::upnp:rootdevice\r\nNTS: ssdp:alive\r\nOPT: "http://schemas.upnp.org/upnp/1/0/"; ns=01\r\n01-NLS: 1704067237\r\nBOOTID.UPNP.ORG: 1704067237\r\nCONFIGID.UPNP.ORG: 1337\r\n\r\n'

>>> a=sniff(prn=prnp0f)
WARNING: Can't open base None
WARNING: p0f base empty.
.-[ 192.168.50.105:44642 -> 20.189.173.13:https (SYN) ]-
|
| Client   = 192.168.50.105:44642
| OS       = UNKNOWN
| Raw sig  = 4:64+0:0:1460:64240,7:mss,sok,ts,nop,ws:df,id+:0
`____

WARNING: Can't open base None
WARNING: p0f base empty.
.-[ 192.168.50.105:33954 -> 13.107.253.44:https (SYN) ]-
|
| Client   = 192.168.50.105:33954
| OS       = UNKNOWN
| Raw sig  = 4:64+0:0:1460:64240,7:mss,sok,ts,nop,ws:df,id+:0
`____

WARNING: more Can't open base None
WARNING: more p0f base empty.
.-[ 13.107.253.44:https -> 192.168.50.105:33954 (SYN+ACK) ]-
|
| Server   = 13.107.253.44:https
| OS       = UNKNOWN
| Raw sig  = 4:45+19:0:1410:43338,9:mss,sok,ts,nop,ws:df:0
`____

.-[ 20.189.173.13:https -> 192.168.50.105:44642 (SYN+ACK) ]-
|
| Server   = 20.189.173.13:https
| OS       = UNKNOWN
| Raw sig  = 4:103+25:0:1440:65535,8:mss,nop,ws,sok,ts:df,id+:0
`____

>>> t = AsyncSniffer()
>>> t.start()
>>> print("hey")
hey
>>> results = t.stop()

>>> t = AsyncSniffer(iface="wlan0", count=200)
>>> t.start()
>>> t.join()
>>> results = t.results
>>> print(len(results))
200

>>> t = AsyncSniffer(prn=lambda x: x.summary(), store=False, filter="tcp")
>>> t.start()
>>> time.sleep(20)
Ether / IP / TCP 192.168.50.105:43274 > 18.244.146.3:https PA / Raw
Ether / IP / TCP 192.168.50.105:50618 > 75.101.147.91:https PA / Raw
Ether / IP / TCP 192.168.50.105:45944 > 34.239.21.204:https PA / Raw
Ether / IP / TCP 192.168.50.105:48834 > 18.205.90.3:https PA / Raw
Ether / IP / TCP 192.168.50.105:58844 > 34.107.221.82:www_http A
Ether / IP / TCP 192.168.50.105:58848 > 34.107.221.82:www_http A
Ether / IP / TCP 34.107.221.82:www_http > 192.168.50.105:58844 A
Ether / IP / TCP 34.107.221.82:www_http > 192.168.50.105:58848 A
Ether / IP / TCP 192.168.50.105:59578 > 52.45.109.157:https PA / Raw
Ether / IP / TCP / HTTP / GET '/nm-check.txt' 
Ether / IP / TCP 192.168.50.105:58844 > 34.107.221.82:www_http A
Ether / IP / TCP 192.168.50.105:58848 > 34.107.221.82:www_http A
Ether / IP / TCP 34.107.221.82:www_http > 192.168.50.105:58844 A
Ether / IP / TCP 34.107.221.82:www_http > 192.168.50.105:58848 A
Ether / IP / TCP 192.168.50.105:43274 > 18.244.146.3:https PA / Raw
Ether / IP / TCP 192.168.50.105:58844 > 34.107.221.82:www_http A
Ether / IP / TCP 192.168.50.105:58848 > 34.107.221.82:www_http A
Ether / IP / TCP 34.107.221.82:www_http > 192.168.50.105:58844 A
Ether / IP / TCP 34.107.221.82:www_http > 192.168.50.105:58848 A
Ether / IP / TCP 192.168.50.105:50618 > 75.101.147.91:https PA / Raw
>>> t.stop()
<Sniffed: TCP:0 UDP:0 ICMP:0 Other:0>

>>> sniff(session=IPSession, iface="wlan0")
^C<Sniffed: TCP:2 UDP:0 ICMP:0 Other:4>
>>> sniff(session=TCPSession, prn=lambda x: x.summary(), store=False)
Ether / IP / UDP / DNS Qry b'staticcdn.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'staticcdn.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'staticcdn.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'staticcdn.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'staticcdn.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'staticcdn.duckduckgo.com.'
Ether / IP / UDP / DNS Ans b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Ans b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Ans b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Qry b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Ans b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Ans b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Ans b'external-content.duckduckgo.com.'
Ether / IP / UDP / DNS Ans
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https S
Ether / IP / UDP / DNS Ans
Ether / IP / UDP / DNS Ans
Ether / IP / UDP / DNS Ans
Ether / IP / UDP / DNS Ans 40.114.178.124
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 SA
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https A
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 A
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 A
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https A
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https A
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https A
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https PA / Raw
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https PA / Raw
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 PA / Raw
Ether / IP / TCP 192.168.50.105:44930 > 40.114.178.124:https A
Ether / IP / TCP 40.114.178.124:https > 192.168.50.105:44930 A
802.3 cc:28:aa:6c:8c:b4 > 01:80:c2:00:00:00 / LLC / STP
^C<Sniffed: TCP:0 UDP:0 ICMP:0 Other:0>

>>> a=sniff(filter="tcp and ( port 25 or port 110 )",
...:  prn=lambda x: x.sprintf("%IP.src%:%TCP.sport% -> %IP.dst%:%TCP.dport%  %2s,TCP.flags% : %TCP.payload%"))

>>> srloop(IP(dst="www.target.com/30")/TCP())
*****^C
Sent 20 packets, received 20 packets. 100.0% hits.
(<Results: TCP:20 UDP:0 ICMP:0 Other:0>,
 <PacketList: TCP:0 UDP:0 ICMP:0 Other:0>)

>>> wrpcap("scapy/cap.cap", a)
>>> b = rdpcap("scapy/cap.cap")
>>> b = sniff(offline="scapy/cap.cap")

>>> hexdump(a)
0000  45 00 00 14 00 01 00 00 40 00 7C E7 7F 00 00 01  E.......@.|.....
0010  7F 00 00 01                                      ....

>>> pkts = sniff(count = 1)
>>> pkt = pkts[0]
>>> pkt
<Ether  dst=ff:ff:ff:ff:ff:ff src=cc:28:aa:6c:8c:b0 type=IPv4 |<IP  version=4 ihl=5 tos=0x0 len=540 id=6813 flags=DF frag=0 ttl=64 proto=udp chksum=0x2b8b src=192.168.50.1 dst=255.255.255.255 |<UDP  sport=distinct dport=distinct len=520 chksum=0xc955 |<Raw  load=b'\x0c\x16\x1f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00mini-wifi-wroclaw-p2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00255.255.255.0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00RT-AX58U\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x003.0.0.4.388\x00\x00\x00\x00\x00\x00\xcc(\xaal\x8c\xb0\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x82\x80\xd9\x00\x00\x02\x1f\x92\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xb7c\xa8\xc0\x00\x01\x01\xbb\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x16\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x071ac8c26d303446d0a1a51f08a9011d7b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xcc(\xaal\x8c\xb0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00' |>>>>
>>> pkt_raw = raw(pkt)
>>> pkt_raw
b"\xff\xff\xff\xff\xff\xff\xcc(\xaal\x8c\xb0\x08\x00E\x00\x02\x1c\x1a\x9d@\x00@\x11+\x8b\xc0\xa82\x01\xff\xff\xff\xff'\x0f'\x0f\x02\x08\xc9U\x0c\x16\x1f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00mini-wifi-wroclaw-p2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00255.255.255.0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00RT-AX58U\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x003.0.0.4.388\x00\x00\x00\x00\x00\x00\xcc(\xaal\x8c\xb0\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x82\x80\xd9\x00\x00\x02\x1f\x92\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xb7c\xa8\xc0\x00\x01\x01\xbb\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x16\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x071ac8c26d303446d0a1a51f08a9011d7b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xcc(\xaal\x8c\xb0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
>>> new_pkt = Ether(pkt_raw)
>>> new_pkt
<Ether  dst=ff:ff:ff:ff:ff:ff src=cc:28:aa:6c:8c:b0 type=IPv4 |<IP  version=4 ihl=5 tos=0x0 len=540 id=6813 flags=DF frag=0 ttl=64 proto=udp chksum=0x2b8b src=192.168.50.1 dst=255.255.255.255 |<UDP  sport=distinct dport=distinct len=520 chksum=0xc955 |<Raw  load=b'\x0c\x16\x1f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00mini-wifi-wroclaw-p2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00255.255.255.0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00RT-AX58U\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x003.0.0.4.388\x00\x00\x00\x00\x00\x00\xcc(\xaal\x8c\xb0\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x82\x80\xd9\x00\x00\x02\x1f\x92\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xb7c\xa8\xc0\x00\x01\x01\xbb\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x16\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x071ac8c26d303446d0a1a51f08a9011d7b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xcc(\xaal\x8c\xb0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00' |>>>>

>>> export_object(pkt)
eNrNU8uP00YYd8K+MAvL8lie7dIH3fBYY+fpuK2EN2u2aRI7chIwh1U0Hk9YC8fJZzsse0BakEBF5dRbD5V6RJx666GHSs5fgfhTemE8mwXUUlGJSz3yzDe/7/t+8z1mdtM4xGi4I3hohwSh4GV5LdoiAQ8c7uKBQ3DIEz8ReEhZjTTHjf98ZzzLxC+8+Fn82xyncenzZ+NfrnPXF6/EP4534+fZ1L7dysLKQnpu/LQzv7TM/R++vuu7q9tuj07BAHtoe3WYfVefLRSE/V98j7/ZXlWtgtz5N/6cINKRF3KyvAe8rVTq77bxo3h3/DPHpZfjnz46sfh3HD8f73KpVPzHP5RL/4EgNSshLONs0cmJuXy+6IhIQgWpJ8qoLEqSU7I/xPA21Q+fBmlrhi4eilxfggNPYMqE6ccwY8JsZkN9+Zc/ffjXV7o+uaOuH5GghzAJeZ1E24PgbnUf4WHu0kM4+AD4jDVHGYfB4J7rkAAOTXxRgLcEz/VH9/l6Mr/xbE4seZinDIetKertoz6BI9Y0Fbc95IuwYB2iskNCHLjDyB34cHRrwZpPTPcC6TKXRQomTq7vkPtwrDZlpZPdEI5bR6gglbOCVJSFgihIYgFOWAeYNoSTGA88j+CEOeQd0kMjL3JcHPGwhLtde+R6tEDdLu+5IcVOPYbTJpzJ1KY24ezWCVSb2YRz1hlK1iOyqCiOWCwoJYKxIpVyttKzs2U4j0YstWhnSOCTWoqd3UcYPrUWkwsrKnJZySOllFekomLbsMwycUb9/g5ceMo2PQ/dCeGzSUV7LvGckL9BwZvIG9EWfE4L+IX+AL7MMPN7CQoXv68cTXEMSGoUwlebsJJhhek0IWMdpMKaaajrFbXVhkvMcF1b62zAZdbJumE019RKDa6wejeNqt5uG2yBqxZPId1om2q1rpktWLVmk9fZ0fWqvgECI9MN1WzCNaZpmkaj2qqAyKjVer3RqberILFb2KABaCZkmVerrt7UIMfCY0YsvPwei2G2W1odCkyrdtpGQ1uvqlBk2vXbutqoVqA0Cf+WZnZppvKe0jAbKo28zJqhVb4zQCHswD5tuQtf/zB6At/YI1vXI/jWFl4Dlqcz0A==

>>> dir()

>>> save_session("session.scapy")
INFO: Saving session into [session.scapy]

>>> load_session("session.scapy")

>>> ans, unans = sr(IP(dst="www.test.fr/30", ttl=(1,6))/TCP())
Begin emission

Finished sending 24 packets

Received 26 packets, got 24 answers, remaining 0 packets
>>> ans.make_table( lambda s,r: (s.dst, s.ttl, r.src) )
  188.114.97.8   188.114.97.9   188.114.97.10  188.114.97.11  
1 192.168.50.1   192.168.50.1   192.168.50.1   192.168.50.1   
2 192.168.99.1   192.168.99.1   192.168.99.1   192.168.99.1   
3 80.50.119.233  80.50.119.233  80.50.119.233  80.50.118.233  
4 83.1.4.234     83.1.4.234     83.1.4.234     83.1.4.234     
5 195.116.35.189 195.116.35.189 195.116.35.189 195.116.35.189 
6 217.98.245.54  217.98.245.54  217.98.245.54  217.98.245.54  

>>> ans, unans = sr(IP(dst="www.test.fr/30", ttl=(1,6))/TCP())
Begin emission

Finished sending 24 packets

Received 24 packets, got 24 answers, remaining 0 packets
>>> ans.make_table(lambda s,r: (s.dst, s.dport, r.sprintf("%IP.id%")))
   188.114.96.8 188.114.96.9 188.114.96.10 188.114.96.11 
80 0            28652        28654         9466          

>>> conf.route
Network          Netmask          Gateway       Iface  Output IP       Metric
0.0.0.0          0.0.0.0          192.168.50.1  wlan0  192.168.50.105  600   
0.0.0.0          0.0.0.0          192.168.50.1  wlan0  192.168.50.105  1024  
127.0.0.0        255.0.0.0        0.0.0.0       lo     127.0.0.1       0     
127.0.0.1        255.255.255.255  0.0.0.0       lo     127.0.0.1       0     
127.255.255.255  255.255.255.255  0.0.0.0       lo     127.0.0.1       0     


>>> conf.route.delt(net="0.0.0.0/0",gw="192.168.50.1", metric=600)
>>> conf.route.add(net="0.0.0.0/0",gw="192.168.8.254")
>>> conf.route.add(host="192.168.1.1",gw="192.168.8.1")
>>> conf.route
Network          Netmask          Gateway        Iface  Output IP       Metric
0.0.0.0          0.0.0.0          192.168.50.1   wlan0  192.168.50.105  1024  
0.0.0.0          0.0.0.0          192.168.8.254  wlan0  192.168.50.105  1     
127.0.0.0        255.0.0.0        0.0.0.0        lo     127.0.0.1       0     
127.0.0.1        255.255.255.255  0.0.0.0        lo     127.0.0.1       0     
127.255.255.255  255.255.255.255  0.0.0.0        lo     127.0.0.1       0     
192.168.1.1      255.255.255.255  192.168.8.1    wlan0  192.168.50.105  1     

>>> conf.route.resync()
>>> conf.route
Network          Netmask          Gateway       Iface  Output IP       Metric
0.0.0.0          0.0.0.0          192.168.50.1  wlan0  192.168.50.105  600   
0.0.0.0          0.0.0.0          192.168.50.1  wlan0  192.168.50.105  1024  
127.0.0.0        255.0.0.0        0.0.0.0       lo     127.0.0.1       0     
127.0.0.1        255.255.255.255  0.0.0.0       lo     127.0.0.1       0     
127.255.255.255  255.255.255.255  0.0.0.0       lo     127.0.0.1       0    

>>> traceroute(["www.yahoo.com","www.altavista.com","www.wisenut.com","www.copernic.com"],maxttl=20)
Begin emission

Finished sending 80 packets

Received 71 packets, got 71 answers, remaining 9 packets
   151.101.194.159:tcp80 211.39.140.160:tcp80 212.82.100.137:tcp80 87.248.119.251:tcp80 
1  192.168.50.1    11    192.168.50.1    11   192.168.50.1    11   192.168.50.1    11   
2  192.168.99.1    11    192.168.99.1    11   192.168.99.1    11   192.168.99.1    11   
3  83.1.4.234      11    83.1.4.234      11   83.1.4.234      11   83.1.4.234      11   
4  80.50.119.233   11    80.50.119.233   11   80.50.119.233   11   80.50.119.233   11   
5  194.204.175.209 11    195.116.35.201  11   195.116.35.201  11   194.204.175.209 11   
6  193.251.249.17  11    193.251.249.15  11   62.115.47.250   11   62.115.47.250   11   
7  -                     193.251.133.3   11   62.115.132.108  11   62.115.120.70   11   
8  151.101.194.159 SA    -                    62.115.122.161  11   62.115.127.91   11   
9  151.101.194.159 SA    154.54.76.209   11   -                    62.115.114.89   11   
10 151.101.194.159 SA    154.54.72.41    11   62.115.139.119  11   213.248.90.45   11   
11 151.101.194.159 SA    154.54.56.93    11   213.248.86.107  11   66.196.64.239   11   
12 151.101.194.159 SA    154.54.44.162   11   66.196.65.19    11   87.248.105.167  11   
13 151.101.194.159 SA    154.54.47.141   11   77.238.190.5    11   87.248.119.251  SA   
14 151.101.194.159 SA    154.54.169.226  11   77.238.190.102  11   87.248.119.251  SA   
15 151.101.194.159 SA    154.54.169.197  11   -                    87.248.119.251  SA   
16 151.101.194.159 SA    154.54.7.129    11   -                    87.248.119.251  SA   
17 151.101.194.159 SA    154.54.165.213  11   -                    87.248.119.251  SA   
18 151.101.194.159 SA    154.54.167.137  11   -                    87.248.119.251  SA   
19 151.101.194.159 SA    154.54.167.142  11   -                    87.248.119.251  SA   
20 151.101.194.159 SA    154.54.88.186   11   -                    87.248.119.251  SA   
(<Traceroute: TCP:21 UDP:0 ICMP:50 Other:0>,
 <Unanswered: TCP:9 UDP:0 ICMP:0 Other:0>)

>>> result, unans = _
>>> result.show()
   151.101.194.159:tcp80 211.39.140.160:tcp80 212.82.100.137:tcp80 87.248.119.251:tcp80 
1  192.168.50.1    11    192.168.50.1    11   192.168.50.1    11   192.168.50.1    11   
2  192.168.99.1    11    192.168.99.1    11   192.168.99.1    11   192.168.99.1    11   
3  83.1.4.234      11    83.1.4.234      11   83.1.4.234      11   83.1.4.234      11   
4  80.50.119.233   11    80.50.119.233   11   80.50.119.233   11   80.50.119.233   11   
5  194.204.175.209 11    195.116.35.201  11   195.116.35.201  11   194.204.175.209 11   
6  193.251.249.17  11    193.251.249.15  11   62.115.47.250   11   62.115.47.250   11   

>>> r2, unans = traceroute(["www.voila.com"],maxttl=20)
Begin emission

Finished sending 20 packets

Received 18 packets, got 18 answers, remaining 2 packets
   69.49.101.52:tcp80 
1  192.168.50.1    11 
2  192.168.99.1    11 
3  83.1.4.234      11 
4  80.50.118.233   11 
5  194.204.175.209 11 
6  193.251.249.15  11 
9  154.54.76.209   11 
10 154.54.62.142   11 
11 154.54.77.246   11 
12 154.54.44.162   11 
13 154.54.41.205   11 
14 38.122.68.114   11 
15 69.49.124.101   11 
16 216.55.190.69   11 
17 69.49.100.147   11 
18 69.49.101.52    SA 
19 69.49.101.52    SA 
20 69.49.101.52    SA 
>>> r3=result+r2
>>> r3.show()
   151.101.194.159:tcp80 211.39.140.160:tcp80 212.82.100.137:tcp80 69.49.101.52:tcp80 87.248.119.251:tcp80 
1  192.168.50.1    11    192.168.50.1    11   192.168.50.1    11   192.168.50.1    11 192.168.50.1    11   
2  192.168.99.1    11    192.168.99.1    11   192.168.99.1    11   192.168.99.1    11 192.168.99.1    11   
3  83.1.4.234      11    83.1.4.234      11   83.1.4.234      11   83.1.4.234      11 83.1.4.234      11   
4  80.50.119.233   11    80.50.119.233   11   80.50.119.233   11   80.50.118.233   11 80.50.119.233   11   
5  194.204.175.209 11    195.116.35.201  11   195.116.35.201  11   194.204.175.209 11 194.204.175.209 11   
6  193.251.249.17  11    193.251.249.15  11   62.115.47.250   11   193.251.249.15  11 62.115.47.250   11   
7  -                     193.251.133.3   11   62.115.132.108  11   -                  62.115.120.70   11   
8  151.101.194.159 SA    -                    62.115.122.161  11   -                  62.115.127.91   11   
9  151.101.194.159 SA    154.54.76.209   11   -                    154.54.76.209   11 62.115.114.89   11   
10 151.101.194.159 SA    154.54.72.41    11   62.115.139.119  11   154.54.62.142   11 213.248.90.45   11   
11 151.101.194.159 SA    154.54.56.93    11   213.248.86.107  11   154.54.77.246   11 66.196.64.239   11   
12 151.101.194.159 SA    154.54.44.162   11   66.196.65.19    11   154.54.44.162   11 87.248.105.167  11   
13 151.101.194.159 SA    154.54.47.141   11   77.238.190.5    11   154.54.41.205   11 87.248.119.251  SA   
14 151.101.194.159 SA    154.54.169.226  11   77.238.190.102  11   38.122.68.114   11 87.248.119.251  SA   
15 151.101.194.159 SA    154.54.169.197  11   -                    69.49.124.101   11 87.248.119.251  SA   
16 151.101.194.159 SA    154.54.7.129    11   -                    216.55.190.69   11 87.248.119.251  SA   
17 151.101.194.159 SA    154.54.165.213  11   -                    69.49.100.147   11 87.248.119.251  SA   
18 151.101.194.159 SA    154.54.167.137  11   -                    69.49.101.52    SA 87.248.119.251  SA   
19 151.101.194.159 SA    154.54.167.142  11   -                    69.49.101.52    SA 87.248.119.251  SA   
20 151.101.194.159 SA    154.54.88.186   11   -                    69.49.101.52    SA 87.248.119.251  SA   

>>> res, unans = traceroute(["www.microsoft.com","www.cisco.com","www.yahoo.com","www.wanadoo.fr","www.pacsec.com"],dport=[80,443],maxttl=20,retry=-2)
Begin emission

Finished sending 200 packets
Begin emission

Finished sending 33 packets
Begin emission

Finished sending 27 packets
Begin emission

Finished sending 23 packets
Begin emission

Finished sending 23 packets

Received 215 packets, got 177 answers, remaining 23 packets
   184.30.21.171:tcp443 184.30.21.171:tcp80 2.16.98.100:tcp443 2.16.98.100:tcp80  44.213.46.149:tcp443 44.213.46.149:tcp80 81.52.142.219:tcp443 81.52.142.219:tcp80 87.248.119.252:tcp443 87.248.119.252:tcp80 
1  192.168.50.1    11   192.168.50.1    11  192.168.50.1    11 192.168.50.1    11 192.168.50.1    11   192.168.50.1    11  192.168.50.1    11   192.168.50.1    11  192.168.50.1    11    192.168.50.1    11   
2  192.168.99.1    11   192.168.99.1    11  192.168.99.1    11 192.168.99.1    11 192.168.99.1    11   192.168.99.1    11  192.168.99.1    11   192.168.99.1    11  192.168.99.1    11    192.168.99.1    11   
3  83.1.4.234      11   83.1.4.234      11  83.1.4.234      11 83.1.4.234      11 83.1.4.234      11   83.1.4.234      11  83.1.4.234      11   83.1.4.234      11  83.1.4.234      11    83.1.4.234      11   
4  80.50.119.233   11   80.50.119.233   11  80.50.119.233   11 80.50.119.233   11 80.50.119.233   11   80.50.119.233   11  80.50.119.233   11   80.50.118.233   11  80.50.118.233   11    80.50.118.233   11   
5  194.204.175.209 11   194.204.175.209 11  194.204.175.209 11 194.204.175.209 11 195.116.35.201  11   194.204.175.209 11  194.204.175.209 11   194.204.175.209 11  195.116.35.201  11    194.204.175.209 11   
6  193.251.249.15  11   193.251.249.17  11  193.251.249.15  11 193.251.249.17  11 193.251.249.15  11   193.251.249.15  11  193.251.249.17  11   193.251.249.17  11  213.248.96.144  11    213.248.96.144  11   
7  193.251.133.3   11   193.251.133.3   11  193.251.133.3   11 193.251.133.3   11 81.52.166.175   11   81.52.166.175   11  193.251.240.103 11   193.251.240.103 11  62.115.132.108  11    62.115.132.108  11   
8  193.251.142.16  11   193.251.142.16  11  193.251.142.16  11 193.251.142.16  11 -                    -                   -                    -                   62.115.123.76   11    62.115.127.91   11   
9  89.149.180.45   11   89.149.180.45   11  89.149.180.226  11 89.149.180.45   11 -                    -                   -                    -                   62.115.136.219  11    62.115.136.213  11   
10 154.14.128.238  11   154.14.128.238  11  154.14.128.238  11 154.14.128.238  11 -                    -                   -                    -                   213.248.90.45   11    213.248.90.45   11   
11 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    -                   81.52.143.167   11   81.52.143.167   11  66.196.64.215   11    66.196.64.239   11   
12 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    -                   81.52.142.219   SA   81.52.142.219   SA  87.248.105.181  11    87.248.105.179  11   
13 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA 44.213.46.149   11   44.213.46.149   11  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
14 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
15 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
16 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
17 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
18 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
19 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
20 184.30.21.171   SA   184.30.21.171   SA  2.16.98.100     SA 2.16.98.100     SA -                    44.213.46.149   SA  81.52.142.219   SA   81.52.142.219   SA  87.248.119.252  SA    87.248.119.252  SA   
>>> res.graph()

>>> res.graph(target="> scapy/graph.svg")

```