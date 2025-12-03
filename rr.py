from collections import deque

n = int(input())
tq = int(input())
p = []
for _ in range(n):
    pid, at, bt = map(int, input().split())
    p.append({'pid': pid, 'at': at, 'bt': bt, 'rbt': bt, 'wt': 0, 'tt': 0, 'ct': 0, 'done': False})

time = 0
completed = 0
readyQueue = deque()
inQueue = [False] * n

for i in range(n):
    if p[i]['at'] <= time:
        readyQueue.append(i)
        inQueue[i] = True

while completed < n:
    if not readyQueue:
        time += 1
        for i in range(n):
            if not p[i]['done'] and not inQueue[i] and p[i]['at'] <= time:
                readyQueue.append(i)
                inQueue[i] = True
        continue
    
    idx = readyQueue.popleft()
    
    execTime = min(tq, p[idx]['rbt'])
    p[idx]['rbt'] -= execTime
    time += execTime
    
    for i in range(n):
        if not p[i]['done'] and not inQueue[i] and p[i]['at'] <= time:
            readyQueue.append(i)
            inQueue[i] = True
    
    if p[idx]['rbt'] == 0:
        p[idx]['ct'] = time
        p[idx]['tt'] = p[idx]['ct'] - p[idx]['at']
        p[idx]['wt'] = p[idx]['tt'] - p[idx]['bt']
        p[idx]['done'] = True
        completed += 1
    else:
        readyQueue.append(idx)

print("\nPID\tAT\tBT\tCT\tTT\tWT")
for i in range(n):
    print(f"{p[i]['pid']}\t{p[i]['at']}\t{p[i]['bt']}\t{p[i]['ct']}\t{p[i]['tt']}\t{p[i]['wt']}")

avgwt = sum(p[i]['wt'] for i in range(n)) / n
avgtat = sum(p[i]['tt'] for i in range(n)) / n
print(f"Average Waiting Time: {avgwt}")
print(f"Average Turnaround Time: {avgtat}")
