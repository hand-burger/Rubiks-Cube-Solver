#pragma once

#include <iostream>
#include <string>
#include <array> // For std::array
#include <time.h> // For random number

using namespace std;

// Store the cube globally and then the turn functions can be void

array<array<array<int, 3>, 3>, 6> cube =
{ {
        // cube[0][0][0] would be the top left cubie on the yellow side
    { { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } } }, // Yellow side - Top side
    { { { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } } }, // Orange side - Left side
    { { { 2, 2, 2 },{ 2, 2, 2 },{ 2, 2, 2 } } }, // Blue side - Front side
    { { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } } }, // Red side - Right side
    { { { 4, 4, 4 },{ 4, 4, 4 },{ 4, 4, 4 } } }, // Green side - Back side
    { { { 5, 5, 5 },{ 5, 5, 5 },{ 5, 5, 5 } } }, // White side - Bottom side
} };

// Copy of cube
array<array<array<int, 3>, 3>, 6> copyOfCube = 
{ {
    { { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } } }, // Yellow side - Top side
    { { { 1, 1, 1 },{ 1, 1, 1 },{ 1, 1, 1 } } }, // Orange side - Left side
    { { { 2, 2, 2 },{ 2, 2, 2 },{ 2, 2, 2 } } }, // Blue side - Front side
    { { { 3, 3, 3 },{ 3, 3, 3 },{ 3, 3, 3 } } }, // Red side - Right side
    { { { 4, 4, 4 },{ 4, 4, 4 },{ 4, 4, 4 } } }, // Green side - Back side
    { { { 5, 5, 5 },{ 5, 5, 5 },{ 5, 5, 5 } } }, // White side - Bottom side
} };

// Function prototypes

// Cube rotations
void r();
void ri();

void l();
void li();

void u();
void ui();

void d();
void di();

void f();
void fi();

void b();
void bi();

// Rotate faces clockwise and counter clockwise
void fcw(int face);

void fccw(int face);

// Scramble the cube with random moves
void scramble();


// Solving functions
void solveYellowSide();

void moveYellowEdges();

void findYellowEdges(int &side, int &pos);

void solveYellowCorners();

void moveYellowCorners();

void findYellowCorners(int &side, int &pos);

void solveMiddle();

void positionMiddleEdge(int color, int edgeSide);

int findBottomMatch(int color);

void middleAlgorithm(int color, int direction);

void solveWhiteSide();

void positionWhiteCorners();

void positionWhiteEdges();

void solveWhiteCorners();

void solveWhiteEdges();

void swapCorners(int face);

int numCorrectCorners();

void getCorner(int num, int corners[]);

int numCorrectEdges();

void rotateEdges(int face, bool rotClockwise);

int cornerOrientation();

int findBestFace(int cornerNum);

void twoCornerRotate(int face, bool goForward);

void twoEdgeRotate(int face, bool isNextTo);

// Makes a copy of the cube
void copyCube();

// Print out the cube array
void printCube();

// Print out the cube array in a more readable format
void betterPrint();

// Tracks the number of moves performed
int numberOfMoves = 0;

int solveCube(array<array<array<int, 3>, 3>, 6> cubeInput)
{
    if (!cubeInput.empty())
    {
        bool valid = true;
        bool solved = true;

        cout << endl << "Cube from webcam input:" << endl;

        cube = cubeInput;

        betterPrint();

        // Check if the cube is valid
        for (size_t i = 0; i < cube.size(); ++i)
        {
            for (size_t j = 0; j < cube[0].size(); ++j)
            {
                for (size_t k = 0; k < cube[0][0].size(); ++k)
                {
                    if (cube[i][j][k] == -1)
                    {
                        valid = false;
                    }
                    else if (cube[i][j][k] != i)
                    {
                        solved = false;
                    }
                }
            }
        }

        if (!valid || solved)
        {
            cout << endl << "Invalid scan, please try again. The cube is either already solved or cannot be solved." << endl;
            return 0;
            cube = copyOfCube;
        }
    }
    else
    {
        // Scramble the cube and print it
        cout << "Scrambling cube..." << endl;
        scramble();
    }

    // Seed the random number generator
    // Explicitly cast to avoid loss in integer precision since it converts time, which is a long integer to an unsigned int
    srand((unsigned int)(time(NULL)));

    // String for user to input moves to turn the cube (When the controls aren't commented out)
    string function;

    // Reset the number of moves so that it doesn't count the scramble
    numberOfMoves = 0;
    cout << endl;
    //betterPrint();

    // Solve the yellow edges and print it
    cout << "Solving yellow edges" << endl;
    solveYellowSide();
    cout << endl;
    betterPrint();

    // Solve the yellow corners and print it
    cout << "Solving yellow corners" << endl;
    solveYellowCorners();
    cout << endl;
    betterPrint();

    // Solve the middle and print it
    cout << "Solving middle" << endl;
    solveMiddle();
    cout << endl;
    betterPrint();

    // Solve the white side and print it
    cout << "Solving white side" << endl;
    solveWhiteSide();
    cout << endl;
    betterPrint();

    cout << "Number of turns: " << numberOfMoves << endl;

    // Cube movement controls (if you want to turn the cube manually)
    // cout << "Enter a function to turn the cube (r, ri, l, li, u, ui, d, di, f, fi, b, bi): ";
    // cin >> function;
    /*while (function != "q")
    {
    solveYellowSide();
    betterPrint();
    cin >> function;
    if (function == "r")
    {
    r();
    }
    else if (function == "ri")
    {
    ri();
    }
    else if (function == "l")
    {
    l();
    }
    else if (function == "li")
    {
    li();
    }
    else if (function == "u")
    {
    u();
    }
    else if (function == "ui")
    {
    ui();
    }
    else if (function == "d")
    {
    d();
    }
    else if (function == "di")
    {
    di();
    }
    else if (function == "f")
    {
    f();
    }
    else if (function == "fi")
    {
    fi();
    }
    else if (function == "b")
    {
    b();
    }
    else if (function == "bi")
    {
    bi();
    }
    }*/

    return 0;
}

