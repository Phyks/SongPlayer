# ifndef _WAVE_STUFF_C_
# define _WAVE_STUFF_C_

# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "wave_stuff.h"



int save_wave_from_array(float *x, int nx, char *file, int Frequence, int BitsPerSample)
{
  FILE *fp;
  unsigned char *uch;
  int  i, j, FileSize, tmp, BytePerSec, DataSize, data, noctets;
  short int AudioFormat = 1, NbrCanaux = 1, BytePerBloc, BitsPerSamp;

  if (file == NULL || x == NULL) return -1;

  noctets = BitsPerSample/8;
  BytePerBloc = (NbrCanaux * BitsPerSample/8);
  DataSize = nx * BytePerBloc; 
  FileSize = DataSize + 44;
  BytePerSec = Frequence * BytePerBloc;  
  BitsPerSamp = (short int)BitsPerSample;
  fp = fopen(file,"wb");
  if (fp == NULL) {fprintf(stderr,"could not open file %s to save wav",file);return 1;}
  // [Bloc de déclaration d'un fichier au format WAVE] 12 octets
  if (fwrite("RIFF",sizeof(char),4,fp) != 4)    {fclose(fp); return 2;}
  if (fwrite(&FileSize,sizeof(int),1,fp) != 1)  {fclose(fp); return 3;}
  if (fwrite("WAVE",sizeof(char),4,fp) != 4)    {fclose(fp); return 4;}
  // [Bloc décrivant le format audio]   24 octets
  if (fwrite("fmt ",sizeof(char),4,fp) != 4)    {fclose(fp); return 5;}
  tmp = 16; //Nombre d'octets du bloc - 8  (0x10) 
  if (fwrite(&tmp,sizeof(int),1,fp) != 1)       {fclose(fp); return 6;}
  if (fwrite(&AudioFormat,sizeof(short int),1,fp) != 1)      
    {fclose(fp); return 7;}
  if (fwrite(&NbrCanaux,sizeof(short int),1,fp) != 1)      
    {fclose(fp); return 8;}
  if (fwrite(&Frequence,sizeof(int),1,fp) != 1) {fclose(fp); return 9;}
  if (fwrite(&BytePerSec,sizeof(int),1,fp) != 1) {fclose(fp); return 10;}
  if (fwrite(&BytePerBloc,sizeof(short int),1,fp) != 1)      
    {fclose(fp); return 11;}
  if (fwrite(&BitsPerSamp,sizeof(short int),1,fp) != 1)      
    {fclose(fp); return 12;}
  // [Bloc des données] 8 octets + datasize
  if (fwrite("data",sizeof(char),4,fp) != 4)    {fclose(fp); return 13;}
  if (fwrite(&DataSize,sizeof(int),1,fp) != 1) {fclose(fp); return 14;}
  for (j = 0, uch = (unsigned char*)&data; j < nx; j++)
    {
      data = (int)x[j];
      if (fwrite(uch,sizeof(unsigned char),noctets,fp) != noctets)    
	{fclose(fp); return j;}
    }
  fclose(fp);
  return 0;
}



