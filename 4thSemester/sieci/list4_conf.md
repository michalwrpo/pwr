To configure the topology in GNS3 as shown in the image, follow these steps. This includes interface configuration and static routing.

---

### **1. Device IP Plan (as per the image):**

| Device | Interface | IP Address     |
| ------ | --------- | -------------- |
| PC1    | Ethernet  | 192.168.1.2/24 |
| Switch | —         | Just Layer 2   |
| R6     | f0/0      | 192.168.1.1/24 |
| R6     | f0/1      | 192.168.4.1/30 |
| R5     | f0/0      | 192.168.3.1/30 |
| R5     | f0/1      | 192.168.0.1/24 |
| R2     | f0/0      | 192.168.4.2/30 |
| R2     | f0/1      | 192.168.2.1/24 |
| R3     | f0/0      | 192.168.2.3/24 |
| PC2    | Ethernet  | 192.168.2.2/24 |
| PC3    | Ethernet  | 192.168.2.4/24 |

---

### **2. PC Configuration (Use VPCS or QEMU Linux Host):**

#### PC1:

```bash
ip 192.168.1.2 255.255.255.0 192.168.1.1
```

#### PC2:

```bash
ip 192.168.2.2 255.255.255.0 192.168.2.1
```

#### PC3:

```bash
ip 192.168.2.4 255.255.255.0 192.168.2.1
```

---

### **3. Router Configurations**

#### R6:

```bash
conf t
interface f0/0
 ip address 192.168.3.2 255.255.255.252
 no shutdown
!
interface f0/1
 ip address 192.168.4.1 255.255.255.252
 no shutdown
!
interface f2/0
 ip address 192.168.1.1 255.255.255.0
 no shutdown
!
ip route 192.168.2.0 255.255.255.0 192.168.4.2
ip route 0.0.0.0 0.0.0.0 192.168.3.1 
exit
```

#### R2:

```bash
conf t
interface f0/0
 ip address 192.168.4.2 255.255.255.252
 no shutdown
!
interface f0/1
 ip address 192.168.2.1 255.255.255.0
 no shutdown
!
ip route 192.168.1.0 255.255.255.0 192.168.4.1
ip route 192.168.3.0 255.255.255.252 192.168.4.1
ip route 0.0.0.0 0.0.0.0 192.168.4.1
exit
```

#### R5:

```bash
conf t
interface f0/0
 ip address 192.168.0.1 255.255.255.0
 no shutdown
!
interface f0/1
 ip address 192.168.3.1 255.255.255.252
 no shutdown
!
ip route 192.168.1.0 255.255.255.0 192.168.3.2
ip route 192.168.2.0 255.255.255.0 192.168.3.2
ip route 0.0.0.0 0.0.0.0 192.168.0.1
exit
```

#### R3:

```bash
conf t
interface f0/0
 ip address 192.168.2.3 255.255.255.0
 no shutdown
ip route 0.0.0.0 0.0.0.0 192.168.2.1
exit
```

---

### **4. Enable Routing (if using Cisco IOS)**

If dynamic routing is desired (optional), use RIP or OSPF. Otherwise, static routing as above suffices.

---

### **5. Connectivity Testing:**

Use `ping` from each PC to test reachability to:

* Other PCs
* The cloud (simulate using a cloud object and NAT on GNS3)

---

If you'd like configuration scripts for GNS3 `.net` files or startup-configs, I can generate those as well. Let me know!
