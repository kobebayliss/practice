import sys


def binary_search_rightmost(arr, lo, hi, x):
    result = -1
    while lo <= hi:
        mid = (lo + hi) // 2
        if arr[mid] == x:
            result = mid
            lo = mid + 1
        elif arr[mid] < x:
            lo = mid + 1
        else:
            hi = mid - 1
    return result


def find_pivot(arr, lo, hi):
    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] > arr[hi]:
            lo = mid + 1
        elif arr[mid] < arr[hi]:
            hi = mid
        else:
            hi -= 1
    return lo


def find_highest_index(arr, n, x, p):
    if n == 0:
        return -1
    result = binary_search_rightmost(arr, p, n - 1, x)
    if result != -1:
        return result
    return binary_search_rightmost(arr, 0, p - 1, x)


out = sys.stdout
while True:
    line1 = sys.stdin.readline()
    if not line1:
        break
    s1 = list(map(int, line1.split()))
    n1 = len(s1)
    p = find_pivot(s1, 0, n1 - 1) if n1 > 0 else 0

    line2 = sys.stdin.readline()
    if not line2:
        break
    for token in line2.split():
        x = int(token)
        out.write(str(find_highest_index(s1, n1, x, p)))
        out.write("\n")
