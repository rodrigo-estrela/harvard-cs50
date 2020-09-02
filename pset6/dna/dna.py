import csv
import sys
from collections import OrderedDict


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

    for tandem in range(1, len(fields)):
        person[fields[tandem]] = readSTR(dna, fields[tandem])

    # Compra the STR counts against each row in the CSV file
    for k, v in db.items():
        matched = True
        # Loop over the fields of a line, except from name field
        for key, tandem in v.items():
            if key != 'name':
                if int(tandem) != person[key]:
                    matched = False
                    break
        if matched:
            print(k)
            return 0

    print('No match')


# Compute the longest run of consecutive repeats in the DNA sequence
def readSTR(s, STR):
    str_len = len(STR)
    sequence_len = len(s)

    i = 0
    longest_run = 0  # Keep track of the longest STR run in the sequence
    while (s.find(STR) >= 0):
        run = 1
        i = s.index(STR) + str_len
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