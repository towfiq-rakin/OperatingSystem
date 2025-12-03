n = int(input())
p = []
for _ in range(n):
    pid, at, bt, pr = map(int, input().split())
    p.append({'pid': pid, 'at': at, 'bt': bt, 'pr': pr, 'wt': 0, 'tt': 0, 'ct': 0, 'done': False})

time = 0
completed = 0

while completed < n:
    idx = -1
    minPr = float('inf')
    
    for i in range(n):
        if not p[i]['done'] and p[i]['at'] <= time:
            if p[i]['pr'] < minPr or (p[i]['pr'] == minPr and p[i]['at'] < p[idx]['at']):
                minPr = p[i]['pr']
                idx = i
    
    if idx == -1:
        time += 1
    else:
        time += p[idx]['bt']
        p[idx]['ct'] = time
        p[idx]['tt'] = p[idx]['ct'] - p[idx]['at']
        p[idx]['wt'] = p[idx]['tt'] - p[idx]['bt']
        p[idx]['done'] = True
        completed += 1

print("\nPID\tAT\tBT\tPR\tCT\tTT\tWT")
for i in range(n):
    print(f"{p[i]['pid']}\t{p[i]['at']}\t{p[i]['bt']}\t{p[i]['pr']}\t{p[i]['ct']}\t{p[i]['tt']}\t{p[i]['wt']}")

avgwt = sum(p[i]['wt'] for i in range(n)) / n
avgtat = sum(p[i]['tt'] for i in range(n)) / n
print(f"Average Waiting Time: {avgwt}")
print(f"Average Turnaround Time: {avgtat}")
