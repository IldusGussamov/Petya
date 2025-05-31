#include <GL/freeglut.h>

struct Point
{
    float x, y;
};

struct Velocuty
{
    float x, y;
};

class Entity
{
public:
    Entity(Point position);
    void draw();
    void setVelocity(Velocuty newVelocity);
    void calculatePosition() {
        // Update position based on velocity
        position.x += velocity.x;
        position.y += velocity.y;

        // Update borders based on new position
        borders[0] = { position.x - w / 2, position.y - h / 2 }; // Bottom left
        borders[1] = { position.x + w / 2, position.y - h / 2 }; // Bottom right  
        borders[2] = { position.x + w / 2, position.y + h / 2 }; // Top right
        borders[3] = { position.x - w / 2, position.y + h / 2 }; // Top left
    }
    float w = 0.1f; // Width of the entity
    float h = 0.2f; // Height of the entity 
private:
    Point position;
    Point borders[4];
    Velocuty velocity;
   
};

Entity::Entity(Point position) {
    this->position = position;
    borders[0] = { position.x - w / 2, position.y - h / 2 }; // Bottom left
    borders[1] = { position.x + w / 2, position.y - h / 2 }; // Bottom right  
    borders[2] = { position.x + w / 2, position.y + h / 2 }; // Top right
    borders[3] = { position.x - w / 2, position.y + h / 2 }; // Top left
    velocity = { 0.0f, 0.0f }; // Initialize velocity
}

void Entity::draw() {
    glColor3f(0.0f, 1.0f, 0.0f); // Set color to green
    glBegin(GL_QUADS);
    glVertex2f(borders[0].x, borders[0].y); // Bottom left
    glVertex2f(borders[1].x, borders[1].y); // Bottom right         
    glVertex2f(borders[2].x, borders[2].y); // Top right
    glVertex2f(borders[3].x, borders[3].y); // Top left     

    glEnd();
}

Entity entity({0.0f, 0.0f});

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    entity.draw();
    glutSwapBuffers();
}

void Entity::setVelocity(Velocuty newVelocity) {
    this->velocity = newVelocity;
}

void timerFunc(int value)
{
    entity.calculatePosition();
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(10, timerFunc, 0); // Call this function again after 10 ms
}


int main(int argc, char **argv)
{
    entity.setVelocity({0.001f, 0.001f}); 
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenGL Window");
    glutDisplayFunc(display);
    glutTimerFunc(1000/60, timerFunc, 0);
    glutMainLoop();
    return 0;
}
