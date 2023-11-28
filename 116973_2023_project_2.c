
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Autor {
   char name[30],priez[30],ty;
} autor;
 typedef struct block {
    char id[12],subject[150],time[30],type[5];
    struct Autor autor,subautor[10];
    int subsize,poradie;
    struct block *next;
} block;
/////////////////////////////
int n(block*pole,FILE **fp,int size){
  int q=0,counter=0,f=0,sub=0,t=0;
  char str[70],*token,*tk,buffer[70],str2[70];
  block *buf;
  if(*fp==NULL){
    *fp= fopen("KonferencnyZoznam2.txt", "r");
  }
 else{//uvolnenie pamati ak uz mame zpojeny zoznam
   buf = pole->next;
   for (int j = 0; j < size; j++) {
     pole->next = buf->next;
     free(buf);
     buf = pole->next;
   }
   q = 0;
   fclose(*fp);
   *fp= fopen("KonferencnyZoznam2.txt", "r");
 }
  if (*fp==NULL){printf("Zaznamy neboli nacitane!\n");return 0;}
  while(!feof(*fp)){
    fgets(str,70,(*fp));
    q++;
  }
  rewind(*fp);
  q=q/5;//counting amount of elements devided by every 5 rows.
  pole->next=(block*)malloc (sizeof(block));
  buf=((*pole).next);
  for (int i=2;i<q+1;i++){
    buf->next=(block*)malloc (sizeof(block));
    buf=(buf->next);
  }
  buf=(pole->next);
  while (!feof(*fp)){
    fgets(str,70,*fp);
    if (counter==1){
      strcpy(buf->id,str);
      (buf->id)[strlen(buf->id)]='\0';//manualy adding end to the string
      buf->poradie=f;
    }
    if (counter==2){
      strcpy(buf->subject,str);
      (buf->subject)[strlen(buf->subject)-1]='\0';
      (buf->subject)[strlen(buf->subject)]='\0';
    }
    if (counter==3){
      for (int i=0;i<strlen(str);i++){
        if(str[i]=='#'){
          buf->type[t]=str[i+1];//saving all of the roles to pole type, later for giving it back to the autor struct
          t++;
          str[i]=' ';
          str[i+1]=' ';
          str[i+2]='.';
        }
      }
      strcpy(str2,str);
      token=strtok(str2,".");
      strcpy((buf->autor).name,token);
      ((buf->autor).name)[strlen((buf->autor).name)]='\0';
      tk=strtok((buf->autor).name," ");
      tk=strtok(NULL," ");

      strcpy((buf->autor).priez,tk);

      ((buf->autor).priez)[strlen((buf->autor).priez)]='\0';
      buf->autor.ty=buf->type[0];
      strcpy(str2,str);
      token=strtok(str2,".");
      token=strtok(NULL,".");
      if(strcmp(token,"\n")!=0){
        strcpy(buffer,token);//saving token from devision by second strtok

        tk=strtok(buffer," ");
        strcpy((buf->subautor[sub]).name,tk);
        (buf->subautor[sub]).name[strlen(buf->subautor[sub].name)]='\0';

        tk=strtok(NULL," ");
        strcpy(buf->subautor[sub].priez,tk);
        (buf->subautor[sub]).priez[strlen(buf->subautor[sub].priez)]='\0';
        (buf->subautor[sub]).ty=buf->type[sub+1];
        strcpy(str2,str);
        token=strtok(str2,".");
        token=strtok(NULL,".");

        sub++;
        while(token!=NULL || strcmp(token,"\n")!=0){

          token=strtok(NULL,".");

          if(token==NULL || strcmp(token,"\n")==0 ||strcmp(token," ")==0){
            break;
          }
          strcpy(buffer,token);

          tk=strtok(buffer," ");

          strcpy(buf->subautor[sub].name,tk);
          (buf->subautor)[sub].name[strlen(buf->subautor[sub].name)]='\0';

          tk=strtok(NULL," ");
          strcpy(buf->subautor[sub].priez,tk);
          (buf->subautor)[sub].priez[strlen(buf->subautor[sub].priez)]='\0';
          (buf->subautor)[sub].ty=buf->type[sub+1];
          sub++;
        }
        (buf->subsize)=sub;
      }
    }
    if (counter==4){
      strcpy(buf->time,str);
      buf->time[strlen(buf->time)]='\0';
      if(sub==0){
        buf->subsize=0;
      }
      if(f!=(q)-1){
        buf=(buf->next);
        sub=0;
        f++;
        t=0;
        counter=0;
      }
      continue;
    }
    counter++;
  }
  printf("Nacitalo sa %d zaznamov\n",q);
  return q;
}
/////////////////////////////
void p(block*pole, int*size){
  block *buf,*pred,*now,*moj;
  int f,counter=1,t=0;
  char str[150],str2[70],*token,*tk;
  (*size)++;
  printf("Zadajte poradie\n");
  scanf("%d",&f);
  f--;

  buf=pole->next;
  if(f>=(*size)){
    f=(*size)-1;
  }
  if(f<0){
    f=(*size)-1;
  }
  if(f!=0){
    for (int i=0;i<(*size)-1;i++){
      if (i==f-1){
        pred=buf;//Save the first element
        now=pred->next;//Save the original second element
        buf->next=(block*)malloc (sizeof(block));
        moj=buf->next;
        pred->next=buf->next;//change the next for the first
        if(f!=(*size)-1){
          buf->next->next=now;//change the next for new second
        }
      }
      if(i==(*size)-2){
        break;
      }
      buf=buf->next;
    }
    if(f==(*size)-1){
      buf=buf->next;
      buf->next=(block*)malloc (sizeof(block));
    }
    buf=pole;
  }
  if(f==0){
    pole->next=(block*)malloc (sizeof(block));
    pole->next->next=buf;
    pred=pole->next;
    now=buf;
    moj=pole->next;//copy pointer of the new fisrt element
  }
  moj->poradie=0;
  buf=pole->next;
  for (int i=0;i<(*size);i++){
    if(buf->poradie>=f){
      buf->poradie++;
    }
    if(i==(*size)-1){
      break;
    }
    buf=buf->next;
  }
  moj->poradie=f;
  //Start putting in information from user
  buf=moj;
  int sub=0,q=(*size);
  char buffer[70];

  printf("Write ID prispevku\n");
  getchar();
  fgets(str,20,stdin);
  int code=0;
  char *tip,b,p;
  while(code==0){
    tip=&str[2];
    b=str[0];
    p=str[1];
    int a=atoi(tip);
    code=1;
    if((b!='U' && b!='P')){//check for the correct id,in order to work with function a

      code=0;
    }
    if(( p!='D' && p!='P')){

      code=0;
    }
    if(a==0){
      a=1;
    }
    if(a%15!=0){

      code=0;
    }
    if(code==0){
      printf("Zoznam je nespravny\n");
      (*size)--;
      if(*size==0){
        return;
      }
      pred->next=now;


      buf=pole->next;
      for (int i=0;i<(*size);i++){
        if(buf->poradie>=f){
          buf->poradie--;
        }
        if(i==(*size)-1){
          break;
        }
        buf=buf->next;
      }
      return;
    }
  }
  strcpy(buf->id,str);
  (buf->id)[strlen(buf->id)]='\0';

  printf("Write Nazov prispevku\n");

  fgets(str,150,stdin);

  strcpy(buf->subject,str);
  (buf->subject)[strlen(buf->subject)-1]='\0';//manualy ending the line for safety and making it not containing the \n symbol
  (buf->subject)[strlen(buf->subject)]='\0';

  printf("Write Autorov prispevku\n");

  fgets(str,70,stdin);
  int u=0;
    for (int i=0;i<strlen(str);i++){
      if(str[i]=='#'){//check for the # symbol and space in the autor name, for safety of program
        buf->type[t]=str[i+1];
        t++;
        str[i]=' ';
        str[i+1]=' ';
        str[i+2]='.';
      }
      if(str[i]==' '){
        u++;
      }
    }
    if(t==0){//counting # symbol and spaces
      printf("Zoznam je nespravny\n");
      (*size)--;
      if(*size==0){
        return;
      }
      pred->next=now;


      buf=pole->next;
      for (int i=0;i<(*size);i++){
        if(buf->poradie>=f){
          buf->poradie--;
        }
        if(i==(*size)-1){
          break;
        }
        buf=buf->next;
      }
      return;
    }
    if(u==2){
      printf("Zoznam je nespravny\n");
      (*size)--;
      if(*size==0){
        return;
      }
      pred->next=now;

      buf=pole->next;
      for (int i=0;i<(*size);i++){
        if(buf->poradie>=f){
          buf->poradie--;
        }
        if(i==(*size)-1){
          break;
        }
        buf=buf->next;
      }
      return;
    }
    strcpy(str2,str);
    token=strtok(str2,".");
    strcpy((buf->autor).name,token);
    ((buf->autor).name)[strlen((buf->autor).name)]='\0';

    tk=strtok((buf->autor).name," ");

    tk=strtok(NULL," ");

    strcpy((buf->autor).priez,tk);
    ((buf->autor).priez)[strlen((buf->autor).priez)]='\0';

    buf->autor.ty=buf->type[0];

    strcpy(str2,str);
    token=strtok(str2,".");
    token=strtok(NULL,".");
    if(strcmp(token,"\n")!=0){
      strcpy(buffer,token);

      tk=strtok(buffer," ");

      strcpy((buf->subautor[sub]).name,tk);
      (buf->subautor[sub]).name[strlen(buf->subautor[sub].name)]='\0';

      tk=strtok(NULL," ");
      strcpy(buf->subautor[sub].priez,tk);
      (buf->subautor[sub]).priez[strlen(buf->subautor[sub].priez)]='\0';
      (buf->subautor[sub]).ty=buf->type[sub+1];
      strcpy(str2,str);
      token=strtok(str2,".");
      token=strtok(NULL,".");

      sub++;
      while(token!=NULL || strcmp(token,"\n")!=0){

        token=strtok(NULL,".");

        if(token==NULL || strcmp(token,"\n")==0 ||strcmp(token," ")==0){
          break;
        }
        strcpy(buffer,token);

        tk=strtok(buffer," ");

        strcpy(buf->subautor[sub].name,tk);
        (buf->subautor)[sub].name[strlen(buf->subautor[sub].name)]='\0';

        tk=strtok(NULL," ");
        strcpy(buf->subautor[sub].priez,tk);
        (buf->subautor)[sub].priez[strlen(buf->subautor[sub].priez)]='\0';
        (buf->subautor)[sub].ty=buf->type[sub+1];
        sub++;
      }
      (buf->subsize)=sub;
    }

    printf("Write Cas prispevku\n");

    fgets(str,70,stdin);
    if( atof(str)>210000000000 || fmod(atof(str),1000)>2000 ||atof(str)<200000000000){//check for the right time, year cant be more 2100 or less then 2000, and time cant be later then 20:00
      printf("Zoznam je nespravny\n");
      (*size)--;
      if(*size==0){
        return;
      }
      pred->next=now;

      buf=pole->next;
      for (int i=0;i<(*size);i++){
        if(buf->poradie>=f){
          buf->poradie--;
        }
        if(i==(*size)-1){
          break;
        }
        buf=buf->next;
      }
      return;
    }
    strcpy(buf->time,str);
    buf->time[strlen(buf->time)]='\0';
    if(sub==0){
      buf->subsize=0;
    }
    if(f!=(q)-1){
      buf=(buf->next);
      sub=0;
      f++;
      t=0;
      counter=0;
    }

  counter++;
}
/////////////////////////////
void z(block*pole, int* size){
  block *buf,*now,*pred=NULL;
  char name[30],priez[30];
  int code=0;
  buf=pole->next;
  scanf("%s %s",name,priez);
  for(int i=0;i<(*size);i++){
    code=0;
    if(strcmp(buf->autor.name,name)==0 && strcmp(buf->autor.priez,priez)==0){//checking name and surname
      printf("Prispevok s nazvom %s bol vymazany.\n",buf->subject);
      if(pred!=NULL){
        pred->next=buf->next;
        free(buf);
        (*size)--;
        code=1;
      }
      if(pred==NULL){
        pole->next=buf->next;
        free(buf);
        (*size)--;
        code=1;
      }
    }
    if(i>=(*size)-1){
      break;
    }
    if(code==0){
      pred=buf;//If, two objects that marked on deletion, was close together, without this code, pred will point to the deleted object
    }
    buf=buf->next;
  }
  buf=pole->next;
  for(int i=0;i<(*size);i++){
    buf->poradie=i;
    if(i==(*size)-1){
      break;
    }
    buf=buf->next;
  }

}
/////////////////////////////
void v(block* pole, int size){
  block *buf;
  buf=pole->next;
  if(size==0){
    printf("Prazdny zoznam zaznamov\n");
    return;
  }
  for(int j=0;j<size;j++){
    printf("%d.\n",buf->poradie+1);
    printf("ID prispevku: %s",buf->id);
    printf("Nazov prispevku: %s\n",buf->subject);
    printf("Mena autorov:\n");
    printf("    1: %s %s (%c)\n",buf->autor.name,buf->autor.priez,buf->autor.ty);
    for(int i=0;i<buf->subsize;i++){
        printf("    %d: %s %s (%c)\n",i+2,buf->subautor[i].name,buf->subautor[i].priez,buf->subautor[i].ty);
    }
    printf("Datum a cas: %c%c%c%c.%c%c.%c%c %c%c:%c%c",buf->time[0],buf->time[1],buf->time[2],buf->time[3],buf->time[4],buf->time[5],buf->time[6],buf->time[7],buf->time[8],buf->time[9],buf->time[10],buf->time[11],buf->time[12]);
    printf("\n");
    buf=(buf->next);
  }
}
/////////////////////////////
void a(block*pole,int size){
  char str[15];
  char *tip,u,p;
  int a=1,code=0;
  block *buf;
  if(size==0){
    printf("Prazdny zoznam zaznamov\n");
    return;
  }
  getchar();
  while(code==0){
    scanf("%d",&a);
    scanf("%s",str);
    u=str[0];
    p=str[1];
    code=1;
    if((u!='U' && u!='P')){
      printf("Zadane udaje nie su korektne, zadaj novy retazec:");
      code=0;
    }
    if(( p!='D' && p!='P')){
      printf("Zadane udaje nie su korektne, zadaj novy retazec:");
      code=0;
    }
    if(a==0){
      a=1;
    }
    if(a%15!=0){
      printf("Zadane udaje nie su korektne, zadaj novy retazec:");
      code=0;
    }
  }
  buf=pole->next;
  for(int i=0;i<(size);i++){
    tip=&(buf->id)[2];
    if(atoi(tip)==a){
      printf("Prispevok s nazvom %s sa bude prezentovat %c%c [%c%c].\n",buf->subject,u,p,(buf->id)[0],(buf->id)[1]);
      buf->id[0]=u;
      buf->id[1]=p;
    }
    if(i==(size)-1){
      break;
    }
    buf=buf->next;
  }
}

