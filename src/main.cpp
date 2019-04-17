#include "main.h"
#include "timer.h"
#include "ball.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// Background B,B1,B2,B3;

bounding_box_t b1,b2,b3;
vector<Background> B;
vector<Platform> P;

vector<Barrier> Bar;
vector<int> bdir;
vector<Lhold> lh;
vector<Rhold> rh;

Ball ball2;
Scoreboard sc;
vector<Score> s;
vector<Magnet1> m1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
int score = 0;
int lives = 5;
int mag = 1;
int coins = 0;
vector<Obstacles> O;
vector<Obstacles> bcoins;

vector<Bigcoin> bigc;
vector<int> bigcoindir;

vector<Speedup> spd;
vector<int> sdir;
vector<int> inctime;

vector<Semc> ring;

vector<Fireline> F;
vector<Obstacles> Fobs;

vector<Boomerang> boom;
float boom_ly;
int boom_t;

vector<Dragon> drag;
vector<int> drag_dir;
vector<Obstacles> fireball;
int dragon_spawn = 0;

vector<Obstacles> waterb;



int nos = 0; //no. of speedup
int speed = 1;

int ct250 = 0;
int count = 0;

int rct = 0; // ring count
int rx,ry, rr; //ring -> center_absicca , center_coordinate, radius

Timer t60(1.0 / 60);
Timer t250(1.0 / 250);
Timer t24(1.0/5);
int x = 0;

int shield = 0; // to see if the player is sheilded
int shield_t;


