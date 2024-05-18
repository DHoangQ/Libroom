#define GL_SILENCE_DEPRECATION
#include "glut.h"
#include "stdlib.h"
#include "stdio.h"
#include "iostream"
#include <windows.h>
#include<math.h>



GLfloat alpha = 0.0, theta = 0.0, axis_x = 0.0, axis_y = 0.0, Calpha = 360.0, C_hr_alpha = 360.0;
GLboolean bRotate = false, fRotate = false, cRotate = true, xz_rotate = false, l_on = true;
const int width = 600;
const int height = 800;
GLboolean amb = true, spec = true, dif = true;


bool l_on1 = false;
bool l_on2 = false;
bool l_on3 = false;



double spt_cutoff = 40;

float rot = 0;

GLfloat eyeX = 0;
GLfloat eyeY = 10;
GLfloat eyeZ = 10;

GLfloat lookX = 0;
GLfloat lookY = 10;
GLfloat lookZ = 0;

static GLfloat v_Cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};


static GLubyte quadIndices[6][4] =
{
   {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};



static void getNormal3p
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void cube(GLfloat colr1, GLfloat colr2, GLfloat colr3)
{



    GLfloat cube_no[] = { 0, 0, 0, 1.0 };
    GLfloat cube_amb[] = { colr1 * 0.3,colr2 * 0.3,colr3 * 0.3,1 };
    GLfloat cube_dif[] = { colr1,colr2,colr3,1 };
    GLfloat cube_spec[] = { 1,1,1,1 };
    GLfloat cube_sh[] = { 10 };


    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_sh);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
            v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
            v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&v_Cube[quadIndices[i][j]][0]);
        }

    }
    glEnd();


}

void book()
{
    float bookLength = 2.0; // Chiều dài của sách
    float bookHeight = 0.2; // Chiều cao của sách khi mở
    float bookWidth = 1.6;  // Chiều rộng của sách

    // Đặt sách trên bàn
    glPushMatrix();
    glTranslatef(1.5, 3.5, 1.4); // Dịch chuyển sách lên trên mặt bàn

    // Vẽ nửa đầu của sách màu đỏ
    glPushMatrix();
    glTranslatef(0, 0, 0); // Dịch chuyển nửa đầu sách
    glScalef(bookLength / 2, bookHeight, bookWidth); // Kích thước nửa đầu
    cube(1.0, 0.0, 0.0); // Màu đỏ
    glPopMatrix();

    // Vẽ nửa sau của sách màu hồng
    glPushMatrix();
    glTranslatef(bookLength / 2, 0, 0); // Dịch chuyển nửa sau sách
    glScalef(bookLength / 2, bookHeight, bookWidth); // Kích thước nửa sau
    cube(1.0, 0.75, 0.8); // Màu hồng
    glPopMatrix();

    glPopMatrix();
}


void table()
{
    float length = .5; // Chiều dài chân bàn
    float height = 3; // Chiều cao chân bàn
    float width = .5; // Chiều rộng chân bàn

    // Đặt chân bàn
    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(4, 0, 0);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(0, 0, 5); 
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(4, 0, 5); 
    cube(0, 0, 0);
    glPopMatrix();

    // Đặt mặt bàn
    glPushMatrix();
    glScalef(length * 10.0, height / 6, width * 7);  // Thay đổi chiều ngang của mặt bàn bằng cách chỉnh giá trị này
    glTranslatef(0, 6, 0);
    cube(1, .8, .4);
    glPopMatrix();

    // Đặt sách trên bàn
    book();
}



void chair()
{
    float length = .5;
    float height = 2;
    float width = .5;

    // Chân ghế
    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(.5, 0, -2);
    cube(0, 0, 1);  // Màu xanh dương
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(3.5, 0, -2);
    cube(0, 0, 1);  // Màu xanh dương
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(.5, 0, -4);
    cube(0, 0, 1);  // Màu xanh dương
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length, height, width);
    glTranslatef(3.5, 0, -4);
    cube(0, 0, 1);  // Màu xanh dương
    glPopMatrix();

    // Mặt ghế
    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length * 4, height / 6, width * 4);
    glTranslatef(0.15, 6, -1.2);
    cube(0, 0, 1);  // Màu xanh dương
    glPopMatrix();

    // Tựa ghế
    glPushMatrix();
    glTranslatef(length / 2, 0, 0);
    glScalef(length * 4, height * 1.2, width);
    glTranslatef(.15, 1, -5);
    cube(0, 0, 1);  // Màu xanh dương
    glPopMatrix();
}