// Clockwise right side turn
void r()
{
    // Track the turn
    cout << "R ";
    numberOfMoves++;

    // Right, Front, Top, Back and Bottom will be modified

    // First make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Blue side becomes white
        cube[2][i][2] = copyOfCube[5][i][2];
        // Yellow side becomes blue
        cube[0][i][2] = copyOfCube[2][i][2];
        // Green side becomes yellow
        cube[4][i][0] = copyOfCube[0][2 - i][2];
        // White side becomes green
        cube[5][i][2] = copyOfCube[4][2 - i][0];
    }

    // Rotate the right side clockwise
    fcw(3);
}

// Counter clockwise right side turn
void ri()
{
    // Track the turn
    cout << "RI ";
    numberOfMoves++;
    // Right, Front, Top, Back and Bottom will be modified

    // First make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // White side becomes blue
        cube[5][i][2] = copyOfCube[2][i][2];
        // Blue side becomes yellow
        cube[2][i][2] = copyOfCube[0][i][2];
        // Yellow side becomes green
        cube[0][2 - i][2] = copyOfCube[4][i][0];
        // Green side becomes white
        cube[4][2 - i][0] = copyOfCube[5][i][2];
    }

    // Rotate the right side counter clockwise
    fccw(3);
}

// Clockwise left side turn
void l()
{
    // Track the turn
    cout << "L ";
    numberOfMoves++;
    // Left, Front, Top, Back and Bottom will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // White side becomes blue
        cube[5][i][0] = copyOfCube[2][i][0];
        // Blue side becomes yellow
        cube[2][i][0] = copyOfCube[0][i][0];
        // Yellow side becomes green
        cube[0][i][0] = copyOfCube[4][2 - i][2];
        // Green side becomes white
        cube[4][2 - i][2] = copyOfCube[5][i][0];
    }

    // Rotate the left side clockwise
    fcw(1);
}

// Counter clockwise left side turn
void li()
{
    // Track the turn
    cout << "LI ";
    numberOfMoves++;
    // Left, Front, Top, Back and Bottom will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Blue side becomes white
        cube[2][i][0] = copyOfCube[5][i][0];
        // Yellow side becomes blue
        cube[0][i][0] = copyOfCube[2][i][0];
        // Green side becomes yellow
        cube[4][i][2] = copyOfCube[0][2 - i][0];
        // White side becomes green
        cube[5][i][0] = copyOfCube[4][2 - i][2];
    }

    // Rotate the left side counter clockwise
    fccw(1);
}

// Clockwise up side turn
void u()
{
    // Track the turn
    cout << "U ";
    numberOfMoves++;
    // Top, Front, Back, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Orange side becomes blue
        cube[1][0][i] = copyOfCube[2][0][i];
        // Green side becomes orange
        cube[4][0][i] = copyOfCube[1][0][i];
        // Red side becomes green
        cube[3][0][i] = copyOfCube[4][0][i];
        // Blue side becomes red
        cube[2][0][i] = copyOfCube[3][0][i];
    }

    // Rotate the top side clockwise
    fcw(0);
}

// Counter clockwise up side turn
void ui()
{
    // Track the turn
    cout << "UI ";
    numberOfMoves++;
    // Top, Front, Back, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Blue side becomes orange
        cube[2][0][i] = copyOfCube[1][0][i];
        // Orange side becomes green
        cube[1][0][i] = copyOfCube[4][0][i];
        // Green side becomes red
        cube[4][0][i] = copyOfCube[3][0][i];
        // Red side becomes blue
        cube[3][0][i] = copyOfCube[2][0][i];
    }

    // Rotate the top side counter clockwise
    fccw(0);
}

// Clockwise down side turn
void d()
{
    // Track the turn
    cout << "D ";
    numberOfMoves++;
    // Bottom, Front, Back, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Blue side becomes orange
        cube[2][2][i] = copyOfCube[1][2][i];
        // Orange side becomes green
        cube[1][2][i] = copyOfCube[4][2][i];
        // Green side becomes red
        cube[4][2][i] = copyOfCube[3][2][i];
        // Red side becomes blue
        cube[3][2][i] = copyOfCube[2][2][i];
    }

    // Rotate the bottom side clockwise
    fcw(5);
}

// Counter clockwise down side turn
void di()
{
    // Track the turn
    cout << "DI ";
    numberOfMoves++;
    // Bottom, Front, Back, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Orange side becomes blue
        cube[1][2][i] = copyOfCube[2][2][i];
        // Green side becomes orange
        cube[4][2][i] = copyOfCube[1][2][i];
        // Red side becomes green
        cube[3][2][i] = copyOfCube[4][2][i];
        // Blue side becomes red
        cube[2][2][i] = copyOfCube[3][2][i];
    }

    // Rotate the bottom side counter clockwise
    fccw(5);
}

// Clockwise front side turn
void f()
{
    // Track the turn
    cout << "F ";
    numberOfMoves++;
    // Front, Top, Bottom, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Yellow side becomes orange
        cube[0][2][i] = copyOfCube[1][2 - i][2];
        // Red side becomes yellow
        cube[3][i][0] = copyOfCube[0][2][i];
        // White side becomes red
        cube[5][0][2 - i] = copyOfCube[3][i][0];
        // Orange side becomes white
        cube[1][2 - i][2] = copyOfCube[5][0][2 - i];
    }

    // Rotate the front side clockwise
    fcw(2);
}

// Counter clockwise front side turn
void fi()
{
    // Track the turn
    cout << "FI ";
    numberOfMoves++;
    // Front, Top, Bottom, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Orange side becomes yellow
        cube[1][i][2] = copyOfCube[0][2][2 - i];
        // Yellow side becomes red
        cube[0][2][2 - i] = copyOfCube[3][2 - i][0];
        // Red side becomes white
        cube[3][2 - i][0] = copyOfCube[5][0][i];
        // White side becomes orange
        cube[5][0][i] = copyOfCube[1][i][2];
    }

    // Rotate the front side counter clockwise
    fccw(2);
}

