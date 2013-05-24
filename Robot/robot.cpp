#include "loadBMP.h"
#include "colorpolygon.h"

static int shoulder = -90, elbow = 0, shoulderRight = -90, elbowRight = 0;
static int shoulder2 = 0, elbow2 = 0, shoulderRight2 = 0, elbowRight2 = 0;

static int leg = 0, legelbow = 0, legRight = 0, legelbowRight = 0;
static int torso = -90;

#define PI_ 3.14159265358979323846
static int du=90,oldmy=-1,oldmx=-1; //du���ӵ���y��ĽǶ�,opengl��Ĭ��y�����Ϸ���
static float r=1.5f,h=0.0f; //r���ӵ���y��İ뾶,h���ӵ�߶ȼ���y���ϵ�����
static float c= PI_ /180.0f; //���ȺͽǶ�ת������
float positionx,positiony,rotax,rotay;

void init(void)
{
	//glClearColor (0.0, 0.0, 0.0, 0.0);
	//glShadeModel (GL_FLAT);
		
	glClearColor (0.0, 0.0, 0.0, 0.0);  // The glClearColor function specifies clear values for the color buffers.
	
	glLoadIdentity();
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); //���ӵ㿴Զ��,y�᷽��(0,1,0)���Ϸ���
    glEnable(GL_LIGHTING);  // ��������Ȳ���ģʽ
    glEnable(GL_LIGHT0);    // ����glEnable()�򿪸ù�Դ
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);    //���ö�ά����

    GLfloat light0_ambient[]  = {1, 1, 1, 1};   //������
    GLfloat light0_diffuse[]  = {1, 1, 1, 1};   //ɢ���
    GLfloat light0_position[] = {0, 5, 0, 1};   //��Դλ��

    // light ����lightָ���Ĺ�Դ��light����ʽΪGL_LIGHTi�ķ��ų�����ʾ
    glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    
    LoadAllTextures();          //��������
}

void display(void)
{
	// glClear (GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // The glClear function clears buffers to preset values.
	
	glDisable (GL_LIGHTING); // ����
	GLfloat mat_ambient1[]  = {1,0,0,1};
	GLfloat mat_emission[]  = {1,1,1,0};

	//GLfloat mat_ambient2[]  = {0.4,0.4,0.8,1};
    //GLfloat  no_emission[]  = {0,0,0,1};

	glPushMatrix();
	
	glPushMatrix();	// ͷ
		glTranslatef (0.0, 1.5, 0.0);
		// �����Դ�
		glRotatef (-80, 1.0, 0.0, 0.0);
		glRotatef (194, 0.0, 0.0, 1.0);

		glBindTexture(GL_TEXTURE_2D,head->texID);
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	//	glutWireSphere(1.0, 20, 8);	 // ����һ�ֻ���ķ�ʽ��ֱ�ӵ���glutWireSphere
	//	gltDrawSphere2(1.0, 20, 8);
		gltDrawSphere2(1.0, 20, 40);         //����̫��
	glPopMatrix();
	

	glPushMatrix();	// ����
		glTranslatef (0.0, -1.0, 0.0);
		glScalef (1.0, 1.7, 0.5);
		colorcube(); // ��ɫ
		//glScalef (2.0, 3.0, 1.0);
		//glutWireCube (1.0);
	glPopMatrix();
	//-----------
	glPushMatrix();	// �ֱ����� �ϱ�
		glTranslatef (1.0, 0.5, 0.0); // 
		glRotatef ((GLfloat) shoulderRight, 0.0, 0.0, 1.0);		// ���ֻ

		glRotatef ((GLfloat) shoulderRight2, 0.0, 1.0, 0.0);		// ���ֻ
		glTranslatef (1.0, 0.0, 0.0);

		glPushMatrix();		// ǰ��
			// glTranslatef (0.0, 2.0, 0.0);
			//glColor3f (0.0, 1.0, 1.0);	//����֮�����ɫ
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.0);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

		glTranslatef (1.0, 0.0, 0.0);
		glRotatef ((GLfloat) elbowRight, 0.0, 0.0, 1.0);
		glRotatef ((GLfloat) elbowRight2, 0.0, 1.0, .0);
		glTranslatef (1.0, 0.0, 0.0);

		glPushMatrix();
			// glTranslatef (0.0, 2.0, 0.0);
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.0);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();
	glPopMatrix();
//----------------
	//---------------
	glPushMatrix();	// �ֱ�����
		glTranslatef (-1.0, 0.5, 0.0);
		glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
		glRotatef ((GLfloat) shoulder2, 0.0, 1.0, 0.0);
		glTranslatef (1.0, 0.0, 0.0);

		glPushMatrix();
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.0);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

		glTranslatef (1.0, 0.0, 0.0);
		glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
		glRotatef ((GLfloat) elbow2, 0.0, 1.0, .0);
		glTranslatef (1.0, 0.0, 0.0);
		glPushMatrix();
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.0);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

	glPopMatrix();
