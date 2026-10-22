#include "raylib.h"
#include "button.hpp"
#include <iostream> 
#include <string>

//functions
int ExampleQuadFunc(int x){
    // int y = x*x;
    int y = x++;
    return y;
}

int main(){

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
    SetTargetFPS(50);
    int frames = 0;

    while(!WindowShouldClose()){

        Vector2 mouse_pos = GetMousePosition();
        bool mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        frames++;
        BeginDrawing();
        ClearBackground(WHITE);

        //changes to x and y of the particle
        particle_x++;
        particle_y = ExampleQuadFunc(particle_x);

        DrawCircle(particle_x, particle_y, 10,BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, BLACK);
        DrawLine(0, screen_height/2, screen_width, screen_height/2, BLACK);

        DrawRectangle(0, (screen_height - screen_height*1/4), screen_width, screen_height*1/4, GRAY);

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
            825, 30, 20, BLACK
        );

        //buttons 
        Button play_btn(1000, (screen_height - screen_height*1/4+20), 170, 80, GREEN, WHITE, GREEN, "PLAY", WHITE, 35);
        play_btn.Draw(mouse_pos, mouse_pressed);

        //Adding and subtracting 
        DrawText(TextFormat(
            "Height\n\n"
            "Angle\n\n"
            "Initial Speed"),
            20, (screen_height - screen_height*1/4+20), 20, BLACK
        );

        Button height_add_btn(90, (screen_height - screen_height*1/4+20), 25, 25, WHITE, GRAY, WHITE, "+", BLACK, 35);
        height_add_btn.Draw(mouse_pos,mouse_pressed);

        Button angle_add_btn(90, (screen_height - screen_height*1/4+65), 25, 25, WHITE, GRAY, WHITE, "+", BLACK, 35);
        angle_add_btn.Draw(mouse_pos,mouse_pressed);

        Button initial_speed_add_btn(159, (screen_height - screen_height*1/4+108), 25, 25, WHITE, GRAY, WHITE, "+", BLACK, 35);
        initial_speed_add_btn.Draw(mouse_pos,mouse_pressed);

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}