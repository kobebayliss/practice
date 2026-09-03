import sys

rows = []
for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    row = [int(x) for x in line.split()]
    rows.append(row)

n = len(rows[1])
for i in range(n):
    print(rows[1][i] + len(rows[0]))