float* read_wave_create_array(char *file, int canal, int verbose, int *ny, int *freq)
{
  FILE *fp;
  char ch[16];
  unsigned char uch[4];
  int i, j, FileSize, BytePerSec, DataSize, nx, data, noctets;
  short int AudioFormat = 1, NbrCanaux, BytePerBloc, BitsPerSamp, si;
  int Frequence, offset, cont; 
  float *xd;

  if (file == NULL) return NULL; 

  fp = fopen(file,"rb"); 
  if (fp == NULL) 
    { fprintf(stderr,"could not open file %s to read wav",file); return NULL;}
  // [Bloc de déclaration d'un fichier au format WAVE] 12 octets
  if (fread(ch,sizeof(char),4,fp) != 4)    // read 4
    {      fclose(fp);       fprintf(stderr,"could not read RIFF label"); return NULL;   }
  if (strncmp(ch,"RIFF",4) != 0)
    {      fclose(fp);       fprintf(stderr,"could not read RIFF tag"); return NULL;   }
  if (fread(&FileSize,sizeof(int),1,fp) != 1)      // read 4
    {      fclose(fp);       fprintf(stderr,"could not read File size");    return NULL;}
  if (verbose)  fprintf(stderr,"file size %d",FileSize);
  if (fread(ch,sizeof(char),4,fp) != 4)        // read 4
    {      fclose(fp);       fprintf(stderr,"could not read WAVE label");   return NULL; }
  if (strncmp(ch,"WAVE",4) != 0)         
    {      fclose(fp);       fprintf(stderr,"could not read WAVE tag");   return NULL; }

  // [Bloc décrivant le format audio]   24 octets
  if (fread(ch,sizeof(char),4,fp) != 4)   // read 4  
    {      fclose(fp);       fprintf(stderr,"could not read fmt label");   return NULL; }
  if (strncmp(ch,"fmt ",4) != 0)  
    {      fclose(fp);       fprintf(stderr,"could not read fmt tag");   return NULL; }
  if (fread(&offset,sizeof(int),1,fp) != 1) // read 4  
    {      fclose(fp);       fprintf(stderr,"could not read offset");   return NULL; }
  if (verbose) fprintf(stderr,"offset %d",offset); // read 4
  if (fread(&AudioFormat,sizeof(short int),1,fp) != 1) // read 2  
    {      fclose(fp);       fprintf(stderr,"could not read Audio format");    return NULL;}
  if (fread(&NbrCanaux,sizeof(short int),1,fp) != 1)   // read 2
    {      fclose(fp);       fprintf(stderr,"could not read Nb. of canaux");    return NULL;}
  if (verbose) fprintf(stderr,"NbrCanaux %d",(int)NbrCanaux); // read 4
  if (fread(&Frequence,sizeof(int),1,fp) != 1)  
    {      fclose(fp);       fprintf(stderr,"could not read Frequence");   return NULL; }
  if (verbose)  fprintf(stderr,"Frequence %d",Frequence);  // read 4
  if (fread(&BytePerSec,sizeof(int),1,fp) != 1)  
    {      fclose(fp);       fprintf(stderr,"could not read BytePerSec");    return NULL;}
  if (verbose) fprintf(stderr,"BytePerSec %d",BytePerSec);
  if (fread(&BytePerBloc,sizeof(short int),1,fp) != 1) // read 2  
    {      fclose(fp);       fprintf(stderr,"could not read BytePerSec");    return NULL; }
  if (verbose) fprintf(stderr,"BytePerBloc %d",(int)BytePerBloc);
  if (fread(&BitsPerSamp,sizeof(short int),1,fp) != 1)  // read 2
    {      fclose(fp);       fprintf(stderr,"could not read BitsPerSamp");   return NULL; }
  if (verbose) fprintf(stderr,"BitsPerSamp %d",(int)BitsPerSamp);
  // [Bloc des données] 8 octets + datasize
  if (fread(ch,sizeof(char),4,fp) != 4)    // read 4
    {      fclose(fp);       fprintf(stderr,"could not read data label");    return NULL;}

  if (strncmp(ch,"LIST",4) == 0)
    {
      if (fread(&offset,sizeof(int),1,fp) != 1) // read 4  
	{      fclose(fp);   fprintf(stderr,"could not read offset");    }
      if (verbose) fprintf(stderr,"found list block skipping %d bytes",offset);
      for (i = 0; i < offset; i++)
	{
	  if (fread(ch,sizeof(char),1,fp) != 1)    
	    {      fclose(fp);   fprintf(stderr,"could not read data");    return NULL;}
	}
      if (fread(ch,sizeof(char),4,fp) != 4)    // read 4
	{      fclose(fp);       fprintf(stderr,"could not read data label");    return NULL;}
    }
  if (strncmp(ch,"data",4) != 0)
    {
      ch[4] = 0;
      cont = 0;
      fprintf(stderr,"could not read data tag!\n read %s instead "
	      "\ntype 1 to continue anything else to stop",ch);
      scanf("%d",&cont);
      if (cont == 1) 
	{
	  fclose(fp); 
	  return NULL;
	}
    }
  if (fread(&DataSize,sizeof(int),1,fp) != 1)  // read 4
    {
      fclose(fp); 
      fprintf(stderr,"could not read datasize");
      return NULL;
    }
  noctets = BitsPerSamp/8;
  nx = DataSize/BytePerBloc;
  if (verbose) fprintf(stderr,"DataSize %d nx %d noctets %d" ,DataSize,nx,noctets);

  if (BytePerBloc != (NbrCanaux * BitsPerSamp/8))
    {
      fclose(fp); 
      fprintf(stderr,"Byte per bloc pb!\n"
	      "Byte per bloc %d != NbrCanaux %d x Bitspersample %d/8"
	      ,BytePerBloc,(int)NbrCanaux,(int)BitsPerSamp);
      return NULL;
    }
  /*
  if (FileSize != DataSize + 44)
    {
      cont = 0;
      i = fprintf(stderr,"File size pb!\n"
		  "File size %d != datasize %d + 44"
		  "\ntype 1 to continue anything else to stop"
		  ,FileSize,DataSize);
      scanf("%d",&cont);
      if (cont == 1) 
	{
	  fclose(fp); 
	  return NULL;
	}
    }
  */
  if (BytePerSec != Frequence * BytePerBloc)
    {
      cont = 0;
      i = fprintf(stderr,"Byte count pb!\n"
		  "Byte per sec %d != Frequence %d x Byte per bloc %d"
		  "\ntype 1 to continue anything else to stop"
		  ,BytePerSec,Frequence,BytePerBloc);
      scanf("%d",&cont);
      if (cont == 1) 
	{
	  fclose(fp); 
	  return NULL;
	}
    }  
  xd = (float*)calloc(nx,sizeof(float));
  if (xd == NULL) 
    {
      fclose(fp); 
      fprintf(stderr,"could not create float array");
      return NULL;
    }
  if (freq) *freq = Frequence;
  if (ny) *ny = nx;
  for (j = 0; j < nx; j++)
    {
      for (i = 0; i < NbrCanaux; i++)
	{
	  uch[0] = uch[1] = uch[2] = uch[3] = 0;
	  data = 0;
	  if (noctets == 1)      
	    {
	      if (fread(uch,sizeof(unsigned char),noctets,fp) != noctets)  
		{
		  fclose(fp); 
		  fprintf(stderr,"could not read unsigned int data at %d %d",i,j);
		  return NULL;
		}
	      data = uch[0];
	    }
	  if (noctets == 2)
	    {
	      if (fread(&si,sizeof(short int),1,fp) != 1)  
		{
		  fclose(fp); 
		  fprintf(stderr,"could not read short int data at %d %d",i,j);
		  return NULL;
		}
	      data = (int)si;
	    }
	  if (noctets == 3)
	    { // to be checked
	      if (fread(uch,sizeof(unsigned char),noctets,fp) != noctets)  
		{
		  fclose(fp); 
		  fprintf(stderr,"could not read data at %d %d",i,j);
		  return NULL;
		}
	      data = (uch[0] << 8) | (uch[1] << 16) | (uch[2] << 24);
	      data /= 256;
	    }
	  if (i == canal) xd[j] = (float)data;
	}
    }
  fclose(fp);
  return xd;
}



# endif