// Clockwise back side turn
void b()
{
    // Track the turn
    cout << "B ";
    numberOfMoves++;
    // Back, Top, Bottom, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Orange side becomes yellow
        cube[1][2 - i][0] = copyOfCube[0][0][i];
        // Yellow side becomes red
        cube[0][0][i] = copyOfCube[3][i][2];
        // Red side becomes white
        cube[3][i][2] = copyOfCube[5][2][2 - i];
        // White side becomes orange
        cube[5][2][2 - i] = copyOfCube[1][2 - i][0];
    }

    // Rotate the back side clockwise
    fcw(4);
}

// Counter clockwise back side turn
void bi()
{
    // Track the turn
    cout << "BI ";
    numberOfMoves++;
    // Back, Top, Bottom, Left and Right will be modified

    // First, make a copy of the current cube to be able to refer to when performing moves
    copyCube();

    for (int i = 0; i < 3; i++)
    {
        // Yellow side becomes orange
        cube[0][0][i] = copyOfCube[1][2 - i][0];
        // Red side becomes yellow
        cube[3][i][2] = copyOfCube[0][0][i];
        // White side becomes red
        cube[5][2][2 - i] = copyOfCube[3][i][2];
        // Orange side becomes white
        cube[1][2 - i][0] = copyOfCube[5][2][2 - i];
    }

    // Rotate the back side counter clockwise
    fccw(4);
}

// Take in the face of the cube and rotate the face clockwise
// The position of the edges and the corners are always the same, so we only need to take in the face number and rotate that face clockwise
void fcw(int face)
{
    cube[face][0][0] = copyOfCube[face][2][0];
    cube[face][0][1] = copyOfCube[face][1][0];
    cube[face][0][2] = copyOfCube[face][0][0];
    cube[face][1][0] = copyOfCube[face][2][1];
    cube[face][1][2] = copyOfCube[face][0][1];
    cube[face][2][0] = copyOfCube[face][2][2];
    cube[face][2][1] = copyOfCube[face][1][2];
    cube[face][2][2] = copyOfCube[face][0][2];
}

// Take in the face of the cube and rotate the face counter clockwise
// The position of the edges and the corners are always the same, so we only need to take in the face number and rotate that face counter clockwise
void fccw(int face)
{
    cube[face][0][0] = copyOfCube[face][0][2];
    cube[face][0][2] = copyOfCube[face][2][2];
    cube[face][0][1] = copyOfCube[face][1][2];
    cube[face][1][0] = copyOfCube[face][0][1];
    cube[face][1][2] = copyOfCube[face][2][1];
    cube[face][2][0] = copyOfCube[face][0][0];
    cube[face][2][1] = copyOfCube[face][1][0];
    cube[face][2][2] = copyOfCube[face][2][0];
}

void scramble()
{
    int moveRandomizer;
    // Perform 18 moves to scramble
    // That's usually enough to get a cube in a good state
    for (int i = 0; i < 18; i++)
    {
        moveRandomizer = rand() % 12;
        switch (moveRandomizer)
        {
        case 0:
            r();
            break;
        case 1:
            ri();
            break;
        case 2:
            l();
            break;
        case 3:
            li();
            break;
        case 4:
            u();
            break;
        case 5:
            ui();
            break;
        case 6:
            d();
            break;
        case 7:
            di();
            break;
        case 8:
            f();
            break;
        case 9:
            fi();
            break;
        case 10:
            b();
            break;
        case 11:
            bi();
            break;
        default:
            break;
        }
    }
}

// Now onto some actual solving things

void solveYellowSide()
{
    // Move any yellow edges out of the yellow side if they exist so that we don't need to check for them later if they're hiding up there
    moveYellowEdges();

    // Solve the yellow edges

    // Loop through each side excluding yellow since all the edges were already moved out
    for (int i = 1; i < 5; i++)
    {
        // Side and position of the edge
        int side = 0, pos = 0;

        // Track the number of turns to put pieces in white layer
        int upMoves = 0;

        // Find an edge to position it
        findYellowEdges(side, pos);
        // Now based on the side which it is on, position it correctly
        // Yellow edge on blue side
        if (side == 1)
        {
            // Get an open slot to put an edge
            while (cube[5][1][0] == 0)
            {
                d();
            }

            // Position the yellow edge
            while (cube[0][1][0] == 0)
            {
                u();
                upMoves++;
            }

            // Now position it based on the position
            if (pos == 1)
            {
                l();
                l();
            }
            else if (pos == 2)
            {
                l();
            }
            else if (pos == 4)
            {
                li();
            }
        }
        // Yellow edge on red side
        else if (side == 2)
        {
            // Get an open slot to put an edge
            while (cube[5][0][1] == 0)
            {
                d();
            }

            // Position the yellow edge
            while (cube[0][2][1] == 0)
            {
                u();
                upMoves++;
            }

            // Now position it based on the position
            if (pos == 1)
            {
                f();
                f();
            }
            else if (pos == 2)
            {
                f();
            }
            else if (pos == 4)
            {
                fi();
            }
            di();
        }
        // Yellow edge on green side
        else if (side == 3)
        {
            // Get an open slot to put an edge
            while (cube[5][1][2] == 0)
            {
                d();
            }

            // Position the yellow edge
            while (cube[0][1][2] == 0)
            {
                u();
                upMoves++;
            }

            // Now position it based on the position
            if (pos == 1)
            {
                r();
                r();
            }
            else if (pos == 2)
            {
                r();
            }
            else if (pos == 4)
            {
                ri();
            }
            d();
            d();
        }
        // Yellow edge on orange side
        else if (side == 4)
        {
            // Get an open slot to put an edge
            while (cube[5][2][1] == 0)
            {
                d();
            }

            // Position the yellow edge
            while (cube[0][0][1] == 0)
            {
                u();
                upMoves++;
            }

            // Now position it based on the position
            if (pos == 1)
            {
                b();
                b();
            }
            else if (pos == 2)
            {
                b();
            }
            else if (pos == 4)
            {
                bi();
            }
            d();
        }
        // Yellow edge on white side
        else if (side == 5)
        {
            for (int j = 0; j < 4 - pos; j++)
            {
                d();
            }
        }

        // Reverse up moves
        for (int j = 0; j < upMoves; j++)
        {
            ui();
        }

        // Now put the edges on the yellow side

        // If yellow edge is on the bottom (white side)
        if (side == 5)
        {
            // Find the color of the current edge
            int color = cube[1][2][1];

            // Set up into the correct spot
            for (int j = 1; j < color; j++)
            {
                u();
            }
            // Move into position
            l();
            l();
            // Undo the setup
            for (int j = 1; j < color; j++)
            {
                ui();
            }
        }

        // If yellow edge is on any other side
        else
        {
            int color = cube[5][1][0];
            if (color < 4)
            {
                // Set up into the correct spot
                for (int j = 1; j < color + 1; j++)
                {
                    u();
                }
            }
            // Move into position
            l();
            bi();
            li();
            if (color < 4)
            {
                // Undo the set up
                for (int j = 1; j < color + 1; j++)
                {
                    ui();
                }
            }
        }
    }
}

