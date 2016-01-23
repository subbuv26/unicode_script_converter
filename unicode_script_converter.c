#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<locale.h>

int main(int argc, char**argv)
{
	if(argc<3)
	{
		printf("Usage %s input_file output_file\n", argv[0]);
		exit(-1);
	}
	
	setlocale(LC_ALL, "");
	wchar_t *wcs, *nwcs;
	char line[500];
	int len,i, base, diff, choice=0;
	
	FILE *ifp=NULL, *ofp=NULL;
	ifp = fopen(argv[1], "r");
	ofp = fopen(argv[2], "w");
	
	fgets(line,500, ifp);
	len = mbstowcs(NULL, line,0)+1;
	wcs = malloc(len *sizeof(int));
	mbstowcs(wcs, line, len);
	base= (int) wcs[0];
	
	if(0x0900<=base && base<=0x097f)
	{
		base = 0x0900;
		printf("The file is in HINDI language\n");
	}
	else if(0x0980<=base && base<=0x09ff)
	{
		base = 0x0980;
		printf("The file is in BENGALI language\n");
	}
	else if(0x0a00<=base && base<=0x0a7f)
	{
		base = 0x0a00;
		printf("The file is in PUNJABI language\n");
	}
	else if(0x0a80<=base && base<=0x0aff)
	{
		base = 0x0a80;
		printf("The file is in GUJARATHI language\n");
	}
	else if(0x0b00<=base && base<=0x0b7f)
	{
		base = 0x0b00;
		printf("The file is in ODIYA language\n");
	}
	else if(0x0b80<=base && base<=0x0bff)
	{
		base = 0x0b80;
		printf("The file is in TAMIL language\n");
	}
	else if(0x0c00<=base && base<=0x0c7f)
	{
		base = 0x0c00;
		printf("The file is in TELUGU language\n");
	}
	else if(0x0c80<=base && base<=0x0cff)
	{
		base = 0x0c80;
		printf("The file is in KANNADA language\n");
	}
	else if(0x0d00<=base && base<=0x0d7f)
	{
		base = 0x0d00;
		printf("The file is in MALAYALAM language\n");
	}
	
	printf("Enter target language for your file\n");
s:	printf("1.Hindi\n2.Bengali\n3.Punjabi\n4.Gujarathi\n5.Odiya\n");
	printf("6.Tamil\n7.Telugu\n8.Kannada\n9.Malayalam\n");
	printf("choose any number for the language : ");
	scanf("%d", &choice);
	
	switch(choice)
	{
		case	1:	diff = 0x0900 - base;
					break;
		case	2:	diff = 0x0980 - base;
					break;
		case	3:	diff = 0x0a00 - base;
					break;
		case	4:	diff = 0x0a80 - base;
					break;
		case	5:	diff = 0x0b00 - base;
					break;
		case	6:	diff = 0x0b80 - base;
					break;
		case	7:	diff = 0x0c00 - base;
					break;
		case	8:	diff = 0x0c80 - base;
					break;
		case	9:	diff = 0x0d00 - base;
					break;
		default:	printf("choose a language from the given list only\n");
					goto s;
	}
	
	if(diff==0x0)
	{
		printf("Transmitting to same language isn't work full \n");
		printf("Select another language\n");
		goto s;
	}
	
	rewind(ifp);
	
	free(wcs);
		while((fgets(line, 500, ifp))!= NULL)
	{
		
		len = mbstowcs(NULL, line,0)+1;
		wcs = malloc(len *sizeof(int));
		nwcs = malloc(len *sizeof(int));
		mbstowcs(wcs, line, len);
		for(i=0;i<len-1;i++)
		{
			if(wcs[i]==' '|| wcs[i]=='\n' || wcs[i]=='.' || wcs[i]==',')
				nwcs[i]=wcs[i];
			else
				nwcs[i]=wcs[i] + diff;
				fprintf(ofp,"%lc", (int) nwcs[i]);
		}
		
	}
	printf("Transmitted to the target language\n");
	return 0;
	
}
