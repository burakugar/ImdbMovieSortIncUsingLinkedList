#include <stdio.h> /* libraries that will be used */
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 1024
/* IMPORTANT: IF THE COMPUTER MEMORY IS NOT ENOUGH, PROGRAM MAY CRASH. I TRY IT ON VIRTUAL MACHINE WHICH HAS LESS MEMORY COMPARING DUAL BOOT AND PROGRAM CRASHED. BUT WHEN I TRIED IT ON A LINUX SYSTEM IT WORK PERFECTRLY */

typedef struct Movie_Budget { /* struct that holds the infos of the movies MAIN STRUCT */
	int budget;
	int year;
	char* name;
	struct Movie_Budget* next;
}movie_budget;
typedef struct genre_s{
/* struct that holds the genre informations of the whole movies we will order the movies by genre
with using this struct*/
/* This struct also holds the each genre's value */
	char* genre;
	int numb;
}genre_s;
typedef struct Movie_Name { /* struct that holds the infos of the movies MAIN STRUCT */
	char* genre;
	char* name;
	double score;
	struct Movie_Name* next;
}movie_name;
typedef struct movies{
	int budget;
	int year;
	char* name;
	char* genre;
	double score;
}movies;
void printList(movie_budget** head, movie_name** head1){
	movie_budget *iter = *head;
	movie_name *iter1= *head1;
   	while ( iter != NULL && iter1 !=NULL) {
        printf("Budget:%-25d      Name:%-55s     Year:%-25d      Score:%lf       Genre:%-25s \n", iter->budget, iter->name,iter->year,iter1->score,iter1->genre);
        iter = iter->next;
        iter1 = iter1->next;
    }
}
void swap(movie_budget *a, movie_budget *b, int max)
{
    int temp = a->year; /* this function swaps the two given linked list element's nodes */
    int budget= a->budget;
    char* temp1= (char*) malloc(sizeof(char)*max); /* this temporary pointer is for swap implemantation */
    strcpy(temp1, a->name);
    a->year = b->year;
    a->budget= b->budget;
    strcpy(a->name,b->name);
    b->year = temp;
    b->budget= budget;
    strcpy(b->name,temp1);
    
}
void swap1(movie_name *a, movie_name *b, int max)
{ /* this function is the swap function for the movie_name nodes */
 /* when we implement bubble sort for movie_name nodes this function will work */
    double score = a->score;
    char* genre= (char*) malloc(sizeof(char)*max);
    char* name= (char*) malloc(sizeof(char)*max);
    strcpy(name, a->name);
    strcpy(genre,a->genre);
    a->score = b->score;
    strcpy(a->name,b->name);
    strcpy(a->genre,b->genre);
    b->score = score;
    strcpy(b->genre,genre);
    strcpy(b->name,name);
    
}

void bubbleSort(movie_budget** head,movie_name** head1,int max) /* this function implements the bubble sort algorithm for movie_budget linked list*/
{
    int flag, i;
    movie_budget* ptr1;
    movie_budget* temp1 = NULL;
    movie_name* ptr2;
    movie_name* temp2 = NULL;
  
    /* if linked list ara empty then exit from the linked list */
    if (head == NULL && head1== NULL)
        return;
    do
    {
        flag = 0;
        ptr1 = *head;
  	ptr2= *head1;
  	for(;ptr1->next == temp1; ptr1= ptr1->next, ptr2=ptr2->next)
        {
            if (ptr1->year > ptr1->next->year)
            { 
                swap(ptr1, ptr1->next,max);
                swap1(ptr2, ptr2->next,max);
                flag = 1;
            }
        }
        temp1 = ptr1;
        temp2= ptr2;
    }
    while (flag!=0);
}

void countcharsinLine(FILE* fp, int l, int* numboflines) {
	int x, i, j;
	int len;
	int count = 0;
	char* temp = (char*)malloc(sizeof(char) * MAX_BUFFER); /* since we can not read the lines without knowing how much
	character in that line, we have to determine a proper guess about what can it be.For example, fgetc or getc is not new line
	sensetive functions. There is no way us to find the new line with that functions. Same fact is valid for fscanf and fgets too.
	So, reading whole line with a temp buffer and after using strlen to find number of character is the most valid solution. */
	for (i = 0; i < l; i++) { /* Until reaching end of file, we are reading the file line by line and saving the number of characters
	in a line in the int** numboflines */
		fgets(temp, MAX_BUFFER, fp);
		len = (int)strlen(temp);
		*(numboflines + i) = len;
	}
}