void moveYellowEdges()
{
    // Loop through the edges
    for (int i = 0; i < 4; i++)
    {
        // If there is a yellow edge in position
        if (cube[0][0][1] == 0)
        {
            // Get an open spot for a yellow edge
            // If the receiving spot it already yellow, move over
            while (cube[5][2][1] == 0)
            {
                d();
            }
            // Bring it down
            f();
            f();
        }
        // Then move to the next edge
        u();
    }
    cout << endl;
}

void findYellowEdges(int &side, int &pos)
{
    // Loop through the edges and find the yellow edges
    // Then once an edge is found set the side and position variables to be able to perform the correct moves
    for (side = 1; side < 6; side++)
    {
        if (cube[side][0][1] == 0)
        {
            pos = 1;
            break;
        }
        if (cube[side][1][2] == 0)
        {
            pos = 2;
            break;
        }
        if (cube[side][1][0] == 0)
        {
            pos = 4;
            break;
        }
    }
}

void solveYellowCorners()
{
    // Move any yellow corners to the bottom
    moveYellowCorners();
    for (int i = 1; i < 5; i++)
    {
        // Side and position of a yellow corner
        int side = 0;
        // Use the position to know which moves to perform
        int pos = 0;

        // If a yellow corner is on the bottom
        bool bottom = false;

        // If a yellow corner is on the right side
        bool right = false;

        // Find a yellow corner to solve
        findYellowCorners(side, pos);

        // Put the corner in the back bottom right corner
        if (side < 5)
        {
            if (pos == 2)
            {
                right = true;
            }
            for (int j = 0; j < side + pos - 1; j++)
            {
                di();
            }
        }
        // If the corner is on the bottom (side == 5)
        else
        {
            bottom = true;
            for (int j = 0; j < pos; j++)
            {
                di();
            }
        }

        // Yellow corner on the right side
        if (right)
        {
            int color = cube[4][2][0];

            // Set up into the correct spot
            if (color < 4)
            {
                for (int j = 0; j < color; j++)
                {
                    u();
                }
            }

            // Move into position
            r();
            d();
            ri();

            // Undo the set up
            if (color < 4)
            {
                for (int j = 0; j < color; j++)
                {
                    ui();
                }
            }
        }

        // Yellow corner on bottom
        else if (bottom)
        {
            int color = cube[3][2][2];

            // Set up into the correct spot
            if (color < 4)
            {
                for (int j = 0; j < color; j++)
                {
                    u();
                }
            }

            // Move into position
            r();
            d();
            d();
            ri();
            di();
            r();
            d();
            ri();

            // Undo set up moves
            if (color < 4)
            {
                for (int j = 0; j < color; j++)
                {
                    ui();
                }
            }
        }

        // Yellow corner on back
        else
        {
            int color = cube[5][2][2];

            // Set up into the correct spot
            if (color < 4)
            {
                for (int j = 0; j < color; j++)
                {
                    u();
                }
            }

            // Move into position
            bi();
            di();
            b();

            // Undo set up moves
            if (color < 4)
            {
                for (int j = 0; j < color; j++)
                {
                    ui();
                }
            }
        }
    }
}


// Move any yellow corners on the yellow side to the white side
void moveYellowCorners()
{
    // Loop over each corner
    for (int i = 0; i < 4; i++)
    {
        if (cube[0][2][2] == 0 || cube[2][0][2] == 0 || cube[3][0][0] == 0)
        {
            // Check all to ensure that another corner isn't put back into the yellow side
            while (cube[1][2][2] == 0 || cube[2][2][0] == 0 || cube[5][0][0] == 0)
            {
                // Find open slot
                d();
            }

            // Put the corner into position
            ri();
            d();
            r();
        }

        // Move to the next corner
        u();
    }
}

// Find the next yellow corner that is not in the correct position
// Updates the side and position to correspond to it
void findYellowCorners(int &side, int &pos)
{
    // Check each side, except for yellow since they were already moved out
    for (side = 1; side < 5; side++)
    {
        if (cube[side][2][0] == 0)
        {
            pos = 1;
            return;
        }
        else if (cube[side][2][2] == 0)
        {
            pos = 2;
            return;
        }
    }
    // Check each corner position and update the position
    if (cube[5][0][0] == 0)
    {
        pos = 2;
    }
    else if (cube[5][0][2] == 0)
    {
        pos = 3;
    }
    else if (cube[5][2][2] == 0)
    {
        pos = 0;
    }
    else
    {
        pos = 1;
    }
}

