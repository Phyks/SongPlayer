(Bad) Artificial Song Generator
===============================

This is just a simple C code to handle wave files (see files wave_stuf.* for the functions) and a simple application to generate purely artificial sounds (just by creating a wave file with values from a sine wave at the good frequency to make a note).

### Included files are :

* _examples_ folder with some examples music sheets and the resulting generated wave files
* _generateur.c_ which is the main program
* _generateur_musicsheet.py_ which is just a simple program to generate basic music sheet to use with the main program
* _wave_stuff.*_ which are the functions to handle wave files

## Usage of the main program

The main program should be compiled using the makefile. 

To use it, just run from command line :
<code>./generateur.out options</code> where 

options are amongst :

* _-m_ (or _--musicsheet_) _file_ where _file_ is the path to the music sheet you want to generate. [mandatory argument]
* _-o_ (or _--output_) _file_ where _file_ is the resulting wave file. [mandatory argument]
* _-b_ (or _--bpm_) _bpm_ where _bpm_ is the speed of the song (in bpm). [mandatory argument]
* _-s_ (or _--silence_) to add silences between notes. [optional argument]
* _-h_ (or _--help_) to display an help message.

## Usage of the basic music sheet generator

This program allows you to write a simple music sheet without always looking for the correspondance between note and frequency. It is very basic and only allows you to use notes amongst :

* RE, MI, FA, SOL, LA, SI, DO (where LA is 440Hz)
* RE2, MI2, FA2, SOL2, LA2, SI2, DO2 (where LA is 880Hz).

or the english corresponding notations :

* D0, E0, F0, G0, A, B, C (where A is 440Hz)
* D, E, F, G, A2, B2, C2 (where A2 is 880Hz)

Length is any integer you want. It will define the length of the note (play with both _length_ and _bpm_ (during playback) params to get what you want).

You can use the _-o_ (_--output_) option with a filename as argument to store the generated music sheet to this specific file.

## License
### TLDR;
	I don't give a damn to anything you can do using this code. It would just be nice to
	quote where the original code comes from.


--------------------------------------------------------------------------------
  	"THE NO-ALCOHOL BEER-WARE LICENSE" (Revision 42):
  
  	Phyks (phyks@phyks.me) wrote this file. As long as you retain this notice you
 	 can do whatever you want with this stuff (and you can also do whatever you want
 	 with this stuff without retaining it, but that's not cool... :/ ). If we meet some 
 	 day, and you think this stuff is worth it, you can buy me a <del>beer</del> soda 
 	 in return.
  																			Phyks
---------------------------------------------------------------------------------
