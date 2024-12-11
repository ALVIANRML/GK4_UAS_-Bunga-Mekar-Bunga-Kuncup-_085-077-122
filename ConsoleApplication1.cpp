#include <glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Variabel untuk rotasi
float rotationX = 0.0f;
float rotationY = 0.0f;

// Variabel untuk animasi bunga
float bloomScale = 0.0f;  // Skala animasi (mekar dan kuncup)
bool blooming = true;     // Status bunga (mekar atau kuncup)

// Variabel untuk gerakan awan
float cloudPosX = -2.0f;   // Posisi awan di sumbu X
float cloudSpeed = 0.01f;   // Kecepatan gerakan awan

// Fungsi untuk menggambar lingkaran dalam 3D (digunakan untuk kelopak)
void drawCircle3D(float radius, float r, float g, float b, float zOffset, float scale) {
    GLfloat materialColor[] = { r, g, b, 1.0f };
    GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);

    glPushMatrix();
    glScalef(scale, scale, scale); // Terapkan skala untuk animasi
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, zOffset);  // Titik tengah lingkaran
    for (int i = 0; i <= 360; ++i) {
        float angle = i * M_PI / 180.0f;
        glVertex3f(radius * cos(angle), radius * sin(angle), zOffset);
    }
    glEnd();
    glPopMatrix();
}

// Fungsi untuk menggambar awan
void drawCloud(float xPos, float yPos, float zPos, float scale) {
    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glColor3f(1.0, 1.0, 1.0);  // Warna putih untuk awan

    drawCircle3D(0.3, 1.0, 1.0, 1.0, 0.0f, scale);
    glTranslatef(0.4f, 0.0f, 0.0f);
    drawCircle3D(0.3, 1.0, 1.0, 1.0, 0.0f, scale);
    glTranslatef(-0.3f, 0.4f, 0.0f);
    drawCircle3D(0.3, 1.0, 1.0, 1.0, 0.0f, scale);
    glTranslatef(-0.4f, 0.0f, 0.0f);
    drawCircle3D(0.3, 1.0, 1.0, 1.0, 0.0f, scale);

    glPopMatrix();
}