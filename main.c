#include <stdio.h>
#include <string.h>

typedef struct{
	int ID;
	char student_firstname[20];
	char student_lastname[20];
	char coursecode [10][9]; //10 rows //10 characters
	char grades [10][4]; // 10 for courses // 5 for the grades
}student_info;

void menu (){
	printf ("\n\t------------- MENU -------------\n");
	printf ("\n\t1- View the content of the file\n");
	printf ("\n\t2- Load file data to an array\n");
	printf ("\n\t3- Check if a student is in the array or not\n");
	printf ("\n\t4- Compute the GPA for a student X\n");
	printf ("\n\t5- Quit\n");
	printf ("\n\t---------------------------------\n");
	printf ("\n\n\tchoice: ");
}

int count_students (FILE*infp){
  char line[30];
  int N=0;

  while (fgets(line,30,infp)!=NULL){
    fscanf (infp,"%s",line);
    if(strcmp (line,"----------------")==0)
      N++;
      
    //printf ("\nhere %d ",N);
  }

return N;
}

void view_file (FILE*infp,char*line){
	while (fgets(line,30,infp)!=NULL){
		printf ("%s",line);
	}
}

void fill_array (FILE*infp,student_info*loadarr, char*line,int N)
{
  fseek(infp, 0,0);
	for (int i=0;i<N;i++){
		fscanf (infp,"%s %s",loadarr[i].student_firstname,loadarr[i].student_lastname);
		fscanf (infp,"%d",&loadarr[i].ID);
		// fgetc(infp);
    
		for (int j=0;j<7;j++){
    fscanf (infp,"%s",line);
    if(strcmp (line,"----------------")==0)
      break;
    else{
      strcpy (loadarr[i].coursecode[j],line);
      fscanf (infp,"%s",loadarr[i].grades[j]);}
      
      }//for j loop
      }// the i for loop
  fscanf (infp,"%s",line);
    
	
	
	/*for (int i=0;i<4;i++){
		printf ("%s %s\n%d\n",loadarr[i].student_firstname,loadarr[i].student_lastname,loadarr[i].ID);
		for (int j=0;j<7;j++){
				printf ("%s %s\n",loadarr[i].coursecode[j],loadarr[i].grades[j]);
			//printf (" ");
				//printf ("%s",loadarr[i].grades[j]);
	        //printf ("\n");
		}
		printf ("%s\n",line);
	}*/
}

char check_for_student (student_info*loadarr,char*look_fn_student,char*look_ln_student,int N){

  for (int i=0;i<N;i++){
    
    if (strcmp (loadarr[i].student_firstname,look_fn_student)==0){
      if (strcmp (loadarr[i].student_lastname,look_ln_student)==0)
        return 1;
        }
  }

return 0;
}

void compute_GPA (int credit, double points, double*GPA, double*finalproduct,int*creditfinal,int i, int j){
  double product;
  product= credit*points;
  *finalproduct+= product;
  *creditfinal+=credit;
  if (j==6){
  *GPA= *finalproduct/ *creditfinal;
  //printf ("student %d : %.2lf\n",i,*GPA);
    }
}

int find_credit (student_info*loadarr,int l,int m){
  int value;
  char value1;
  value1= loadarr[l].coursecode[m][4];
  value= (int)(value1);
  return value;
}

double numberofpoints (student_info*loadarr,int l,int m){
  double point_value;
  
  if (strcmp (loadarr[l].grades[m],"A+\0")==0){
    point_value=4.0;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"A\0")==0){
    point_value=4.0;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"A-\0")==0) {
    point_value=3.67;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"B+\0")==0){
    point_value=3.33;
    return point_value;} 
  if (strcmp (loadarr[l].grades[m],"B\0")==0){
    point_value=3.00;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"B-\0")==0){
    point_value=2.67;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"C+\0")==0){
    point_value=2.33;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"C\0")==0){
    point_value=2.00;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"C-\0")==0){
    point_value=1.67;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"D+\0")==0){
    point_value=1.33;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"D\0")==0){
    point_value=1.00;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"D-\0")==0){
    point_value=1.00;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"F\0")==0){
    point_value=0.00;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"F\0")==0){
    point_value=0.00;
    return point_value;}
  if (strcmp (loadarr[l].grades[m],"N/A\0")==0){
    point_value= -1.00;
    return point_value;}
}

