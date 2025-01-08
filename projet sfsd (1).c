#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <locale.h>

typedef struct {
    float mark;
    int coef;
} note;

typedef struct {
    int id;
    char full_name[30];
    int yob;
    char group[2];
    note sfsd;
    note oop;
    note anal;
    note alge;
    float ave;
    int SD;
} Student;

struct rec {
             int id;
             float av;
};
// Function to find the student's position and check if it already exists
int Position(const char *filename, int count, int newId,FILE *file) {

    file = fopen(filename, "r");
    if (file==NULL) {
        printf("Error:  Unable to open file.\n");
        return -1;
    }

    int left = 0, right = count - 1, mid;
    Student student;
    int pos = 0;

    while ( fscanf(file,"%d;%*[^;];%*d;%*[^;];%*f,%*d;%*f,%*d;%*f,%*d;%*f,%*d;%*f;%*d\n",
                  &student.id) != EOF) {
        // on utilise la recherche binaire car le fichier est ordonee
        mid = left + (right - left) / 2;
        if (student.id == newId) {
            fclose(file);
            return -1; //  le id est exist
        }
        if (student.id < newId) {
            left = mid + 1;
            pos++;
        } else {
            right = mid - 1;
        }
    }

    fclose(file);
    return pos; //laposition ou en ajout l'etudiant
}

// Function to add a student
void add(const char *filename, FILE *file) {

    file = fopen(filename, "r+");
    if (file==NULL) {
        printf("Error: Unable to open file.\n");
        return;}

    Student buf ;
    FILE *temp_file;
    int count = 0; // le nombres des etudiant dans le fichier

    // Count the number of students in the file
    while ( fscanf(file, "%d;%*[^;];%*d;%*[^;];%*f,%*d;%*f,%*d;%*f,%*d;%*f,%*d;%*f;%*d\n",
               &buf.id)!= EOF) {
        count++;}

    fseek(file,0,SEEK_SET); // Go back to the beginning of the file

    // entrer les information de l'etudiant
    printf("Enter the student ID: ");
    scanf("%d", &buf.id);

    // virifier si il exist ou savoir sa position
    int pos = Position(filename, count, buf.id,file);
    if (pos == -1) {
        printf("Error: ID already exists.\n");
        fclose(file);
        return;}

     int i ,j;
char buffer [1024];

 printf("Enter the full name:");
   gets(buf.full_name);
   gets(buf.full_name);
    printf("Enter the group: ");
   gets(buf.group);
    printf("Enter the date of birth (1990–2020): ");
    scanf("%d",&buf.yob);
    while (buf.yob < 1990 || buf.yob > 2020) {
        printf("Error: Enter a valid DOB (1990–2020): ");scanf("%d",&buf.yob);}

    printf("Enter the module notes :\n");
  do { printf("SFSD:");       scanf("%f",&buf.sfsd.mark);} while ((buf.sfsd.mark<0)||(buf.sfsd.mark>20));
   do { printf("OOP:");        scanf("%f",&buf.oop.mark); }while ((buf.oop.mark<0)||(buf.oop.mark>20));
   do { printf("Analysis:");   scanf("%f",&buf.anal.mark);}while ((buf.anal.mark<0)||(buf.anal.mark>20));
    do { printf("Algebra:");    scanf("%f",&buf.alge.mark);}while ((buf.alge.mark<0)||(buf.alge.mark>20));
    buf.ave=(buf.sfsd.mark*4+buf.oop.mark*3+buf.anal.mark*2+buf.alge.mark*5)/14;
 do { printf("Enter SD: ");scanf("%d",&buf.SD); }while ((buf.SD !=1 )&& (buf.SD !=0));

   // Ouvrir un fichier temporaire
    temp_file = fopen("temp.txt", "w");
    if (!temp_file) {
        printf("Erreur : impossible de créer un fichier temporaire.\n");
        fclose(file);
        return;}

    // Copier les lignes jusqu'à la position souhaitée
    for (i = 0; i < pos; i++) {
        fgets(buffer, sizeof(buffer), file);
        fputs(buffer, temp_file);}

    // Ajouter les nouvelles données
    fprintf(temp_file, "%d;%s;%d;%s;%.1f,%d;%.1f,%d;%.1f,%d;%.1f,%d;%.1f;%d\n",
            buf.id, buf.full_name, buf.yob, buf.group,
            buf.sfsd.mark, 4, buf.oop.mark, 3, buf.anal.mark, 2, buf.alge.mark, 5, buf.ave, buf.SD);

    // Copier le reste des données
    while (fgets(buffer, sizeof(buffer), file)) {
        fputs(buffer, temp_file);}// Fermer les fichiers
    fclose(file);
    fclose(temp_file);

// Remplacer lefichier original par le fichier temporaire
    remove(filename);
    rename("temp.txt", filename);

    printf(" student successfully added to position %d \n", pos);}



