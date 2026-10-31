#include "raylib.h"
#include "button.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <functional>
#include <vector>

// //functions
// PROJECTILE X AND Y COORDINATE CALCULATIONS

float CalculteXInitialVelocity(int angle, float velocity)
{
    // initial speed (x component)
    return velocity * cos(PI / 180 * angle);
}

float CalculteYInitialVelocity(int angle, float velocity)
{
    // initial speed (y component)
    return velocity * sin(PI / 180 * angle);
}

float CalculateXPos(float velocity, float seconds)
{
    return seconds * velocity;
    // formula of s = ut + (1/2)at^2
}

float CalculateYPos(float velocity, float seconds, double gravity)
{
    return seconds * velocity - (0.5) * gravity * (seconds * seconds);
    // formula of s = ut + (1/2)at^2
}

float MetreToPixel(float metre)
{
    return metre * 10;
}

int main()
{
    std::cout << "Starting the 2D projectiles simulation" << std::endl;

    // constants
    const int screen_width = 1200;
    const int screen_height = 800;

    // Projectiles -- constants
    const double gravity_acceleration = 9.80665; //(m/^2)

    // Projectiles -- initial variables//
    float angle = 30;            // in degrees
    float initial_velocity = 30; // m/s

    // Particle center coordinates (starting)
    float initial_xPos = 35;
    float initial_yPos = screen_height / 2 + 150;

    float particle_x;
    float particle_y;

    float newXPos;
    float newYPos;

    InitWindow(screen_width, screen_height, "2D_Projectiles_Simulation");
    SetTargetFPS(60);
    bool play = false;
    bool landed = false;
    bool start = false;
    bool reset = false;

    float elapsed_time = 0;
    Texture2D mainScreen = LoadTexture("images/title_screen_2D.jpg");

    std::vector<float> x_trailVector;
    std::vector<float> y_trailVector;

    while (!WindowShouldClose())
    {
        Vector2 mouse_pos = GetMousePosition();
        bool mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // main title screen and start button
        BeginDrawing();
        ClearBackground(WHITE);

        if (start == false)
        {
            DrawTexture(mainScreen, 0, 0, WHITE);
            Button start_btn((screen_width / 2) - 60, (screen_height / 2) + 35, 170, 80, RED, PINK, RED, "START", WHITE, 35,
                             [&start]()
                             {
                                 start = true;
                             });
            start_btn.Draw(mouse_pos, mouse_pressed);
        }
        else
        {
            UnloadTexture(mainScreen);

            DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, BLACK);
            // DrawLine(0, screen_height/2, screen_width, screen_height/2, BLACK);
            DrawLine(0, screen_height / 2 + 150, screen_width, screen_height / 2 + 150, BLACK); // 55

            for (int i = 0; i < screen_width; i += 10)
            {
                DrawLine(i, screen_height / 2 + 150 - 10, i, screen_height / 2 + 150 + 10, BLACK);
            }

            DrawRectangle(0, (screen_height - screen_height * 1 / 4), screen_width, screen_height * 1 / 4, GRAY);

            DrawText(TextFormat(
                         "Angle of Trajectory: %.2f degrees\n"
                         "Initial Speed: %.2f m/s\n"
                         "(Angle)Recommended Min: 15, Max: 85\n"
                         "(Speed)Recommended Min: 30, Max: 90",
                         angle, initial_velocity),
                     20, 20, 20, BLACK);

            DrawText(TextFormat(
                         "Gravity Acceleration: %.5f m/s^2\n"
                         "Elapsed Time %.2f s\n",
                         gravity_acceleration, elapsed_time),
                     825, 30, 20, BLACK);

            // buttons
            Button play_btn(1000, (screen_height - screen_height * 1 / 4 + 20), 170, 80, GREEN, LIME, GREEN, "PLAY", WHITE, 35,
                            [&]()
                            {
                                elapsed_time = 0;
                                play = true;
                                landed = false;
                            });

            Button stop_btn(1000, (screen_height - screen_height * 1 / 4 + 20), 170, 80, RED, PINK, RED, "STOP", WHITE, 35,
                            [&play]()
                            {
                                play = false;
                            });

            if (play == false)
            {
                // reset == false;
                play_btn.Draw(mouse_pos, mouse_pressed);
            }
            else
            {
                stop_btn.Draw(mouse_pos, mouse_pressed);
            }

            Button reset_btn(1000, (screen_height - screen_height * 1 / 4 + 90), 170, 50, LIGHTGRAY, WHITE, LIGHTGRAY, "RESET SCREEN", BLACK, 20, [&reset](){
             
                reset = true;
            });
            
            reset_btn.Draw(mouse_pos, mouse_pressed);

            if(reset == true){

                x_trailVector.clear();
                y_trailVector.clear();
                reset = false;
            }

            // Adding and subtracting
            DrawText(TextFormat(
                         // "Height\n\n"
                         "Angle\n\n"
                         "Initial Speed"),
                     20, (screen_height - screen_height * 1 / 4 + 20), 20, BLACK);

            Button angle_add_btn(90, (screen_height - screen_height * 1 / 4 + 20), 25, 25, WHITE, GRAY, WHITE, "+", BLACK, 35,
                                 [&angle]()
                                 {
                                     angle += 5;
                                 });
            angle_add_btn.Draw(mouse_pos, mouse_pressed);

            Button angle_subtract_btn(130, (screen_height - screen_height * 1 / 4 + 20), 25, 25, WHITE, GRAY, WHITE, "-", BLACK, 35,
                                      [&angle]()
                                      {
                                          angle -= 5;
                                      });
            angle_subtract_btn.Draw(mouse_pos, mouse_pressed);

            Button initial_velocity_add_btn(159, (screen_height - screen_height * 1 / 4 + 63), 25, 25, WHITE, GRAY, WHITE, "+", BLACK, 35,
                                            [&initial_velocity]()
                                            {
                                                initial_velocity += 5;
                                            });
            initial_velocity_add_btn.Draw(mouse_pos, mouse_pressed);

            Button initial_velocity_subtract_btn(199, (screen_height - screen_height * 1 / 4 + 63), 25, 25, WHITE, GRAY, WHITE, "-", BLACK, 35,
                                                 [&initial_velocity]()
                                                 {
                                                     initial_velocity -= 5;
                                                 });
            initial_velocity_subtract_btn.Draw(mouse_pos, mouse_pressed);

            if (play && !landed)
            {
                float current_time = GetFrameTime();
                elapsed_time += current_time;
                newXPos = CalculateXPos(CalculteXInitialVelocity(angle, initial_velocity), elapsed_time);
                newYPos = CalculateYPos(CalculteYInitialVelocity(angle, initial_velocity), elapsed_time, gravity_acceleration);

                // std::cout<< newYPos;
                // calculate displacement for x,y -- convert to px to draw
                particle_x = initial_xPos + MetreToPixel(newXPos);
                particle_y = initial_yPos - MetreToPixel(newYPos);

                // velocity at a time
                float v;
                // v = u + at
                v = (CalculteYInitialVelocity(angle, initial_velocity)) + (-gravity_acceleration) * elapsed_time;

                // if the particle hits the ground and also the speed is negative(decreasing)
                // so the bool landed is not at the starting
                if (((particle_y + 10) >= initial_yPos) && (v < 0))
                {
                    std::cout << "LANDED!!!!" << std::endl;
                    particle_y = initial_yPos - 10;
                    landed = true;
                }

                // draw a dot to keep a trail of the circle's trajectory
                // every 10 px
                // use a vector to push coordinates and keep drawing every single trail

                x_trailVector.push_back(particle_x);
                y_trailVector.push_back(particle_y);

                for (int i = 0; i < x_trailVector.size(); i++)
                {
                    if (i % 5 == 0)
                    {
                        DrawCircle(x_trailVector[i], y_trailVector[i], 3, RED);
                    }
                }
            }
            else if (play && landed)
            {
                DrawRectangle(300, 250, 600, 250, LIGHTGRAY);
                DrawText(TextFormat(
                             "Total Time Taken: %.2fs\n\n"
                             "Total Displacement(x): %.2fpx",
                             elapsed_time, (particle_x - initial_xPos)),
                         350, 300, 25, BLACK);

                char arr[] = "FINISH!!!!";
                DrawText(arr, (screen_width / 2) - 120, screen_height / 2, 70, BLACK);
            }
            else if (!play)
            {
                // x_trailVector.clear();
                // y_trailVector.clear();
                landed = false;
                elapsed_time = 0;
                particle_x = initial_xPos;
                particle_y = initial_yPos;
            }

            DrawCircle(particle_x, particle_y, 10, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}