//---------------
	//----------
	glPushMatrix();	// ����
		glTranslatef (0.5, -2.5, 0.0);
		glRotatef (-90, 0.0, 0.0, 1.0);
		glRotatef ((GLfloat) legRight, 0.0, 1.0, 0.0);
		glTranslatef (1.2, 0.0, 0.0);

		glPushMatrix();
		// glTranslatef (2.5, 1.5, 0.0);
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.2);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

		glTranslatef (1.0, 0.0, 0.0);
		glRotatef ((GLfloat) legelbowRight, 0.0, 1.0, 0.0);
		glTranslatef (1.0, 0.0, 0.0);
		glPushMatrix();
			// glTranslatef (2.5, 1.5, 0.0);
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.0);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

	glPopMatrix();
//-------------

	//----------
	glPushMatrix();	// ����
		glTranslatef (-0.5, -2.5, 0.0);
		glRotatef (-90, 0.0, 0.0, 1.0);
		glRotatef ((GLfloat) leg, 0.0, 1.0, 0.0);
		glTranslatef (1.2, 0.0, 0.0);

		glPushMatrix();
			// glTranslatef (2.5, 0.5, 0.0);
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.2);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

		glTranslatef (1.0, 0.0, 0.0);
		glRotatef ((GLfloat) legelbow, 0.0, 1.0, 0.0);
		glTranslatef (1.0, 0.0, 0.0);
		glPushMatrix();
			// glTranslatef (2.5, 0.5, 0.0);
			//glScalef (2.0, 0.4, 1.0);
			//glutWireCube (1.0);
			glScalef (1.0, 0.4, 0.5);
			colorcube();
		glPopMatrix();

	glPopMatrix();
//-------------
	glPopMatrix();
	//glutSwapBuffers();
	
	glFlush();  // ����ǿ��ˢ�»��壬��֤��ͼ�����ִ�У������Ǵ洢�ڻ�����[2]�еȴ�������OpenGL���
    glutSwapBuffers();  // glutSwapBuffers������OpenGL��GLUT���߰�������ʵ��˫���弼����һ����Ҫ�������ú����Ĺ����ǽ�������������ָ�롣

}
void displayT()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); //���ӵ㿴Զ��,y�᷽��(0,1,0)���Ϸ���
	
//	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	//ָ���������λ��	
	glScalef ( 0.5,  0.5, 0.5);
	display();
	
}
/*
void reshape2 (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(130.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}
*/
void myreshape (int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // The glClear function clears buffers to preset values.
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);				//ָ���ӿڴ�С
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
		
	gluPerspective(160.0, (GLfloat) w/(GLfloat) h, 1, 20);		//͸��ͶӰ
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	//ָ���������λ��	
}
/*
void myReshape2(int w, int h)
{
 glViewport(0, 0, w, h);

// Use a perspective view 

 glMatrixMode(GL_PROJECTION); 
 glLoadIdentity();
	if(w<=h) glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 
       2.0* (GLfloat) h / (GLfloat) w, 2.0, 20.0);
	else glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h, 
       2.0* (GLfloat) w / (GLfloat) h, 2.0, 20.0);

// Or we can use gluPerspective 

// gluPerspective(45.0, w/h, -10.0, 10.0); 

 glMatrixMode(GL_MODELVIEW);
}*/
/*
void mymouse(int button,int state,int x,int y)
{   
    if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON){   // ������������
        glRotatef(15.0, 1.0, 0.0, 0.0);
    }
    if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON){   // ����Ҽ�������
        glRotatef(15.0, -10.0, 0.0, 0.0);
    }
	if(state==GLUT_DOWN && button==GLUT_MIDDLE_BUTTON){   // ����Ҽ�������
        glRotatef(15.0, 0.0, 10.0, 0.0);
    }
}
*/
void motion(int x,int y){
	 rotay=y-positiony-40;
	 rotax=x-positionx;
	 displayT();	  
}
/*
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h == 0) h = 1;
    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.5f, -1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}
*/
void Mouse(int button, int state, int x, int y) //���������
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON){   // ������������
        glRotatef(15.0, 0.0, 10.0, 0.0);
    }
    if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON){   // ����Ҽ�������
        glRotatef(15.0, 0.0, 0.0, 10.0);
    }
	if(state==GLUT_DOWN && button==GLUT_MIDDLE_BUTTON){   // ����м�������
        glRotatef(15.0, 10.0, 0.0, 0.0);
    }
	glutPostRedisplay();
    if(state==GLUT_DOWN) //��һ����갴��ʱ,��¼����ڴ����еĳ�ʼ����
        oldmx=x,oldmy=y;
}

