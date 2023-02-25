import csv
from os import path
from sys import argv


DATABASE = argv[1]
SEQUENCE = argv[2]

if path.isfile(DATABASE) == False:
    print("Usage: python dna.py data.csv sequence.txt")
else:
    f_database = open(DATABASE, 'r')

if path.isfile(SEQUENCE) == False:
    print("Usage: python dna.py data.csv sequence.txt")
else:
    f_sequence = open(SEQUENCE, 'r')


def main():
    header = f_database.readline()
    nucleotide_bases = header.split(',')
    nucleotide_bases = set_bases(nucleotide_bases)
    sequence = f_sequence.read()
    counted_sequences = {}

    for base in nucleotide_bases:
        lenght = len(base)
        sequence_tmp = sequence
        count = 0

        while sequence_tmp.find(base) != -1:
            index = sequence_tmp.find(base)
            result = count_bases(index, lenght, base, sequence_tmp)

            counter = result[0]
            index = result[1]

            if counter > count:
                count = 0
                count += counter
                sequence_tmp = sequence_tmp[index:]
                continue
            else:
                sequence_tmp = sequence_tmp[index:]
                continue

        counted_sequences.update({base: count})

    base_len = len(nucleotide_bases)
    match = ''

    for line in f_database:
        person = line.split(',')
        person[-1] = person[-1].strip()

        match = validate(nucleotide_bases, counted_sequences, person, base_len)
        if match != "No match":
            print(match)
            break

    if match == "No match":
        print(match)

def validate(nucleotide_bases, counted_sequences, person, lenght):
    checked = False
    for item in range(lenght):
        person_value = int(person[item + 1])
        if person_value == counted_sequences[nucleotide_bases[item]]:
            checked = True
        else:
            checked = False
            break

    if checked is True:
        return person[0]
    else:
        return "No match"

def count_bases(index, lenght, base, sequence):
    counter = 0

    while True:
        cut_sequence = sequence[index: index + lenght]

        if cut_sequence == base:
            counter += 1
            index += lenght
        else:
            return [counter, index]

def set_bases(nucleotide_bases):
    for base in nucleotide_bases:
        if base == "name":
            nucleotide_bases.remove(base)
        elif not base.isalpha():
            nucleotide_bases[-1] = nucleotide_bases[-1].strip()

    return nucleotide_bases

main()
f_database.close()
f_sequence.close()
