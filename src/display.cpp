#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "display.h"

Display::Display(int width, int height, const std::string &title)
{   
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
     
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // atleast 32 bits in buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    m_isClosed = false;

    GLenum status = glewInit();

    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize." << std::endl;
    } 
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit(); 
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed()
{
    return m_isClosed;
}

void Display::Update()

{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e; // container for os events

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            m_isClosed = true;
        }
    }
} 