void full_set()
{
    glPushMatrix();
    table();
    glPopMatrix();

    glPushMatrix();
    chair();
    glPopMatrix();

}


void full_set_chair_table()
{
   


    glPushMatrix();
    glTranslatef(0, 0, -6);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 0, -6);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5, 0, -6);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 0, -6);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -12);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 0, -12);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5, 0, -12);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 0, -12);
    full_set();
    glPopMatrix();

}


void fan_face()
{
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);//kích thước cánh quạt
    glTranslatef(-0.4, 19, -.4);
    cube(1.000, 1.000, 1.000);
    glPopMatrix();
}


void stand()
{
    glPushMatrix();
    glScalef(.5, 5, .5);
    glTranslatef(0, 2, 0);
    cube(0.392, 0.584, 0.929);
    glPopMatrix();
}

void leg()
{
    glPushMatrix();
    glScalef(5, 0.07, 1.8);
    glTranslatef(0, 140, -0.3);
    cube(0.392, 0.584, 0.929);
    glPopMatrix();
}


void fan_set()
{
    glPushMatrix();
    glPushMatrix();
    fan_face();
    glPopMatrix();



    glPushMatrix();
    leg();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(-5, 0.0, 0);
    leg();
    glPopMatrix();


    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(-6, 0, 0);
    leg();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 0);
    leg();
    glPopMatrix();
}

void fan()
{


    glPushMatrix();
    glRotatef(alpha, 0, .1, 0);
    fan_set();
    glPopMatrix();

    glPushMatrix();
    stand();
    glPopMatrix();

}
void fan_full_set()
{

    // Giảm giá trị y để đưa quạt lên cao hơn, gần sát trần nhà
    glPushMatrix();
    glTranslatef(7, 3, -9); 
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 3, -9); 
    fan();
    glPopMatrix();


}

void bookshelf() {
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    // Mảng màu sắc cố định cho sách, mỗi sách một màu khác nhau
    GLfloat book_colors[15][3] = {  // có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(1.2, 0, 8.5);
    cube(1, 0.6, 0.2);
    glPopMatrix();


    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2;
        glTranslatef(7, y_position, 11.5);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth);
        cube(0.8, 0.8, 0.8);

        int num_books = 9;  // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05;
            GLfloat book_height = 17;
            GLfloat book_depth = 1;
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2);
            glScalef(book_thickness, book_height, book_depth);
            cube(book_colors[j % 15][0], book_colors[j % 15][1], book_colors[j % 15][2]);  // Sử dụng màu từ mảng màu cố định
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}


