
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "wave_stuff.h"

# define MAX_LINE_LENGTH 1024


int main(int argc, char **argv)
{
  char line[MAX_LINE_LENGTH], *l;
  float *xd = NULL;
  int i, freq = 0, nx = 0, canal = 0, BitsPerSample = 16, data, min, max;
  FILE *fp;

  if (argc < 4)
    {
      fprintf(stderr,"Usage: %s wave_data.txt wavefile_to_create.wav frequency BitsPerSample\nExample %s d:\\low.wav 44100 16\n",argv[0],argv[0]);
      return 0;
    }
  if ((fp = fopen(argv[1], "r")) == NULL)
    {
      fprintf(stderr,"cannot open file %s\n",argv[1]);
      return 1;
    }
  if (sscanf(argv[3],"%d",&freq) != 1)
    {
      fprintf(stderr,"cannot read freq value %s\n",argv[3]);
      return 1;
    }
  if (argc > 4)      sscanf(argv[4],"%d",&BitsPerSample);

  for(nx = 0, l = fgets(line, MAX_LINE_LENGTH, fp); l != NULL; l = fgets(line, MAX_LINE_LENGTH, fp))
    {
      if (strcspn(line,"%") >= strlen(line))
	{
	  if (sscanf(line,"%d",&data) == 1)
	      nx++;
	} 
    }  
  fclose(fp);
  if (nx <= 0) 
    {
      fprintf(stderr,"could not read data");
      return 2;
    }
  xd = (float*)calloc(nx,sizeof(float));
  if (xd == NULL) 
    {
      fprintf(stderr,"could not create float array");
      return 2;
    }
  min = max = 0;
  fp = fopen(argv[1], "r");
  for(i = 0, l = fgets(line, MAX_LINE_LENGTH, fp); l != NULL; l = fgets(line, MAX_LINE_LENGTH, fp))
    {
      if (strcspn(line,"%") >= strlen(line))
	{
	  if (sscanf(line,"%d",&data) == 1)
	    {
	      xd[i] = (float)data;
	      i++;
	    }
	} 
    }  
  fclose(fp);
  printf("%d sample read\n",nx);
  i = save_wave_from_array(xd, nx, argv[2], freq, BitsPerSample);
  if (i)
    {
      fprintf(stderr,"cannot save wave file %s\n",argv[2]);
      return 2;
    }
  free(xd);
  return 0;
}