void addList(movie_budget** head, movie_name** head1,int budget, double score, char* genre, char* name, int year,int max,int i) {
	int flag=0;
	movie_budget* current= *head;
	movie_name* current1= *head1;
	
	if((*head)==NULL || (*head1)==NULL){ /* if all linked lists are empty */
		(*head)= (movie_budget*) malloc(sizeof(movie_budget)); 	/* allocate the head pointers of the link list and create first
		nodes*/
		(*head1)= (movie_name*) malloc(sizeof(movie_name)); /* allocate the head pointers of the link list and create first
		nodes*/	
		(*head)->budget=budget; 
		(*head)->name= (char*) malloc(sizeof(char)*max); /* before we fill the name and genre, we have to allocate char*'s */
		(*head)->year=year;
		strcpy((*head)->name,name);	/* fill the first node with informations of the first movie */
		(*head1)->name= (char*) malloc(sizeof(char)*max);
		(*head1)->genre= (char*) malloc(sizeof(char)*max);
		strcpy((*head1)->name,name);	
		(*head1)->score=score;			
		strcpy((*head1)->genre,genre);
		(*head)->next= NULL; /* head1-> empty node ->NULL */
		(*head1)->next= NULL; /* head1-> empty node ->NULL */
		goto v; /* when the filling is done, go to the next movie, quit from the loop*/
	}
	else if((*head)->year == year){ /* this else if block is available when there is only one node in the linked list and the next node's year is equal to the head node */
		if((*head)->budget > budget){
			movie_budget* temp= (movie_budget*) malloc(sizeof(movie_budget*)); 
			/* temp is temporary node which holds the informations of the movie that will be added*/
			/* if the node's year will be added is not greater than the head note such as head:200 and node is: 100
			then add it in from of the node */
			temp->budget= budget; 
			temp->year= year; 
			temp->name= (char*) malloc(sizeof(char)*max);
			strcpy(temp->name,name);
			temp->next= *head; 
			movie_name* temp1= (movie_name*) malloc(sizeof(movie_name*)); 
			temp1->score= score;		
			temp1->name= (char*) malloc(sizeof(char)*max);
			temp1->genre= (char*) malloc(sizeof(char)*max);
			strcpy(temp1->name,name);
			strcpy(temp1->genre,genre);
			temp1->next= *head1; /* visualization: head-> node1->null */
						/* head->node1->node2 -> null */
			*head= temp;
			*head1=temp1;
			goto v;
	}
		else{	/* if the node is greater than head note such as head: 1990 temp: 1991 then we have to add the node at the end of the linked list */
			movie_budget* temp= (movie_budget*) malloc(sizeof(movie_budget*)); 
			temp->budget= budget; 
			temp->year= year;
			temp->name= (char*) malloc(sizeof(char)*max);
			strcpy(temp->name,name);
			movie_name* temp1= (movie_name*) malloc(sizeof(movie_name*)); 
			temp1->score= score;		
			temp1->name= (char*) malloc(sizeof(char)*max); /* allocating new node's elements */
			temp1->genre= (char*) malloc(sizeof(char)*max);
			strcpy(temp1->name,name);
			strcpy(temp1->genre,genre);
				while(current->next->year == year && current->next->budget > budget ){
				current= current->next; /* if there are any element in the linked list such as 1991, we have to make the order according to budgets */
				current1=current1->next;
				}
			temp->next= current->next;
			temp= current->next;
			goto v;
	}
	
	}
	else if((*head)->year > year){ /* if there is one node in the linked list and the node's year that will be added is not greater than the node in the linked list we have to add
	the new node in front of the current node */
	/* such as if the current node in the linked list is 1999, and if our node is 1998 we have to move create linked list such that: head -> 1998 -> 1999 -> null */
			movie_budget* temp= (movie_budget*) malloc(sizeof(movie_budget*)); /* we did create a new node and temp points to it */
			/* head (iter)-> first movie ->NULL */
			temp->budget= budget; /* filling the temp node's elements */
			temp->year= year;
			temp->name= (char*) malloc(sizeof(char)*max);
			strcpy(temp->name,name);
			temp->next= *head; // temp-> yeni gelen bilgilerle dolan kutucuk -> head(iter) -> ilk filmin bilgileri -> NULL
			movie_name* temp1= (movie_name*) malloc(sizeof(movie_name*)); // temp1-> bos kutucuk
			/* head (iter)-> new movie ->NULL */
			temp1->score= score;		
			temp1->name= (char*) malloc(sizeof(char)*max);
			temp1->genre= (char*) malloc(sizeof(char)*max);
			strcpy(temp1->name,name);
			strcpy(temp1->genre,genre);
			temp1->next= *head1; /* temp-> new node -> head(iter) -> first node -> NULL*/
			*head= temp;
			*head1=temp1;
			goto v;
			} 
	else {
	/* if there is one node in the linked list and the node's year that will be added is greater than the node in the linked list we have to add
	the new node at the end of the current node */
	/* such as if the current node in the linked list is 1999, and if our node is 2000 we have to move create linked list such that: head -> 1999 -> 2000 -> null */
		movie_budget* iter= (*head); /* iterators that we will be used for creating linked lists */ 
		movie_name* iter1= (*head1);
		movie_budget* equal;
		movie_name* equal1; /* to implement this algorithm we have to go through null with iterators and in the last node we have to add the current node */
		movie_budget* prev;
		movie_name* prev1;
		while(iter!=NULL){
			if(iter->year == year){
			equal= iter;
			equal1=iter1; /* if there are movies with the same year make the flag assing it's place to equal */
			flag=1;
			goto k;
			}
		prev=iter;
		prev1=iter1;
		iter=iter->next;
		iter1=iter1->next;
		}
		k:
		iter= *head;
		iter1= *head1;
		if(flag==1){ /* if flag==1, then we know there are at least one movie which have the same year with the node to be added */
			if(budget<= equal->budget){ /* we have to add the new node according to budget */
				movie_budget* temp2= (movie_budget*) malloc(sizeof(movie_budget*)); 
				movie_name* temp3= (movie_name*) malloc(sizeof(movie_name*)); 
				temp2->year= year;
				temp2->budget= budget;
				temp2->name= (char*) malloc(sizeof(char)*max);
				strcpy(temp2->name,name);
				temp3->name= (char*) malloc(sizeof(char)*max); /* allocating and filling the name and genre strings of the movie_budget list */
				temp3->genre= (char*) malloc(sizeof(char)*max);
				strcpy(temp3->name,name);
				strcpy(temp3->genre,genre);
				temp3->score=score;
				temp2->next=equal;
				prev->next=temp2;
				temp3->next=equal1;
				prev1->next=temp3;
			}
			
			else /* this else is available for the linked list such as: 2000-> 2001 -> 2003-> NULL and when the new node is 2002 and final linked list have to be
			2000->2001->2002->2003->NULL */ 

			{ 
				while(equal->next!= NULL && equal->next->year == year && equal->next->budget < budget){
				equal=equal->next; /* go forward since 2002 is greater then current node's year */
				equal1=equal1->next;
			}
				movie_budget* temp2= (movie_budget*) malloc(sizeof(movie_budget*)); 
				movie_name* temp3= (movie_name*) malloc(sizeof(movie_name*)); 
				temp2->year= year;
				temp2->budget= budget;
				temp2->name= (char*) malloc(sizeof(char)*max);
				strcpy(temp2->name,name);
				temp3->name= (char*) malloc(sizeof(char)*max); /* allocating and filling the name and genre strings of the movie_budget list */
				temp3->genre= (char*) malloc(sizeof(char)*max);
				strcpy(temp3->name,name);
				strcpy(temp3->genre,genre);
				temp3->score=score;
				temp2->next=equal->next;
				equal->next= temp2;
				temp3->next=equal1->next;
				equal1->next= temp3;
			}
			goto v;	
		}
		else{ 
		/* if all the possibilies are not satisfied then we know we have to add the element at the end of the linked list */
			while(iter->next!= NULL && iter->next->year < year){
			/* we move the iter through the end of the linked list to add new node to the end*/
				iter=iter->next;
				iter1=iter1->next;
			}	
				movie_budget* temp2= (movie_budget*) malloc(sizeof(movie_budget*)); // temp-> bos kutucuk
				movie_name* temp3= (movie_name*) malloc(sizeof(movie_name*)); // temp1-> bos kutucuk
				temp2->next= iter->next;
				iter->next= temp2;
				temp2->year= year;
				temp2->budget= budget;
				temp2->name= (char*) malloc(sizeof(char)*max);
				strcpy(temp2->name,name);
				temp3->next= iter1->next; /* adding new node to the end */
				iter1->next=temp3;
				temp3->name= (char*) malloc(sizeof(char)*max); /* allocating and filling the name and genre strings of the movie_budget list */
				temp3->genre= (char*) malloc(sizeof(char)*max);
				strcpy(temp3->name,name);
				strcpy(temp3->genre,genre);
				temp3->score=score;
				goto v;
			 }
			
			}
		v:;
		}
