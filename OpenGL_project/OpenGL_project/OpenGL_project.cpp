#include <GLUT.h>
#include <iostream>
#include <math.h>
#include <SOIL.h>
#include <string>

#define HEAD 0
#define FACE 1
#define BODY 2
#define FRONT 3
#define SIDE 4
#define BOTTOM 5
#define TOP 6
#define M_PI 3.14159265


// 회전 및 줌 변수
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat zoom = 1.0f;

// 마우스 위치 및 드래그 상태를 저장하는 변수
int mouseX = 0, mouseY = 0;
bool isDragging = false;

GLuint textureID[10];

void loadTexture()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 배경을 검은색으로 설정

    glEnable(GL_TEXTURE_2D);  // 2D 텍스처 사용을 활성화

    // 머리 텍스쳐 로딩
    textureID[HEAD] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/head.jpg",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    // 얼굴 텍스쳐 로딩
    textureID[FACE] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/face.jpg",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    // 상체 텍스처 로딩
    textureID[BODY] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/body.jpg",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    // 배경 이미지 앞단 로딩
    textureID[FRONT] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/frontimage.bmp",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    // 배경 이미지 좌, 우, 뒤 부분 로딩
    textureID[SIDE] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/side.png",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    // 배경이미지 바닥 부분 로딩
    textureID[BOTTOM] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/brick.png",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    // 배경이미지 상단 부분 로딩
    textureID[TOP] = SOIL_load_OGL_texture(
        "C:/Users/chan/Documents/GitHub/OpenGL_project/data/qqq.png",  // 텍스처 파일 경로와 이름
        SOIL_LOAD_AUTO,  // 텍스처 로딩 옵션
        SOIL_CREATE_NEW_ID,  // 새로운 텍스처 ID 생성
        SOIL_FLAG_INVERT_Y  // Y 축을 뒤집음
    );

    for (int i = 0; i < 7; i++) {
        glBindTexture(GL_TEXTURE_2D, textureID[i]); // 텍스처 바인딩
        // 범위 넘어갔을때 좌표 반복
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // 색상을 선형적으로 보간
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}
void background()
{
    // 깊이 테스트를 활성화. 물체들 간의 상대적인 거리를 기반으로 그려질 픽셀을 결정하는 데 사용
    glEnable(GL_DEPTH_TEST);

    /*----------------------------------------------*/
    // 앞면 텍스처 활성화
    glPushMatrix(); // 변환 매트릭스를 푸시
    glEnable(GL_TEXTURE_2D); // 2차원 텍스처링을 활성화
    glBindTexture(GL_TEXTURE_2D, textureID[FRONT]); // 앞면 텍스처를 바인딩
    glBegin(GL_QUADS); // 사각형 그리기 위한 glBegin 호출 시작

    // 다음으로 각 꼭짓점에 대한 텍스처 좌표와 위치 정의
    glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, 10.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, 10.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-10.0, 10.0, 10.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /*----------------------------------------------*/
    // 상단 면 텍스처 활성화
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[TOP]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, 10.0, -10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(10.0, 10.0, -10.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, 10.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-10.0, 10.0, 10.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /*----------------------------------------------*/
    // 하단 면 텍스쳐 활성화
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[BOTTOM]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
    glTexCoord2f(5.0, 0.0); glVertex3f(10.0, -10.0, 10.0);
    glTexCoord2f(5.0, 5.0); glVertex3f(10.0, -10.0, -10.0);
    glTexCoord2f(0.0, 5.0); glVertex3f(-10.0, -10.0, -10.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();


    // 좌측 면 텍스처 활성화
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[SIDE]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-10.0, 10.0, 10.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-10.0, 10.0, -10.0);

    // 우측 면 텍스쳐 활성화
    glTexCoord2f(0.0, 0.0); glVertex3f(10.0, -10.0, 10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, -10.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, -10.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(10.0, 10.0, 10.0);

    // 뒷면 텍스쳐 활성화
    glTexCoord2f(0.0, 0.0); glVertex3f(10.0, -10.0, -10.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-10.0, -10.0, -10.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-10.0, 10.0, -10.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(10.0, 10.0, -10.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void face() {
    glPushMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);  // 기본 색 흰색 설정

    glEnable(GL_TEXTURE_2D);  // 2차원 텍스처링 활성화
    glBindTexture(GL_TEXTURE_2D, textureID[FACE]);  // 얼굴 텍스처 바인딩

    GLUquadricObj* obj1;  // 객체 생성
    obj1 = gluNewQuadric();
    gluQuadricTexture(obj1, GL_TRUE);  // 객체에 텍스처 적용
    gluSphere(obj1, 1.4f, 30, 30);  // 구체 생성

    glBindTexture(GL_TEXTURE_2D, 0); 
    glDisable(GL_TEXTURE_2D);  

    glPopMatrix();  
}
void head() {
    glPushMatrix();  

    glEnable(GL_TEXTURE_2D);  // 2차원 텍스처링 활성화
    glBindTexture(GL_TEXTURE_2D, textureID[HEAD]);  // 머리 텍스처 바인딩

    GLUquadricObj* obj;  // 쿼드릭 객체를 생성합니다. 
    obj = gluNewQuadric();

    // 도넛 모양 그리기
    glColor3f(1.0f, 1.0f, 1.0f);  // 기본 색 흰색 설정
    const float radius = 1.2f;  // 도넛 반경 설정
    const float thickness = 1.4f;  // 도넛 두께 설정
    const int numSlices = 50;  // 도넛 슬라이스 수 설정
    const int numStacks = 50;  // 도넛 스택 수 설정
    glTranslatef(0, 0, 1.3f);
    glRotatef(-10.0, 1.0f, 0.0f, 0.0f);
    for (int i = 0; i < numStacks; ++i)
    {
        float theta1 = static_cast<float>(i) * (2.0f * 3.141592f) / numStacks;
        float theta2 = static_cast<float>(i + 1) * (2.0f * 3.141592f) / numStacks;
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numSlices; ++j)
        {
            float phi = static_cast<float>(j) * (2.0f * 3.141592f) / numSlices;
            float x = (radius + thickness * cos(theta2)) * cos(phi);
            float y = (radius + thickness * cos(theta2)) * sin(phi);
            float z = thickness * sin(theta2);

            glTexCoord2f(static_cast<float>(j) / numSlices, static_cast<float>(i + 1) / numStacks);
            glVertex3f(x, y, z);

            x = (radius + thickness * cos(theta1)) * cos(phi);
            y = (radius + thickness * cos(theta1)) * sin(phi);
            z = thickness * sin(theta1);

            glTexCoord2f(static_cast<float>(j) / numSlices, static_cast<float>(i) / numStacks);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}
void upper_body() {

    glPushMatrix();  

    glEnable(GL_TEXTURE_2D);  // 2차원 텍스처링 활성화.
    glBindTexture(GL_TEXTURE_2D, textureID[BODY]);  // 상체 텍스처 바인딩

    glTranslatef(0.0f, 0.0f, -2.4f);  // 현재 물체를 지정된 좌표로 이동
    GLUquadricObj* obj = gluNewQuadric();  // 객체 생성
    gluQuadricTexture(obj, GL_TRUE);  // 객체에 텍스처 적용
    gluCylinder(obj, 1.3, 0.6, 1.2, 32, 32);  // 원통을 생성

    glBindTexture(GL_TEXTURE_2D, 0);  // 텍스처 바인딩 해제
    glDisable(GL_TEXTURE_2D);  // 2차원 텍스처링 비활성화

    glPopMatrix();  
}
void halfSphere() {
    // 반지름과 분할 수
    float radius = 1.3f;
    int slices = 50;
    int stacks = 50;

    // 모델뷰 행렬을 x축을 중심으로 180도 회전
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    // 반구 윗부분 그리기
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f); // 법선 벡터 설정
    glVertex3f(0.0f, 0.0f, 0.0f); // 정점 설정
    for (int j = 0; j <= slices; j++) {
        float theta = static_cast<float>(j) * (M_PI / slices); // 각도 계산
        float x = radius * sin(theta); // x 좌표 계산
        float y = radius * cos(theta); // y 좌표 계산
        glVertex3f(x, y, 0.0f); // 새로운 정점 추가
    }
    glEnd();

    // 반구 측면 그리기
    for (int i = 1; i <= stacks; i++) {
        float phi1 = static_cast<float>(i - 1) * (M_PI / stacks); // 현재 스택 각도 계산
        float phi2 = static_cast<float>(i) * (M_PI / stacks); // 다음 스택 각도 계산

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; j++) {
            float theta = static_cast<float>(j) * (2.0f * M_PI / slices); // 슬라이스 각도 계산

            // 각 좌표 계산
            float x1 = radius * sin(theta) * cos(phi1);
            float y1 = radius * cos(theta) * cos(phi1);
            float z1 = radius * sin(phi1);

            float x2 = radius * sin(theta) * cos(phi2);
            float y2 = radius * cos(theta) * cos(phi2);
            float z2 = radius * sin(phi2);

            // 법선 벡터 설정, 정점 추가
            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);
            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}
void lower_body() {
    glPushMatrix();
    // 하반신
    glTranslatef(0.0f, 0.0f, -2.4f);
    glScalef(1.0f, 1.0f, 0.7f);
    halfSphere(); // 하반신 그리기
    glPopMatrix(); 
}

void shoes() {
    GLUquadricObj* obj = gluNewQuadric();

    // 오른쪽 신발
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f);
    glTranslatef(0.8f, 0.0f, -3.3f);
    glScalef(0.5f, 1.0f, 0.5f);
    gluSphere(obj, 0.8f, 30, 30);
    glPopMatrix();

    // 왼쪽 신발
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f);
    glTranslatef(-0.8f, 0.0f, -3.3f);
    glScalef(0.5f, 1.0f, 0.5f);
    gluSphere(obj, 0.8f, 30, 30);
    glPopMatrix();
}
void arm() {
    GLUquadricObj* obj = gluNewQuadric();

    // 오른쪽 팔
    glPushMatrix();
    glColor3f(0.976471f, 0.87451f, 0.67451f); // 색상 설정
    glTranslatef(1.3f, -1.3f, -1.0f); // 위치 설정
    glRotatef(120.0, -1.0f, -0.4f, 0.0f); // 회전 각도 설정
    gluCylinder(obj, 0.3, 0.2, 1.7, 32, 32); // 원통 팔
    glPopMatrix();

    // 왼쪽 팔.
    glPushMatrix();
    glColor3f(0.976471f, 0.87451f, 0.67451f); // 색상 설정
    glTranslatef(-1.8f, 0.0f, -2.4f); // 위치 설정
    glRotatef(55.0, 0.0f, 1.0f, 0.0f); // 회전 각도 설정
    gluCylinder(obj, 0.3, 0.2, 1.5, 32, 32); // 원통 팔
    glPopMatrix();
}

void hand() {
    GLUquadricObj* obj = gluNewQuadric();;

    // 오른쪽 손
    glPushMatrix();
    glTranslatef(1.3, -1.4f, -0.95f); // 위치 설정
    glColor3f(0.976471f, 0.87451f, 0.67451f); // 색상 설정
    gluSphere(obj, 0.3f, 30, 30); // 구 형태의 손
    glPopMatrix();

    // 왼쪽 손
    glPushMatrix();
    glTranslatef(-1.85, 0.0f, -2.4f); // 위치 설정
    glColor3f(0.976471f, 0.87451f, 0.67451f); // 색상 설정
    gluSphere(obj, 0.3f, 30, 30); // 구 형태의 손.
    glPopMatrix();
}

void display()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);  // 배경 회색으로 설정
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // 카메라 설정 등 추가 작업 수행 가능

    // 3D 모델링 메쉬 그리기
    glTranslatef(0.0f, 0.0f, -33.0f);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glScalef(zoom, zoom, zoom);

    // 배경 그리기
    background();

    // 캐릭터 그리기 (얼굴이 기준)
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    face();
    head();
    upper_body();
    lower_body();
    shoes();
    arm();
    hand();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            // 마우스 드래그 시작
            isDragging = true;
            mouseX = x;
            mouseY = y;
        }
        else
        {
            // 마우스 드래그 종료
            isDragging = false;
        }
    }
}

void mouseMotion(int x, int y)
{
    if (isDragging)
    {
        // 마우스 드래그 중일 때 회전
        rotationX += (GLfloat)(y - mouseY) * 0.2f;
        rotationY += (GLfloat)(x - mouseX) * 0.2f;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    // 키보드 입력 이벤트 처리
    if (key == 'a')
    {
        zoom += 0.1f;
        glutPostRedisplay();
    }
    else if (key == 'z')
    {
        zoom -= 0.1f;
        if (zoom < 0.1f)
            zoom = 0.1f;
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mesh");

    loadTexture(); // 텍스쳐를 로드
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();

    return 0;
}







