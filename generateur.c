# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "math.h"
# include "wave_stuff.h"
# include "getopt.h"
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

void print_help() {
    fprintf(stderr, "\t\t\t\t================\n");
    fprintf(stderr, "\t\t\t\t|| SongPlayer ||\n");
    fprintf(stderr, "\t\t\t\t================\n\n");
    fprintf(stderr, "Usage :\n");
    fprintf(stderr, "=======\n\tgenererateur.out options\n\n");
    fprintf(stderr, "Options :\n");
    fprintf(stderr, "=========\n");
    fprintf(stderr, "\t-h\t\t--help\t\t\tPrint this help message.\n");
    fprintf(stderr, "\t-o file\t\t--output file\t\tSpecify the output wave file (mandatory).\n");
    fprintf(stderr, "\t-b bpm\t\t--bpm bpm\t\tSpecify the speed in bpm to play the song (mandatory).\n");
    fprintf(stderr, "\t-m musicsheet\t--musicsheet\t\tSpecify the input music sheet to use (mandatory).\n");
    fprintf(stderr, "\t-s\t\t--silence\t\tAdd some silences between notes (optional).\n");
}

int main(int argc, char **argv)
{
    float *xd;
    int nx = 0, freq = 44100, canal = 0, verbose = 0, BitsPerSample = 16, dureeNote = 0, start = 0, n = 0, silence = 0, Split1, Split2;
    float time = 0.5;
    char ligne[TAILLE_MAX];
    char* output = NULL;
    FILE* musicsheet = NULL;

    const char* const short_options = "hm:b:o:s";
    const struct option long_options[] = {
        { "help", 0, NULL,  'h' },
        { "bpm", 1, NULL, 'b' },
        { "musicsheet", 1, NULL,  'm' },
        { "output", 1, NULL,  'o' },
        { "silence", 0, NULL,  's' },
        { NULL, 0, NULL,  0   }
    };
    int next_option = 0;

    do {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        switch(next_option)
        {
            case 'h':
                print_help();
                return EXIT_SUCCESS;
                break;

            case 'm':
                musicsheet = fopen(optarg, "r");
                break;

            case 'o':
                output = optarg;
                break;

            case 's':
                silence = 1;
                break;

            case 'b':
                time = 1./atof(optarg)*60.;
                break;
        }
    } while(next_option != -1);

    if(musicsheet == NULL || output == NULL) {
        print_help();
        return EXIT_SUCCESS;
    }

    fgets(ligne, TAILLE_MAX, musicsheet);
    n = atoi(ligne);

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

    while(fgets(ligne, TAILLE_MAX, musicsheet) != NULL)
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

    save_wave_from_array(xd, nx, output, freq, BitsPerSample);
    return 0;
}
