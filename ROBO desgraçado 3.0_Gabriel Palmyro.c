#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct
{
	float x;
	float y;
}ponto;//define ponto no plano cartesiano

typedef struct no
{
	ponto p;
	struct no *prox;
}no;//define o tipo nó de lista

typedef struct
{
	no *inicio;
}lista;//define o tipo lista encadeada

//cria uma lista de áreas cobertas usando um vetor de listas
void CriarListaAreas(int n, lista A[n])//cria uma lista l vazia
{
	int i;
	for(i=0;i<n;i++)
	{
		A[i].inicio=NULL;
	}
	
}
//Insere um novo ponto p1 na lista de pontos chamada área. Ou seja, cada área coberta é formada por uma lista de 4 pontos
int InserirListaPonto(lista *area,ponto p1)
{
	no *novo,*aux;
	
	novo = malloc(sizeof (no));
	
	if(!novo)
		return 0;
	
	novo->prox=NULL;
	novo->p = p1;
	
	
	if(area->inicio==NULL)//lista na posição i está vazia
	{
		area->inicio = novo;//o no novo é o primeiro da lista
		
	}
	else
	{
		aux = area->inicio;
		while(aux->prox!=NULL)
		{
			aux = aux->prox;
		}
		aux->prox = novo;	
	}
	
	return 1;
}
//cria uma estrutura ponto formada pelas coordenadas x e y
ponto CriarPonto(float x2, float y2)
{
	ponto p;
	p.x = x2;
	p.y = y2;
	return p;
}
//criar os pontos p3 e p4 a partir de p1 e p2 informados pelo usuário
void CriarPontosArea(ponto p1,ponto p3,ponto *p2, ponto *p4)
{
	p2->x= p1.x;
	p2->y = p3.y;
	p4->x = p3.x;
	p4->y = p1.y;
	printf("p2 = (%f,%f)\n",p2->x,p2->y);
	printf("p4 = (%f,%f)\n",p4->x,p4->y);
}
// função que calcula a distancia entre dois pontos
int calculaDist(ponto pos, ponto A){
	
	int tempX, tempY, dis;
    tempX = A.x - pos.x;
    if(tempX < 0){
    	tempX = tempX * -1;
	}
    
    tempY = A.y - pos.y;
    if(tempY < 0){
    	tempY = tempY * -1;
	}
	
    dis = tempX + tempY;
	    
    return dis;
}


int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	
	int x1, y1, x2, y2, n,i = 0, x, y, j, k, menor, cont = 0, distT;
	ponto pi, pf, p1, p2, p3, p4;
	lista A;
	no *aux, *aux2; //ponteiro auxiliar que percorre as listas de pontos 
	
	printf("Posicao inicial do robo\n");
	scanf("%f %f",&pi.x,&pi.y);
	printf("Posicao final do robo\n");
	scanf("%f %f",&pf.x, &pf.y);
	printf("Numero de areas cobertas\n");
	scanf("%d",&n);
	lista area[n]; //vetor que armazena uma lista encadeada em cada posição do vetor
	//Ou seja, uma lista de 4 pontos que formam uma área coberta
	CriarListaAreas(n,area); //função que cria o vetor que armazena uma lista para cada área coberta.
	//cria uma lista vazia
	
	while(i<n)
	{
		printf("Canto inferior esquerdo\n");
		scanf("%d%d",&x1,&y1);
		p1 = CriarPonto(x1,y1);
		
		//função que insere o ponto p1 na lista de pontos na posição i do vetor lista
		InserirListaPonto(&area[i],p1);
		
		printf("Canto superior direito\n");
		scanf("%d%d",&x2,&y2);
		p3 = CriarPonto(x2,y2);
		
		InserirListaPonto(&area[i],p3);
		//função que cria os outros dois pontos que pertencem a área coberta	
		CriarPontosArea(p1,p3,&p2,&p4);
		//insere os dois pontos criados na lista de pontos na posição i
		InserirListaPonto(&area[i],p2);
		InserirListaPonto(&area[i],p4);
		i++;
		
		
	}
	
	//impressao da lista de areas cobertas
	for(i=0;i<n;i++)
	{
		aux = area[i].inicio;
		printf("\nPontos da area %d\n",i+1);
		while(aux!=NULL)
		{
			printf("Ponto %i = (%f,%f)\n",j,aux->p.x,aux->p.y);
				aux = aux->prox;
				j++;
		}	
	}
	puts("\n");
	
	 for(i = 0; i < n-1; i++){ 				//looping que vai da primeira area ate n-1 (penultima area)
	 	menor = 100; 						// o valor de menor está estabelecido como alto para sempre haver uma distancia menor que ele
	 	aux = area[i].inicio; 				//esse aux sempre aponta para cada ponto que vai ser comparado com cada ponto da area i+1
        for(j = 0; j < 4; j++){ 			//esse for é o que faz o aux caminhar pela area 1
        	aux2 = area[i+1].inicio;	
        	for(k = 0; k < 4; k++){ 		// esse for é o que faz o aux2 caminhar pela area 2 comparando com o ponto do aux
        		distT = calculaDist(aux->p, aux2->p);
        		if(distT < menor){
        			menor = distT; 	
				}
				aux2 = aux2->prox;
			}
			aux = aux->prox;
		}
		cont = cont + menor;
    } 
    
	
	printf("O robo passa por %d areas descobertas\n", cont);
}

