def fibonachi(a):
    n1 = 1
    n2 = 1
    print("1")
    for i in range (a):
        n = n1+n2
        print(f"{n}, ")
        n3 = n2
        n2 = n1
        n1 = n1+n3


b = input("Введите число : ")
if b.strip() == "":
    print ("Пустая строка")
else :
    a = int (b)
    fibonachi(a)