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
    printf("Distancia: %d\n", dis);
    
    return dis;
}
// função que calcula qual o ponto da proxima area mais perto do ponto do robo
ponto andarRobo(lista *area, ponto pos){
	no *aux;
	ponto final1;
    int dist1, dist2, dist3, dist4, menor, i;
    // area->inicio->p.x = 5; como mudar as operações
    aux = area->inicio;
    dist1 = calculaDist(pos, aux->p);
    aux = aux->prox;
    dist2 = calculaDist(pos, aux->p);
    aux = aux->prox;
    dist3 = calculaDist(pos, aux->p);
    aux = aux->prox;
    dist4 = calculaDist(pos, aux->p);
	
	menor = dist1;
	aux = area->inicio;
   	if(dist2 < menor){
   		i = 1;
   		aux = aux->prox;
   		final1 = aux->p;
        menor = dist2;
	} else {
		final1 = aux->p;
		i = 0;
	}
	
	if (dist3 < menor){
		while(i<3){
			aux = aux->prox;
			i++;
		}
		final1 = aux->p;
        menor = dist3;
	}
	
	if (dist4 < menor){
		while(i<4){
			aux = aux->prox;
			i++;
		}
		final1 = aux->p;
	}
	
	return final1;
}


int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	
	int x1, y1, x2, y2, n,i=0,x,y,j, distF = 0;
	ponto pi, pf, p1, p2, p3, p4, tempPos;
	lista A;
	no *aux;//ponteiro auxiliar que percorre as listas de pontos para impressão
		
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
	puts("\n\n");
	
	 for(i = 0; i < n; i++){
        tempPos = andarRobo(&area[i], pi);
        distF = distF + calculaDist(pi, tempPos);
        pi.x = tempPos.x;
        pi.y = tempPos.y;
       	printf("Posicao atual do robo: %f.0,%f.0\n", pi.x, pi.y);
    }
    
    distF = distF + calculaDist(pi, pf);
	
	printf("Distancia final de %.0f,%.0f ate %.0f,%.0f eh de: %d", pi.x,pi.y,pf.x,pf.y,distF);
}