int calculateLine(FILE* fp) { /* this function returns the number of lines in given file */
	int n, x, count = 0;
	char* str = (char*)malloc(sizeof(char) * 1000); /* for calculating the line number, we choose a big number to allocate */
	while (fgets(str, 1000, fp) != NULL) {
		count++;
	}
	return count;
}
/* this function manages the file and receiving the inputs */
int findmaxofeachLine(int l, int* numboflines) {
	int i, max;
	max = numboflines[0]; /* this function calculates the maximum characters in the lines for the given file */
	for (i = 1; i < l; i++) {
		if (numboflines[i] > numboflines[i - 1]) {
			max = numboflines[i]; /* comparing the element consequently */
		}
	}
	return max;
}
void findRepeat(movie_budget** head, movie_name** head1,int budget, double score, char* genre, char* name, int year){
	movie_budget* iter;
	movie_name* iter1;
	iter= *head;
	iter1= *head1;
	while(iter->next != NULL && (*head)->next != NULL){ 
		if(strcmp(name,iter->name)==0){
			iter->budget=budget;
			strcpy(iter->name,name);
			iter->year=year;
			goto a;
		}
		iter=iter->next;
	}
	a:
	while(iter1 != NULL && *head1 != NULL){
		if(strcmp(name,iter1->name)==0){
			iter1->score=score;
			strcpy(iter1->name,name);
			strcpy(iter1->genre,genre);
			return;
		}
		iter1=iter1->next;
	}
}
/* this function takes the movie budget and name linked lists head pointers and reverse them to get descending order */
/* we added the elements at the end of the program in ascending order using bubble sort this time we are reversing the oreder */
void reverseList(movie_budget** head, movie_name** head1){
	movie_budget *iter,*pre,*next;
	movie_name *iter1,*pre1,*next1;
	iter=*head;
	pre=NULL; /* we are using iterators to make the order reverse */
	while(iter!=NULL){
		next=iter->next; /* we first create a new node which holds the previous state of the current node and at each iteration we are changing the current->next backwards */
		iter->next=pre;
		pre=iter;
		iter=next;
	}
	*head=pre;
	iter1=*head1;
	pre1=NULL;
	while(iter1!=NULL){
		next1=iter1->next;
		iter1->next=pre1;
		pre1=iter1;
		iter1=next1;
	}
	*head1=pre1; /* at the end, we are making the reverse node's head as our list's head pointer */
}
void printMenu(int* n) { /* Printing the menu to the panel */
	int scanf_control;
	printf("\n1. List of the Sorted Data\n");
	printf("2. List of the Genres\n");
	printf("3.List of the Movie Through the Years\n");
	printf("4.List of the Movie Through the Scores\n");
	printf("5.All Informations of a Single Movie\n");
	printf("6.Avarage of the IMDB Scores\n");
	printf("7.Frequence of the Genres\n");
	printf("8.Exit\n");
	printf("\nPlease Select an Operation: ");
	scanf_control = scanf("%d", &(*n)); /* scanning the menu option */
	if (*n > 8 || *n < 1 || scanf_control != 1) {
		printf("Try Again! \n"); /* if the menu option is not in the interval or a char printf error message */
	}
}
/* implements bubblesort for the budgets */
void bublesortbudget(movies* Movies,int n,int max){
	 int j,i,flag;
	char* name= (char*) malloc(sizeof(char)*max);
	char* genre= (char*) malloc(sizeof(char)*max);
	int budget;
	int year;
	double score;
	 for(j = 0; j<n; j++)
    {
      /* make flag 0 initially which means there is no swapped element */
        flag = 0;
        i = 0;
        while(i<n-1)
        {
           /* we are comparing subsequent elements one by one */
            if (Movies[i].budget >Movies[i+1].budget)
            {
                
                budget = Movies[i].budget;
                Movies[i].budget= Movies[i+1].budget;
               Movies[i+1].budget = budget;
                year = Movies[i].year;
                Movies[i].year= Movies[i+1].year;
               Movies[i+1].year = year;
                score = Movies[i].score;
                Movies[i].score= Movies[i+1].score;
               Movies[i+1].score = score;
               strcpy(name,Movies[i].name);
               strcpy(Movies[i].name,Movies[i+1].name);
               strcpy(Movies[i+1].name,name);
               strcpy(genre,Movies[i].genre);
               strcpy(Movies[i].genre,Movies[i+1].genre);
               strcpy(Movies[i+1].genre,genre);
          /* make the flag 1 after swap implemantation */
                flag = 1;
            }
            i++;
        }
        //if swapped is false then the array is sorted
        //we can stop the loop
        if (!flag)
            break;
    }
}
/* implements bubblesort for the scores */
void bublesortscore(movies* Movies,int n,int max){
	 int j,i,flag;
	char* name= (char*) malloc(sizeof(char)*max);
	char* genre= (char*) malloc(sizeof(char)*max);
	int budget;
	int year;
	double score;
for(j = 0; j<n; j++)
    {
        /* make flag 0 initially which means there is no swapped element */
        flag = 0;
        i = 0;
        while(i<n-1)
        {
            /* we are comparing subsequent elements one by one */
            if (Movies[i].score >Movies[i+1].score)
            {
                 /* if the current movie's score is greater, swap it's infos with the next node */
                budget = Movies[i].budget;
                Movies[i].budget= Movies[i+1].budget;
               Movies[i+1].budget = budget;
                year = Movies[i].year;
                Movies[i].year= Movies[i+1].year;
               Movies[i+1].year = year;
                score = Movies[i].score;
                Movies[i].score= Movies[i+1].score;
               Movies[i+1].score = score;
               strcpy(name,Movies[i].name);
               strcpy(Movies[i].name,Movies[i+1].name);
               strcpy(Movies[i+1].name,name);
               strcpy(genre,Movies[i].genre);
               strcpy(Movies[i].genre,Movies[i+1].genre);
               strcpy(Movies[i+1].genre,genre);
               /* make the flag 1 after swap implemantation */
                flag = 1;
            }
            i++;
        }
       /* if flag is 0 at the end, it means array is sorted already */
        if (flag==0)
            break;
    }
} 
/* implements bubblesort for the years */
void bublesortyear(movies* Movies,int n,int max){
	int j,i,flag;
	char* name= (char*) malloc(sizeof(char)*max);
	char* genre= (char*) malloc(sizeof(char)*max);
	int budget;
	int year;
	double score;
	 for(j = 0; j<n; j++)
    {
       
        flag = 0;
        i = 0;
        while(i<n-1)
        {
           /* we are comparing subsequent elements one by one */
            if (Movies[i].year >Movies[i+1].year)
            {
                 /* if the current movie's score is greater, swap it's infos with the next node */
                budget = Movies[i].budget;
                Movies[i].budget= Movies[i+1].budget;
               Movies[i+1].budget = budget;
                year = Movies[i].year;
                Movies[i].year= Movies[i+1].year;
               Movies[i+1].year = year;
                score = Movies[i].score;
                Movies[i].score= Movies[i+1].score;
               Movies[i+1].score = score;
               strcpy(name,Movies[i].name);
               strcpy(Movies[i].name,Movies[i+1].name);
               strcpy(Movies[i+1].name,name);
               strcpy(genre,Movies[i].genre);
               strcpy(Movies[i].genre,Movies[i+1].genre);
               strcpy(Movies[i+1].genre,genre);
                /* make the flag 1 after swap implemantation */
                flag = 1;
            }
            i++;
        }
        /* if flag is 0 at the end, it means array is sorted already */
        if (!flag)
            break;
    }
}
void part1(movie_budget** head, movie_name** head1,int max,int l){
	int n,i,k,count=1,count1=0,z,p,m;
	movies* Movies= (movies*) malloc(sizeof(movies)*l); /* this is the movie struct array which comprimise of movies and it's elements such as year etc */
	char** genres= (char**) malloc(sizeof(char*)*l); /* this is the genre array that holds the genres */
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	s:
	printf("1.Budget\n");
	printf("2.Genre\n");
	printf("3.Name\n");
	printf("4.Score\n");
	printf("5.Year\n");
	printf("Please select an operation: ");
	scanf("%d",&n);
if(n==1){
		f:
		printf("1.Single Selection\n");
		printf("2.Multiple Selection\n");
		printf("Please select an operation: ");
		scanf("%d",&k);
		if(k==1){
			printf("Enter the movie number: ");
			scanf("%d",&z); /* for the single movie just take it's number and print the infos */
			printf("\n %d.Movie \n",z);
			while(iter->next!=NULL){
				if(count==z){
				printf("%d %s %s %lf %d",iter->budget,iter->name,iter1->genre,iter1->score,iter->year);
				break;
				}
			iter=iter->next;
			iter1=iter1->next;
			count++;
			}
			iter= *head;
			iter1= *head1;
		}
		else if(k==2){
			printf("Enter the start budget \n");
			scanf("%d",&p);
			printf("Enter the end budget \n");
			scanf("%d",&m); /* for multiple selection we are taking the start and end budgets and till we reach null in our linked list we are passing a new node 
			at each iteration and if the current node is between the interval, we are assigning it to the movie array with it's informations */
			while(iter->next!=NULL){
				if(p <= iter->budget && iter->budget <= m ){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
				}
			iter=iter->next;
			iter1=iter1->next;
			}
			bublesortbudget(Movies,count1,max); /* at the end, we are implementing bubble sort for getting the true order */
			
		for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
		}
			
		}
		else{
		printf("Please choose a valid menu !");
		goto f;
      	 }	
	
	}
