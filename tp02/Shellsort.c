#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
typedef struct Jogador
{
		int id;
		char nome[100];
		int altura;
		int peso;
		char universidade[100];
		int anoNascimento;
		char cidadeNascimento[100];
		char estadoNascimento[100];
} Jogador;

 typedef struct Log
{
    int matricula;
    int mov;
    int cmp;
    clock_t tempo;


} Log;

 int getId(Jogador* x)
 {
	return x->id;
 }
 char* getNome(Jogador* x )
{
	return x->nome;
}
 int getAltura(Jogador* x)
{
	return x->altura;
}
 int getPeso(Jogador* x)
{
	return x->peso;
}
 char* getUniversidade(Jogador* x)
{
	return x->universidade;
}
 int getAnoNascimento(Jogador* x)
{
	return x->anoNascimento;
}
 char* getCidadeNascimento(Jogador* x)
{
	return x->cidadeNascimento;
}
 char* getEstadoNascimento(Jogador* x)
{
	return x->estadoNascimento;
}
void setId(Jogador *x, int novoId)
{
	x->id = novoId;
}
void setNome(Jogador* x, char* nome)
{
	strcpy(x->nome, nome);
}
void setAltura(Jogador* x, int altura)
{
	x->altura = altura;
}
void setPeso(Jogador* x, int peso)
{
	x->peso = peso;
}
void setUniversidade(Jogador *x, char* universidade)
{
	strcpy(x->universidade, universidade);
}
void setAnoNascimento(Jogador* x, int anoNascimento)
{
	x->anoNascimento = anoNascimento;
}
void setCidadeNascimento(Jogador* x, char* cidadeNascimento)
{
	strcpy(x->cidadeNascimento, cidadeNascimento);
}
void setEstadoNascimento(Jogador* x, char* estadoNascimento)
{
	strcpy(x->estadoNascimento, estadoNascimento);
}
//metodo que cria um clone de um jogador
Jogador clone(Jogador *x)
{
	Jogador clone;
	clone.id = getId(x);
	strcpy(clone.nome, getNome(x));
	clone.altura = getAltura(x);
        clone.peso = getPeso(x);
        clone.anoNascimento = getAnoNascimento(x);
        strcpy(clone.universidade, getUniversidade(x));
	strcpy(clone.cidadeNascimento, getCidadeNascimento(x));
	strcpy(clone.estadoNascimento, getEstadoNascimento(x));

	return clone;
}
//Metodo para ler o arquivo e retornar um ponteiro para os Jogadores selecionados
Jogador* ler()
{
 FILE* arq = fopen("/tmp/players.csv","r");
 if(arq == NULL)
 {
	 printf("nao abriu");
 }
 char temp[1000];
 int cont;
 int num = 0;
 Jogador *y=malloc(sizeof(Jogador));
 Jogador *resp = malloc(3923*sizeof(Jogador));
   while(fscanf(arq, "%[^\n]", temp) != EOF)
   {
	   cont = 0; 
	   fgetc(arq);
	   char *items[8];
	   items[4]="";
	   items[6]="";
	   items[7]="";
           char *token  = strtok(temp,",");
	   for(int i = 0; token ; i++)
	   {
            items[i] = token;
            token = strtok(NULL, ",");
            cont++;
	   }
//ifs para tratar casos em que existiam informações faltantes
	   if(cont == 7 && strlen(items[7])==0)
       {
           items[7] = items[6];
       }
	   else if(cont ==5)
	   {
		   items[5] = items[4];
		   items[4] = "";
	   }
       if(atoi(items[5]) == 0)
       {
           items[6] = items [5];
       }
	   if(atoi(items[4]) != 0)
       {
           items[5] = items[4];
       }

	   setId(y, atoi(items[0]));
	   setNome(y, items[1]);
	   setAltura(y, atoi(items[2]));
	   setPeso(y, atoi(items[3]));
	   setUniversidade(y, items[4]);
	   setAnoNascimento(y, atoi(items[5]));
       setCidadeNascimento(y, items[6]);
	   setEstadoNascimento(y, items[7]);

//ifs para setar corretamente campos não informados
           if(strlen(items[4])==0 || atoi(getUniversidade(y))>0)
	   {
	           setUniversidade(y, "nao informado");
	   }
	     if(strlen(items[6])==0)
	   {
		  setCidadeNascimento(y, "nao informado");
	   }
	     if(strlen(items[7])==0)
	   {
		   setEstadoNascimento(y, "nao informado");
	   }
	     if(getAnoNascimento(y)==0)
         {
             setAnoNascimento(y, atoi(items[4]));
         }
         
//comparar o input do usuario com o que esta sendo lid
	 resp[num] =clone(y);
	 num++;
   }
   fclose(arq);
   return resp;
}