void onMouseMove(int x,int y) //��������϶�
{
    du+=x-oldmx; //����ڴ���x�᷽���ϵ������ӵ��ӵ���y��ĽǶ��ϣ�����������ת��
    h +=0.03f*(y-oldmy); //����ڴ���y�᷽���ϵĸı�ӵ��ӵ��y�����ϣ�������ת��
    if(h>1.0f) h=1.0f; //�ӵ�y������һЩ���ƣ�����ʹ�ӵ�̫���
    else if(h<-1.0f) h=-1.0f;
    oldmx=x,oldmy=y; //�Ѵ�ʱ�����������Ϊ��ֵ��Ϊ��һ�μ���������׼��
}
static int i = 0;

void myidle() // jump
{
	if(i == 5){
		//glutIdleFunc(0);
		//glutPostRedisplay();
		i = 0;
	}
	glTranslatef( 0.0, 3.0-i*6.0/4.0, 0.0 );
	leg = 40 - 10*i;
	legelbow = -80 + 20*i; // ���
	legRight = 40 - 10*i;
	legelbowRight = -80 + 20*i;

	shoulder = 240 + i*30/4;
	elbow = 20 - i * 5;
	shoulderRight = 300 - i*30/4;
	elbowRight = -20 + i * 5;

	Sleep(200);
	glutPostRedisplay();
	i += 1;
}

void myidle2()
{
	//glTranslatef( 0.0, 3.0-i*6.0/4.0, 0.0 );
	leg = 0;
	legelbow = 0; // ���
	legRight = 0;
	legelbowRight = 0;
	Sleep(200);
	glutPostRedisplay();
}

void myidle3() // running
{
	if(i == 7){
		//glutIdleFunc(0);
		//glutPostRedisplay();
		i = 0;
	}
	leg = 40 - 10*i;
	legelbow = -80 + 10*i; // ���

	legRight = -40 + 10*i;
	legelbowRight = -80 + 10*i;

	elbowRight2 = 20 + i * 10;
	shoulderRight2 = -330 - i*30/4;
	elbow2 = 20 + i * 10;
	shoulder2 = 330 + i*30/4;

	Sleep(200);
	glutPostRedisplay();
	i += 1;
}

