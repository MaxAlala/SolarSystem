from math import *

name = "max"
age = 50
print("My name \n is " + name)
print("my age i s " + str(age))
print(len(str(age)))
print(str(age)[0])
print(name[0].upper())
name = name.upper()
print(name)
print(name.index("X"))
name = name.replace("MA", "ALALA")
print(name)

integer = -555
print(abs(integer))
print(pow(4, 6))
print(round(4.9))

print(str(sqrt(36)) + " is sqrt of 36")

# urName = input("Enter ur name: ")
# print("Ur name is: " + urName)

# lists


planets = ["earth", "mars", "neptune"]
wtf = ["first", 2, True]
print("current planets are: " + str(planets[0:2]))

wtf.extend(planets)
wtf.append("planets")
wtf.append("planets")
wtf.append("planets")
wtf.insert(1, "trulySecond")
# wtf.remove("planets")
# wtf.clear()
wtf.pop()

print(wtf.index("mars"))
print(wtf.count("planets"))
# wtf.sort() wont work because of generic
print(wtf)
numbers = [1, 2, 3, 4]
numbers.reverse()
numbers = planets.copy()
print(numbers)
tuplePlanet = ("earth", "mars")  # cant be changed = mutable


def myLovelyFunction(name):
    print("love planet: " + name)


myLovelyFunction("earth ")


def cube(num):
    num = num * num * num; #num is local value
    print("wont work this way")
myint = 5
cube(myint) # myint is the same
print(myint)

is_planet = True
is_asteroid = True

if is_planet or is_planet:
    print("this is planet!")
elif is_asteroid and not (is_asteroid):
    print("never will be reached")
else:
    print("this isnt planet!")


def max_num(num1, num2, num3):
    if num1 >= num2 and num1 >= num3:
        return num1
    elif num2 >= num1 and num2 >= num3:
        return num2
    else:
        return num3


print(max_num(333, 22, 444))
# you are either not male or not tall

# user_num1 = float(input("Enter first number: "))
# op = input("input your operator: ")
# user_num2 = float(input("Enter second number: "))
#
# if op == "+":
#     print(user_num1 + user_num2)
# elif op == "-":
#     print(user_num1 - user_num2)
# elif op == "/":
#     print(user_num1 / user_num2)
# elif op == "*":
#     print(user_num1 * user_num2)
# else:
#     print("invalid operator. ")
#
# # dictionary

dict = {
    "Ms": "Mars",
    "Eh": "Earth",
    "Nn": "Neptune"
}

print(dict.get("Ms"))
# print(dict["Mz"])
print(dict.get("Mbbr", "Not a valid key"))


i = 1
while i <= 10:
    print(i)
    i += 1


for letter in "Hello Friend!":
    print(letter)

systems = ["Solar", "Alpha", "Betelgeize"];

for sys in systems:
    print(sys)