int beam_t;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    // initText2D( "Holstein.DDS" );
    // Compute Camera matrix (view)
    //Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
     Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    
    b1.x = ball2.position[0];
    b1.y = ball2.position[1];
    b1.height = 0.6f;
    b1.width = 0.6f;
    for(int i = 0; i<O.size(); i++)
    {
       b2.x = O[i].position[0];
       b2.y = O[i].position[1];
       b2.height = 0.3f;
       b2.width = 0.3f;
       if(detect_collision(b1,b2) == false)
        O[i].draw(VP);
       else
       {
        score += 10;
        coins ++;
        change_score();
        O.erase(O.begin() + i);
       }
    }
    for(int i = 0; i<bcoins.size(); i++)
    {
       b2.x = bcoins[i].position[0];
       b2.y = bcoins[i].position[1];
       b2.height = 0.3f;
       b2.width = 0.3f;
       if(detect_collision(b1,b2) == false)
        bcoins[i].draw(VP);
       else
       {
        score += 25;
        coins ++;
        change_score();
        bcoins.erase(bcoins.begin() + i);
       }
    }
    for(int i = 0; i<Bar.size(); i++)
    {
       b2.x = Bar[i].position[0];
       b2.y = Bar[i].position[1];
       b2.height = 0.1f;
       b2.width = 2.0f;
       if(detect_collision(b1,b2) == true && shield == 0 && count - beam_t >= 100)
       {
        lives --;
        ball2.set_position(-2,-3);
       }
    }
    for(int i = 0; i<spd.size(); i++)
    {
       b2.x = spd[i].position[0];
       b2.y = spd[i].position[1];
       b2.height = 0.2f;
       b2.width = 2*sqrt(3)*0.1;
       if(detect_collision(b1,b2) == true)
       {
        speed += 3;
        inctime.push_back(count);
        spd.clear();
        nos = 0;
        break;
       }
    }


    //detecting collision with fireline
    if(F.size() > 0 && shield == 0)
    {
        if(check_col_fireline(b1) == true)
        {
            score -= 100;
            if(score < 0)
                score = 0;
            ball2.set_position(F[0].position[0],-3);
        }
    }


    // detecting collision with boomerang
    if(boom.size() > 0 && shield == 0)
    {
        if(check_col_with_boom() == true)
        {
            lives--;
            ball2.set_position(boom[0].position[0],-3);
        }    
    }
    for(int i = 0; i<bigc.size(); i++)
    {
       b2.x = bigc[i].position[0];
       b2.y = bigc[i].position[1];
       b2.height = 0.8f;
       b2.width = 0.8f;
       if(detect_collision(b1,b2) == false)
        bigc[i].draw(VP);
       else
       {
        score += 50;
        coins ++;
        change_score();
        bigc.erase(bigc.begin() + i);
        bigcoindir.erase(bigcoindir.begin() + i);
       }
    }

    for(int i = 0 ; i < inctime.size(); i++)
    {
        if(count - inctime[i] >= 180)
        {
            speed -= 3;
            inctime.erase(inctime.begin() + i);
            break;
        }
    }
    ball2.draw(VP);
    for(int i = 0; i < B.size(); i++)
        B[i].draw(VP);
    for(int i = 0; i <P.size(); i++)
        P[i].draw(VP);
    for(int i = 0; i <Bar.size(); i++)
    {
        if(count - beam_t >= 100)
        Bar[i].draw(VP);
        lh[i].draw(VP);
        rh[i].draw(VP);
    }


    for(int i = 0; i < s.size();i++)
        s[i].draw(VP);

    for(int i = 0; i < m1.size(); i++)
        m1[i].draw(VP);

    for(int i = 0 ; i< spd.size();i++)
        spd[i].draw(VP);

    for(int i =0; i < ring.size();i++)
        ring[i].draw(VP);

    for(int i = 0 ; i < F.size(); i++)
        F[i].draw(VP);
    for(int i = 0; i < Fobs.size(); i++)
        Fobs[i].draw(VP); 

    for(int i = 0; i < boom.size(); i++)
        boom[i].draw(VP);


    // dragon and fireball drawing
    for(int i = 0; i < drag.size(); i++)
        drag[i].draw(VP);

    // collision of fireball and water balloons
    for(int i = 0; i<fireball.size(); i++)
    {
        b2.x = fireball[i].position[0];
        b2.y = fireball[i].position[1];
        b2.height = 0.3f;
        b2.width = 0.3f;
        for(int j = 0; j < waterb.size(); j++)
        {
            b3.x = waterb[i].position[0];
            b3.y = waterb[i].position[1];
            b3.height = 0.3f;
            b3.width = 0.3f;
            if(detect_collision(b2,b3) == true)
            {
                lives += 0.2;
                if(lives > 5)
                    lives = 5;
                fireball.erase(fireball.begin() + i);
                waterb.erase(waterb.begin() + j);
            }    
        }
    }


    for(int i = 0; i<fireball.size(); i++)
    {
       b2.x = fireball[i].position[0];
       b2.y = fireball[i].position[1];
       b2.height = 0.3f;
       b2.width = 0.3f;
       if(detect_collision(b1,b2) == false || shield == true)
        fireball[i].draw(VP);
       else
       {
        lives -= 0.2;
        fireball.erase(fireball.begin() + i);
       }
    }

    for(int i = 0; i < waterb.size(); i++)
    {
        waterb[i].draw(VP);
    }


    char score_print[200];
    sprintf(score_print, "Score : %d  Health : %d ", score, lives);
    glfwSetWindowTitle(window, score_print);

    // score board lives
    sc.draw(VP);
    Lifebar lf;
    if(lives > 10/3)
        lf = Lifebar(0,-0.2, COLOR_DRAGON,lives);
    else if(lives > 5/3)
        lf = Lifebar(0,-0.2, COLOR_YELLOW,lives);
    else
        lf = Lifebar(0,-0.2, COLOR_RED,lives);
    lf.draw(VP);
    Emptybar eb = Emptybar(0,-0.2,COLOR_BALL,lives);
    eb.draw(VP);

    ball2.check_air(x++);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int press_p = glfwGetKey(window, GLFW_KEY_P);
    int press_s = glfwGetKey(window, GLFW_KEY_S);

    if (left) {
        ball2.tick(-1,"x",mag);
        if(ball2.position[0] <= -3.7)
            ball2.position[0] = -3.7;
    }
    if(right)
    {
        ball2.tick(1,"x",mag);
        if(ball2.position[0] >= 3.7)
            ball2.position[0] = 3.7;
    }
    float xc  = ball2.position[0];
    if(up)
    {
        if(rct == 0 || xc < rx - rr + 0.35f || xc > rx + rr - 0.35f)
        { 
            x = 1;
           for(int i = 0; i< 5; i++)
                ball2.tick(-1,"y",mag);
        }
    }

    if(rct == 1 && xc >= rx - rr + 0.35f && xc <= rx + rr - 0.35f)
    {
        shield = 1;
        float localr = rr - 0.35;
        float yo = sqrt(localr*localr - (xc-rx)*(xc-rx)) + ry;
        ball2.position[1] = yo;
    }
    else
    {
        shield = 0;
    }
    if(press_p && dragon_spawn == 1)
    {
        throw_balloons();
    }
    if(press_s)
    {
        screen_zoom = 1;
        reset_screen();
    }
}