// Function to search for a student by ID
void  search_stud(FILE *F, int search_id,const char *filename) {
Student buf; int found=0;
F = fopen(filename, "r");
if (F == NULL) {
printf("Error opening file!\n");
}
while (fscanf(F, "%d;%[^;];%d;%[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
&buf.id, buf.full_name, &buf.yob, buf.group,
&buf.sfsd.mark, &buf.sfsd.coef, &buf.oop.mark, &buf.oop.coef,
&buf.anal.mark, &buf.anal.coef, &buf.alge.mark, &buf.alge.coef,
&buf.ave, &buf.SD) == 14) {
if (buf.id == search_id) {
printf("student found \n");
printf("The information of the student are:\n");
printf("ID: %d\n", buf.id);
printf("Full Name: %s\n", buf.full_name);
printf("Year of Birth: %d\n", buf.yob);
printf("Group: %s\n", buf.group);
printf("SFSD Mark: %.2f, Coefficient: %d\n", buf.sfsd.mark, buf.sfsd.coef);
printf("OOP Mark: %.2f, Coefficient: %d\n", buf.oop.mark, buf.oop.coef);
printf("Anal Mark: %.2f, Coefficient: %d\n", buf.anal.mark, buf.anal.coef);
printf("Alge Mark: %.2f, Coefficient: %d\n", buf.alge.mark, buf.alge.coef);
printf("Average: %.2f\n", buf.ave);
printf("SD: %d\n", buf.SD);
found=1; }
}
if (found !=1){printf("not found\n");}
fclose(F);
}

// function to display students of a group in order
void organ(char file[],int n)
{
int a,i,j,Pmax;
struct rec c[n],a;
char buf[50];

FILE *f;
//open the File
f=fopen(file,"r");
if(f==NULL)printf("error");

//store average in t[] and id in v[]
for(j=0;j<n;j++)
               { fscanf(f,"%d;%*[^;];%*d;%*[^;];%*f,%*d;%*f,%*d;%*f,%*d;%*f,%*d;%f;%*d\n",&c[j].id,&c[j].av);}
fclose(f);

// sorting the two arrays simultaneously using the method of permutation
for(i=0;i<n;i++)
                {Pmax=i;
                 for(j=i+1;j<n;j++){ if(c[j].av>c[Pmax].av){ Pmax=j;}}
                 if(i!=Pmax){ x=c[i]; c[i]=c[Pmax]; c[Pmax]=x;
                            }
                }
//extract the name of each student in the array from the file
for(j=0;j<n;j++)
               {f=fopen(file,"r");
                do{fscanf(f,"%d;%[^;];%*d;%*[^;];%*f,%*d;%*f,%*d;%*f,%*d;%*f,%*d;%*f;%*d\n",&a,&buf);}while(a!=c[j].id);
                fclose(f);
//display the information of student first, sec....
                if(a==c[j].id){printf("%.2d.",a); printf("%s: ",buf); printf("%.2f\n",c[j].av); }
               }
}