void bookshelf2()
{
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    // Vẽ phần khung chính của tủ sách
    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(-0.5, 0, 8.5); // Điều chỉnh vị trí tương đối
    cube(1, 0.6, 0.2); // Màu sắc của khung tủ
    glPopMatrix();

    // Vẽ các ngăn kệ và sách đứng trên mỗi kệ
    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2; // Vị trí ngang của mỗi ngăn
        glTranslatef(-2.9, y_position, 11.5);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth); // Kích thước của ngăn kệ
        cube(0.8, 0.8, 0.8); // Màu sắc của ngăn

        // Vẽ sách đứng trên kệ
        int num_books = 10; // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05; // Độ dày của sách
            GLfloat book_height = 17; // Chiều cao của sách
            GLfloat book_depth = 1; // Độ sâu của sách
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2); // Đặt sách trên kệ
            glScalef(book_thickness, book_height, book_depth); // Kích thước sách
            // Sử dụng màu đã định trước cho sách
            cube(book_colors[j][0], book_colors[j][1], book_colors[j][2]);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf3()
{
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    // Vẽ phần khung chính của tủ sách
    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(-2.2, 0, 8.5); // Điều chỉnh vị trí tương đối
    cube(1, 0.6, 0.2); // Màu sắc của khung tủ
    glPopMatrix();

    // Vẽ các ngăn kệ và sách đứng trên mỗi kệ
    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2; // Vị trí ngang của mỗi ngăn
        glTranslatef(-13, y_position, 11.5);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth); // Kích thước của ngăn kệ
        cube(0.8, 0.8, 0.8); // Màu sắc của ngăn

        // Vẽ sách đứng trên kệ
        int num_books = 13; // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05; // Độ dày của sách
            GLfloat book_height = 17; // Chiều cao của sách
            GLfloat book_depth = 1; // Độ sâu của sách
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2); // Đặt sách trên kệ
            glScalef(book_thickness, book_height, book_depth); // Kích thước sách
            // Sử dụng màu đã định trước cho sách
            cube(book_colors[j][0], book_colors[j][1], book_colors[j][2]);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf4() {
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    // Mảng màu sắc cố định cho sách, mỗi sách một màu khác nhau
    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(1.2, 0, 6);
    cube(1, 0.6, 0.2);
    glPopMatrix();


    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2;
        glTranslatef(7, y_position, 7.7);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth);
        cube(0.8, 0.8, 0.8);

        int num_books = 9;  // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05;
            GLfloat book_height = 17;
            GLfloat book_depth = 1;
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2);
            glScalef(book_thickness, book_height, book_depth);
            cube(book_colors[j % 15][0], book_colors[j % 15][1], book_colors[j % 15][2]);  // Sử dụng màu từ mảng màu cố định
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf5() {
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    // Mảng màu sắc cố định cho sách, mỗi sách một màu khác nhau
    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(1.2, 0, 3.5);
    cube(1, 0.6, 0.2);
    glPopMatrix();


    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2;
        glTranslatef(7, y_position, 4.1);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth);
        cube(0.8, 0.8, 0.8);

        int num_books = 9;  // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05;
            GLfloat book_height = 17;
            GLfloat book_depth = 1;
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2);
            glScalef(book_thickness, book_height, book_depth);
            cube(book_colors[j % 15][0], book_colors[j % 15][1], book_colors[j % 15][2]);  // Sử dụng màu từ mảng màu cố định
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf6()
{
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    // Vẽ phần khung chính của tủ sách
    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(-0.5, 0, 6); // Điều chỉnh vị trí tương đối
    cube(1, 0.6, 0.2); // Màu sắc của khung tủ
    glPopMatrix();

    // Vẽ các ngăn kệ và sách đứng trên mỗi kệ
    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2; // Vị trí ngang của mỗi ngăn
        glTranslatef(-2.9, y_position, 7.7);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth); // Kích thước của ngăn kệ
        cube(0.8, 0.8, 0.8); // Màu sắc của ngăn

        // Vẽ sách đứng trên kệ
        int num_books = 10; // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05; // Độ dày của sách
            GLfloat book_height = 17; // Chiều cao của sách
            GLfloat book_depth = 1; // Độ sâu của sách
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2); // Đặt sách trên kệ
            glScalef(book_thickness, book_height, book_depth); // Kích thước sách
            // Sử dụng màu đã định trước cho sách
            cube(book_colors[j][0], book_colors[j][1], book_colors[j][2]);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf7()
{
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    // Vẽ phần khung chính của tủ sách
    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(-0.5, 0, 3.5); // Điều chỉnh vị trí tương đối
    cube(1, 0.6, 0.2); // Màu sắc của khung tủ
    glPopMatrix();

    // Vẽ các ngăn kệ và sách đứng trên mỗi kệ
    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2; // Vị trí ngang của mỗi ngăn
        glTranslatef(-2.9, y_position, 4.1);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth); // Kích thước của ngăn kệ
        cube(0.8, 0.8, 0.8); // Màu sắc của ngăn

        // Vẽ sách đứng trên kệ
        int num_books = 10; // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05; // Độ dày của sách
            GLfloat book_height = 17; // Chiều cao của sách
            GLfloat book_depth = 1; // Độ sâu của sách
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2); // Đặt sách trên kệ
            glScalef(book_thickness, book_height, book_depth); // Kích thước sách
            // Sử dụng màu đã định trước cho sách
            cube(book_colors[j][0], book_colors[j][1], book_colors[j][2]);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf8()
{
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    // Vẽ phần khung chính của tủ sách
    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(-2.2, 0, 6); // Điều chỉnh vị trí tương đối
    cube(1, 0.6, 0.2); // Màu sắc của khung tủ
    glPopMatrix();

    // Vẽ các ngăn kệ và sách đứng trên mỗi kệ
    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2; // Vị trí ngang của mỗi ngăn
        glTranslatef(-13, y_position, 7.7);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth); // Kích thước của ngăn kệ
        cube(0.8, 0.8, 0.8); // Màu sắc của ngăn

        // Vẽ sách đứng trên kệ
        int num_books = 13; // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05; // Độ dày của sách
            GLfloat book_height = 17; // Chiều cao của sách
            GLfloat book_depth = 1; // Độ sâu của sách
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2); // Đặt sách trên kệ
            glScalef(book_thickness, book_height, book_depth); // Kích thước sách
            // Sử dụng màu đã định trước cho sách
            cube(book_colors[j][0], book_colors[j][1], book_colors[j][2]);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void bookshelf9()
{
    glPushMatrix();

    // Các thông số kích thước của tủ sách
    GLfloat shelf_height = 12, shelf_width = 6, shelf_depth = 1.5;

    GLfloat book_colors[15][3] = {  // Giả sử có 15 màu cho 15 quyển sách
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0},
        {0.5, 0.3, 0.2}, {0.3, 0.2, 0.5}, {0.2, 0.5, 0.3},
        {0.7, 0.4, 0.1}, {0.1, 0.4, 0.7}, {0.4, 0.7, 0.1},
        {0.8, 0.6, 0.2}, {0.2, 0.8, 0.6}, {0.6, 0.2, 0.8}
    };

    // Vẽ phần khung chính của tủ sách
    glPushMatrix();
    glScalef(shelf_width, shelf_height, shelf_depth);
    glTranslatef(-2.2, 0, 3.5); // Điều chỉnh vị trí tương đối
    cube(1, 0.6, 0.2); // Màu sắc của khung tủ
    glPopMatrix();

    // Vẽ các ngăn kệ và sách đứng trên mỗi kệ
    for (int i = 1; i < 6; i++) {
        glPushMatrix();
        GLfloat y_position = i * 2; // Vị trí ngang của mỗi ngăn
        glTranslatef(-13, y_position, 4.1);
        glScalef(shelf_width - 0.2, 0.1, shelf_depth); // Kích thước của ngăn kệ
        cube(0.8, 0.8, 0.8); // Màu sắc của ngăn

        // Vẽ sách đứng trên kệ
        int num_books = 13; // Số lượng sách trên mỗi kệ
        for (int j = 0; j < num_books; j++) {
            glPushMatrix();
            GLfloat book_thickness = 0.05; // Độ dày của sách
            GLfloat book_height = 17; // Chiều cao của sách
            GLfloat book_depth = 1; // Độ sâu của sách
            glTranslatef(0.1 + j * book_thickness, 0.1, (shelf_depth - book_depth) / 2); // Đặt sách trên kệ
            glScalef(book_thickness, book_height, book_depth); // Kích thước sách
            // Sử dụng màu đã định trước cho sách
            cube(book_colors[j][0], book_colors[j][1], book_colors[j][2]);
            glPopMatrix();
        }

        glPopMatrix();
    }

    glPopMatrix();
}

