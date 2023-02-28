#include "Screen.h"

namespace code
{
    Screen::Screen() : m_window(NULL),
                       m_renderer(NULL),
                       m_texture(NULL),
                       m_buff1(NULL),
                       m_buff2(NULL)
    {
    }

    bool Screen::init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            return false;
        }
        m_window = SDL_CreateWindow("Particle Fire Explosion!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (m_window == NULL)
        {
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (m_renderer == NULL)
        {
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        if (m_texture == NULL)
        {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        m_buff1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        m_buff2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        
        memset(m_buff1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // 0xFF(easy to understand?) = 255;
        memset(m_buff2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // 0xFF(easy to understand?) = 255;
        /*for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        {
            m_buff[i] = 0x00000000;
        }*/

        return true;
    }
    void Screen::boxblur(){
    // swap the buffer so pixel is in buffer2 and we are drawinng to buffer 1.
        Uint32 *temp = m_buff1;
        m_buff1 = m_buff2;
        m_buff2 = temp;

        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                /*
                 0 0 0
                 0 1 0    giving 1 the average value
                 0 0 0*/

                int redtotal = 0;
                int greentotal = 0;
                int bluetotal = 0;
                // itrating for the pixel at 1's position
                for (int row = -1; row <= 1; row++)
                {
                    for (int col = -1; col <= 1; col++)
                    {
                        int currentx = x + col;
                        int currenty = y + row;
                        // checking so pixel doesn't take value from pixel out of edge of the screen
                        if (currentx >= 0 && currentx < SCREEN_WIDTH && currenty >= 0 && currenty < SCREEN_HEIGHT)
                        {
                            Uint32 color = m_buff2[currenty * SCREEN_WIDTH + currentx];

                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;

                            redtotal += red;
                            greentotal += green;
                            bluetotal += blue;
                        }
                    }
                }

                Uint8 red = redtotal / 9;
                Uint8 green = greentotal / 9;
                Uint8 blue = bluetotal / 9;

                setPixel(x, y, red, green, blue);
            }
        }
    }
    //void Screen::clear(){
    //    memset(m_buff, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    //}
    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
        
        if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT){
            return ;
        }
        
        Uint32 color =0;

        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;

        m_buff1[(y * SCREEN_WIDTH) + x] = color;  
    }
    void Screen::update()
    {
        SDL_UpdateTexture(m_texture, NULL, m_buff1, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);

    }
    bool Screen::processEvent()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return false;
            }
        }
        return true;
    }
    void Screen::close()
    {
        delete[] m_buff1;
        delete[] m_buff2;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

} /*namespace code*/