else if(n==2){ /* searching genre */
		g:
		printf("1.Single Selection\n");
		printf("2.Multiple Selection\n");
		printf("Please select an operation: ");
		scanf("%d",&k);
		if(k==1){
			printf("Enter the movie number: ");
			scanf("%d",&z);
			printf("\n %d.Movie \n",z);
			while(iter->next!=NULL){
				if(count==z){
				printf("%d %s %s %lf %d",iter->budget,iter->name,iter1->genre,iter1->score,iter->year);
				break;
				}
			iter=iter->next;
			iter1=iter1->next;
			count++;
			}
			iter= *head;
			iter1= *head1;
		}
		else if(k==2){
		int count4=0;	/* for multiple selection we are taking the start and end genres and till we reach null in our linked list we are passing a new node 
			at each iteration and if the current node is between the interval, we are assigning it to the movie array with it's informations */
			printf("Enter the start value: \n");
			scanf("%d",&p);
			printf("Enter the end value: \n");
			scanf("%d",&m);
			while(iter->next!=NULL){
				if(count4 <= p && count4 <= m ){
				Movies[count4].name= (char*) malloc(sizeof(char)*max);
				Movies[count4].genre= (char*) malloc(sizeof(char)*max);
				Movies[count4].budget=iter->budget;
				Movies[count4].score=iter1->score;
				strcpy(Movies[count4].genre,iter1->genre);
				strcpy(Movies[count4].name,iter1->name);
				Movies[count4].year=iter->year;
				count4+=1;
				}
			iter=iter->next;
			iter1=iter1->next;
			}
		for(i=0;i<count4;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
		}
			
		}
	
		else{
		printf("Please choose a valid menu !");
		goto g;
      	 }	
      	}
      	
