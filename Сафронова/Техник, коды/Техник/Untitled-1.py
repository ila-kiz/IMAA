def fu(a):
  first = 1
  second = 1
  print("1")
  for i in range(a):
    print(f"{first + second}, ")
    temp = second
    second = first
    first = first + temp


a = input("Введите число: ")

if not a.isdigit():
    print("Ошибка!")
else:
    b = int(a)
    print(f"Число: {b}")
    fu(b)
