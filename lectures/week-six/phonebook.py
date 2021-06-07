from cs50 import get_string

people = {
    "Brian": "000-99-111",
    "Chase": "666-111-123"
}

name = get_string("name: ")

if name in people:
    print(f"number: {people[name]}")