void solveMiddle()
{
    // Side and color of a middle edge
    int side = -1;
    int color = -1;

    // The number of correct edges
    int count = 0;

    // Slightly jank go to statement, but it works perfectly for this application and it exists, so I may as well use it?
beginning:
    // Edge is found
    if (side != -1)
    {
        // Move the edge to the correct position
        positionMiddleEdge(color, side);
        // Number of correct edges++
        count++;
        // Reset the side and color
        side -= 1;
        color = -1;
    }

    // Check each side
    for (int i = 1; i <= 4; i++)
    {
        // Find an edge that is not in the correct position
        side = findBottomMatch(i);

        // Edge is found
        if (side != -1)
        {
            // Set the color to the side it was found on
            color = i;
            goto beginning;
        }
    }

    // If no edge found yet, check each side
    for (int i = 1; i <= 4; i++)
    {
        // If there isn't an edge on the side, continue
        if (cube[i][1][0] != (i))
        {
            // Perform the middle algorithm
            middleAlgorithm(i, 1);

            // If too much action
            if (count >= 15)
            {
                // Resolve the yellow side
                solveYellowSide();
                solveYellowCorners();
            }

            // Back to the top
            goto beginning;
        }

        // If there isn't an edge on the side, continue
        else if (cube[i][1][2] != i)
        {
            // Perform the middle algorithm
            middleAlgorithm(i, 2);

            // If too much action
            if (count >= 10)
            {
                // Resolve the yellow side
                solveYellowSide();
                solveYellowCorners();
            }

            goto beginning;
        }
    }
}

// Find the matching edge on the bottom
int findBottomMatch(int color)
{
    // Check each side
    for (int i = 1; i <= 4; i++)
    {
        // If the edge is correct, continue
        if (cube[i][2][1] == color)
        {
            // If it's an even numbered side
            if (i % 2 == 0)
            {
                // And if the white side is open
                if (cube[5][abs(2 - i)][1] != 5)
                {
                    // Return the side
                    return i;
                }

            }
            // If it's an odd numbered side
            else
            {
                // And if the white side is open
                if (cube[5][abs(2 - i)][i - 1] != 5)
                {
                    // Return the side
                    return i;
                }

            }
        }
    }
    // If no edge found, return -1
    return -1;
}

// Put the middle edge in the correct position
void positionMiddleEdge(int color, int edgeSide)
{
    // If the edge is already on the right side
    if (edgeSide - color == 0)
    {
        // Perform the middle algorithm
        middleAlgorithm(color, -1);
    }
    // If the edge is one off
    else if (edgeSide - color == 1)
    {
        // Set up and perform the middle algorithm
        di();
        middleAlgorithm(color, -1);
    }
    // If the edge is two off
    else if (edgeSide - color == 2)
    {
        // Set up and perform the middle algorithm
        di();
        di();
        middleAlgorithm(color, -1);
    }
    // If the edge is three off
    else if (edgeSide - color == 3)
    {
        // Set up and perform the middle algorithm
        d();
        middleAlgorithm(color, -1);
    }
    // If the edge is four off
    else if (edgeSide - color == -1)
    {
        // Set up and perform the middle algorithm
        d();
        middleAlgorithm(color, -1);
    }
    // If the edge is five off
    else if (edgeSide - color == -2)
    {
        // Set up and perform the middle algorithm
        d();
        d();
        middleAlgorithm(color, -1);
    }
    // If the edge is six off
    else if (edgeSide - color == -3)
    {
        // Set up and perform the middle algorithm
        di();
        middleAlgorithm(color, -1);
    }
}

// Solve the middle edges
void middleAlgorithm(int color, int direction)
{
    // If the edge is on the orange side
    if (color == 1)
    {
        // If direction is 1 or the edge spot is green
        if (cube[5][1][0] == 4 || direction == 1)
        {
            // Solve
            d();
            b();
            di();
            bi();
            di();
            li();
            d();
            l();
        }
        // If direction is 2 or the edge spot is blue
        else if (cube[5][1][0] == 2 || direction == 2)
        {
            // Solve
            di();
            fi();
            d();
            f();
            d();
            l();
            di();
            li();
        }
    }
    // If the edge is on the blue side
    else if (color == 2)
    {
        // If direction is 1 or the edge spot is orange
        if (cube[5][0][1] == 1 || direction == 1)
        {
            // Solve
            d();
            l();
            di();
            li();
            di();
            fi();
            d();
            f();
        }
        // If direction is 2 or the edge spot is red
        else if (cube[5][0][1] == 3 || direction == 2)
        {
            // Solve
            di();
            ri();
            d();
            r();
            d();
            f();
            di();
            fi();
        }
    }
    // If the edge is on the red side
    else if (color == 3)
    {
        // If direction is 1 or the edge spot is blue
        if (cube[5][1][2] == 2 || direction == 1)
        {
            // Solve
            d();
            f();
            di();
            fi();
            di();
            ri();
            d();
            r();
        }
        // If direction is 2 or the edge spot is green
        else if (cube[5][1][2] == 4 || direction == 2)
        {
            // Solve
            di();
            bi();
            d();
            b();
            d();
            r();
            di();
            ri();
        }
    }
    // If the edge is on the green side
    else if (color == 4)
    {
        // If direction is 1 or the edge spot is red
        if (cube[5][2][1] == 3 || direction == 1)
        {
            d();
            r();
            di();
            ri();
            di();
            bi();
            d();
            b();
        }
        // If direction is 2 or the edge spot is orange
        else if (cube[5][2][1] == 1 || direction == 2)
        {
            di();
            li();
            d();
            l();
            d();
            b();
            di();
            bi();
        }
    }
}

// Do all these functions to solve the white side
void solveWhiteSide()
{
    // Get all the white corners and edges in the correct position to be able to be solved
    positionWhiteCorners();
    positionWhiteEdges();
    // Then solve them
    solveWhiteCorners();
    solveWhiteEdges();
}