void noticeBoard()
{
    // Vẽ bảng thông báo dưới dạng một hình chữ nhật màu xanh dương
    glPushMatrix();
    glTranslatef(-4, 5, -14.95); // Điều chỉnh vị trí cạnh cửa sổ
    glScalef(4, 8, 0); // Điều chỉnh kích thước của bảng thông báo
    cube(0, 0, 1); // Sử dụng màu xanh dương cho bảng thông báo
    glPopMatrix();

    // Vẽ đường kẻ 
    glPushMatrix();
    glTranslatef(-2.7, 11, -14.93); // Điều chỉnh vị trí để đặt vào giữa bảng thông báo
    glScalef(1.5, 0.5, 0); // Điều chỉnh kích thước của đường kẻ (mỏng và dài)
    cube(1, 1, 1); // Màu cho đường kẻ
    glPopMatrix();

    // Vẽ đường kẻ 
    glPushMatrix();
    glTranslatef(-3.5, 10, -14.93); // Điều chỉnh vị trí để đặt vào giữa bảng thông báo
    glScalef(3, 0.2, 0); // Điều chỉnh kích thước của đường kẻ (mỏng và dài)
    cube(1, 1, 1); // Màu cho đường kẻ
    glPopMatrix();
    
    // Vẽ đường kẻ 
    glPushMatrix();
    glTranslatef(-3.5, 9, -14.93); // Điều chỉnh vị trí để đặt vào giữa bảng thông báo
    glScalef(3, 0.2, 0); // Điều chỉnh kích thước của đường kẻ (mỏng và dài)
    cube(1, 1, 1); // Màu cho đường kẻ
    glPopMatrix();

    // Vẽ đường kẻ 
    glPushMatrix();
    glTranslatef(-3.5, 8, -14.93); // Điều chỉnh vị trí để đặt vào giữa bảng thông báo
    glScalef(3, 0.2, 0); // Điều chỉnh kích thước của đường kẻ (mỏng và dài)
    cube(1, 1, 1); // Màu cho đường kẻ
    glPopMatrix();

    // Vẽ đường kẻ
    glPushMatrix();
    glTranslatef(-3.5, 7, -14.93); // Điều chỉnh vị trí để đặt vào giữa bảng thông báo
    glScalef(3, 0.2, 0); // Điều chỉnh kích thước của đường kẻ (mỏng và dài)
    cube(1, 1, 1); // Màu cho đường kẻ
    glPopMatrix();


}

