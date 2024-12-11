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
// Fungsi untuk menggambar mawar dalam 3D dengan volume lebih banyak dan rapat
void drawRose3D(float scale) {
    // Kelopak merah besar (lapisan luar di depan)
    for (int i = 0; i < 22; ++i) { // Tambahkan lebih banyak kelopak (12 + 10)
        glPushMatrix();
        glRotatef(i * 16.36, 0.0, 0.0, 1.0); // Rotasi dengan sudut yang lebih kecil
        glTranslatef(0.0, 0.0, -0.015f);     // Offset z lebih rapat
        glScalef(1.8, 0.8, 1.0);
        drawCircle3D(0.5, 1.0, 0.0, 0.0, 0.0f, scale);
        glPopMatrix();
    }

    // Kelopak merah menengah (lapisan kedua)
    for (int i = 0; i < 22; ++i) { // Tambahkan lebih banyak kelopak (12 + 10)
        glPushMatrix();
        glRotatef(i * 16.36, 0.0, 0.0, 1.0); // Rotasi dengan sudut yang lebih kecil
        glTranslatef(0.0, 0.0, -0.03f);      // Offset z lebih rapat
        glScalef(1.5, 0.7, 1.0);
        drawCircle3D(0.4, 0.9, 0.1, 0.1, -0.01f, scale);
        glPopMatrix();
    }

    // Kelopak hitam (lapisan lebih dalam)
    for (int i = 0; i < 18; ++i) { // Tambahkan lebih banyak kelopak (8 + 10)
        glPushMatrix();
        glRotatef(i * 20.0, 0.0, 0.0, 1.0); // Rotasi dengan sudut yang lebih kecil
        glTranslatef(0.0, 0.0, -0.045f);    // Offset z lebih rapat
        glScalef(1.3, 0.7, 1.0);
        drawCircle3D(0.33, 0.1, 0.1, 0.1, -0.02f, scale);
        glPopMatrix();
    }

    // Lapisan tengah kelopak merah kecil
    for (int i = 0; i < 16; ++i) { // Tambahkan lebih banyak kelopak (6 + 10)
        glPushMatrix();
        glRotatef(i * 22.5, 0.0, 0.0, 1.0); // Rotasi dengan sudut yang lebih kecil
        glTranslatef(0.0, 0.0, -0.06f);     // Offset z lebih rapat
        glScalef(0.9, 0.5, 1.0);
        drawCircle3D(0.2, 1.0, 0.0, 0.0, 0.01f, scale);
        glPopMatrix();
    }

    // Inti bunga (lapisan paling dalam)
    drawCircle3D(0.1, 1.0, 0.0, 0.0, 0.08f, scale);
}

// Fungsi untuk menggambar mawar
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Atur kamera untuk tampilan 3D
    gluLookAt(0.0, 0.0, 2.0,  // Posisi kamera
        0.0, 0.0, 0.0,  // Titik yang dilihat kamera
        0.0, 1.0, 0.0); // Arah atas kamera

    // Gambar awan bergerak di latar belakang
    drawCloud(cloudPosX, 1.0f, -2.0f, 1.0f);  // Gambar awan pada posisi awal

    // Terapkan rotasi berdasarkan input keyboard
    glRotatef(rotationX, 1.0, 0.0, 0.0); // Rotasi pada sumbu X
    glRotatef(rotationY, 0.0, 1.0, 0.0); // Rotasi pada sumbu Y

    // Gambar mawar di tengah layar
    glPushMatrix();
    drawRose3D(bloomScale); // Tambahkan skala untuk animasi
    glPopMatrix();

    glutSwapBuffers();
}