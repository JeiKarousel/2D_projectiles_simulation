#pragma once
#include "raylib.h"

// main class
class Button
{

public:
    int x_pos, y_pos, height, width;
    Color default_color, hover_color, pressed_color;

    // constructor
    Button(int x_pos, int y_pos, int width, int height, Color default_color, Color hover_color, Color pressed_color)
    {
        this->x_pos = x_pos;
        this->y_pos = y_pos;
        this->height = height;
        this->width = width;
        this->default_color = default_color;
        this->hover_color = hover_color;
        this->pressed_color = pressed_color;
    }
    // destructor
    ~Button()
    {
    }

    Rectangle rect = {x_pos, y_pos, width, height};

    // methods
    void Draw(Vector2 mouse_pos, bool mouse_pressed)
    {
        // pressed, hover then default
        if(is_pressed(mouse_pos, mouse_pressed, rect)){
            DrawRectangleRec(rect, pressed_color);
        }
        else if(is_hovered(mouse_pos, rect)){
            DrawRectangleRec(rect, hover_color);
        }
        else{
            DrawRectangleRec(rect, default_color);
        }
    }

    bool is_hovered(Vector2 mouse_pos, Rectangle rect){
        if (CheckCollisionPointRec(mouse_pos, rect)){
            return true; 
        }
        return false; 
    }

    bool is_pressed(Vector2 mouse_pos, bool mouse_pressed, Rectangle rect)
    {
        if (is_hovered( mouse_pos, rect) && mouse_pressed){
            return true; 
        }
        return false; 
    }
};

// subclass