void window()
{
    glPushMatrix();
    glScalef(0.1, 10, 10);
    glTranslatef(-140, .3, -.5);
    cube(.5, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 10, .1);
    glTranslatef(-139, .3, 0);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 10);
    glTranslatef(-139, 75, -.5);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 10);
    glTranslatef(-139, 130, -.5);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 10);
    glTranslatef(-139, 30, -.5);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 10, .1);
    glTranslatef(-139, .3, -50);
    cube(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 10, .1);
    glTranslatef(-139, .3, 50);
    cube(0, 0, 0);
    glPopMatrix();



}

void windows()
{
    glPushMatrix();
    window();
    noticeBoard(); // Vẽ bảng thông báo
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    window();
    glPopMatrix();
}



void bulb()
{
    // Vẽ phần thân bóng đèn (dạng hộp)
    glPushMatrix();
    glScalef(4, 0.535, .5); // Điều chỉnh tỷ lệ của thân bóng đèn
    glTranslatef(0, 10, 0); // Điều chỉnh vị trí thân bóng đèn
    cube(1, 1, 1); // Màu trắng
    glPopMatrix();

    // Vẽ phần đế của bóng đèn (dạng hộp nhỏ hơn)
    glPushMatrix();
    glScalef(.2, .3, .2); // Điều chỉnh tỷ lệ của đế bóng đèn
    glTranslatef(0.7, 18, 0.7); // Điều chỉnh vị trí đế bóng đèn
    cube(1, 0, 0); // Màu đỏ
    glPopMatrix();
}

void bulb_set()
{
    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(-12, 8.2, -12);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(12, 8.2, -12);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(-12, 8.2, 12);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(12, 8.2, 12);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(-5, 8.2, -5);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(5, 8.2, -5);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(-5, 8.2, 5);
    bulb();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(5, 8.2, 5);
    bulb();
    glPopMatrix();

}
void door()
{
    glPushMatrix();
    glScalef(3.8, 10, .2);
    glTranslatef(2.2, 0, -75);
    cube(.8, .7, .5);
    glPopMatrix();

    glPushMatrix();
    glScalef(.3, 1, .2);
    glTranslatef(28, 4.5, -73);
    cube(0, 0, 0);
    glPopMatrix();
}
void Walls(float scale)
{

    glPushMatrix();
    glScalef(scale, 1, scale);
    glTranslatef(-0.5, -1, -0.5);
    cube(0.8, 0.8, 0.8);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(scale / 2, scale / 4, 0);
    glScalef(1, scale / 2, scale);
    glTranslatef(-1, -0.5, -0.5);
    cube(0.871, 0.722, 0.529);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-scale / 2 + 1, scale / 4, 0);
    glScalef(1, scale / 2, scale);
    glTranslatef(-1, -0.5, -0.5);
    cube(0.871, 0.722, 0.529);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, scale / 4, scale / 2);
    glScalef(scale, scale / 2, 1);
    glTranslatef(-0.5, -0.5, -1);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, scale / 4, scale / 2);
    glScalef(scale, scale / 2, 1);
    glTranslatef(-0.5, -0.5, -31);
    cube(1.000, 0.855, 0.725);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, scale / 2, 0);
    glScalef(scale, 1, scale);
    glTranslatef(-0.5, -1, -0.5);
    cube(0.871, 0.722, 0.529);
    glPopMatrix();

}

