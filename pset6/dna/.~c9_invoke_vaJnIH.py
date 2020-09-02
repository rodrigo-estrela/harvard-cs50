import csv
import sys
from collections import OrderedDict
# Short Tandem Repeat STR
# DNA Database as CSV file
# name,AGAT,AATG,TATC
# dna sequence as .txt file
def main():
    if len(sys.argv) is not 3:
        print('Usage error')
        return 1

    # Open the CSV file and read contents into memory
    database_file = sys.argv[1]
    db = {}
    with open(database_file, 'r') as csvFile:
        csvReader = csv.DictReader(csvFile)
        fields = csvReader.fieldnames
        for line in csvReader:
            db[line['name']] = line
    
    
    # Open the text file and read the sequence content into memory
    sequence_file = sys.argv[2]
    with open(sequence_file, 'r') as file:
        dna = file.readline()
    
    # Compute the longest run of consecutive repeats in the DNA sequence
    person = OrderedDict()
    person['name'] = 'No match'

    for tandem in range(1,len(fields)):
        person[fields[tandem]] = readSTR(dna, fields[tandem])
    
    for k, v in db.items():
        matched = True
        for tandem in v:
            if tandem is not 'name':
                if int(v[tandem]) != person[tandem]:
                    matched = False
                    break
            


# Compute the longest run of consecutive repeats in the DNA sequence
def readSTR(s, STR):
    str_len = len(STR)
    sequence_len = len(s)

    i = 0
    longest_run = 0 # Keep track of the longest STR run in the sequence
    while (s.find(STR) >= 0):
        run = 1
        i += s.find(STR) + str_len #
        sub_string = s[i: i + str_len]

        while (sub_string == STR):
            run += 1
            i += str_len
            if i > (sequence_len - str_len):
                break
            sub_string = s[i: i + str_len]

        if run > longest_run:
            longest_run = run
        s = s[i:]
    return longest_run

main()

    # First row of CSV file has name as first column, and them STRs for each of the remaining columns
    # Each remaining row corresponds to a person
    # Python's csv module has reader and DictReader
    # Python's sys module gives you access to sys.argv for command-line arguments
    # Once you've opened a text file f using open(filename), you can read its contents using f.read()
# For each STR, compute the longest run of consecutive repeats in the DNA sequence
    # For each position in the sequence: compute how many times the STR repeats starting at that position
    # For each position, keep checking successive substrings until the STR repeats no longer.
    # len(s) in Python will get you the length of the string s
    # s[i:j] in Python takes the string s, and returns the substring with all characters from the ith character up to (but no including) the jth
# Compra the STR counts against each row in the CSV file
    # Save STR counts in some data structure.
    # For each row in the data, check if each STR count matches. If so, print out the persons's name
    # int(x) takes the string x and turns it into an integer
    # to confirm a match, you'll need to check every column other than the first column