#include "raylib.h"
#include "button.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <functional>

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

    float elapsed_time = 0;
    Texture2D mainScreen = LoadTexture("images/title_screen_2D.jpg");

    while (!WindowShouldClose())
    {
        Vector2 mouse_pos = GetMousePosition();
        bool mouse_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // main title screen and start button
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (start == false)
        {
            DrawTexture(mainScreen, 0,0, WHITE);
            Button start_btn(1000, (screen_height - screen_height * 1 / 4 + 20), 170, 80, RED, PINK, RED, "START", WHITE, 35,
                             [&start]()
                             {
                                 start = true;
                             });
            start_btn.Draw(mouse_pos, mouse_pressed);
        }
        else
        {
            UnloadTexture(mainScreen);

            if (play && !landed)
            {
                float current_time = GetFrameTime();
                elapsed_time += current_time;
                newXPos = CalculateXPos(CalculteXInitialVelocity(angle, initial_velocity), elapsed_time);
                newYPos = CalculateYPos(CalculteYInitialVelocity(angle, initial_velocity), elapsed_time, gravity_acceleration);

                // calculate displacement for x,y -- convert to px to draw
                particle_x = initial_xPos + MetreToPixel(newXPos);
                particle_y = initial_yPos - MetreToPixel(newYPos);

                if ((particle_y + 10) >= initial_yPos)
                {
                    particle_y = initial_yPos - 10;
                    landed = true;
                }
            }
            else if (!play)
            {
                landed = false;
                elapsed_time = 0;
                particle_x = initial_xPos;
                particle_y = initial_yPos;
            }
            else
            {
                DrawRectangle(300,300,600,300,WHITE);
                DrawText(TextFormat(
                         "Total Time Taken: %.2ftotal time\n\n"
                         "Total Displacement: %.2fdisplacement"),
                     20, (screen_height - screen_height * 1 / 4 + 20), 20, BLACK);
            }

            DrawCircle(particle_x, particle_y, 10, BLACK);

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
                play_btn.Draw(mouse_pos, mouse_pressed);
            }
            else
            {
                stop_btn.Draw(mouse_pos, mouse_pressed);
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

        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}