import subprocess

file = open("out.txt", 'w')
processes = []

# Launch the C program on cores 0–9
for i in range(10):
    p = subprocess.Popen(["taskset", "-c", str(i), "./app.out"], stdout=file)
    processes.append(p)

# Wait for all processes to complete
for p in processes:
    p.wait()

file.close()
