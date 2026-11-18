def febonachi(a):
    c1 = 1
    c2 = 1
    print("1")
    for i in range (a):
        n = c1+c2
        print(n)
        c2 = c1
        c1 = n


b = input("Введите неотрицательное число : ")
while True:
    if b.strip() == "":
        print("пустая строка")
        b = input("Введите неотрицательное число : ")
        continue
    elif b.isdigit() == False:
        print("Введено не число")
        b = input("Введите неотрицательное число : ")
        continue
    else :
        a = int(b)
        febonachi(a)
        break