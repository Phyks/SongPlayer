# include "stdio.h"
# include "stdlib.h"
# include "string.h"

int main()
{
	char note[100];
	int stop = 0, duree = 0;
	
	while(stop == 0)
	{
		printf("Note ? ");
	    	scanf("%s", note);
	    	
	    	printf("Durée ? ");
	    	scanf("%d", duree);
	    	
	    	switch(note)
	    	{
	    		case "RE":
	    		printf("294:%d\n",duree);
	    		break;
	    		
	    		case "MI":
	    		printf("330:%d\n",duree);
	    		break;
	    		
	    		case "FA":
	    		printf("349:%d\n",duree);
	    		break;
	    		
	    		case "SOL":
	    		printf("392:%d\n",duree);
	    		break;
	    		
	    		case "LA":
	    		printf("440:%d\n",duree);
	    		break;
	    		
	    		case "SI":
	    		printf("494:%d\n",duree);
	    		break;
	    		
	    		case "DO":
	    		printf("523:%d\n",duree);
	    		break;
	    		
	    		case "RE2":
	    		printf("587:%d\n",duree);
	    		break;
	    		
	    		case "MI2":
	    		printf("659:%d\n",duree);
	    		break;
	    		
	    		case "FA2":
	    		printf("699:%d\n",duree);
	    		break;
	    		
	    		case "SOL2":
	    		printf("794:%d\n",duree);
	    		break;
	    		
	    		case "LA2":
	    		printf("880:%d\n",duree);
	    		break;
	    		
	    		case "SI2":
	    		printf("988:%d\n",duree);
	    		break;
	    		
	    		default:
	    		stop = 1;
	    		break;
	    	}
	}
    	
	return 0;
}