void positionWhiteCorners()
{
    // Store the
    int dTurns[4];

    int bestNumDTurns = 0;
    int pos1 = -1;
    int pos2 = -1;

    for (int i = 0; i < 4; i++)
    {
        dTurns[i] = numCorrectCorners();

        if (dTurns[i] == 4)
        {
            pos1 = 4;
            bestNumDTurns = i;
            break;
        }
        else if (dTurns[i] < 4 && dTurns[i] > -1)
        {
            if (pos2 == -1)
            {
                pos1 = dTurns[i];
                bestNumDTurns = i;
            }
        }
        else if (dTurns[i] > 4)
        {
            int side1 = dTurns[i] % 10 + 1;
            int side2 = (int)(dTurns[i] / 10) + 1;

            // If the corners are beside each other
            if (side2 == (side1 + 1) || side1 == (side2 + 1) || (side2 == 4 && side1 == 1) || (side2 == 1 && side1 == 4))
            {
                pos1 = side1;
                pos2 = side2;
                bestNumDTurns = i;
            }
            else if (pos2 == -1)
            {
                pos1 = side1;
                pos2 = side2;
                bestNumDTurns = i;
            }
        }
        d();
    }

    for (int i = 0; i < bestNumDTurns && pos1 != 4; i++)
    {
        d();
    }

    // Now actually position the corners

    if (pos1 == 4)
    {
        return;
    }
    else if (pos2 != -1 && (pos2 == (pos1 + 1) || pos1 == (pos2 + 1) || (pos2 == 4 && pos1 == 1) || (pos2 == 1 && pos1 == 4)))
    {
        int oppFace = pos2 + 3;

        if (oppFace > 4)
        {
            oppFace -= 4;
        }

        swapCorners(oppFace);
        positionWhiteCorners();
        return;
    }
    else if (pos2 != -1)
    {
        int face = pos1 + 4;

        if (face > 4)
        {
            face -= 4;
        }

        int face2 = face + 1;
        if (face2 > 4)
        {
            face2 -= 4;
        }

        swapCorners(face);
        swapCorners(face2);
        swapCorners(face);
        positionWhiteCorners();
        return;
    }
    else
    {
        int face = pos1 + 2;

        if (face > 4)
        {
            face -= 4;
        }

        swapCorners(face);
        positionWhiteCorners();
        return;
    }

}

int numCorrectCorners()
{
    int cornerColors[3];
    int side1 = 0;
    int side2 = 0;

    int count = 0;

    int colorsMatch = 0;
    int position[4] = { -1, -1, -1, -1 };

    for (int i = 0; i < 4; i++)
    {
        getCorner(i, cornerColors);

        side1 = i + 1;
        side2 = i + 2;

        if (side2 == 5)
        {
            side2 = 1;
        }

        for (int j = 0; j < 3; j++)
        {
            if (cornerColors[j] == side1 || cornerColors[j] == side2)
            {
                colorsMatch++;
            }

        }

        if (colorsMatch == 2)
        {
            position[i] = 1;
            count++;
        }

        colorsMatch = 0;
    }

    int pos = 0;
    int multiplier = 1;

    if (count == 4)
    {
        return 4;
    }
    else if (count == 2 || count == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (position[i] == 1)
            {
                pos += i * multiplier;
                multiplier *= 10;
            }

        }
    }
    else
    {
        pos = -1;
    }

    return pos;
}

// Pre-defined moves to swap corners, given the face
void swapCorners(int face)
{
    // If the face is 1
    if (face == 1)
    {
        // Swap the corners
        di();
        fi();
        d();
        b();
        di();
        f();
        d();
        bi();
        di();
    }
    // If the face is 2
    else if (face == 2)
    {
        // Swap the corners
        di();
        ri();
        d();
        l();
        di();
        r();
        d();
        li();
        di();
    }
    // If the face is 3
    else if (face == 3)
    {
        // Swap the corners
        di();
        bi();
        d();
        f();
        di();
        b();
        d();
        fi();
        di();
    }
    // If the face is 4
    else if (face == 4)
    {
        // Swap the corners
        di();
        li();
        d();
        r();
        di();
        l();
        d();
        ri();
        di();
    }
}

void getCorner(int num, int corners[])
{
    if (num == 0)
    {
        corners[0] = cube[1][2][2];
        corners[1] = cube[2][2][0];
        corners[2] = cube[5][0][0];
    }
    else if (num == 1)
    {
        corners[0] = cube[2][2][2];
        corners[1] = cube[3][2][0];
        corners[2] = cube[5][0][2];
    }
    else if (num == 2)
    {
        corners[0] = cube[3][2][2];
        corners[1] = cube[4][2][0];
        corners[2] = cube[5][2][2];
    }
    else if (num == 3)
    {
        corners[0] = cube[4][2][2];
        corners[1] = cube[1][2][0];
        corners[2] = cube[5][2][0];
    }
}

void positionWhiteEdges()
{
    // Get the number of correct edges
    int pos = numCorrectEdges();

    if (pos == 0)
    {
        rotateEdges(2, true);
        positionWhiteEdges();
        return;
    }
    else if (pos == 5)
    {
        return;
    }
    else
    {
        bool clockwise = pos > 0;

        int face = abs(pos) + 1;

        if (face > 4)
        {
            face -= 4;
        }

        rotateEdges(face, clockwise);
        return;
    }
}