//Function to extract a group

 void extractstudent(FILE *f,char group[],const char *filename) {
     f= fopen(filename, "r");
    char file[15];// to store the name of the temporary file
    if (f == NULL) {
        printf("Error cannot opening file.\n");
        return ;
    }
     FILE *F;// a pointer of the new file
     F=fopen("file.txt","w");
     strcpy(file,"file.txt");
     Student student  ;
     int nbrstudgrp =0;
     while (!feof(f)){
            (fscanf(f,"%d;%[^;];%d;%[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
                  &student.id,&student.full_name, &student.yob,&student.group,// &
                  &student.sfsd.mark, &student.sfsd.coef, &student.oop.mark, &student.oop.coef,
                  &student.anal.mark, &student.anal.coef, &student.alge.mark, &student.alge.coef,
                  &student.ave, &student.SD)) ;
     if  (strcmp(student.group,group) == 0) {

    nbrstudgrp++;
   fprintf(F,"%d;%s;%d;%s;%.2f,%d;%.2f,%d;%.2f,%d;%.2f,%d;%.2f;%d\n",
                  student.id,student.full_name, student.yob,student.group,
                  student.sfsd.mark, student.sfsd.coef, student.oop.mark, student.oop.coef,
                  student.anal.mark, student.anal.coef, student.alge.mark, student.alge.coef,
                  student.ave, student.SD);




}} fclose(F);
if(nbrstudgrp!=0) organ(file,nbrstudgrp);else{printf("No element found !\n");}
fclose(f);
}


//supression logique
   void supp_logique(const char *filename,FILE *file)
    {   FILE *temp ;
        char ch[100];
        Student buf ;
        int num ;


        file = fopen (filename,"r");
        temp = fopen ("temp.txt","w");

         if ( file != NULL && temp != NULL )
         {
            printf("give the student id to delete : \n");
            scanf("%d",&num);
            int trouve = 0;
            while(fgets(ch,100,file)!=NULL)
            {

                sscanf(ch,"%d;%[^;];%d;%2[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d",&buf.id,buf.full_name,&buf.yob,&buf.group,
                       &buf.sfsd.mark,&buf.sfsd.coef,&buf.oop.mark,&buf.oop.coef,&buf.anal.mark,&buf.anal.coef,
                       &buf.alge.mark,&buf.alge.coef,&buf.ave,&buf.SD);

                        if(buf.id == num )
                       { if (buf.SD == 0)
                           {buf.SD = 1 ; trouve = 1 ;}
                            else trouve = 2 ;
                       }

                       fprintf(temp,"%d;%s;%d;%2s;%.1f,%d;%.1f,%d;%.1f,%d;%.1f,%d;%.1f;%d\n",buf.id,buf.full_name,buf.yob,buf.group,
                       buf.sfsd.mark,buf.sfsd.coef,buf.oop.mark,buf.oop.coef,buf.anal.mark,buf.anal.coef,
                       buf.alge.mark,buf.alge.coef,buf.ave,buf.SD);


            }

            switch (trouve) {
            case 0 : printf("\nstudent %d not found.\n",num);
            break ;
            case 1 : printf ("\nstudent %d deleted successfully.\n",num);
            break ;
            case 2 : printf ("\nstudent %d already deleted.\n",num);
            break ;
            }


                fclose(temp);
                fclose(file);

         }


        else printf("\nerror\n");


            remove(filename);
        rename("temp.txt", filename);

    }



