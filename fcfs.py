n = int(input())
p = []
for _ in range(n):
    pid, at, bt = map(int, input().split())
    p.append({'pid': pid, 'at': at, 'bt': bt, 'wt': 0, 'tt': 0, 'ct': 0})

p.sort(key=lambda x: x['at'])

time = 0
for i in range(n):
    if time < p[i]['at']:
        time = p[i]['at']
    time += p[i]['bt']
    p[i]['ct'] = time
    p[i]['tt'] = p[i]['ct'] - p[i]['at']
    p[i]['wt'] = p[i]['tt'] - p[i]['bt']

print("\nPID\tAT\tBT\tCT\tTT\tWT")
for i in range(n):
    print(f"{p[i]['pid']}\t{p[i]['at']}\t{p[i]['bt']}\t{p[i]['ct']}\t{p[i]['tt']}\t{p[i]['wt']}")

avgwt = sum(p[i]['wt'] for i in range(n)) / n
avgtat = sum(p[i]['tt'] for i in range(n)) / n
print(f"Average Waiting Time: {avgwt}")
print(f"Average Turnaround Time: {avgtat}")
