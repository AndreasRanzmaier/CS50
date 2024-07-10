presidents = [
    ("George", 1789),
    ("John", 1798),
    ("Thomas", 1801),
    ("James", 1809)
]

for president, year in presidents:
    print(f"In {year}, {president} took office.")

pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetabel": 11,
    "buffalo chicken": 12
}

for pie, price in pizzas.items():
    print(f"A whole {pie} pizza costs {price}")


class Student:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def changeAge(self, age):
        self.age = age

    def print(self):
        print(f"{self.name} - {self.age}")

andi = Student("Andi", 21)
andi.print()
andi.changeAge(22)
andi.print()