//function for the physical deletion of students that have 1 in SD:
void sup_phy(const char *filename,FILE *F) {
    FILE *f;//pointer for the temporary file;
    //pointer for the original file;
    Student buf;// buffer used for the read / write operations with the files
    //the physical deletion :
    f=fopen("supp.txt","w");//open the temporary file in write  mode
    F=fopen(filename,"r");//open the temporary file in read mode
     if(F==NULL) { puts("Error.the file Listes_Etudiants.txt can not open\n"); }   //indecat the error if it does exist
     if(f==NULL) {puts("Error.the file filestud.txt can not open\n"); }   //indecat the error if it does exist ;
    while (!feof(F)) {
        fscanf(F, "%d;%[^;];%d;%2[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
               &buf.id, &buf.full_name, &buf.yob, &buf.group,
               &buf.sfsd.mark, &buf.sfsd.coef,
               &buf.oop.mark, &buf.oop.coef,
               &buf.anal.mark, &buf.anal.coef,
               &buf.alge.mark, &buf.alge.coef,
               &buf.ave, &buf.SD);//read the informations from the original file to the buffer;
        if(buf.SD==0) {fprintf(f, "%d;%s;%d;%s;%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
                       buf.id, buf.full_name, buf.yob, buf.group,
                       buf.sfsd.mark, buf.sfsd.coef,
                       buf.oop.mark, buf.oop.coef,
                       buf.anal.mark, buf.anal.coef,
                       buf.alge.mark, buf.alge.coef,
                       buf.ave, buf.SD);}//write the informations from the buffer to the temporary file according to the condition;
    }
    fclose (f);/*close the temporary file */ fclose (F);//close the original file

    //copy the informations from the temporary file into the original file
    f=fopen("supp.txt","r");//open the temporary file in read  mode
    F=fopen(filename,"w");//open the original file in write  mode
    if(F==NULL) puts("Error.the file Listes_Etudiants.txt can not open\n");    //indecat the error if it does exist ;
    if(f==NULL) puts("Error.the file filestud.txt can not open\n");    //indecat the error if it does exist ;
    while (!feof(f)) {
        fscanf(f, "%d;%[^;];%d;%2[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
               &buf.id, &buf.full_name, &buf.yob, &buf.group,
               &buf.sfsd.mark, &buf.sfsd.coef,
               &buf.oop.mark, &buf.oop.coef,
               &buf.anal.mark, &buf.anal.coef,
               &buf.alge.mark, &buf.alge.coef,
               &buf.ave, &buf.SD);//read the informations from the temporary  file to the buffer;
        fprintf(F, "%d;%s;%d;%s;%.2f,%d;%.2f,%d;%.2f,%d;%.2f,%d;%.2f;%d\n",
                buf.id, buf.full_name, buf.yob, buf.group,
                buf.sfsd.mark, buf.sfsd.coef,
                buf.oop.mark, buf.oop.coef,
                buf.anal.mark, buf.anal.coef,
                buf.alge.mark, buf.alge.coef,
                buf.ave, buf.SD);//write the informations from the buffer to the original file
    }

    fclose (f);//close the temporary file
    fclose (F);//close the original file

    //display the original file with new informations
    F=fopen(filename,"r");//open the original file in read mode
    if(F==NULL) puts("Error.the file Listes_Etudiants.txt can not open\n");//indecat the error if it does exist

        while (!feof(F)) {
            fscanf(F, "%d;%[^;];%d;%2[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",&buf.id, &buf.full_name, &buf.yob, &buf.group,
                   &buf.sfsd.mark, &buf.sfsd.coef,
                   &buf.oop.mark, &buf.oop.coef,
                   &buf.anal.mark, &buf.anal.coef,
                   &buf.alge.mark, &buf.alge.coef,
                   &buf.ave, &buf.SD);//read the informations from the original file to the buffer;
            printf("%d;%s;%d;%s;%.2f,%d;%.2f,%d;%.2f,%d;%.2f,%d;%.2f;%d\n",
                   buf.id, buf.full_name, buf.yob, buf.group,
                   buf.sfsd.mark, buf.sfsd.coef,
                   buf.oop.mark, buf.oop.coef,
                   buf.anal.mark, buf.anal.coef,
                   buf.alge.mark, buf.alge.coef,
                   buf.ave, buf.SD);//write the informations from the buffer to the screen

        }
        fclose (F);//close the file


};


// Function to modify a student's data in the file

