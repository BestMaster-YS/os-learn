import sys

count, n = 5, 0
while True:
    ch = sys.stdin.read(count)
    print(ch)
    print("__")
    flag = True
    if ch != "<><_ " or ch != "><>_ ":
        flag = False
    assert flag == True
    n += 1
    if n == 100000:
        print(f'{n} Ok.')
        n = 0
