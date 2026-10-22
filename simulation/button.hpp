#pragma once
#include "raylib.h"
#include <string>

// main class
class Button
{

public:
    int x_pos, y_pos, height, width;
    Color default_color, hover_color, pressed_color, text_color;
    std::string txt;
    int font_size;
    Rectangle rect;

    // constructor
    // Button(int x_pos, int y_pos, int width, int height, Color default_color, Color hover_color, Color pressed_color, std::string txt, Color text_color, int font_size)
    // {
    //     this->x_pos = x_pos;
    //     this->y_pos = y_pos;
    //     this->height = height;
    //     this->width = width;
    //     this->default_color = default_color;
    //     this->hover_color = hover_color;
    //     this->pressed_color = pressed_color;
    //     this->txt = txt;
    //     this->text_color = text_color;
    //     this->font_size = font_size;
    // }
    Button(int x_pos, int y_pos, int width, int height, Color default_color, Color hover_color, Color pressed_color, std::string txt, Color text_color, int font_size) :
    x_pos(x_pos), y_pos(y_pos), width(width), height(height), default_color(default_color), hover_color(hover_color), pressed_color(pressed_color), txt(txt), text_color(text_color), font_size(font_size),
    rect{(int)x_pos, (int)y_pos, (int)width, (int)height}
    {
    }
    // destructor
    ~Button()
    {
    }

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
        DrawText(txt.c_str(), (x_pos + (width-MeasureText(txt.c_str(), font_size))/2), (y_pos + (height-font_size)/2), font_size, text_color);
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