void tick_elements() {

   ball2.tick(1,"x",mag);
    camera_rotation_angle += 0;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
        
    ball2       = Ball(-2,-3,COLOR_RED);
    

    B.push_back(Background(-3,0, COLOR_LRED));
    B.push_back(Background(-1,0, COLOR_LPURPLE));
    B.push_back(Background(1,0, COLOR_LRED));
    B.push_back(Background(3,0, COLOR_LPURPLE));
    B.push_back(Background(5,0, COLOR_LRED));
    

    P.push_back(Platform(-3,-4.25, COLOR_BLACK));
    P.push_back(Platform(-1,-4.25, COLOR_BALL));
    P.push_back(Platform(1,-4.25, COLOR_BLACK));
    P.push_back(Platform(3,-4.25, COLOR_BALL));
    P.push_back(Platform(5,-4.25, COLOR_BLACK));


    sc = Scoreboard(0,-0.2, COLOR_BLACK);

    s.push_back(Score(2,3.85,0,COLOR_BALL));
    s.push_back(Score(1.7,3.85,0,COLOR_BALL));
    s.push_back(Score(1.4,3.85,0,COLOR_BALL));
    s.push_back(Score(1.1,3.85,0,COLOR_BALL));
    s.push_back(Score(0.8,3.85,0,COLOR_BALL));
    
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 900;
    int height = 900;
    int ct = 0;
    int ctp = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        
        if(lives <= 0)
            break;
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            count ++;
            if(count % 60 == 0)
            {
                srand(time(0));
                int x = rand()%6 - 3;
                srand(time(0));
                int cord = rand()%6 - 3;
                for(int i = 1; i <=5; i++)
                    O.push_back(Obstacles(i*x,cord, COLOR_YELLOW));
            }
            if(count % 300 == 0)
            {
                srand(time(0));
                int x = rand()%6 - 3;
                srand(time(0));
                int cord = rand()%6 - 3;
                for(int i = 1; i <=5; i++)
                    bcoins.push_back(Obstacles(i*x,cord, COLOR_BROWN));
            }
            if(count % 500 == 0)
            {
                srand(time(0));
                int x = rand()%6 -3;
                srand(time(0));
                bigc.push_back(Bigcoin(6,x,COLOR_GOLD));
                bigcoindir.push_back(-1);
            }
            srand(time(0));
            if(rand() % 20 == 0 && rct == 0) 
            {
                shield_t = count;
                rct = 1;
                
                make_ring(rand()%6 - 3, -3, 0.1);
            }
            if(count - shield_t >= 500)
            {
                rct = 0;
                ring.clear();
            }
            srand(time(0));
            if(count % 200 == 0 && F.size() == 0) 
            {
                srand(time(0));
                int lx = rand()%7 - 3;
                srand(time(0));
                int ly = rand()%7 - 3;
                F.push_back(Fireline(lx,ly,COLOR_FIRE));
                float theta = F[0].rotation*3.142/180;
                float x1,x2,y1,y2;
                x1 = 0.8f;
                y1 = 0.05f;
                x2 = x1*cos(theta) - sin(theta)*y1;
                y2 = sin(theta)*x1 + cos(theta)*y1;
                Fobs.push_back(Obstacles(x2 + lx,y2 + ly,COLOR_BLACK));
                x1 = -0.8f;
                y1 = 0.05f;
                x2 = x1*cos(theta) - sin(theta)*y1;
                y2 = sin(theta)*x1 + cos(theta)*y1;
                Fobs.push_back(Obstacles(x2+lx ,y2 + ly,COLOR_BLACK));
                
            }
            if(count % 1000 == 0)
                create_boomerang();

            if(count % 2000 == 0 && drag.size() == 0)
            {
                dragon_spawn = 1;
                srand(time(0));
                drag.push_back(Dragon(3,rand()%6 - 3,COLOR_DRAGON));
                drag_dir.push_back(-1);
            }
            if(count % 3000 == 0 && drag.size() > 0)
            {
                dragon_spawn = 0;
                drag.clear();
                drag_dir.clear();
            }

            // dragon ticking
            dragon_tick();

            //balloon ticking
            balloon_tick();

            draw();

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
        }

        if(t250.processTick()) {
           // for(int i = 0; i <1; i++)
            ct250 ++;
            srand(time(0));
            if(rand() % 11 == 0 and Bar.size() < 1)
            {
                beam_t = count;
                srand(time(0));
                int ly = rand()%5 - 2;
                srand(time(0));
                int lx = rand()%5 - 2;
                Bar.push_back(Barrier(lx, ly , COLOR_FIRE));
                lh.push_back(Lhold(lx-1,ly, COLOR_BLACK));
                rh.push_back(Rhold(lx+1 ,ly, COLOR_BLACK));
                bdir.push_back(-1);
                srand(time(0));
                int ly2 = rand()%5-2;
                while(ly == ly2)
                {
                    ly2 = rand()%5-2;
                }
                Bar.push_back(Barrier(lx, ly2 , COLOR_FIRE));
                lh.push_back(Lhold(lx-1,ly2, COLOR_BLACK));
                rh.push_back(Rhold(lx+1 ,ly2, COLOR_BLACK));
                bdir.push_back(1);
            }
            srand(time(0));
            if(rand() % 17 == 0)
            {
                if(mag == 1)
                {
                    mag = 3;
                    m1.push_back(Magnet1(3,3,COLOR_RED));
                }
            }
            srand(time(0));
            if(rand() % 23 == 0)
            {
                mag = 1;
                m1.clear();
            }
            srand(time(0));
            if(rand() % 19 == 0 && nos == 0)
            {
                nos ++;
                srand(time(0));
                spd.push_back(Speedup(5,rand()%6-3,COLOR_BLACK));
                sdir.push_back(-1);
            }
            goto label;
        }
    label:
        if(t24.processTick()) {
            for(int i = 0; i < O.size();i++)
            {
                if(O[i].position[0] <= -5){
                    O.erase(O.begin() + i);
                }
                O[i].tick(-1,"x", speed );
            }

            
            if(count - boom_t <= 180 && boom.size() > 0)
                tick_boom();
            else
                boom.clear();

            for(int i = 0; i < bcoins.size();i++)
            {
                if(bcoins[i].position[0] <= -5){
                    bcoins.erase(bcoins.begin() + i);
                }
                bcoins[i].tick(-1,"x", speed);
                // O[i].draw(VP);
            }
            for(int i = 0; i < Bar.size();i++)
            {
                if(count - beam_t >= 600)
                {
                    Bar.erase(Bar.begin() + i);
                    bdir.erase(bdir.begin() + i);
                    lh.erase(lh.begin() + i);
                    rh.erase(rh.begin() + i);
                }
                if(count - beam_t >= 100)
                {
                    Bar[i].tick(bdir[i],"y", speed);
                    lh[i].tick(bdir[i],"y",speed);
                    rh[i].tick(bdir[i],"y",speed);
                }
                if(Bar[i].position[1] >= 3 || Bar[i].position[1] <= -3)
                    bdir[i] *= -1;
            }
            for(int i = 0; i < F.size();i++)
            {
                if(F[i].position[0] <= -5){
                    F.erase(F.begin() + i);
                    Fobs.clear();
                    break;
                }
                F[i].tick(-1,"x", speed );
            }
            for(int i = 0; i < Fobs.size();i++)
                Fobs[i].tick(-1,"x", speed );
            for(int i = 0; i < spd.size();i++)
            {
                if(spd[i].position[0] <= -5.5)
                {
                    nos = 0;
                    spd.erase(spd.begin() + i);
                    sdir.erase(sdir.begin() + i);
                }
                spd[i].tick(sdir[i],"xy", speed);
                if(spd[i].position[1] >= 3 || spd[i].position[1] <= -3.5)
                    sdir[i] *= -1;
                // O[i].draw(VP);
            }
            for(int i = 0; i < bigc.size();i++)
            {
                if(bigc[i].position[0] <= -5.5)
                {
                    nos = 0;
                    bigc.erase(bigc.begin() + i);
                    bigcoindir.erase(bigcoindir.begin() + i);
                }
                bigc[i].tick(bigcoindir[i],"xy", speed);
                if(bigc[i].position[1] >= 3 || bigc[i].position[1] <= -3.5)
                    bigcoindir[i] *= -1;
                // O[i].draw(VP);
            }
            for(int i = 0; i < B.size(); i++)
            {
                if(B[i].position[0] <= -5)
                {
                    B.erase(B.begin() + i);
                    if(ct == 0)
                    {
                        ct = 1;
                        B.push_back(Background(5,0, COLOR_LPURPLE));
                    }
                    else
                    {
                        ct = 0;
                        B.push_back(Background(5,0, COLOR_LRED));
                    }
                }
                B[i].tick(-1,"x", speed);
            }
            for(int i = 0; i < P.size(); i++)
            {
                if(P[i].position[0] <= -5)
                {
                    P.erase(P.begin() + i);
                    if(ctp == 0)
                    {
                        ctp = 1;
                        P.push_back(Platform(5,-4.25, COLOR_BALL));
                    }
                    else
                    {
                        ctp = 0;
                        P.push_back(Platform(5,-4.25, COLOR_BLACK));
                    }
                }
                P[i].tick(-1,"x", speed);
            }


        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void change_score(){
    s.clear();
    int no = score;
    int absicca = 2;
    
    s.push_back(Score(2,3.85,no%10,COLOR_BALL));
    no = no/10;
    s.push_back(Score(1.7,3.85,no%10,COLOR_BALL));
    no = no/10;
    s.push_back(Score(1.4,3.85,no%10,COLOR_BALL));
    no = no/10;
    s.push_back(Score(1.1,3.85,no%10,COLOR_BALL));
    no = no/10;
    s.push_back(Score(0.8,3.85,no%10,COLOR_BALL));
    no = no/10;
}

void make_ring(float x, float y,float r)
{
    ring.clear();
    float x1 = x + 0.25;
    float y1 = -3.2;
    float n = 1000;
    float pi = 3.142;
    r = 1;
    for(int i = 1; i <= 180; i++)
    {
        if(i % 2)
            ring.push_back(Semc(x + r*cos(i*pi/180),y1+r*sin(i*pi/180),COLOR_SHEILD));
        else
            ring.push_back(Semc(x + r*cos(i*pi/180),y1+r*sin(i*pi/180),COLOR_BALL));
    }
    rx = x;
    ry = y1;
    rr = 1;
}
bool check_col_fireline(bounding_box_t a)
{
    float theta = F[0].rotation*3.142/180;
    float cx = F[0].position[0];
    float cy = F[0].position[1];
    float x1,x2,y1,y2;
    x1 = 0.8f;
    y1 = 0.05f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    float p1x = x2 + cx;
    float p1y = y2 + cy;
    x1 = -0.8f;
    y1 = 0.05f;
    x2 = x1*cos(theta) - sin(theta)*y1;
    y2 = sin(theta)*x1 + cos(theta)*y1;
    float p2x = x2 + cx;
    float p2y = y2 + cy;
    float bx = ball2.position[0];
    float by = ball2.position[1];
    if(p1x < p2x)
    {
        float t = p1x;
        p1x = p2x;
        p2x = t;
    }
    if(p1y < p2y)
    {
        float t = p1y;
        p1y = p2y;
        p2y = t;
    }

    if(bx >= p2x && bx <= p1x && by >= p2y && by <= p1y)
    {
        float m = tan(theta);
        // cout<< m<<endl;
        float val = (by - m*bx - cy + m*cx)/sqrt(1 + m*m);
        if(val < 0.3f)
            return true;
    }
    return false;
}

void create_boomerang()
{
    float x1 = ball2.position[0];
    float y1 = ball2.position[1];
    float x =x1 + 2;
    float y = y1 + 1;
    boom_t = count;
    boom.push_back(Boomerang(x,y,COLOR_WOODEN,x1,y1));
}

void tick_boom()
{
    if(count - boom_t <= 60)
    {
        boom[0].tick(-1,"x",speed);
    }
    else if(count - boom_t <= 132)
    {
        float cx = boom[0].focus[0];
        float cy =boom[0].focus[1];
        float r = 1.0f;
        float theta = 3.142/2 + ((count - boom_t - 60)/12) *(3.142)/6;
        boom[0].set_position(cx + r*cos(theta), cy + r*sin(theta));

    }
    else
    {
        boom[0].tick(1,"x",speed);
    }
}
bool check_col_with_boom()
{
    float x1 = ball2.position[0];
    float  y1 = ball2.position[1];
    float x2 = boom[0].position[0];
    float y2 = boom[0].position[1];
    float d = sqrt((x1 -x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    if(d <= 0.4f)
        return true;
    else
        return false;
}


void dragon_tick()
{
    int live = 0;
    if(drag.size())
        live = 1;
    if(live == 1)
    {
        drag[0].tick(drag_dir[0],"y",speed);
        if(drag[0].position[1] >= 3 || drag[0].position[1] <= -3)
                    drag_dir[0] *= -1;
        srand(time(0));
        if(rand()%5 == 0 && count % 20 == 0)
        {
            fireball.push_back(Obstacles(drag[0].position[0] - 0.6f,drag[0].position[1],COLOR_FIRE));
        }
    }
    for(int i = 0; i < fireball.size(); i++)
    {
        if(fireball[i].position[1] <= -3.5 ||  fireball[i].position[0] <= -3.5)
            fireball.erase(fireball.begin() + i);
        else
        {
            fireball[i].tick2(1,"xy",speed);
        }
    }
}


void throw_balloons()
{
    if(count % 3 == 0)
        waterb.push_back(Obstacles(ball2.position[0] + 0.5f, ball2.position[1],COLOR_WATER));
}


void balloon_tick()
{
    for(int i = 0; i < waterb.size(); i++)
    {
        if(waterb[i].position[1] > 3.5 ||  waterb[i].position[0] > 3)
            waterb.erase(waterb.begin() + i);
        else
        {
            waterb[i].tick3(1,"xy",speed);
        }
    }    
}