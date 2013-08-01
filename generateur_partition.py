#!/usr/bin/python

import sys
import getopt

try:
    opts, args = getopt.gnu_getopt(sys.argv, "ho:", ["help", "output"])
except getopt.GetoptError:
    sys.exit("[ERROR] Unable to parse command line arguments. "
             "See -h option for more infos on how to use.")

for opt, arg in opts:
    if opt in ("-h", "--help"):
        print("Music sheet generator for the sound player. Usage :")
        print("-h \t --help \t Displays this help message")
        print("-o file \t --output file \t Save the generated music sheet to "
              "the specified file")

    elif opt in ("-o", "--output"):
        output = arg


continue_while = True
notes = {"RE": 294, "MI": 330, "FA": 349, "SOL": 392, "LA": 440, "SI": 494,
         "DO": 523, "RE2": 587, "MI2": 659, "FA2": 699, "SOL2": 794, "LA2": 880,
         "SI2": 988}
partition = ''

while continue_while:
    note = input("Note ? ")

    if note.lower() == "quit":
        continue_while = False
        continue

    length = input("Length ? ")

    try:
        length = int(length)
    except ValueError:
        continue_while = False
        sys.exit("[ERROR] Entered length is not a number.")

    if note.upper() not in notes.keys():
        sys.exit("[ERROR] Unknown note "+note+".")
    else:
        partition += str(notes[note.upper()])+":"+str(length)+"\n"
        print("\nPartition :\n"+partition)

if output != '':
    try:
        with open(output, 'w') as output_fh:
            output_fh.write(partition)
    except:
        sys.exit("[ERROR] Unable to write music sheet to the specified output"
                 "file.")