int numCorrectEdges()
{
    int edges[4][2] = { { cube[5][1][0], cube[1][2][1] },{ cube[5][0][1], cube[2][2][1] },{ cube[5][1][2], cube[3][2][1] },{ cube[5][2][1], cube[4][2][1] } };

    int correctPos = -1;
    int numCorrect = 0;
    bool isOneCorrect = false;
    int positions[4];

    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (edges[i - 1][j] == i)
            {
                isOneCorrect = true;
                correctPos = i - 1;
                numCorrect++;
            }

            if (edges[i - 1][j] != 5)
            {
                positions[i - 1] = edges[i - 1][j];
            }
        }
    }

    if (numCorrect == 4)
    {
        return 5;
    }

    if (!isOneCorrect)
    {
        return 0;
    }
    else
    {
        bool clockwise = false;
        bool firstTime = true;
        int numTimesThrough = 0;
        numCorrect = 0;
        int temp;
        int temp2;

        while (numCorrect != 4)
        {
            firstTime = true;
            numCorrect = 0;
            for (int i = 0; i < 4; i++)
            {
                if (i != correctPos)
                {
                    if (firstTime)
                    {
                        firstTime = false;
                        temp = positions[i];

                        int j = i - 1;

                        if (j < 0)
                        {
                            j += 4;
                        }
                        if (j == correctPos)
                        {
                            j--;
                            if (j < 0)
                            {
                                j += 4;
                            }
                        }

                        positions[i] = positions[j];
                    }
                    else
                    {
                        temp2 = positions[i];
                        positions[i] = temp;
                        temp = temp2;
                    }
                }

                if (positions[i] == i + 1)
                {
                    numCorrect++;
                }
            }

            numTimesThrough++;
        }

        clockwise = numTimesThrough == 1;
        correctPos++;

        if (!clockwise)
        {
            correctPos = -1 * (correctPos);
        }
    }

    return correctPos;
}

void rotateEdges(int face, bool rotClockwise)
{
    if (face == 1)
    {
        if (rotClockwise)
        {
            f();
            f();
            d();
            li();
            r();
            f();
            f();
            l();
            ri();
            d();
            f();
            f();
        }
        else
        {
            f();
            f();
            di();
            li();
            r();
            f();
            f();
            l();
            ri();
            di();
            f();
            f();
        }
    }
    else if (face == 2)
    {
        if (rotClockwise)
        {
            r();
            r();
            d();
            fi();
            b();
            r();
            r();
            f();
            bi();
            d();
            r();
            r();
        }
        else
        {
            r();
            r();
            di();
            fi();
            b();
            r();
            r();
            f();
            bi();
            di();
            r();
            r();
        }
    }
    else if (face == 3)
    {
        if (rotClockwise)
        {
            b();
            b();
            d();
            ri();
            l();
            b();
            b();
            r();
            li();
            d();
            b();
            b();
        }
        else
        {
            b();
            b();
            di();
            ri();
            l();
            b();
            b();
            r();
            li();
            di();
            b();
            b();
        }
    }
    else if (face == 4)
    {
        if (rotClockwise)
        {
            l();
            l();
            d();
            bi();
            f();
            l();
            l();
            b();
            fi();
            d();
            l();
            l();
        }
        else
        {
            l();
            l();
            di();
            bi();
            f();
            l();
            l();
            b();
            fi();
            di();
            l();
            l();
        }
    }
}

void solveWhiteCorners()
{
    int result = cornerOrientation();

    while (result != 5)
    {
        twoCornerRotate(abs(findBestFace(result)), findBestFace(result) > 0);

        result = cornerOrientation();
    }
}

int cornerOrientation()
{
    int numCorrect = 0;
    int wrongPosition = 0;

    int corners[4] = { cube[5][0][0], cube[5][0][2], cube[5][2][2], cube[5][2][0] };

    // Loop over and check if the corners are in the correct position
    for (int i = 0; i < 4; i++)
    {
        if (corners[i] == 5)
        {
            numCorrect++;
        }
        else
        {
            wrongPosition = i;
        }
    }

    // If all the corners are in the right position
    if (numCorrect == 4)
    {
        return 5;
    }

    return wrongPosition;
}

int findBestFace(int cornerNum)
{
    int corners[4] = { cube[5][0][0], cube[5][0][2], cube[5][2][2], cube[5][2][0] };

    int corner1 = cornerNum + 1;
    int corner2 = cornerNum - 1;

    if (corner1 > 3)
    {
        corner1 = 4 - corner1;
    }

    if (corner2 < 0)
    {
        corner2 += 4;
    }

    int finalCorner = -1;
    int face = -1;

    if (corners[cornerNum] == corners[corner1])
    {
        finalCorner = corner1;

        face = corners[finalCorner] + 1;

        if (face > 4)
        {
            face -= 4;
        }

        return face;
    }
    else if (corners[cornerNum] == corners[corner2])
    {
        finalCorner = corner2;

        face = corners[finalCorner] + 1;

        if (face > 4)
        {
            face -= 4;
        }

        return face;
    }
    else if (abs(corners[cornerNum] - corners[corner1]) == 2 && corners[corner1] != 5)
    {
        finalCorner = corner1;
        face = corners[cornerNum];
        return -face;
    }
    else if (abs(corners[cornerNum] - corners[corner2]) == 2 && corners[corner2] != 5)
    {
        finalCorner = corner2;
        face = corners[cornerNum];
        return -face;
    }
    else
    {
        face = corners[cornerNum];
        return face;
    }
}

