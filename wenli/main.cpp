//
//  main.cpp
//  wenli
//
//  Created by 薛梓赫 on 2018/5/16.
//  Copyright © 2018年 薛梓赫. All rights reserved.
//

#include <iostream>

#include <GLUT/GLUT.h>



#include <stdlib.h>

#include <stdio.h>

#define stripeImageWidth 32

GLubyte stripeImage[4 * stripeImageWidth];
static float A=1.0;
static float B=1.0;
static float C=1.0;


void makeStripeImage(void) //生成纹理

{
    int j;
    
    for (j = 0; j<stripeImageWidth; j++)
        
    {
        stripeImage[4 * j + 0] = (GLubyte)((j <= 4) ? 255 : 0);
        
        stripeImage[4 * j + 1] = (GLubyte)((j>4) ? 255 : 0);
        
        stripeImage[4 * j + 2] = (GLubyte)0;
        
        stripeImage[4 * j + 3         ] = (GLubyte)255;
        
    }
    
}

// 平面纹理坐标生成

static GLfloat xequalzero[] = { A, B, C, 1 };

static GLfloat slanted[] = { 1.0, 1.0, 1.0, 0.0 };

static GLfloat *currentCoeff;

static GLenum currentPlane;

static GLint currentGenMode;

static float roangles;

void init(void)

{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glShadeModel(GL_SMOOTH);
    
    makeStripeImage();
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0,
                 
                 GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    currentCoeff = xequalzero;
    
    currentGenMode = GL_OBJECT_LINEAR;
    
    currentPlane = GL_OBJECT_PLANE;
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    
    glTexGenfv(GL_S, currentPlane, currentCoeff);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
    
    roangles = 45.0f;
    
}

void display(void)

{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);// 设置多边形正面的镜面反射属性
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);// 指定镜面指数
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse0); //设置多边形正面漫反射属性
    //glTranslatef(0, 0, 4+1);
    glRotatef(45, 1, 0, 1);
    glutSolidTeapot(2);
    glPopMatrix();
    
    glFlush();
    
}

void reshape(int w, int h)

{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    if (w <= h)
        
        glOrtho(-3.5, 3.5, -3.5*(GLfloat)h / (GLfloat)w,
                
                3.5*(GLfloat)h / (GLfloat)w, -3.5, 3.5);
    
    else
        
        glOrtho(-3.5*(GLfloat)w / (GLfloat)h,
                
                3.5*(GLfloat)w / (GLfloat)h, -3.5, 3.5, -3.5, 3.5);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
}
void keyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
        case '1':
            A=A+1.0;
            xequalzero[0]=A;
            init();
            
            break;
        case '2':
            B=B+1.0;
            xequalzero[1]=B;
            init();
            
            break;
        case '3':
            C=C+1.0;
            xequalzero[2]=C;
            init();
            
            break;
        case '4':
            A=A-1.0;
            xequalzero[0]=A;
            init();
            
            
            break;
        case '5':
            B=B-1.0;
            xequalzero[1]=B;
            init();
            
            
            break;
        case '6':
            C=C-1.0;
            xequalzero[2]=C;
            init();
            
            
            break;
    }
}
void idle()

{
    roangles += 0.05f;
    
    glutPostRedisplay();
    
}

int main(int argc, char** argv)

{
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(256, 256);
    
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow(argv[0]);
    
    glutIdleFunc(idle);
    
    init();
    
    glutDisplayFunc(display);
    
    glutReshapeFunc(reshape);
    
    glutKeyboardFunc(&keyboard);
    
    glutMainLoop();
    
    
    return 0;
    
}