else if(n==3){ /* searching name */
		h:
		printf("1.Single Selection\n");
		printf("2.Multiple Selection\n");
		printf("Please select an operation: ");
		scanf("%d",&k);
		if(k==1){
			printf("Enter the movie number: ");
			scanf("%d",&z);
			printf("\n %d.Movie \n",z);
			while(iter->next!=NULL){
				if(count==z){
				printf("%d %s %s %lf %d",iter->budget,iter->name,iter1->genre,iter1->score,iter->year);
				break;
				}
			iter=iter->next;
			iter1=iter1->next;
			count++;
			}
			iter= *head;
			iter1= *head1;
		}
		else if(k==2){
		int count4=0;
			printf("Enter the start value: \n");
			scanf("%d",&p);
			printf("Enter the end value: \n");
			scanf("%d",&m);
			while(iter->next!=NULL){
				if(count4 <= p && count4 <= m ){
				Movies[count4].name= (char*) malloc(sizeof(char)*max);
				Movies[count4].genre= (char*) malloc(sizeof(char)*max);
				Movies[count4].budget=iter->budget;
				Movies[count4].score=iter1->score;
				strcpy(Movies[count4].genre,iter1->genre);
				strcpy(Movies[count4].name,iter1->name);
				Movies[count4].year=iter->year;
				count4+=1;
				}
			iter=iter->next;
			iter1=iter1->next;
			}
	for(i=0;i<count4;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	}
			
    }

		else{
		printf("Please choose a valid menu !");
		goto h;
      	 }	
 }
      	
