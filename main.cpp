#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>
#include "estruturas.h"

#define TAMANHO  30 /*Tamanho default dos objetos*/

/*ponto X, Y e Z; Angulo de rotação; Fator de aceleração*/
GLdouble pX=5, pY=0, pZ=10, rttAngl = 0, accl=1.0;
/*ponto X anterior, ponto Z anterior*/
GLdouble p_oldX = 0, p_oldZ = 0;
/*Angulo da perspectiva, razão de x, y da perspectiva*/
GLfloat angle, fAspect;
/*Valor do pi*/
double PI = 3.141592653; 
/*qtd de objetos no arquivo;  Camera atual*/
int qtd=0,  atualCamera = 4; 
/*Instância a lista de objetos*/
tObj *objetos = (tObj *) malloc(sizeof(tObj));
/*opcao de movimento, lat: direcao moviento n-norte, s-sul, 
                    lng: direcao movimento l-leste, o-oeste*/
char op, lat='n',lng='l';

/*Função q define o valor da escala dos objetos*/
double valEscala(double pontoIni, double pontoFim) {
    double dif  =  pontoFim - pontoIni; /*Pega o tamanho do objeto*/
    double razao = dif/2;/*Traz o objeto para o ponto zero*/
    return razao + pontoIni; /*Retorna o ponto inicial do objeto*/ 
}
   
/*Função que desenha os eixos x, y e z  no universo*/
void desenhaVertices() {
    /*Desenha o eixo X*/
    glPushMatrix();
    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(200,0,0);         
        glVertex3f(-200,0,0);  
    glEnd();
    glPopMatrix();
    
    /*Desenha o eixo Y*/
    glPushMatrix();
    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0,200,0);         
        glVertex3f(0,-200,0);  
    glEnd();
    glPopMatrix();

    /*Desenha o eixo Z*/
    glPushMatrix();
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0,0,5000);         
        glVertex3f(0,0,-5000);  
    glEnd();
    glPopMatrix();
}

