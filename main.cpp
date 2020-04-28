//Made by Nick Gaston, Ryan Simas, Israel Avilez

#include <QApplication>

/*
 Things to add or consider:
 1. Intro screen / menu
 2. Outro screen once you have won the game
 3. Plate for paddle (current method is drawing a shape for paddle from img)
 */


int main(int argc, char *argv[]) //These are command-line parameters, argc means an array of c-string pointers and argv specifies the number of elements within argv or the number of c-string pointers pointed to by argv
{
    QApplication a(argc, argv);

    return a.exec(); //exec() functions replace the current process image with a new process image
}

