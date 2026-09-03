import sys
def bsearch(array, target):
    l = 0
    r = len(array) - 1
    result = -1
    while l <= r:
        mid = (l + r) // 2
        if array[mid] == target:
            result = mid
            l = mid + 1
        elif array[mid] > target:
            r = mid - 1
        else:
            l = mid + 1
    return result


rows = []
for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    row = [int(x) for x in line.split()]
    rows.append(row)

for target in rows[1]:
    print(bsearch(rows[0], target))