/////////////////////////////
void r(block*pole,int size){
  block*buf,*a,*b,*pa,*pb,*buffer;
  int nowa=-1,nowb=-1,preda,predb,c=0;
  if(size<2){//we cant change two elements in struct if we dont have atleast two.
    printf("Malo elementov v zozname\n");
    return;
  }
  while(c==0){
    nowa=-1;
    nowb=-1;
    scanf("%d %d",&nowa,&nowb);
    nowa--;
    nowb--;
    c=1;
    if(nowa<0 || nowb<0){
      printf("Oba cisla musia byt>0\n");
      return;
    }
    if(nowa==nowb){
      printf("Cisla musia byt rozne\n");
      return;
    }
    if(nowa>=size || nowb>=size){
      printf("Cisla musia byt <= %d\n",size);
      return;
    }
  }
  if (nowa>nowb){
    c=nowa;
    nowa=nowb;
    nowb=c;
  }
  preda=nowa-1;
  predb=nowb-1;
  buf=pole->next;
  for(int i=0;i<size;i++){
    if(i==nowa-1){
      pa=buf;
      a=buf->next;
    }
    if(i==nowb-1){
      pb=buf;
      b=buf->next;
    }
    if(i==size-1){
      break;
    }
    buf=buf->next;
  }
  if(nowa==0){
    a=pole->next;
    pa=pole;
  }

  if(nowa!=nowb-1 ){//becouse of pointers, if we do the same for close one elements, that will couse them to point on themself
    pa->next=b;
    buffer=b->next;
    b->next=a->next;
    pb->next=a;
    a->next=buffer;
  }
  if(nowa==nowb-1 ){
    pa->next=b;
    a->next=b->next;
    b->next=a;
  }
  buf=pole->next;
  for(int i=0;i<(size);i++){
    buf->poradie=i;
    if(i==(size)-1){
      break;
    }
    buf=buf->next;
  }
}
/////////////////////////////
int main() {
block pole;
block *buf;
FILE *fp=NULL;
int size=0,min=0;
char c[10];
  while(1){
  scanf("%s",c);
  if(strcmp(c, "n")==0){
    size=n(&pole,&fp,size);
  }
  else if(strcmp(c, "v")==0){
    v(&pole,size);
  }
  else if(strcmp(c, "r")==0){
    r(&pole,size);
  }
  else if(strcmp(c, "a")==0){
    a(&pole,size);
  }
  else if(strcmp(c, "p")==0){
    p(&pole,&size);
  }
  else if(strcmp(c, "z")==0){
    z(&pole,&size);
  }
  else if(strcmp(c, "k")==0){
    buf = pole.next;
    for (int j = 0; j < size; j++) {
      pole.next = buf->next;
      free(buf);
      buf = pole.next;
    }
    size = 0;
    fclose(fp);
    return 0;
  }
  else{
    printf("I couldnt understand you\n");
  }


  }
}
