#include<stdio.h>

void print_email(char* s1, char*s2)
{
	FILE *fout = fopen("emails.dat", "a");
	char* s_rev;
	s_rev = (char*)malloc(sizeof(char)*200);
	int i=0;
	int k=0;
	while(s1[i++]);
	for(int j=i-1; j>=0; j--)
	{
		if(s1[j]==0) continue;
		s_rev[k++] = s1[j];
	}
	for(int j=0; s2[j]; j++)
	{
		if(s2[j]==0) continue;
		s_rev[k++] = s2[j];
	}
//	printf("%d", k);
	int c=0;
	for(int j=0; j<k; j++)
	{
		if(s_rev[j]=='.') c++;
//		printf("%c", s_rev[j]);
	}
	if(c==0) return;
	s_rev[k] = '\n';
	fwrite(s_rev, 1, k+1, fout);
}

int isAlphabetOrDigit(char c)
{
	int d = (int)c;
//	printf("%d", d);
	if(d==0) return 1;  //@ char is bounded by a '0' char. Dont know why. Drove me crazy for half an hour
	if(d==95) return 1; //_
	if(d==46) return 1; //.
	if(d>=64 && d<=90) return 1; //capital alphabets
	if(d>=48 && d<=57) return 1; //digits
	if(d>=97 && d<=122) return 1;//small aplhabets
	return 0;
}


void get()
{
	FILE *fin = fopen("google.csv", "r");
	long lSize;
	char * buffer;
	size_t result;
	char *email1;
	char *email2;

	int i;
	int j;
	int k;
	int count = 0;
	char *s_rev = (char*)malloc(sizeof(char)*200);


	// obtain file size:
	fseek (fin , 0 , SEEK_END);
	lSize = ftell (fin);
	rewind (fin);
	buffer = (char*) malloc (sizeof(char)*lSize);


	fread (buffer,1,lSize,fin);

	email1 = (char*) malloc (sizeof(char)*200);
				for(i=0; i<200; i++)
				{
					email1[i]=NULL;
				}
	email2 = (char*) malloc (sizeof(char)*200);
				for(i=0; i<200; i++)
				{
					email2[i]=NULL;
				}

	
	for(i=0; i<lSize; i++)
	{	
		if(buffer[i]=='@')	//if its a @
		{	j=i;
			count++;
			k=0;			
			while(isAlphabetOrDigit(buffer[j])) //go back in the line until you find a " "
			{
				if(buffer[j] == 0) {j--; continue;}
				email1[k++]=buffer[j--];
			}
			email1[k] = NULL;
			j=i+1;		//go to the '@' index
			k=0;
			while(buffer[j]!=',')	//go ahead from '@' until you find a " "
			{			
				if(buffer[j] == 0) { j++; continue;}
				email2[k++] = buffer[j++];
			}
			email2[k] = '\0';	//NULL at end of email id
			print_email(email1, email2);
			}
	}
	printf("%d", count);
	free(buffer);
}


int main()
{
	get();
	return 0;
}