//função para imprimir o jogador selecionado
void imprimir(Jogador *x)
{
	printf("[");
	printf("%d", getId(x));
	printf(" ## ");
	printf("%s", getNome(x));
	printf(" ## ");
	printf("%d", getAltura(x));
	printf(" ## ");
	printf("%d", getPeso(x));
	printf(" ## ");
	printf("%d", getAnoNascimento(x));
	printf(" ## "); 
	printf("%s", getUniversidade(x));
	printf(" ## "); 
	printf("%s", getCidadeNascimento(x));
	printf(" ## ");
	printf("%s]", getEstadoNascimento(x));
	printf("\n");
}
//metodo para trocar dois jogadores de posição no array
void swap(Jogador *i, Jogador *j)
{
	Jogador tmp = *i;
	*i = *j;
	*j = tmp;
	
}
//metodo de comparacao entre jogaddores considerando peso como o atributo inicial e nome como o secundário
int compare2(Log *log, Jogador *x, Jogador *y)
{

	if(getPeso(x) != getPeso(y))
	{
		log->cmp ++;
		return getPeso(x) > getPeso(y);
	}
	else
	{
		log->cmp ++;
		return strcmp(getNome(x), getNome(y));
	}
}
void insercaoPorCor(Jogador *array, Log *log, int n, int cor, int h){
    for (int i = (h + cor); i < n; i+=h) {
        Jogador tmp = array[i];
        int j = i - h;
	  while ((j >= 0) && compare2(log, &array[j], &tmp)>0)
	 {

		array[j+h] = array[j];
		log->mov ++;
		j-=h;

        }
        array[j + h] = tmp;
	log->mov ++;
    }
}
void shellsort(Jogador *array, Log *log, int n) {
    int h = 1;

    do { h = (h * 3) + 1; } while (h < n);

    do {
        h /= 3;
        for(int cor = 0; cor < h; cor++){
            insercaoPorCor(array, log,  n, cor, h);
        }
    } while (h != 1);
}
//metodo para criar um arquivo contendo as informações do objeto log
void fazerLog(Log *log)
{
 FILE* arq = fopen("815336_Shellsort.txt", "w");
  if(arq == NULL)
	  printf("Arquivo nao encontrado");
  else
  {
	  fprintf(arq, "815336\t");
	  fprintf(arq, "%d\t%d\t", log->cmp, log->mov);
	  fprintf(arq, "%f\t", (float)log->tempo/CLOCKS_PER_SEC);
  }
   fclose(arq);
}
int main()
{
  //criação de variavéis e alocação de memória
  clock_t start_t, end_t;
  Log *log = malloc(sizeof(Log));
  char temp[100];
  int i =0;
  Jogador *y = malloc(3923*sizeof(Jogador));
  y = ler();
  Jogador *z= malloc(3923*sizeof(Jogador));
  //while para ler o input ate ser digitado FIM
  while(1)
  {
  scanf("%[^\n]", temp);
  char ch = getchar();
   if(strcmp(temp, "FIM")== 0)
   {
		  break; 
   }
   int num = atoi(temp);
   z[i]= y[num+1]; 
  i++; 

  }
  start_t = clock();
//chamada do metódo de ordenação por Shellsort
  shellsort(z, log, i);
  end_t = clock();
  log->tempo = end_t - start_t;
//impressão dos elementos
 for(int j = 0; j<i ; j++)
  imprimir(z+j);
  fazerLog(log);
//liberação de memoria dos ponteiros
  free(log);
  free(z);
  free(y);
  return 0;
}