void desenhaTopografia () {

    /*Desenha uma das ruas*/
    glPushMatrix();
    glBegin(GL_QUADS);			
        glColor3f(0.0f, 0.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( -15.0f, 0.0f, -150.0f);
		glVertex3f( 15.0f, 0.0f, -150.0f);
		glVertex3f( 15.0f, 0.0f,  150.0f);
		glVertex3f( -15.0f, 0.0f, 150.0f);
	glEnd();
    glPopMatrix();

    /*Desenha uma das ruas*/
    //glPushMatrix();
    glBegin(GL_QUADS);			
        glColor3f(0.0f, 0.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( -175.0f, 0.0f, -150.0f);
		glVertex3f( -145.0f, 0.0f, -150.0f);
		glVertex3f( -145.0f, 0.0f,  150.0f);
		glVertex3f( -175.0f, 0.0f, 150.0f);
	glEnd();
    glPopMatrix();

    /*Desenha uma das ruas*/
    glPushMatrix();
    glBegin(GL_QUADS);			
        glColor3f(0.0f, 0.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( 175.0f, 0.0f, -150.0f);
		glVertex3f( 145.0f, 0.0f, -150.0f);
		glVertex3f( 145.0f, 0.0f, 150.0f);
		glVertex3f( 175.0f, 0.0f, 150.0f);
	glEnd();
    glPopMatrix();

    /*Desenha uma das ruas*/
    glPushMatrix();
    glBegin(GL_QUADS);			
        glColor3f(0.0f, 0.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( -175.0f, 0.0f, -150.0f);
        glVertex3f( 175.0f, 0.0f, -150.0f);	
        glVertex3f( 175.0f, 0.0f, -120.0f);		
		glVertex3f( -175.0f, 0.0f, -120.0f);
	glEnd();
    glPopMatrix();

    /*Desenha uma das ruas*/
    glPushMatrix();
    glBegin(GL_QUADS);			
        glColor3f(0.0f, 0.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( -175.0f, 0.0f, 150.0f);
        glVertex3f( 175.0f, 0.0f, 150.0f);	
        glVertex3f( 175.0f, 0.0f, 120.0f);		
		glVertex3f( -175.0f, 0.0f, 120.0f);
	glEnd();
    glPopMatrix();    
    
    /*Desenha uma das ruas*/
    glPushMatrix();
    glBegin(GL_QUADS);			
        glColor3f(0.0f, 0.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( -175.0f, 0.0f, 15.0f);
        glVertex3f( 175.0f, 0.0f, 15.0f);	
        glVertex3f( 175.0f, 0.0f, -15.0f);		
		glVertex3f( -175.0f, 0.0f,-15.0f);
	glEnd();
    glPopMatrix();
    

    /*Desenha o plano*/
    glPushMatrix();
	glBegin(GL_QUADS);			
        glColor3f(0.0f, 1.0f, 0.0f);
        glNormal3f( 0.0f, 1.0f, 0.0f);/*Normal da face*/
		glVertex3f( -175.0f, -0.4f, -150.0f);
		glVertex3f( 175.0f, -0.4f, -150.0f);
		glVertex3f( 175.0f, -0.4f,  150.0f);
		glVertex3f( -175.0f, -0.4f, 150.0f);/*Desenha um objeto no universo*/
    glEnd();
    glPopMatrix();
}
void desenha (tObj objeto) {
    
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(valEscala(objeto.pIniX, objeto.pFimX), 
                 valEscala(objeto.pIniY, objeto.pFimY), 
                 valEscala(objeto.pIniZ, objeto.pFimZ));
    glScalef((objeto.pFimX - objeto.pIniX)/TAMANHO, 
             (objeto.pFimY - objeto.pIniY)/TAMANHO, 
             (objeto.pFimZ - objeto.pIniZ)/TAMANHO);
    glutSolidCube(TAMANHO);                   
    glPopMatrix();
}


/*Detecta  a colisao do veiculo com os demais objetos*/
int detectaColisao(tObj carro) {
    
    int colX = 0, colZ = 0;    

    for (int i=0; i < qtd; i++) {
        /*Colidiu em X*/
        if ((carro.pIniX >= objetos[i].pIniX) &&
            (carro.pIniX <= objetos[i].pFimX))
            colX = 1;       
        /*Colidiu em X*/          
        if ((carro.pFimX >= objetos[i].pIniX) &&
            (carro.pFimX <= objetos[i].pFimX))
            colX = 1;

        /*Colidiu em Z*/
        if ((carro.pIniZ >= objetos[i].pIniZ) &&
            (carro.pIniZ <= objetos[i].pFimZ))
            colZ = 1;
          
        /*Colidiu em Z*/
        if ((carro.pFimZ >= objetos[i].pIniZ) &&
            (carro.pFimZ <= objetos[i].pFimZ))
            colZ = 1;

        if (colZ && colX)
            return 1;/*Haverá uma colisão se houverem colisões simultâneas 
                        em X e Z*/
        
        colZ = colX = 0; /*Reseta as flags de colisão*/
    
    }
    
    return 0;
    
}

/*Desenha e move o veículo*/
void moveVeiculo () {
    
    tObj carro;
    
    /*monta o veículo pelos vértices*/
    carro.pIniX = 0  + pX;
    carro.pFimX = 10 + pX;    
    carro.pIniY = 0  + pY; 
    carro.pFimY = 5  + pY;
    carro.pIniZ = 0  + pZ;
    carro.pFimZ = 15 + pZ;
    
    if (detectaColisao(carro)) {
        printf("Colidiu!\n");        
        pX = p_oldX;
        pZ = p_oldZ;
        carro.pIniX = 0  + pX;
        carro.pFimX = 10 + pX;    
        carro.pIniY = 0  + pY; 
        carro.pFimY = 5  + pY;
        carro.pIniZ = 0 + pZ;
        carro.pFimZ = 15 + pZ;
    }
    
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);   
    glTranslatef(valEscala(carro.pIniX, carro.pFimX), 
                     valEscala(carro.pIniY, carro.pFimY), 
                     valEscala(carro.pIniZ, carro.pFimZ));
    glRotatef(rttAngl, 0, 1, 0);
    glScalef((carro.pFimX - carro.pIniX)/5, 
                 (carro.pFimY - carro.pIniY)/5, 
                 (carro.pFimZ - carro.pIniZ)/5);
    glutSolidCube(5);        
    glPopMatrix();
        

}

// Função callback chamada para fazer o desenho
void desenhaUniverso()
{
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    

    desenhaVertices();
    desenhaTopografia();   
    
    for (i=0; i < qtd; i++)
        desenha(objetos[i]);/*Desenha os objetos do mundo*/

    if (atualCamera != 2) 
        moveVeiculo(); /*Desenha o veiculo no ponto desejado*/
    
    glutSwapBuffers();// Executa os comandos OpenGL

 }

void moveCamera() {
    tObj carro; /*Objeto carro*/
 
       switch (atualCamera) {
        case 2: /*Primeira pessoa*/
            carro.pIniX = 0  + pX;
            carro.pFimX = 10 + pX;    
            carro.pIniY = 0  + pY; 
            carro.pFimY = 5  + pY;
            carro.pIniZ = 0  + pZ;
            carro.pFimZ = 15 + pZ;
            
            if (detectaColisao(carro)) {
                pX = p_oldX;
                pZ = p_oldZ;
                printf("Colidiu!\n");
            }
            
            /*Posiciona a câmera em primeira pessoa*/
            gluLookAt((carro.pIniX+carro.pFimX)/2, (carro.pIniY+carro.pFimY)/2
                        ,(carro.pIniZ+carro.pFimZ)/2, 
                        cos(((rttAngl+90)/180)*PI) + (carro.pIniX+carro.pFimX)/2
                        , (carro.pIniY+carro.pFimY)/2, 
                        sin(((rttAngl-90)/180)*PI) + (carro.pIniZ+carro.pFimZ)/2
                        , 0,1,0); 
            break;
        case 3: /*Perspectiva*/                
                gluLookAt(pX+(75*((pX)/(fabs(pX)))),135,pZ+(145*((pZ)/(fabs(pZ)))), 0,0,0, 0,1,0);
                carro.pIniX = 0  + pX;
                carro.pFimX = 10 + pX;    
                carro.pIniY = 0  + pY; 
                carro.pFimY = 5  + pY;
                carro.pIniZ = 0  + pZ;
                carro.pFimZ = 15 + pZ;
                /*gluLookAt((carro.pIniX+carro.pFimX)/2, (carro.pIniY+carro.pFimY)/2
                        ,((carro.pIniZ+carro.pFimZ)/2) + 50, 
                        cos(((rttAngl+90)/180)*PI) + (carro.pIniX+carro.pFimX)/2
                        , (carro.pIniY+carro.pFimY)/2, 
                        sin(((rttAngl-90)/180)*PI) + (((carro.pIniZ+carro.pFimZ)/2)+50)
                        , 0,1,0); */

/*                gluLookAt( (cos(((rttAngl+90)/180)*PI) + (carro.pIniX+carro.pFimX)/2)
                        , (carro.pIniY+carro.pFimY)/2
                        , (sin(((rttAngl-90)/180)*PI) + (carro.pIniZ+carro.pFimZ)/2) + 10
                        , (cos(((rttAngl+90)/180)*PI) + (carro.pIniX+carro.pFimX)/2)
                        , 35
                        , (sin(((rttAngl-90)/180)*PI) + (carro.pIniZ+carro.pFimZ)/2)
                        , 0,1,0);*/

//            if (!op )
//                gluLookAt( (cos(((rttAngl-90)/180)*PI) + pX) /*+ (sin(((rttAngl-90)/180)*PI) + pX)*/
//                            , 85
//                            , (sin(((rttAngl+90)/180)*PI) + (pZ+50)) /*+ (cos(((rttAngl+90)/180)*PI) + pZ)*/
//                          , pX
//                            , 15
//                            , pZ
//                            , 0,1,0);
//           else
//                gluLookAt( (sin(((rttAngl+90)/180)*PI) + (pX+50)) /*+ (sin(((rttAngl-90)/180)*PI) + pX)*/
//                            , 85
//                            , (cos(((rttAngl-90)/180)*PI) + pZ) /*+ (cos(((rttAngl+90)/180)*PI) + pZ)*/
//                           , pX
//                            , 15
//                            , pZ 
//                            , 0,1,0);

            break;
        case 4: /*camera topo*/            
            //gluLookAt(pX,375,pZ, pX,pY,pZ, 0,0,-1); 
            gluLookAt(0,365,0, 0,0,0, 0,0,-1); 
            break;
        default:
            break;
    }
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 

   	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"     
	GLfloat posicaoLuz[4]={0.0, 150.0, 0.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};    
	GLint especMaterial = 60;
 
 	// Especifica que a cor de fundo da janela será 
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
    glMaterialfv(GL_BACK,GL_SPECULAR, especularidade);	
	// Define a concentração do brilho
	glMateriali(GL_BACK, GL_SHININESS,especMaterial);    

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );


	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	///Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
    // Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);


	angle=45;

}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	tObj carro;
    
    // Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
    //gluPerspective(angle,fAspect,0.1,5000);
    gluPerspective(angle,fAspect,2.5,5000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
    moveCamera();
 
}

// Callback para gerenciar eventos do teclado para teclas especiais 
void Teclado (int key, int x, int y)       {       
        
        p_oldX = pX;
        p_oldZ = pZ;

        /*Troca a direção norte, sul*/
        if (fabs(rttAngl) <=  90)             
            lat = 'n';
        else
            lat = 's';
        /*TROCA A DIREÇÃO LESTE - OESTE*/
        if (rttAngl > 0) 
            lng='o';
        else
            lng='l';            
        
        op = '\0';
		switch (key) {
			/*Rotação para esquerda do veículo*/
            case GLUT_KEY_LEFT :
                
                if (fabs(rttAngl+5)>180) { /*Caso o ângulo fique maior que 
                                            180 graus, mudo o sentido*/            
                    rttAngl = rttAngl*(-1);
                    if (rttAngl > 0) 
                        lng='o';
                    else
                        lng='l';
                }                
                op = 'r';
                rttAngl+=5;
                break;
            /*Rotação para direita do veículo*/
			case GLUT_KEY_RIGHT :
                if (fabs(rttAngl-5)>180) {  /*Caso o ângulo fique maior que 180 graus, mudo o sentido*/           
                    rttAngl = rttAngl*(-1);
                    if (rttAngl > 0) 
                        lng='o';
                    else
                        lng='l';
                }                
                op = 'r';
                rttAngl-=5;                
                break;
			/*Movimento para frente do veículo*/
            case GLUT_KEY_UP :
                pX = ((cos(((rttAngl+90)/180)*PI) * accl) + pX);
                pZ = (((sin(((rttAngl-90)/180)*PI)) * accl) + pZ);                
				break;
			/*Movimento de Ré do veículo*/
            case GLUT_KEY_DOWN : 
                pX = (pX - (cos(((rttAngl+90)/180)*PI)) * accl);
                pZ = (pZ - ((sin(((rttAngl-90)/180)*PI)) * accl));
				break;
			case GLUT_KEY_PAGE_UP : 
                if (accl < 5)/*Aumenta a marcha =P*/
                    accl+=0.5;
				break;
			case GLUT_KEY_PAGE_DOWN :             
                if (accl < 5)/*Diminui a marcha =(*/
                    accl-=0.5;
				break;
            
            case GLUT_KEY_F2 : /*Primeira pessoa*/               
                atualCamera = 2;
                break;
            case GLUT_KEY_F3 : /*Visão perspectiva*/
                atualCamera = 3;
                break;
            case GLUT_KEY_F4 :/*Visão do topo*/
                atualCamera = 4;
                break;            
		}

        glLoadIdentity();        
        moveCamera();
        
        glutPostRedisplay();        
        
  }

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);    
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Programa Principal
int main(void)
{
    /*Carrega os objetosdo arquivo*/
    objetos = carregaObjetos(objetos,&qtd);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
	glutInitWindowSize(350,300);
	glutCreateWindow("Super Buccaneer 2000");
	glutDisplayFunc(desenhaUniverso);
    glutSpecialFunc(Teclado);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();  

}



