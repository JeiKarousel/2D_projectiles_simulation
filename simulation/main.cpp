#include "raylib.h"
#include "button.hpp"
#include <iostream> 

//functions
int ExampleQuadFunc(int x){
    // int y = x*x;
    int y = x++;
    return y;
}

int main(){

    Vector2 mouse_pos = GetMousePosition();
    bool mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    std::cout<< "Starting the 2D projectiles simulation" << std::endl; 

    //constants
    const int screen_width = 1200;
    const int screen_height = 800;

    //Projectiles -- constants
    const double gravity_acceleration = 9.80665; //(m/^2)
    const int displacement = (screen_width-100);

    //Projectiles -- initial variables//
    float angle = 30; // in degrees 
    float height = screen_height/2;  
    float speed_u = 10; // m/s 
    float speed_v = 20;
    float total_time = 5; // in seconds 

    //Particle center coordinates
    int particle_x = 15;
    int particle_y = height;

    InitWindow(screen_width, screen_height, "2D_Projectiles_Simulation");
    // SetTargetFPS(60);
    SetTargetFPS(200);
    int frames = 0;

    while(!WindowShouldClose()){

        frames++;
        BeginDrawing();
        ClearBackground(WHITE);

        //changes to x and y of the particle
        particle_x++;
        particle_y = ExampleQuadFunc(particle_x);

        DrawCircle(particle_x, particle_y, 10,BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, BLACK);
        DrawLine(0, screen_height/2, screen_width, screen_height/2, BLACK);

        DrawRectangle(0, (screen_height - screen_height*1/4), 1200, screen_height*1/4, GRAY);

        DrawText(TextFormat(
            "Height from ground: %d m\n"
            "Angle of Trajectory: %.2f degrees\n"
            "Initial Speed: %.2f m/s\n"
            "Final Speed: %.2f m/s\n",
            height, angle, speed_u, speed_v), 
            20, 20, 20, BLACK
        );

        DrawText(TextFormat(
            "Gravity Acceleration: %.5f m/s^2\n"
            "Displacement: %d m\n"
            "Total time: %.2f s\n",
            gravity_acceleration, displacement, total_time),
            850, 30, 20, BLACK
        );

    // //Projectiles -- constants
    // const double gravity_acceleration = 9.80665; //(m/^2)
    // const int displacement = (screen_width-100);

    // //Projectiles -- initial variables//
    // float angle = 30; // in degrees 
    // float height = screen_height/2;  
    // float speed_u = 10; // m/s 
    // float speed_v = 20;
    // float total_time = 5; // in seconds

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}