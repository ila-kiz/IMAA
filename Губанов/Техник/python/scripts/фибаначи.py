def fib(n):
    fir = 1
    sec = 1

    for i in range(n):
        print(fir)
        temp = sec
        sec = fir
        fir = fir + temp

while True:
    try:
        n = int(input("Введите число: "))
        break
        
    except ValueError:
        print("Это не число, введите число")

fib(n)