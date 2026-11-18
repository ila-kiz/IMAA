start = int(input("Введите число: "))

if start <= 10:
    for i in range(start, 11):
        print(i)
else:
    for i in range(start, 9, -1):
        print(i)