else if(n==4){ /* searching the scores. When user chooses multiple selection program receives the interval and traverse through whole array and marks the movies satisfy the conditions */
		k:
		printf("1.Single Selection\n");
		printf("2.Multiple Selection\n");
		printf("Please select an operation: ");
		scanf("%d",&k);
		if(k==1){
			printf("Enter the movie number: ");
			scanf("%d",&z);
			printf("\n %d.Movie \n",z);
			while(iter->next!=NULL){
				if(count==z){
				printf("%d %s %s %lf %d",iter->budget,iter->name,iter1->genre,iter1->score,iter->year);
				break;
				}
			iter=iter->next;
			iter1=iter1->next;
			count++;
			}
			iter= *head;
			iter1= *head1;
		}
		else if(k==2){
			double d1,d2;
			printf("Enter the start score \n");
			scanf("%lf",&d1);
			printf("Enter the end score \n"); /* searching the movies which has scores between two user input */
			scanf("%lf",&d2);
			while(iter1->next!=NULL){
				if(d1 <= iter1->score && iter1->score <= d2 ){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
				}
			iter=iter->next;
			iter1=iter1->next;
			}
			bublesortscore(Movies,count1,max);
			
	for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	}
			
		}
		else{
		printf("Please choose a valid menu !");
		goto k;
      	 }	
	
	}
else if(n==5){ /* this function receives a interval from the user for multiple selection and order the movies in that interval */
		j:
		printf("1.Single Selection\n");
		printf("2.Multiple Selection\n");
		printf("Please select an operation: ");
		scanf("%d",&k);
		if(k==1){
			printf("Enter the movie number: ");
			scanf("%d",&z);
			printf("\n %d.Movie \n",z);
			while(iter->next!=NULL){
				if(count==z){
				printf("%d %s %s %lf %d",iter->budget,iter->name,iter1->genre,iter1->score,iter->year);
				break;
				}
			iter=iter->next;
			iter1=iter1->next;
			count++;
			}
			iter= *head;
			iter1= *head1;
		}
		else if(k==2){
			int d1,d2;
			printf("Enter the start year \n");
			scanf("%d",&d1);
			printf("Enter the end year \n");
			scanf("%d",&d2);
			while(iter->next!=NULL){
				if(d1 <= iter->year && iter->year <= d2 ){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
				}
			iter=iter->next;
			iter1=iter1->next;
			}
			bublesortyear(Movies,count1,max);
			
	for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	}
			
		}
		else{
		printf("Please choose a valid menu !");
		goto j;
      	 }	
	
	}
else{
	printf("Choose a valid menu:");
	goto s;
  }
  free(genres);
  free(Movies);
}
void part2(movie_budget** head, movie_name** head1,int max,int l){
	int n,i,k,c=0,z,p,m;
	int flag=0;
	movies* Movies= (movies*) malloc(sizeof(movies)*l);
	char** genres= (char**) malloc(sizeof(char*)*l);
	for(i=0;i<l;i++){
	genres[i]= (char*) malloc(sizeof(char)*max);
		}
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	while(iter->next!=NULL){
		if(c==0){
			strcpy(*(genres+c),iter1->genre);
	    }
		else{	
		   for(i=0;i<c;i++){
			if(strcmp(*(genres+i),iter1->genre)==0){
				flag=1;
			}
		    }
			if(flag!=1){
				strcpy(*(genres+c),iter1->genre);
			}
		}
		iter=iter->next;
		iter1=iter1->next;
		c++;
		flag=0;
	}
	
	for(i=0;i<c;i++){
		if(strcmp(*(genres+i),"\0")!=0 && strcmp(*(genres+i)," ")!=0 && strcmp(*(genres+i),"\n")!=0 )
		printf("%s\n",*(genres+i));
		}
	free(Movies);
	free(genres);
	}
void part3(movie_budget** head, movie_name** head1,int max,int l){
	int n,i,k,count1=0,z,p,m;
	movies* Movies= (movies*) malloc(sizeof(movies)*l);
	movies* Movies1= (movies*) malloc(sizeof(movies)*l);
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	int miny,maxy;
 v:
	printf("Please enter a year: ");
	scanf("%d", &n);
	iter= *head;
	maxy= iter->next->year;
	miny= iter->next->year;
	while(iter->next!=NULL){
	 if(iter->year < iter->next->year && maxy < iter->next->year){
		maxy=iter->next->year;
		}
		iter=iter->next;
	}
	iter= *head;
	while(iter->next!=NULL){
	 if(iter->year > iter->next->year && miny < iter->next->year){
		miny=iter->next->year;
		}
		iter=iter->next;
	}
	printf("miny: %d",miny);
	iter=*head;
	if(n > maxy || n<miny){
	printf("Please enter a year between intervals: \n");
	printf("max: %d min %d", maxy,miny);
	goto v;
	}
	printf("Until (0) or Since (1) %d ",n); 
	scanf("%d",&k);	
 if(k==0){
		while(iter->next!=NULL){
			if( iter->year <= n){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
			  }
			  iter=iter->next;
			  iter1=iter1->next;
			}
		   bublesortyear(Movies,count1,max);
	for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	     }
	 }
 else if(k==1){
		while(iter->next!=NULL){
			if( iter->year >= n){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
			  }
			  iter=iter->next;
			  iter1=iter1->next;
			}
		   bublesortyear(Movies,count1,max);
	for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	     }
	 }
 else{
 	printf("Choose a valid menu");
 	goto v;	
	}
