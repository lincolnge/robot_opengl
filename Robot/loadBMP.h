#define BITMAP_ID 0x4D42
#define PI 3.1415926

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )   // �������Կ���̨�������õ���ں����� mainCRTStartup

//---------- �������ݽṹ
typedef struct{
    int width;              //������
    int height;             //����߶�
    unsigned int texID;     //������� ID
    unsigned char * data;   //ʵ����������
}texture;


static float year = 0, month = 0, day = 0, angle = 300;
static bool first=false;

texture * head,* hand,* moon;           //����ָ��

//---------- ����λͼ��Ϊ��������
unsigned char * LoadBmpFile(char * filename,BITMAPINFOHEADER * bmpInfoHeader){
    
    FILE * file;
    BITMAPFILEHEADER bmpFileHeader;
    unsigned char * image;
    unsigned int imageIdx = 0;
    unsigned char tempRGB;
    
    file = fopen(filename,"rb");        
    if(file == NULL)
        return 0;
    
    fread(& bmpFileHeader,sizeof(BITMAPFILEHEADER),1,file);         // ��ȡ BMP �ļ�ͷ
        
    fread(bmpInfoHeader,sizeof(BITMAPINFOHEADER),1,file);           // ��λͼ��Ϣͷ
    fseek(file,bmpFileHeader.bfOffBits,SEEK_SET);                   // ���ļ�ָ���Ƶ�λͼ���ݵĿ�ʼ��
    image = (unsigned char * )malloc(bmpInfoHeader->biSizeImage);   // �����ڴ��λͼ����
       
    fread(image,1,bmpInfoHeader->biSizeImage,file);                 // ��ȡλͼ����
        
    // ��ת R �� B ֵ�Եõ� RGB����Ϊλͼ��ɫ��ʽ�� BGR
    for (imageIdx = 0;imageIdx < bmpInfoHeader->biSizeImage;imageIdx += 3)
    {
        tempRGB = image[imageIdx];
        image[imageIdx] = image[imageIdx + 2];
        image[imageIdx + 2] = tempRGB;
    }
    
    fclose(file);
    return image;
    
}

//---------- ���������ļ�
texture * LoadTexFile(char * filename){
    
    BITMAPINFOHEADER texInfo;
    texture * thisTexture;
    
    thisTexture = (texture * )malloc(sizeof(texture));
    if(thisTexture == NULL)
        return 0;
    
    thisTexture->data = LoadBmpFile(filename,&texInfo); // �����������ݲ������Ч��
    if (thisTexture->data == NULL)
    {
        free(thisTexture);
        return 0;
    }

    thisTexture->width = texInfo.biWidth;               // ��������Ŀ�͸�
    thisTexture->height = texInfo.biHeight;
    
    glGenTextures(1,&thisTexture->texID);               // �������������
    
    return thisTexture;
}

//---------- ��ʼ�������������ݺ�����
BOOL LoadAllTextures(){

    head = LoadTexFile("head.bmp");
    if(head == NULL)
        return FALSE;
    
    glBindTexture(GL_TEXTURE_2D,head->texID);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // ͼ�������ͼ��ռ�ӳ�䵽֡����ͼ��ռ�(ӳ����Ҫ���¹�������ͼ��,
        // �����ͻ����Ӧ�õ�������ϵ�ͼ��ʧ��),��ʱ�Ϳ���glTexParmeteri()������ȷ����ΰ���������ӳ�������.
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,head->width,head->height,GL_RGB,GL_UNSIGNED_BYTE,head->data);

	
	hand = LoadTexFile("hand.bmp");           
    if(hand == NULL)
        return FALSE;
    
    glBindTexture(GL_TEXTURE_2D,hand->texID);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,hand->width,hand->height,GL_RGB,GL_UNSIGNED_BYTE,hand->data);
	
    return TRUE;
}

void gltDrawSphere2(GLfloat fRadius, GLint iSlices, GLint iStacks)	// ������
{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
    GLfloat ds = 1.0f / (GLfloat) iSlices;
    GLfloat dt = 1.0f / (GLfloat) iStacks;
    GLfloat t = 1.0f;   
    GLfloat s = 0.0f;
    GLint i, j;     
    
    for (i = 0; i < iStacks; i++) 
    {
        GLfloat rho = (GLfloat)i * drho;
        GLfloat srho = (GLfloat)(sin(rho));
        GLfloat crho = (GLfloat)(cos(rho));
        GLfloat srhodrho = (GLfloat)(sin(rho + drho));
        GLfloat crhodrho = (GLfloat)(cos(rho + drho));
        
        
        glBegin(GL_TRIANGLE_STRIP);
        s = 0.0f;
        for ( j = 0; j <= iSlices; j++) 
        {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));
            
            GLfloat x = stheta * srho;
            GLfloat y = ctheta * srho;
            GLfloat z = crho;
            
            glTexCoord2f(s, t);
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
            
            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;
            glTexCoord2f(s, t - dt);
            s += ds;
            glNormal3f(x, y, z);
            glVertex3f(x * fRadius, y * fRadius, z * fRadius);
        }
        glEnd();
        
        t -= dt;
    }

}
