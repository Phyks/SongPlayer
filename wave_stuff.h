# ifndef _WAVE_STUFF_H_
# define _WAVE_STUFF_H_


/*
  read a sound wave file and save it in a float array which is allocated by the function
  char *file  : the filename of the sound wave file (example "c:\\music\\test.wav"
  int canal   : the canal to be read if the wav file is in stereo two values are possible 0 and 1
  int verbose : flag producing lost of debugging info if different of 0
  int *ny     : the address of an integer to return the number of points read
  int *freq   : the address of an integer to return the sampling frequency 
  if the function fails it return a null pointer
 */
float* read_wave_create_array(char *file, int canal, int verbose, int *ny, int *freq);
/*
  save an array of float in a file of format wav, 
  char *file        : the filename of the futur sound wave file (example "c:\\music\\test.wav"
  int BitsPerSample : the number of bits per sample (typically 16)
  int verbose       : flag producing lost of debugging info if different of 0
  int nx            : the number of points to save
  int Frequence     : the sampling frequency
  on success return 0 otherwise an error code 
 */
int save_wave_from_array(float *x, int nx, char *file, int Frequence, int BitsPerSample);

# endif

