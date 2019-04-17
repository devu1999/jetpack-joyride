#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int dir,const char* xy, int mag);
    void check_air(int x);
    double speed;
private:
    VAO *object;
};


class Obstacles {
public:
    Obstacles() {}
    Obstacles(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int dir,const char* xy, int spd);   
    void tick2(int dir,const char* xy, int spd);
    void tick3(int dir,const char* xy, int spd);
    void check_air();
    double speed;
private:
    VAO *object;
};

class Background {
public:
    Background() {}
    Background(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
	 void tick(int dir,const char* xy, int spd);
    double speed;
private:
    VAO *object;
};

class Platform {
public:
    Platform() {}
   	Platform(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
	 void tick(int dir,const char* xy, int spd);
    double speed;
private:
    VAO *object;
};


class Barrier {
public:
    Barrier() {}
    Barrier(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};

class Score {
public:
    Score() {}
    Score(float x, float y,int no, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

class Scoreboard {
public:
    Scoreboard() {}
    Scoreboard(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

class Magnet1 {
public:
    Magnet1() {}
    Magnet1(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

class Speedup {
public:
    Speedup() {}
    Speedup(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};


class Bigcoin {
public:
    Bigcoin() {}
    Bigcoin(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};

class Semc {
public:
    Semc() {}
    Semc(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int dir,const char* xy, int spd);
    void check_air();
    double speed;
private:
    VAO *object;
};

class Lhold {
public:
    Lhold() {}
    Lhold(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};

class Rhold {
public:
    Rhold() {}
    Rhold(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};


class Sballs {
public:
    Sballs() {}
    Sballs(float x, float y, color_t color,int side, float theta);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int dir,const char* xy, int spd);
    void check_air();
    double speed;
private:
    VAO *object;
};

class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color, float x1, float y1);
    glm::vec3 position;
    glm::vec3 focus;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
     void tick(int dir,const char* xy, int spd);
    // void check_air();
    double speed;
private:
    VAO *object;
};

class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int dir,const char* xy, int spd);
    void check_air();
    double speed;
private:
    VAO *object;
};

class Lifebar {
public:
    Lifebar() {}
    Lifebar(float x, float y, color_t color,float score);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

class Emptybar {
public:
    Emptybar() {}
    Emptybar(float x, float y, color_t color,float score);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