free(Movies);
}
void part4(movie_budget** head, movie_name** head1,int max,int l){
/* this function order the movies according to given score */

	int i,k,count1=0,z,p,m;
	double n;
	movies* Movies= (movies*) malloc(sizeof(movies)*l);
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	double maxy, miny;
 p:
	printf("Please enter a score: ");
	scanf("%lf", &n);
	iter1= *head1;
	maxy= iter1->next->score;
	miny= iter1->next->score;
	while(iter1->next!=NULL){
	 if(iter1->score < iter1->next->score && maxy < iter1->next->score){
		maxy=iter1->next->score;
		}
		iter1=iter1->next;
	}
	iter1= *head1;
	while(iter1->next!=NULL){
	 if(iter1->score > iter1->next->score && miny < iter1->next->score){
		miny=iter1->next->score;
		}
		iter1=iter1->next;
	}
	iter1=*head1;
	if(n > maxy || n<miny){
	printf("Please enter a score between intervals: \n");
	goto p;
	}
	
	printf("Until (0) or Since (1) %lf ",n); 
	scanf("%d",&k);
 if(k==0){
		while(iter1->next!=NULL){
			if( iter1->score <= n){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
			  }
			  iter=iter->next;
			  iter1=iter1->next;
			}
		   bublesortscore(Movies,count1,max);
	for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	     }
	 }
 else if(k==1){
		while(iter1->next!=NULL){
			if( iter1->score>= n){
				Movies[count1].name= (char*) malloc(sizeof(char)*max);
				Movies[count1].genre= (char*) malloc(sizeof(char)*max);
				Movies[count1].budget=iter->budget;
				Movies[count1].score=iter1->score;
				strcpy(Movies[count1].genre,iter1->genre);
				strcpy(Movies[count1].name,iter1->name);
				Movies[count1].year=iter->year;
				count1+=1;
			  }
			  iter=iter->next;
			  iter1=iter1->next;
			}
		   bublesortscore(Movies,count1,max);
	for(i=0;i<count1;i++){
		if(Movies[i].budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("unknown %lf %s %s %d\n",Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);
		}
		else{
			/* other movies are printed as usual */
		printf("%d %lf %s %s %d\n",Movies[i].budget,Movies[i].score,Movies[i].name,Movies[i].genre,Movies[i].year);	
		}
	     }
	 }
 else{
 	printf("Choose a valid menu");
 	goto p;	
	}
	free(Movies);
}
void part5(movie_budget** head, movie_name** head1,int max,int l){
/* this function is for the printing the information of the single movie by getting the name */
	int i,k,count1=0,z,p,m;
	double n;
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	char* name= (char*) malloc(sizeof(char)*max);
	char* genre= (char*) malloc(sizeof(char)*max);
	printf("Enter the name of the movie: ");
	getc(stdin);
	fflush(stdin);
	scanf("%[^\n]s",name);
	int year,budget;
	double score;
		while(iter1->next!=NULL){
			if(strcmp(name,iter->name)==0){
				budget=iter->budget;
				score=iter1->score;
				strcpy(genre,iter1->genre);
				strcpy(name,iter1->name);
				year=iter->year;
			  }
			  iter=iter->next;
			  iter1=iter1->next;
			}
		if(budget==-1){
		/* Unknown budgets are marked with -1 */
		printf("\nBudget: Unknown \nScore:%lf\nName:%s\nGenre:%s\nYear:%d\n",score,name,genre,year);
		}
		else{
			/* other movies are printed as usual */
		printf("\nBudget:%d \nScore:%lf\nName:%s\nGenre:%s\nYear:%d\n",budget,score,name,genre,year);	
		}
	free(name);
	free(genre);
   }
void part6(movie_budget** head, movie_name** head1,int max,int l){
/* this function calculates the avarage of the imdb scores of the movies by traversing the list */
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	int i,k,c=0;
	double sum=0;
	double av;
	  while(iter1->next!=NULL){
	  	 sum+=iter1->score;
	  	 c++;	
		  iter=iter->next;
		  iter1=iter1->next;
		}
	av= (double) (sum/ c);
	printf("Avarage of the IMDB scores : %lf\n",av);	
   }
   
 void part7(movie_budget** head, movie_name** head1,int max,int l){ /* in this function we create a genre array and we are comparing all the genres with the current genre. If it is diffferent than others then we are adding it to the array as a new argument, else we just increment the genre counter */
	int n,i,k,c=0,z,p,m;
	int flag=0;
	movie_budget* iter= *head;
	movie_name* iter1= *head1;
	genre_s* Genres= (genre_s*) malloc(sizeof(genre_s)*l);
	char* genres= (char*) malloc(sizeof(char*)*max);
	for(i=0;i<l;i++){ 
	Genres[i].genre= (char*) malloc(sizeof(char)*max);
	Genres[i].numb=0;
		}
	while(iter1->next!=NULL){
	if(c==0){
		  strcpy(Genres[c].genre,iter1->genre);
		  Genres[c].numb=Genres[c].numb+1;
		  c++;
		}
	else{
		  for(i=0;i<c;i++){
		     if(strcmp(Genres[i].genre,iter1->genre)==0)
		    	flag=1;
		   }
		  if(flag!=1){
		  strcpy(Genres[c].genre,iter1->genre);
		  Genres[c].numb=Genres[c].numb+1;
		  c++; 
		}  
		  else{
		    for(i=0;i<c;i++){
		      if(strcmp(Genres[i].genre,iter1->genre)==0)
		    	Genres[i].numb=Genres[i].numb+1;
		   }
		 } 
	     }
	flag=0;	
	iter= iter->next;
	iter1= iter1->next;
	}
	for(i=0;i<c;i++){
	printf("%s : %d \n",Genres[i].genre, Genres[i].numb);
	}
	free(Genres);
	free(genres);
   }
