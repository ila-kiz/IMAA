contacts = {}

def menu():
   print("1-добавить, 2-найти, 3-все, 0-выход")
def add():
   name = input("Имя: ").strip()
   if not name:
       return
   if name in contacts:
       print("уже есть")
       return
   phone = input("телефон: ").strip()
   if not phone:
       return
   contacts[name] = phone
   print("добавлено.")


def find():
   name = input("Имя: ").strip()
   if not name:
       return
   if name in contacts:
       print(contacts[name])
   else :
       print("не найден.")

def all():
   if not contacts:
       print("список пуст.")
       return
   for name, phone in contacts.items():
       print (f"{name}: {phone}")





def main():
   while True:
       menu()
       choise = input("> ").strip()
       if choise == "1":
           add()
       elif choise == "2":
           find()
       elif choise == "3":
           all()
       elif choise == "0":
           print("Пока!")
           break
       else:
           print("не понял")



if __name__ == "__main__":
   main()
