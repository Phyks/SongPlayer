
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "wave_stuff.h"


int main(int argc, char **argv)
{
  float *xd;
  int i, freq = 0, nx = 0, canal = 0, verbose = 0;

  if (argc < 3)
    {
      fprintf(stderr,"Usage: %s wavefile canal [verbose]\nExample %s d:\\low.wav 1\n",argv[0],argv[0]);
      return 0;
    }
  if (sscanf(argv[2],"%d",&canal) != 1)
    {
      fprintf(stderr,"cannot read canal value %s\n",argv[2]);
      return 1;
    }
  if (argc > 3)      sscanf(argv[3],"%d",&verbose);
  xd = read_wave_create_array(argv[1], canal, verbose, &nx, &freq);
  if (xd == NULL)
    {
      fprintf(stderr,"cannot read canal wave file %s\n",argv[1]);
      return 2;
    }
  printf("%% %s wave file, canal %d, frequence %d, nb. of sample %d\n",argv[1],canal,freq,nx);
  for (i = 0; i < nx; i++)
    printf("%d\n",(int)xd[i]);
 
  return 0;
}
