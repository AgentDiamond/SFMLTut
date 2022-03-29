#include "Game.h"


int main()
{
    //Init Game engine
    Game game;
    
    //Game loop
    while (game.running())
    {
        //Update
        //Render
        window.clear(); //clear old frame
        window.display(); //tell aoo that window is done drawing



        return 0;
    }
}