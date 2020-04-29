#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "classes.cpp"

//Floor Vertices
float fVert[4][3] = {
    {-50.0,6.0, -50.0},
    {+50.0,6.0, -50.0},
    {+50.0,6.0, +50.0},
    {-50.0,6.0, +50.0}
};

//rendering floor
void drawFloor(){
    glBegin(GL_QUADS);
    glVertex3fv(fVert[0]);
    glVertex3fv(fVert[1]);
    glVertex3fv(fVert[2]);
    glVertex3fv(fVert[3]);
    glEnd();
}

//Reaction array
vector<Reaction> Reactions;

void drawReactions(){
    //Initialize if you want to use some other way @ashu
    
    // Reactions.emplace_back(temp);
    // for(auto i:Reactions)
    //     i.draw();
    Reactions[0].draw();
}

//main display function
void display(){
    
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    gluLookAt(view.eyeX, view.eyeY, view.eyeZ, view.targetX, view.targetY, view.targetZ, 0, 0,1);
    glRotatef(view.xAngle, 0.0f, 0.0f, 1.0f);
    glRotatef(view.yAngle, 1.0f, 0.0f, 0.0f);
    adjustCam();
    glPushMatrix();
    

    glColor4f(0.3, 0.3, 0.3, 1.0);
    drawFloor();
    glPopMatrix();

    glPushMatrix();
    drawReactions();
    glPopMatrix();
    if(maxFPS)
        glutPostRedisplay();
    fps();

    glutSwapBuffers();
}

//Called on mouse click and get the stencil index of object on which it is clicked
// void getObj(int button, int state, int x, int y){
//     if(state != GLUT_DOWN) return;
    
//     if(start ==0)
//     {
//         start = -1;
//     }else
//     {
//         int w_height = glutGet(GLUT_WINDOW_HEIGHT);

//         GLuint index;

//         glReadPixels(x, w_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
//         atomInfoS = "Atomic Number : "+ to_string(index) +"\n"+AtomInfo[index];
//     }
//     glutPostRedisplay(); 
// }
int main(int argc, char** argv)
{
    cout<<M_PI/180.0f<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_STENCIL | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize (1080, 700);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("CG1-Project");
    glutFullScreen();
    //mousetoCenter();
    glutSetCursor(GLUT_CURSOR_NONE);

    Initialize_Detail();

    Reaction temp("Sulphonication");
    Reactions.emplace_back(temp);
    timer(0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutMouseFunc(getObj);
    glutKeyboardFunc (NormalKeyHandler);
    //glutSpecialFunc(specialKeyboard);
    glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}