void plantPot()
{
    glPushMatrix();

    // Kích thước giảm cho chậu
    GLfloat pot_height = 3.0, pot_width = 2.5, pot_depth = 2.5;

    // Màu sắc cơ bản cho chậu
    GLfloat pot_color[3] = { 0.45, 0.32, 0.25 }; // Màu nâu đất

    // Vẽ phần chính của chậu
    glPushMatrix();
    glTranslatef(10.0, 0.5, 0.0); // Căn giữa chậu
    glScalef(pot_width, pot_height, pot_depth); // Thay đổi kích thước chậu
    cube(pot_color[0], pot_color[1], pot_color[2]); // Tô màu cho chậu
    glPopMatrix();

    // Thêm vành chậu ở phía trên
    glPushMatrix();
    GLfloat rim_height = 0.25, rim_thickness = 0.3;
    glTranslatef(9.9, pot_height + 0.125, -0.1); // Đặt vành chậu lên trên
    glScalef(pot_width + rim_thickness, rim_height, pot_depth + rim_thickness); // Làm vành chậu rộng hơn một chút so với thân
    cube(0.6, 0.4, 0.3); // Màu tối hơn cho vành
    glPopMatrix();

    // Vẽ cây trong chậu
    glPushMatrix();
    GLfloat plant_height = 4.0;
    GLfloat leaf_color[3] = { 0.0, 0.6, 0.0 }; // Màu xanh lá cho lá
    glTranslatef(11.0, pot_height + 0.5, 0.5); // Bắt đầu cây phía trên chậu
    glScalef(1.0, plant_height, 1.5); // Cây to, cao
    cube(leaf_color[0], leaf_color[1], leaf_color[2]); // Tô màu cho cây
    glPopMatrix();

    // Vẽ tán cây 
    glPushMatrix();
    glTranslatef(11.5, 7.0, 1.5); // Di chuyển lên phía trên cây
    glutSolidSphere(2.5, 20, 20); // Vẽ hình cầu làm tán cây
    glPopMatrix();

    glPopMatrix();


}

void plantPot2()
{
    glPushMatrix();

    // Kích thước giảm cho chậu
    GLfloat pot_height = 3.0, pot_width = 2.5, pot_depth = 2.5;

    // Màu sắc cơ bản cho chậu
    GLfloat pot_color[3] = { 0.45, 0.32, 0.25 }; // Màu nâu đất

    // Vẽ phần chính của chậu
    glPushMatrix();
    glTranslatef(-13.0, 0.5, 0.0); // Căn giữa chậu
    glScalef(pot_width, pot_height, pot_depth); // Thay đổi kích thước chậu
    cube(pot_color[0], pot_color[1], pot_color[2]); // Tô màu cho chậu
    glPopMatrix();

    // Thêm vành chậu ở phía trên
    glPushMatrix();
    GLfloat rim_height = 0.25, rim_thickness = 0.3;
    glTranslatef(-13.0, pot_height + 0.125, -0.1); // Đặt vành chậu lên trên
    glScalef(pot_width + rim_thickness, rim_height, pot_depth + rim_thickness); // Làm vành chậu rộng hơn một chút so với thân
    cube(0.6, 0.4, 0.3); // Màu tối hơn cho vành
    glPopMatrix();

    // Vẽ cây trong chậu
    glPushMatrix();
    GLfloat plant_height = 4.0;
    GLfloat leaf_color[3] = { 0.0, 0.6, 0.0 }; // Màu xanh lá cho lá
    glTranslatef(-12.5, pot_height + 0.5, 0.5); // Bắt đầu cây phía trên chậu
    glScalef(1.0, plant_height, 1.5); // Cây to, cao
    cube(leaf_color[0], leaf_color[1], leaf_color[2]); // Tô màu cho cây
    glPopMatrix();

    // Vẽ tán cây 
    glPushMatrix();
    glTranslatef(-11.5, 7.0, 1.5); // Di chuyển lên phía trên cây
    glutSolidSphere(2.5, 20, 20); // Vẽ hình cầu làm tán cây
    glPopMatrix();

    glPopMatrix();


}