int main (){
	FILE*infp;
  FILE*infpcopy;
	char line[30], look_fn_student[10], look_ln_student[10], arr[30];
  double points, product, finalproduct=0, GPA;
	int choice, credit, creditfinal=0, flag=0, number_students=0;
  char reply;
	student_info loadarr[50];
	
  infp=fopen("students_data.txt","r");
  number_students=count_students (infp);
  fclose (infp);
  //printf ("%d",number_students);
  
	//menu ();
	while (choice !=5){
		menu();
		scanf ("%d",&choice);
		switch (choice){
			
			case 1:
				infp=fopen("students_data.txt","r");
				if (infp==NULL)
					printf ("\n\t FILE DOES NOT EXIST");
				else {
					view_file (infp, line);
		        	fclose (infp);
		        }
				break;
			case 2:
				infp=fopen("students_data.txt","r");
				fill_array (infp,loadarr,line,number_students);
				fclose (infp);
				flag=1;
        printf ("\n\tARRAY FILLED");
				break;
			case 3:
        if (flag==0)
          printf ("FILL ARRAY FIRST IN CHOICE N:2");
        if (flag==1){
				printf ("Enter the full name of the student you're looking for: ");
        scanf ("%s %s",look_fn_student,look_ln_student);
        //printf ("\n%s %s",look_fn_student,look_ln_student);
        reply=check_for_student (loadarr,look_fn_student,look_ln_student,number_students);
        if (reply==1)
          printf ("\nthe student %s %s exists in the array",look_fn_student,look_ln_student);
        if (reply==0)
          printf ("\nthe student %s %s does NOT exist in the array",look_fn_student,look_ln_student);
        }
				break;
			case 4:
			if (flag==0)
          printf ("FILL ARRAY FIRST IN CHOICE N:2");
      if (flag==1){
        for (int i=0;i<number_students;i++){
          strcpy (arr,loadarr[i].student_firstname);
          strncat (arr,loadarr[i].student_lastname,strlen(loadarr[i].student_lastname));
          strcat (arr,"_GPA.txt");
          infpcopy=fopen (arr,"w");
          //fprintf(infp,"666666");
          //fclose(infpcopy);
          for (int j=0;j<7;j++){
            credit= find_credit (loadarr,i,j);
            points= numberofpoints (loadarr,i,j);
            if (points == -1.00)
              credit = 0;
            
            compute_GPA (credit,points,&GPA,&finalproduct,&creditfinal,i,j);
            /*product= credit*points;
            
            finalproduct+= product;
            creditfinal+=credit;
            }

          GPA= finalproduct/creditfinal;*/
}
          printf ("student %d : %.2lf\n",i,GPA);
            
          fseek(infpcopy,0,0);
          for (int j=0;j<7;j++)
          
            fprintf (infpcopy,"\t%s%-5s\n",loadarr[i].coursecode[j],loadarr[i].grades[j]);
            fprintf (infpcopy,"\n\t--------------------------------",stdin);
            fprintf (infpcopy,"\n\tYour GPA is: %.2lf\n",GPA);
          fclose(infpcopy);
            }
        
      }
				
				break;
			case 5:
				printf ("\n\t         bye !");
        printf ("\n\n it worked !!  ～(^з^)~~☆");
        printf ("\n\n\t         ʕ°ᴥ°ʔ");
				break;
			default:
				printf ("this choice is not valid");
			
				break;
		}
    }
}