void twoCornerRotate(int face, bool goForward)
{
    if (face == 1)
    {
        if (goForward)
        {
            bi();
            u();
            b();
            l();
            u();
            li();
            d();
            l();
            ui();
            li();
            bi();
            ui();
            b();
            di();
        }
        else
        {
            d();
            bi();
            u();
            b();
            l();
            u();
            li();
            di();
            l();
            ui();
            li();
            bi();
            ui();
            b();
        }
    }
    else if (face == 2)
    {
        if (goForward)
        {
            li();
            u();
            l();
            f();
            u();
            fi();
            d();
            f();
            ui();
            fi();
            li();
            ui();
            l();
            di();
        }
        else
        {
            d();
            li();
            u();
            l();
            f();
            u();
            fi();
            di();
            f();
            ui();
            fi();
            li();
            ui();
            l();
        }
    }
    else if (face == 3)
    {
        if (goForward)
        {
            fi();
            u();
            f();
            r();
            u();
            ri();
            d();
            r();
            ui();
            ri();
            fi();
            ui();
            f();
            di();
        }
        else
        {
            d();
            fi();
            u();
            f();
            r();
            u();
            ri();
            di();
            r();
            ui();
            ri();
            fi();
            ui();
            f();
        }
    }
    else if (face == 4)
    {
        if (goForward)
        {
            ri();
            u();
            r();
            b();
            u();
            bi();
            d();
            b();
            ui();
            bi();
            ri();
            ui();
            r();
            di();
        }
        else
        {
            d();
            ri();
            u();
            r();
            b();
            u();
            bi();
            di();
            b();
            ui();
            bi();
            ri();
            ui();
            r();
        }
    }
}

// Position the white edges
void solveWhiteEdges()
{
    // List of the white edges
    int edges[4] = { cube[5][1][0], cube[5][0][1], cube[5][1][2], cube[5][2][1] };

    bool isTogether = false;
    bool isStart = false;
    int numWrong = 0;

    // Positions of the two edges
    int pos1 = -1;
    int pos2 = -1;
    int j = 0;

    for (int i = 0; i < 5; i++)
    {
        j = i;

        if (i == 4)
        {
            j = 0;
        }

        if (edges[j] != 5)
        {
            numWrong++;
            if (!isStart)
            {
                pos1 = j;
                isStart = true;
            }
            else
            {
                pos2 = j;
                isTogether = true;
            }
        }
        else
        {
            isStart = false;
        }
    }

    if (numWrong >= 4)
    {
        twoEdgeRotate(1, false);
        twoEdgeRotate(2, false);
        return;
    }
    else
    {
        if (pos2 != -1)
        {
            twoEdgeRotate(pos2 + 1, isTogether);
        }
        else
        {
            twoEdgeRotate(pos1 + 1, isTogether);
        }
        return;
    }
}

// Takes in the face and if the edges are together, then swaps the edges
void twoEdgeRotate(int face, bool isNextTo)
{
    // Use the face and if the edges are together and a set of pre-defined moves to solve the edges
    if (face == 1)
    {
        if (isNextTo)
        {
            l();
            ui();
            d();
            f();
            f();
            d();
            d();
            u();
            u();
            b();
            d();
            bi();
            u();
            u();
            d();
            d();
            f();
            f();
            di();
            u();
            li();
            di();
        }
        else
        {
            l();
            ui();
            d();
            f();
            f();
            d();
            d();
            u();
            u();
            b();
            d();
            d();
            bi();
            u();
            u();
            d();
            d();
            f();
            f();
            di();
            u();
            li();
            di();
            di();
        }
    }
    else if (face == 2)
    {
        if (isNextTo)
        {
            f();
            ui();
            d();
            r();
            r();
            d();
            d();
            u();
            u();
            l();
            d();
            li();
            u();
            u();
            d();
            d();
            r();
            r();
            di();
            u();
            fi();
            di();
        }
        else
        {
            f();
            ui();
            d();
            r();
            r();
            d();
            d();
            u();
            u();
            l();
            d();
            d();
            li();
            u();
            u();
            d();
            d();
            r();
            r();
            di();
            u();
            fi();
            di();
            di();
        }
    }
    if (face == 3)
    {
        if (isNextTo)
        {
            r();
            ui();
            d();
            b();
            b();
            d();
            d();
            u();
            u();
            f();
            d();
            fi();
            u();
            u();
            d();
            d();
            b();
            b();
            di();
            u();
            ri();
            di();
        }
        else
        {
            r();
            ui();
            d();
            b();
            b();
            d();
            d();
            u();
            u();
            f();
            d();
            d();
            fi();
            u();
            u();
            d();
            d();
            b();
            b();
            di();
            u();
            ri();
            di();
            di();
        }
    }
    else if (face == 4)
    {
        if (isNextTo)
        {
            b();
            ui();
            d();
            l();
            l();
            d();
            d();
            u();
            u();
            r();
            d();
            ri();
            u();
            u();
            d();
            d();
            l();
            l();
            di();
            u();
            bi();
            di();
        }
        else
        {
            b();
            ui();
            d();
            l();
            l();
            d();
            d();
            u();
            u();
            r();
            d();
            d();
            ri();
            u();
            u();
            d();
            d();
            l();
            l();
            di();
            u();
            bi();
            di();
            di();
        }
    }

}

// Just makes a copy of the cube
void copyCube()
{
    copyOfCube = cube;
}

// Just prints the entire cube array
void printCube()
{
    for (size_t i = 0; i < cube.size(); ++i)
    {
        for (size_t j = 0; j < cube[0].size(); ++j)
        {
            for (size_t k = 0; k < cube[0][0].size(); ++k)
            {
                cout << cube[i][j][k] << ", ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void betterPrint()
{
    /*
    0 0 0
    0 0 0
    0 0 0
    4 4 4 3 3 3 2 2 2 1 1 1
    4 4 4 3 3 3 2 2 2 1 1 1
    4 4 4 3 3 3 2 2 2 1 1 1
    5 5 5
    5 5 5
    5 5 5
    */

    // Print the top section
    for (int i = 0; i < 3; i++)
    {
        cout << string(12, ' ');
        for (int j = 0; j < 3; j++)
        {
            cout << cube[0][i][j] << " ";
        }
        cout << endl;
    }

    // Print the middle section
    for (int j = 0; j < 3; j++)
    {
        for (int k = 1; k < 5; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                cout << cube[k][j][i] << " ";
            }
        }
        cout << endl;
    }

    // Print the bottom section
    for (int i = 0; i < 3; i++)
    {
        cout << string(12, ' ');
        for (int j = 0; j < 3; j++)
        {
            cout << cube[5][i][j] << " ";
        }
        cout << endl;
    }

}

