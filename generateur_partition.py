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
        print("-h \t\t --help \t Displays this help message")
        print("-o file \t --output file \t Save the generated music sheet to "
              "the specified file")

        print("\nAllowed values for notes are RE, MI, FA, SOL, LA, SI, DO"
              "(corresponding to LA = 440Hz) and RE2, MI2, FA2, SOL2, LA2, "
              "SI2, DO2 (corresponding to LA2 = 880Hz)")

        print("\nYou can also use the corresponding english notations D0, E0, "
              "F0, G0, A (440Hz), B, C, D, E, F, G, A2, B2")

        print("\nTo quit, just enter \"quit\" as note")
        sys.exit()

    elif opt in ("-o", "--output"):
        output = arg


continue_while = True
notes = {"RE": 294, "MI": 330, "FA": 349, "SOL": 392, "LA": 440, "SI": 494,
         "DO": 523, "RE2": 587, "MI2": 659, "FA2": 699, "SOL2": 794,
         "LA2": 880, "SI2": 988}
notes_english = {"D0": 294, "E0": 330, "F0": 349, "G0": 392, "A": 440,
                 "B": 494, "C": 523, "D": 587, "E": 659, "F": 699, "G": 794,
                 "A2": 880, "B2": 988}

music_sheet = ''

while continue_while:
    note = input("Note ? ")

    if note.lower() == "quit" or note.lower() == "q":
        continue_while = False
        continue

    length = input("Length ? ")

    try:
        length = int(length)
    except ValueError:
        continue_while = False
        sys.exit("[ERROR] Entered length is not a number.")

    if note.upper() in notes.keys():
        music_sheet += str(notes[note.upper()])+":"+str(length)+"\n"
    elif note.upper() in notes_english.keys():
        music_sheet += str(notes_english[note.upper()])+":"+str(length)+"\n"
    else:
        sys.exit("[ERROR] Unknown note "+note+".")
    
    print("\nMusic sheet :\n"+music_sheet)

if output != '':
    try:
        with open(output, 'w') as output_fh:
            output_fh.write(music_sheet)
    except:
        sys.exit("[ERROR] Unable to write music sheet to the specified output"
                 "file.")
