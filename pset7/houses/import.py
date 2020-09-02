import sys
import csv
from cs50 import SQL


def main():
    # Check command-line arguments
    if len(sys.argv) != 2:
        print('Usage: python import.py characters.csv')
        return 1
    
    db = SQL("sqlite:///students.db")
    
    # open csv file given by command line argument
    characters = sys.argv[1]
    with open(characters, 'r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        for line in csv_reader:
            values = parse_name(line['name'])
            values += [line['house'], line['birth']]
            # Insert each student into the students table of students.db
            db.execute("INSERT into students VALUES(NULL,?,?,?,?,?)", values)


# Parse name first, middle and last name
def parse_name(name):
    x = name.split()
    
    if len(x) == 2:
        return [x[0], None, x[1]]
    else:
        return x


main()