void handleFile(FILE* fp, char* str, int l, int max, char** genres, int* count, double* sum ){
	int i, a = 0, k,n, flag = 0,year;
	movie_budget* head; //= (movie_budget*)malloc(sizeof(movie_budget)); /*head is the head pointer of the movie_budget linked list */
	movie_name* head1; //= (movie_name*)malloc(sizeof(movie_name)); /* head1 is the head pointer of the movie_name linked list */
	head=NULL;
	head1=NULL;
	double genre_d, score;
	movies* Movies= (movies*) malloc(sizeof(movies)*l);
	int budget;
	char* budget_s = (char*)malloc(max * sizeof(char)); /* temporary array for implementing budget parse operation  */
	char* name = (char*)malloc(max * sizeof(char)); /* temporary array for implementing name parse operation */
	char* genre = (char*)malloc(max * sizeof(char)); /* temporary array for implementing genre parse operation */
	fseek(fp, 0, SEEK_SET);
	fgets(str, max, fp); 
	max += max;
	//fgets(str,max,fp); /* getting the first line which is not a movie */
	for (i = 0; i < l; i++) 
	{ /* until reaching the number of movie which is l */
		fgets(str, max, fp); /* start read the file line by line str: buffer for fgets*/
		//printf("i:%d, %s\n", i, str);
		flag = 0;
		sscanf(str, "%[^,],%[^,], %[^,] , %lf, %d", budget_s, genre, name, &score, &year);
		/* we are parsing the str by using sscanf */
		*sum = *sum + score; /* sum variable is for calculating the avarage of the imdb scores */
		*count = *count + 1; /* count variable is for counting the number of movies */
		if (strcmp(budget_s, "unknown") == 0 || strcmp(budget_s, "Unknown") == 0)
		{
			budget = -1; /* if the budget is unknown mark it as -1 */
		}
		else {
			sscanf(budget_s, "%d", &budget); /* if it is not unknown, parse it as double and assign to variable budget */
		}
		/* we are saving movies to movies struct array */
		Movies[i].budget= budget;
		Movies[i].name= (char*) malloc(sizeof(char)*max);
		Movies[i].genre= (char*) malloc(sizeof(char)*max);
		strcpy(Movies[i].name,name);
		strcpy(Movies[i].genre,genre);
		Movies[i].score=score;
		Movies[i].year=year;
		for(k=0;k<i;k++){
			if(strcmp(Movies[k].name,name)==0){
				findRepeat(&head,&head1,budget,score,genre,name,year);
				goto b;
			
			}
		} 

		addList(&head,&head1,budget,score,genre,name,year,max,i);
		b:;
	}
	bubbleSort(&head,&head1,max);
	reverseList(&head,&head1);
	do{
	printMenu(&n); /* Printing the menu to the panel */
	switch (n) {
	case 1:
		part1(&head,&head1,max,l);
		break;
	case 2:
		part2(&head,&head1,max,l);
		break;
	case 3:
		part3(&head,&head1,max,l);
		break;
	case 4:
		part4(&head,&head1,max,l);
		break;
	case 5:
		part5(&head,&head1,max,l);
		break;
	case 6:
		part6(&head,&head1,max,l);
		break;
	case 7:
		part7(&head,&head1,max,l);
		break;
	case 8:
		exit(1);
	default:
		printf("Please enter a valid input!");
		}
	}
	while (1);
	}

int main() {
	FILE* fp = fopen("Movies.txt","r"); /* Opening the file */
	int n, l, i, x = 0, max;
	int count = 0;
	double sum = 0;
	l = calculateLine(fp); /* calculating the number of lines in the file */
	fseek(fp, SEEK_SET, 0); /* carrying cursor to the start point */
	int* numboflines = (int*)malloc(sizeof(int) * l); /* this is the array that holds the number of chracters in each line */
	if (fp == NULL) { /* if the file cannot be opened give an error message */
		printf("Error opening the file");
		exit(1);
	}
	countcharsinLine(fp, l, numboflines); /* filling the array numboflines which holds the number of character in each line in the file */
	max = findmaxofeachLine(l, numboflines); /* max number of characters in a line in the file */
	max = max + max;
	char** genres = (char**)malloc(l * sizeof(char*)); /* since realloc cannot be used, we are assuming there are genres in the files at least
	number of the movies */
	char* str = (char*)malloc(max * sizeof(char)); /* str is the string that used with fgets which reads the whole line in the file */
	fseek(fp, SEEK_SET, 0);
	handleFile(fp, str, l, max, genres, &count, &sum);
	free(str);
	free(genres);
	fclose(fp);/* closing the file */
	return 0;
}