void light()
{


    GLfloat l_amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat l_dif[] = { 0.961, 0.871, 0.702 };
    GLfloat l_spec[] = { 0.2,0.2,0.2,1 };
    GLfloat l_no[] = { 0, 0, 0, 1.0 };
    GLfloat l_pos1[] = { -20,20,20,1.0 };
    GLfloat l_pos2[] = { 44,30,-5,1.0 };
    GLfloat l_pos3[] = { 0,60,0,1.0 };



    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if (l_on1)
    {
        if (amb == true)
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
        }

        if (dif == true)
        {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
        }
        if (spec == true)
        {
            glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);

    }
    glLightfv(GL_LIGHT0, GL_POSITION, l_pos1);







    if (l_on2)
    {
        if (amb == true)
        {
            glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
        }

        if (dif == true)
        {
            glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
        }
        if (spec == true)
        {
            glLightfv(GL_LIGHT1, GL_SPECULAR, l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);

    }
    glLightfv(GL_LIGHT1, GL_POSITION, l_pos2);



    if (l_on3)
    {
        if (amb == true)
        {
            glLightfv(GL_LIGHT2, GL_AMBIENT, l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2, GL_AMBIENT, l_no);
        }

        if (dif == true)
        {
            glLightfv(GL_LIGHT2, GL_DIFFUSE, l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2, GL_DIFFUSE, l_no);
        }
        if (spec == true)
        {
            glLightfv(GL_LIGHT2, GL_SPECULAR, l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT2, GL_SPECULAR, l_no);
        }

    }
    else
    {
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_no);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_no);
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_no);
    }

    glLightfv(GL_LIGHT2, GL_POSITION, l_pos3);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    GLfloat spt_ct[] = { spt_cutoff };
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);


    glRotatef(rot, 0, 1, 0);
    light();
    fan_full_set();
    full_set_chair_table();
    Walls(30);
    windows();
    bookshelf();
    bookshelf2();
    bookshelf3();
    bookshelf4();
    bookshelf5();
    bookshelf6();
    bookshelf7();
    bookshelf8();
    bookshelf9();
    bulb_set();
    plantPot();
    plantPot2();
    door();
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'd':
        rot++;
        break;

    case 'a':
        rot--;
        break;

    case 'w':
        eyeY++;
        break;

    case 's':
        eyeY--;
        break;

    case 'z':
        eyeX = 0;
        eyeZ++;
        lookZ++;
        break;

    case 'x':
        eyeZ--;
        break;


    case '1':
        l_on1 = !l_on1;
        break;
    case '2':
        l_on2 = !l_on2;
        break;
    case '3':
        l_on3 = !l_on3;
        break;
    case '6':
        dif = !dif;
        break;

    case '7': //bat/tat quat
        if (fRotate == false) {
            fRotate = true; break;
        }
        else {
            fRotate = false; break;
        }
    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if (theta > 360.0)
            theta -= 360.0 * floor(theta / 360.0);
    }


    if (fRotate == true)
    {
        alpha += 0.8;
        if (alpha > 360.0)
            alpha -= 360.0 * floor(alpha / 360.0);
    }

    if (fRotate == true)
    {
        alpha += 39.2;
        if (alpha > 360.0)
            alpha -= 360.0 * floor(alpha / 360.0);
    }


    glutPostRedisplay();

}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(height, width);
    glutCreateWindow("libraryroom");



    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);


    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);




    glutMainLoop();



    return 0;
}
