(Bad) Artificial Song Generator
===============================

This is just a simple C code to handle wave files (see files wave_stuf.* for the functions) and a simple application to generating purely artificial sounds (just by creating a wave file with values from a sine wave at the good frequency to make a note.

### Included files are :

* _examples_ folder with some examples music sheets and the resulting generated wave files
* _generateur.c_ which is the main program
* _generateur_partition.py_ which is just a simple program to generate basic music sheet to use with the main program
* _wave_stuff.*_ which are the functions to handle wave files

## Usage of the main program

The main program should be compiled using the makefile. 

To use it, just run from command line :
<code>generateur.out partition output.wav bpm silence</code> where 

* _partition_ is the path to the music sheet you want to generate
* _output.wav_ is the resulting wave files
* _bpm_ is the speed of the song (in bpm)
* _silence_ is an integer that should be set to 1 to add silences between notes

## Usage of the basic music sheet generator

This program allows you to write a simple music sheet without always looking for the correspondance between note and frequency. It is very basic and only allows you to use notes amongst :

* RE, MI, FA, SOL, LA, SI, DO (where LA is 440Hz)
* RE2, MI2, FA2, SOL2, LA2, SI2, DO2 (where LA is 880Hz).

Length is any integer you want. It will define the length of the note (play with both length and bpm params to get what you want).

You can use the -o (--output) option with a filename as argument to store the generated music sheet to this specific file.

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