void myidle4() // jump and somersault
{
	if(i >= 3 && i <= 6){
		glRotatef(90, 1, 0, 0);
	}
	if(i == 10){
		//glutIdleFunc(0);
		//glutPostRedisplay();
		i = 0;
	}
	//if( i < 3 || i > 6){
		glTranslatef( 0.0, 3.0-i*6.0/10.0, 0.0 );
	//}
	leg = 180 - 18*i;
	legelbow = -100 + 8*i; // ���
	legRight = 180 - 18*i;
	legelbowRight = -100 + 8*i;

	shoulder = 240 + i*30/10;
	elbow = 20 - i * 2;
	shoulderRight = 300 - i*30/10;
	elbowRight = -20 + i * 2;

	Sleep(200);
	glutPostRedisplay();
	i += 1;
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		// left shoulder
		case ' ':
			//i = 0;
			//glutIdleFunc(myidle);
			
			if(!first)
			{
				glutIdleFunc(myidle);
				first=!first;
			}
			else
			{
				glutIdleFunc(0);
				//glutIdleFunc(0);
				first=!first;
			}
			
			break;
		case 'c':			
			if(!first)
			{
				glutIdleFunc(myidle3);
				first=!first;
			}
			else
			{
				glutIdleFunc(0);
				//glutIdleFunc(0);
				first=!first;
			}
			
			break;
		case 'v':			
			if(!first)
			{
				glutIdleFunc(myidle4);
				first=!first;
			}
			else
			{
				glutIdleFunc(0);
				//glutIdleFunc(0);
				first=!first;
			}
			break;
		case 'x':
			glTranslatef( 0.0, 3.0, 0.0 );
			leg = 40;
			legelbow = -80; // ���
			legRight = 40;
			legelbowRight = -80;
			glutPostRedisplay();
			break;
		case 'z':
			glTranslatef( 0.0, -3.0, 0.0 );
			leg = 0;
			legelbow = 0; // ���
			legRight = 0;
			legelbowRight = 0;
			glutPostRedisplay();
			break;
		case 's':			
			if(shoulder>-90)
				break;
			shoulder = (shoulder + 5) % 360;	// shoulderһ��ʼ��-90
			glutPostRedisplay();
			break;
		case 'w':
			if(shoulder<-270)	// ̧�� ̧��һȦ��180 ���Ա��270
				break;
			shoulder = (shoulder - 5) % 360;
			glutPostRedisplay();
			break;
		case 'd':		
			if(elbow>0)
				break;
			elbow = (elbow + 5) % 360;	// elbowһ��ʼ��0
			glutPostRedisplay();
			break;
		case 'e':
			if(elbow<-170)
				break;
			elbow = (elbow - 5) % 360;	// ̧����
			glutPostRedisplay();
			break;

		// right shoulder
		case 'r':
			if(shoulderRight>90)
				break;
			shoulderRight = (shoulderRight + 5) % 360;
			glutPostRedisplay();
			break;
		case 'f':		
			if(shoulderRight<-90)
				break;
			shoulderRight = (shoulderRight - 5) % 360;
			glutPostRedisplay();
			break;
		case 't':
			if(elbowRight>180)
				break;
			elbowRight = (elbowRight + 5) % 360;
			glutPostRedisplay();
			break;
		case 'g':
			if(elbowRight<0)
				break;
			elbowRight = (elbowRight - 5) % 360;
			glutPostRedisplay();
			break;

		// left leg
		case 'y':
			if(leg>90)
				break;
			leg = (leg + 5) % 360;	// legһ��ʼ��0
			glutPostRedisplay();
			break;
		case 'h':
			if(leg<0)
				break;
			leg = (leg - 5) % 360;
			glutPostRedisplay();
			break;
		case 'u':
			if(legelbow>0)	// ���
				break;
			legelbow = (legelbow + 5) % 360;
			glutPostRedisplay();
			break;
		case 'j':
			if(legelbow<-90)
				break;
			legelbow = (legelbow - 5) % 360;
			glutPostRedisplay();
			break;

		// right leg
		case 'i':
			if(legRight>90)
				break;
			legRight = (legRight + 5) % 360;
			glutPostRedisplay();
			break;
		case 'k':
			if(legRight<0)
				break;
			legRight = (legRight - 5) % 360;
			glutPostRedisplay();
			break;
		case 'o':
			if(legelbowRight>0)
				break;
			legelbowRight = (legelbowRight + 5) % 360;
			glutPostRedisplay();
			break;
		case 'l':
			if(legelbowRight<-90)
				break;
			legelbowRight = (legelbowRight - 5) % 360;
			glutPostRedisplay();
			break;

		case 27:
			exit(0);
			break;
		default:
			break;
		}
}
/*
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mymouse); // glutMouseFunc
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // ���е�GLUT��������glutǰ׺������Щ���һЩ��ʼ���ĺ�����glutInitǰ׺
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // ��Ӧ��ʹ�ú���glutInitDisplayMode()������ʾ��ʽ
    // GLUT_RGBA����GLUT_RGB��ָ��һ��RGBA���ڣ�����һ��Ĭ�ϵ���ɫģʽ,GLUT_DEPTH.��Ȼ������� 
    glutInitWindowSize (800, 800);     // �������������ô��ڴ�С��ʹ�ú���glutInitWindowSize������ 
    glutInitWindowPosition (10, 10);  // ����ȷ������λ�ã���Ĭ�ϵ�����Ļ���Ͻǣ�������ʹ�ú���glutInitWindowPosition����
    glutCreateWindow (argv[0]); // ���ú���glutCreateWindow()������������

    init ();

	glutDisplayFunc(display); // glutDisplayFunc��������ע��һ����ͼ������ ��������ϵͳ�ڱ�Ҫʱ�̾ͻ�Դ���������»��Ʋ���
    glutIdleFunc(display);
//    glutDisplayFunc(displayT); // glutDisplayFunc��������ע��һ����ͼ������ ��������ϵͳ�ڱ�Ҫʱ�̾ͻ�Դ���������»��Ʋ���
//    glutIdleFunc(displayT);  //���ò��ϵ�����ʾ����
	glutReshapeFunc(myreshape); // ����ı䴰�ڴ�Сʱ�Ļص�(CallBack)����,��Ҫ���Լ���д��ReShape Function��ע�� ,
    // ÿ�����ڵĴ�С����״�ı�ʱ���������ڸձ�����ʱ���ǴΣ���GLUT��������������������ص�����������������µĿ�Ⱥ͸߶ȡ�

    //glutIdleFunc(myidle);   // glutIdleFunc����ȫ�ֵĻص���������û�д����¼�����ʱ��GLUT�����ܿ���ִ�к�̨�������������������
    // ������ã����idle function�ᱻ���ϵ��ã�ֱ���д����¼�����
    //glutMouseFunc(mymouse); // glutMouseFunc
	//glutIdleFunc(myidle);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	
    glutKeyboardFunc(keyboard);   // OpenGL�ļ�����Ӧ�ص�����

    glutMainLoop(); // GLUT�ṩ��һ�������ó������һ������������ѭ����һֱ�ȴ�������һ���¼�
    return 0;
}