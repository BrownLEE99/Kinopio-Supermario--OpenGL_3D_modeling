# Kinopio-Supermario--OpenGL_3D_modeling

https://github.com/BrownLEE99/Kinopio-Supermario--OpenGL_3D_modeling/assets/137032025/32968c39-a2dc-47dc-91a6-c6583af34abf

[20182601_김찬일 20182646_이현수.pptx](https://github.com/BrownLEE99/Kinopio-Supermario--OpenGL_3D_modeling/files/12040370/20182601_.20182646_.pptx)

# 반구체 생성
![HalfSphere](https://github.com/BrownLEE99/Kinopio-Supermario--OpenGL_3D_modeling/assets/137032025/ce06e6c0-c809-4a06-9ac5-f3a253913114)
- 문제 : 일반적인 구체 생성의 경우 gluSphere을 통해 생성하면 됐지만 반구를 만드는 함수는 없었다
- 해결 : https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere 를 보면 재귀식을 통해 구체를 그리는데 해당 코드를 이용하여 반구 그리는 코드를 직접 작성하였다.

```
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
```
