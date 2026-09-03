import sys


def binary_search_rightmost(arr, lo, hi, x):
    if lo > hi:
        return -1

    mid = (lo + hi) // 2

    if arr[mid] == x:
        right_result = binary_search_rightmost(arr, mid + 1, hi, x)
        if right_result != -1:
            return right_result
        return mid
    elif arr[mid] < x:
        return binary_search_rightmost(arr, mid + 1, hi, x)
    else:
        return binary_search_rightmost(arr, lo, mid - 1, x)


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


def find_highest_index(arr, n, x):
    if n == 0:
        return -1

    p = find_pivot(arr, 0, n - 1)
    result = binary_search_rightmost(arr, p, n - 1, x)
    if result != -1:
        return result

    return binary_search_rightmost(arr, 0, p - 1, x)


data = sys.stdin.read().split("\n")
s1 = list(map(int, data[0].split()))
s2 = list(map(int, data[1].split()))
n1 = len(s1)

out = []
for x in s2:
    out.append(str(find_highest_index(s1, n1, x)))
print("\n".join(out))
