# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "math.h"
# include "wave_stuff.h"
# ifndef M_PI
 # define M_PI 3.14159265358979323846
# endif 
# define TAILLE_MAX 100

char **str_split (char *s, const char *ct)
{
   char **tab = NULL;

   if (s != NULL && ct != NULL)
   {
      int i;
      char *cs = NULL;
      size_t size = 1;

/* (1) */
      for (i = 0; (cs = strtok (s, ct)); i++)
      {
         if (size <= i + 1)
         {
            void *tmp = NULL;

/* (2) */
            size <<= 1;
            tmp = realloc (tab, sizeof (*tab) * size);
            if (tmp != NULL)
            {
               tab = tmp;
            }
            else
            {
               fprintf (stderr, "Memoire insuffisante\n");
               free (tab);
               tab = NULL;
               exit (EXIT_FAILURE);
            }
         }
/* (3) */
         tab[i] = cs;
         s = NULL;
      }
      tab[i] = NULL;
   }
   return tab;
}

void generer_note(int freq, int note, int duree, float *xd, int start)
{  
  int i;
  
  for (i = start; i < start+duree; i++)
  {
  	xd[i] += (int)(32767 *sin(2*M_PI*note*i/freq));
  }
}

int main(int argc, char **argv)
{
  if (argc < 5)
    {
      fprintf(stderr,"Usage: %s partition output.wav bpm silence\nsilence should be 1 to add silence between notes.\n",argv[0]);
      return 0;
    }
    
  float *xd;
  int nx = 0, freq = 44100, canal = 0, verbose = 0, BitsPerSample = 16, dureeNote = 0, start = 0, n = 0, silence, Split1, Split2;
  float time = 1./atof(argv[3])*60.;
  char ligne[TAILLE_MAX];
  FILE* partition = NULL;
  
  partition = fopen(argv[1], "r");
  fgets(ligne, TAILLE_MAX, partition);
  n = atoi(ligne);
  silence = atoi(argv[4]);
  
  if(silence == 1)
  {
  	nx = (int)(freq*time*(n+n/8));
  }
  else
  {
  	nx = (int)(freq*time*n);
  }
  
  dureeNote = (int)(freq*time);
  xd = (float*)calloc(nx,sizeof(float));

  while(fgets(ligne, TAILLE_MAX, partition) != NULL)
  {
    if(strchr(ligne, ':')!=NULL)
    {
        char** Split=str_split(ligne, ":");
        Split1=atoi(Split[0]);
        Split2=atoi(Split[1]);
    }
    else
    {
    	Split1=atoi(ligne);
    	Split2=1;
    }
    
    generer_note(freq, Split1, Split2*dureeNote, xd, start);
    start += Split2*dureeNote;
    
    if(silence == 1)
    {
    	generer_note(freq, 0, (int)(Split2*dureeNote/8), xd, start);
   	start += (int)(Split2*dureeNote/8);
    }
  }
  
  save_wave_from_array(xd, nx, argv[2], freq, BitsPerSample);
  return 0;
}
