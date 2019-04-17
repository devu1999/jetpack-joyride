#include "ball.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = 0.3f;
    float y1 = 0.0f;
    float z1 = 0.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = 0.0f;
        x1 = x2;
        y1 = y2; 
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int dir,const char* xy, int mag) {
    speed = 0.01;
    if(strcmp(xy,"x") == 0)
        this->position.x +=  dir*0.03;
    else if(strcmp(xy,"y") == 0 &&  this->position.y - dir*speed<= 3)
    {
        if(mag == 1)
            this->position.y -= dir*0.03;
        else
        {
            if(dir == -1 && this->position.y - mag*dir*speed<= 3)
                this->position.y -= mag*dir*0.03;
        }
    }
}

void Ball::check_air(int x)
{
    if(this->position.y >= -3 + 0.01)
        this->position.y -= 0.005*x;
    if(this->position.y < -3)
        this->position.y = -3;
}


Obstacles::Obstacles(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 1000;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = 0.15f;
    float y1 = 0.0f;
    float z1 = 1.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 1.0f;
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = 1.0f;
        x1 = x2;
        y1 = y2; 
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Obstacles::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Obstacles::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Obstacles::tick(int dir,const char* xy, int spd) {
    if(strcmp(xy,"x") == 0)
        this->position.x += spd*dir*0.1;
    else if(strcmp(xy,"y") == 0 && this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -= dir*0.02;
    }
}

void Obstacles::tick2(int dir,const char* xy, int spd) {
    this->position.x -= spd*0.1;
    this->position.y -= spd*0.02;
}

void Obstacles::tick3(int dir,const char* xy, int spd) {
    this->position.x += spd*0.1;
    this->position.y += spd*0.02;
}

void Obstacles::check_air()
{
    if(this->position.y >= -3.5 + 0.01)
        this->position.y -= 0.01;
}


Background::Background(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = 1.0f;
    float y1 = 0.0f;
    float z1 = -1.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -1.0f;
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = 4*x2;
        vertex_buffer_data[k++] = 4*y2;
        vertex_buffer_data[k++] = -1.0f;
        x1 = x2;
        y1 = y2; 
    }
   
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Background::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Background::tick(int dir,const char* xy, int spd) {
    //this->rotatio+n +=dir* 0;
    if(strcmp(xy,"x") == 0)
        this->position.x += spd*dir*0.1;
    else if(strcmp(xy,"y") == 0 && this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -= dir*0.02;
    }
}



Platform::Platform(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[40];
    float x1 = 1.0f;
    float y1 = 0.0f;
    float z1 = -1.0f;
    int k = 0;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -1.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;


    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Platform::tick(int dir,const char* xy, int spd) {
    // this->rotation += 0.1;
    if(strcmp(xy,"x") == 0)
        this->position.x += spd*dir*0.1;
    else if(strcmp(xy,"y") == 0 && this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -= dir*0.02;
    }
}



Barrier::Barrier(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    
    GLfloat vertex_buffer_data[400];  
    int k = 0;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;

    
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}

void Barrier::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Barrier::tick(int dir,const char * xy, int spd) {
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*-1*0.2;
    // if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    // {
        this->position.y -= spd*dir*0.1;
    // }
}


Score::Score(float x, float y, int no, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[400];
    int k = 0;
    int notr = 0;

//1
    if(no == 0 || no == 2 || no == 3 || (no >=5  && no <=9))
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //2
    if(no != 7 && no >=2 && no <= 9)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.2f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.05f -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.2f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //3
    if(no == 0 || no == 2 || no == 3 || no == 5 || no == 6 || no == 8 || no == 9)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f ;
        vertex_buffer_data[k++] = -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.4f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.05f -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.4f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //4
    if(no == 0 || no == 4 || no == 5 || no == 6 || no == 8 || no == 9)
    {
        notr ++;        
        vertex_buffer_data[k++] = 0.0f ;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }

    //5
    if((no >=0 && no <= 4) || (no >=7 && no <= 9))
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //6
    if(no == 0 || no == 2 || no == 6 || no == 8 || no == 9)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //7
    if(no != 2)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f - 0.2f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f - 0.2f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }

    
    this->object = create3DObject(GL_TRIANGLES, notr*6, vertex_buffer_data, color, GL_FILL);
}

void Score::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Scoreboard::Scoreboard(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[40];
    int k = 0;

    vertex_buffer_data[k++] = 4.0f;
    vertex_buffer_data[k++] = 3.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -4.0f;
    vertex_buffer_data[k++] = 3.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -4.0f;
    vertex_buffer_data[k++] = 4.5f;
    vertex_buffer_data[k++] = -1.0f;

    vertex_buffer_data[k++] = -4.0f;
    vertex_buffer_data[k++] = 4.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 4.0f;
    vertex_buffer_data[k++] = 4.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 4.0f;
    vertex_buffer_data[k++] = 3.5f;
    vertex_buffer_data[k++] = -1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Scoreboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

Magnet1::Magnet1(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[40];
    int k = 0;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = sqrt(3)*0.2f;
    vertex_buffer_data[k++] = -0.2f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -sqrt(3)*0.2f;
    vertex_buffer_data[k++] = -0.2f;
    vertex_buffer_data[k++] = -1.0f;

    
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Magnet1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Speedup::Speedup(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[40];
    int k = 0;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = sqrt(3)*0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f + sqrt(3)*0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f + sqrt(3)*0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 2*sqrt(3)*0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;

    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Speedup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Speedup::tick(int dir,const char * xy, int spd) {
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*-1*0.2;
    // if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    // {
        this->position.y -= dir*0.1;
    // }
}


Bigcoin::Bigcoin(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 10000;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = 0.4f;
    float y1 = 0.0f;
    float z1 = 0.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        x1 = x2;
        y1 = y2; 
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Bigcoin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bigcoin::tick(int dir,const char * xy, int spd) {
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*-1*0.2;
    // if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    // {
        this->position.y -= dir*0.1;
    // }
}


Semc::Semc(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 1000;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = 0.05f;
    float y1 = 0.0f;
    float z1 = 0.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = 0.0f;
        x1 = x2;
        y1 = y2; 
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Semc::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Semc::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Semc::tick(int dir,const char* xy, int spd) {
    if(strcmp(xy,"x") == 0)
        this->position.x += spd*dir*0.1;
    else if(strcmp(xy,"y") == 0 && this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -= dir*0.02;
    }
}

void Semc::check_air()
{
    if(this->position.y >= -3.5 + 0.01)
        this->position.y -= 0.01;
}

Lhold::Lhold(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    
    GLfloat vertex_buffer_data[400];  
    int k = 0;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Lhold::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Lhold::tick(int dir,const char * xy, int spd) {
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*-1*0.2;
    // if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    // {
        this->position.y -= spd*dir*0.1;
    // }
}

Rhold::Rhold(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    
    GLfloat vertex_buffer_data[400];  
    int k = 0;

    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.2f;
    vertex_buffer_data[k++] = 0.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.1f;
    vertex_buffer_data[k++] = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Rhold::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rhold::tick(int dir,const char * xy, int spd) {
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*-1*0.2;
    // if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    // {
        this->position.y -= spd*dir*0.1;
    // }
}

Fireline::Fireline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    srand(time(0));
    this->rotation = rand() % 12 *30;
    if(this->rotation == 90 || this->rotation == 270)
        this->rotation -= 30;
    speed = 0.005;
    
    GLfloat vertex_buffer_data[3000];  
    int k = 0;
    float pi = 3.142;
    float theta = pi*this->rotation/180 ;
    float x1,y1,x2,y2;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;

    x1 = 0.8f;
    y1 = 0.0f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    vertex_buffer_data[k++] = x2;
    vertex_buffer_data[k++] = y2;
    vertex_buffer_data[k++] = 0.0f;
    x1 = 0.8f;
    y1 = 0.1f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    vertex_buffer_data[k++] = x2;
    vertex_buffer_data[k++] = y2;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;


    x1 = 0.8f;
    y1 = 0.1f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    vertex_buffer_data[k++] = x2;
    vertex_buffer_data[k++] = y2;
    vertex_buffer_data[k++] = 0.0f;

    x1 = -0.8f;
    y1 = 0.1f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    vertex_buffer_data[k++] = x2;
    vertex_buffer_data[k++] = y2;
    vertex_buffer_data[k++] = 0.0f;
    

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;

    x1 = -0.8f;
    y1 = 0.0f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    vertex_buffer_data[k++] = x2;
    vertex_buffer_data[k++] = y2;
    vertex_buffer_data[k++] = 0.0f;

    x1 = -0.8f;
    y1 = 0.1f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    vertex_buffer_data[k++] = x2;
    vertex_buffer_data[k++] = y2;
    vertex_buffer_data[k++] = 0.0f;

    
    this->object = create3DObject(GL_TRIANGLES, ( 3)*3, vertex_buffer_data, color, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fireline::tick(int dir,const char * xy, int spd) {
    if(strcmp(xy,"x") == 0)
        this->position.x += spd*dir*0.1;
    else if(strcmp(xy,"y") == 0 && this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -= dir*0.02;
    }
}
 

Sballs::Sballs(float x, float y, color_t color,int side,float theta) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 1000;
    float pi = 3.142;
    float x1,y1,z1,x2,y2,cx,cy;
    GLfloat vertex_buffer_data[9*n];
    
    x1 = side*0.8f;
    y1 = 0.05f;
    cx = x1*cos(theta) - sin(theta)*y1;
    cy = sin(theta)*x1 + cos(theta)*y1;
    x1 = cx + 0.05 ;
    y1 = cy;
    z1 = 0.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = cx;
        vertex_buffer_data[k++] = cy;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = 0.0f;
        x1 = x2;
        y1 = y2; 
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Sballs::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sballs::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sballs::tick(int dir,const char* xy, int spd) {
    if(strcmp(xy,"x") == 0)
        this->position.x += spd*dir*0.1;
    else if(strcmp(xy,"y") == 0 && this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -= dir*0.02;
    }
}




Boomerang::Boomerang(float x, float y, color_t color,float x1, float y1) {
    this->position = glm::vec3(x, y, 0);
    this->focus = glm::vec3(x1, y1, 0);
    this->rotation = 0;
    speed = 0.005;
    
    GLfloat vertex_buffer_data[400];  
    int k = 0;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.5f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.5f;
    vertex_buffer_data[k++] = 0.5f;
    vertex_buffer_data[k++] = 0.0f;

    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = -0.5f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.0f;
    vertex_buffer_data[k++] = 0.5f;
    vertex_buffer_data[k++] = -0.5f;
    vertex_buffer_data[k++] = 0.0f;
    

    

    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Boomerang::tick(int dir,const char * xy, int spd) {

    //eqn of a parabola y2 = 4x
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*dir*0.2;
    if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    {
        this->position.y -=spd*dir*0.1;

    }
    
}


Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 1000;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = 0.4f;
    float y1 = 0.0f;
    float z1 = 1.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i  <= 400 || i > 600)
        {
            vertex_buffer_data[k++] = 0.0f;
            vertex_buffer_data[k++] = 0.0f;
            vertex_buffer_data[k++] = 1.0f;
            vertex_buffer_data[k++] = x1;
            vertex_buffer_data[k++] = y1;
            vertex_buffer_data[k++] = z1;
        }
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        if(i  <= 400 || i > 600)
        {
            vertex_buffer_data[k++] = x2;
            vertex_buffer_data[k++] = y2;
            vertex_buffer_data[k++] = 1.0f;
        }
        x1 = x2;
        y1 = y2; 
    }

    this->object = create3DObject(GL_TRIANGLES, (n-200)*3, vertex_buffer_data, color, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick(int dir,const char* xy, int spd) {
    if(strcmp(xy,"x") == 0 || strcmp(xy,"xy") == 0)
        this->position.x += spd*-1*0.2;
    // if((strcmp(xy,"y") == 0 || strcmp(xy,"xy") == 0 )&& this->position.y - dir*speed>= -3.5 && this->position.y - dir*speed<= 1)
    // {
        this->position.y -= spd*dir*0.1;
    // }
}

void Dragon::check_air()
{
    if(this->position.y >= -3.5 + 0.01)
        this->position.y -= 0.01;
}


Lifebar::Lifebar(float x, float y, color_t color, float score) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    GLfloat vertex_buffer_data[40];
    int k = 0;
    float add = score * 0.5f;

    vertex_buffer_data[k++] = -3.5f;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;

    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Lifebar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Emptybar::Emptybar(float x, float y, color_t color, float score) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    GLfloat vertex_buffer_data[40];
    int k = 0;
    float add = score * 0.5f;

    vertex_buffer_data[k++] = -3.5f + 2.5f;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f + 2.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;

    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f + 2.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Emptybar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
