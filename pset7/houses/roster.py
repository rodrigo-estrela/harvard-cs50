import sys
from cs50 import SQL


def main():
    # Check command line argument
    if len(sys.argv) != 2:
        print("Usage: python roster.py house_name")
        return 1
    
    db = SQL("sqlite:///students.db")
    
    house = sys.argv[1]
    
    # Query database for all students in house
    students = db.execute("SELECT * FROM students WHERE house =? ORDER BY last ASC, first ASC", house)
    # Print ou each student's full name and birth year
    for s in students:
        if s['middle'] == None:
            print(s['first'] + ' ' + s['last'] + ', born ' + str(s['birth']))
        else:
            print(s['first'] + ' ' + s['middle'] + ' ' + s['last'] + ', born ' + str(s['birth']))


main()