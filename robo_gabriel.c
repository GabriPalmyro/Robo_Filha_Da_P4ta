#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int x;
	int y;
}pRobo;

typedef struct
{
	int x;
	int y;
}ponto;

typedef struct
{
	ponto p1;
	ponto p3;
}area;


int calculaDist(pRobo pos, ponto A){
    int dis, tempX, tempY;
    tempX = A.x - pos.x;
    if(tempX < 0){
        tempX = tempX * -1;
    }
    tempY = A.y - pos.y;
    if(tempY < 0){
        tempX = tempX * -1;
    }
    dis = tempX + tempY;
    printf("%d\n", dis);
    return dis;
}

ponto andarRobo(int n, area areas[n], pRobo ini){
    ponto final1;

   if(calculaDist(ini, areas[n].p1) < calculaDist(ini, areas[n].p3)){
        final1.x = areas[n].p1.x;
        final1.y = areas[n].p1.y;
    } else {
        final1.x = areas[n].p3.x;
        final1.y = areas[n].p3.y;
    }

    return final1;
}

int main()
{
    int n, i, distF = 0;
    pRobo ini;
    ponto tempPos, fin;
    scanf("%d %d %d %d", &ini.x, &ini.y, &fin.x, &fin.y);
    scanf("%d", &n);
    area areas[n];

    for(i = 0; i < n; i++){
        scanf("%d %d %d %d", &areas[i].p1.x, &areas[i].p1.y, &areas[i].p3.x, &areas[i].p3.y);
    }

    for(i = 0; i < n; i++){
        tempPos = andarRobo(i, areas, ini);
        distF = distF + calculaDist(ini, tempPos);
        ini.x = tempPos.x;
        ini.y = tempPos.y;
    }

    distF = distF + calculaDist(ini, fin);

    printf("\nDist final : %d", distF);


    return 0;
}