FILE *modify (FILE *F, int id, char *answer,const char *filename) {

    FILE *f; // Temporary file for changing data
    Student buf;
    char change[10]; // Temporary storage for group change
    float change1;   // Temporary storage for mark change
    float new_ave;
    int found=0;


    // Open file
    F = fopen(filename, "r");
    if (F == NULL ){puts("error in opening F"); return NULL;}

     // check if the id exists
    while (fscanf(F, "%d;%[^;];%d;%[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
                  &buf.id, &buf.full_name, &buf.yob, &buf.group,
                  &buf.sfsd.mark, &buf.sfsd.coef, &buf.oop.mark, &buf.oop.coef,
                  &buf.anal.mark, &buf.anal.coef, &buf.alge.mark, &buf.alge.coef,
                  &buf.ave, &buf.SD) == 14) { if(id==buf.id){found=1; break;} }

                   //if id not found, the temporary file isnt created at all
                if (found==0) { puts("id not found"); fclose(F); return;}

                 // check the validation of the input field to modify
    while (strcmp(answer, "group") != 0 &&
           strcmp(answer, "sfsd") != 0 &&
           strcmp(answer, "oop") != 0 &&
           strcmp(answer, "anal") != 0 &&
           strcmp(answer, "alge") != 0) {
        printf("Enter a valid field to modify (group, sfsd, oop, anal, alge): ");
        scanf("%s", answer);
    }


                // returns the original file pointer to the begining
                fseek(F,0,SEEK_SET);

        // opens the temporary file in writing mode only if the id exists
                f = fopen("Temp_Listes_Etudiants.txt", "w");
                if (f == NULL) {puts("Error opening f!"); return NULL;}

    // Read and process each student record
    while (fscanf(F, "%d;%[^;];%d;%[^;];%f,%d;%f,%d;%f,%d;%f,%d;%f;%d\n",
                  &buf.id, &buf.full_name, &buf.yob, &buf.group,
                  &buf.sfsd.mark, &buf.sfsd.coef, &buf.oop.mark, &buf.oop.coef,
                  &buf.anal.mark, &buf.anal.coef, &buf.alge.mark, &buf.alge.coef,
                  &buf.ave, &buf.SD) == 14) {

        if (buf.id == id) {
            // Prompt for new data
            if (strcmp(answer, "group") == 0) {
                printf("Enter the new group: ");
                scanf("%s", change);
                strcpy(buf.group, change);
            } else {
                printf("Enter the new %s mark: ", answer);
                scanf("%f", &change1);

                // Update the corresponding mark using the function "strcmp" to campare (returns a 0 if the two strings are equal)
                if (strcmp(answer, "sfsd") == 0) buf.sfsd.mark = change1;
                else if (strcmp(answer, "oop") == 0) buf.oop.mark = change1;
                else if (strcmp(answer, "anal") == 0) buf.anal.mark = change1;
                else if (strcmp(answer, "alge") == 0) buf.alge.mark = change1;

                // update average
                new_ave = (buf.sfsd.mark * buf.sfsd.coef +
                           buf.oop.mark * buf.oop.coef +
                           buf.anal.mark * buf.anal.coef +
                           buf.alge.mark * buf.alge.coef) /
                          (buf.sfsd.coef + buf.oop.coef + buf.anal.coef + buf.alge.coef);
                buf.ave = new_ave;


            }
        }

        // Write the updated record to the temporary file
        fprintf(f, "%d;%s;%d;%s;%.1f,%d;%.1f,%d;%.1f,%d;%.1f,%d;%.1f;%d\n",
                buf.id, buf.full_name, buf.yob, buf.group,
                buf.sfsd.mark, buf.sfsd.coef, buf.oop.mark, buf.oop.coef,
                buf.anal.mark, buf.anal.coef, buf.alge.mark, buf.alge.coef,
                buf.ave, buf.SD);
    }

    // Close files and replace it with the original file
    fclose(F);
    fclose(f);
    // deleting the old version of the file and replacing it with the new updated file that we created by renaming it
    remove(filename);
    rename("Temp_Listes_Etudiants.txt",filename);
    printf("data modified succesfully\n");

    return f;
}



int main() {

FILE *F;
const char *filename = "Listes_Etudiants.txt";

int search_id,n,nbs,i;
char groupe[2];
char answer[10];
puts("1.add");
puts("2.searching");
puts("3.logiqual delete");
puts("4.physical delete");
puts("5.extract a group");
puts("6.modification");
scanf("%d",&n);
switch (n){

case 1 : printf("How many student do you want to add ?\t");
         scanf("%d",&nbs);
         for(i=0;i<nbs;i++){add(filename,F);} break;

case 2 : printf("How many student do you want to search for ?\t");
         scanf("%d",&nbs);
         for(i=0;i<nbs;i++){
         printf("Enter the ID of the %d student:\n",i+1);
         scanf("%d", &search_id);
         search_stud(F, search_id,filename);} break;

case 3 : printf("How many student do you want to delete?\t");
         scanf("%d",&nbs);
         for(i=0;i<nbs;i++){setlocale(LC_NUMERIC, "C");
         supp_logique (filename,F) ;} break;

case 4 : sup_phy(filename,F); break;

case 5 : printf("enter the group:\n");
         scanf("%s",groupe);
         extractstudent(F, groupe,filename); break;

case 6 : printf("How many student do you want to modify its information?\t");
         scanf("%d",&nbs);
         for(i=0;i<nbs;i++){printf("Enter the ID of the %d student to modify: ",i+1);
         scanf("%d", &search_id);
         printf("Enter the field to modify (group, sfsd, oop, anal, alge): ");
         scanf("%s", answer);
         modify(F, search_id, answer,filename);} break;

}

return 0;
}
