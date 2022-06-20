# Rubik's Cube Solver with OpenCV
<img alt="opencv" src="https://qph.fs.quoracdn.net/main-qimg-748316a749bdb46f5cdbe02e976e5500" height="40" hspace="10"> <img alt="c++" src="https://raw.githubusercontent.com/isocpp/logos/master/cpp_logo.png" height="40" hspace="10">

### C++ Program to scan and solve Rubik's Cube

# Cube Scanner

## How it works

First each face of the Rubik's Cube is scanned.

```c++
Mat yellow = img.clone();

faceScans[0] = yellow(ROI);

...

Mat orange = img.clone();

faceScans[1] = orange(ROI);

...

Mat blue = img.clone();

faceScans[2] = blue(ROI);

...
```

With each face of the cube scanned, the colors must be extracted.

First pre processing is applied to the images.

```c++
// Blur the image
GaussianBlur(faceScans[i], faceScans[i], Size(3, 3), 0, 0);

// and convert to the HSV color space
cvtColor(faceScans[i], faceScans[i], COLOR_BGR2HSV);
```

Six masks are then created and blurred of each color for each face.

```c++
// Yellow mask
inRange(faceScans[i], Scalar(18, 134, 45), Scalar(40, 238, 237), faceMasks[0]);
dilate(faceMasks[0], faceMasks[0], kernel);
// Orange mask
inRange(faceScans[i], Scalar(0, 50, 75), Scalar(19, 255, 255), faceMasks[1]);
dilate(faceMasks[1], faceMasks[1], kernel);
// Blue mask
inRange(faceScans[i], Scalar(104, 135, 43), Scalar(122, 255, 210), faceMasks[2]);
dilate(faceMasks[2], faceMasks[2], kernel);
// Red mask
inRange(faceScans[i], Scalar(0, 132, 0), Scalar(9, 255, 178), faceMasks[3]);
dilate(faceMasks[3], faceMasks[3], kernel);
// Green mask
inRange(faceScans[i], Scalar(60, 45, 50), Scalar(76, 255, 170), faceMasks[4]);
dilate(faceMasks[4], faceMasks[4], kernel);
// White mask
inRange(faceScans[i], Scalar(101, 13, 76), Scalar(120, 160, 255), faceMasks[5]);
dilate(faceMasks[5], faceMasks[5], kernel);
```

With these mask created, the nine cubies are checked for their color value with each mask. 

The masks create a binary image where the white sections were included in the HSV ranges. As such, the places where the image are where the color is.

```c++
// Now compare faceMasks[j] to the color at point colorPoints[k]
Scalar color = faceMasks[j].at<uchar>(Point(colorPoints[k].x, colorPoints[k].y));

// And if the color is white
if (color[0] == 255)
{
    // Save it to the array

    // The color point determines the position of the cube so that can be used to determine where to save it to the array
    cube[i][k / 3][k % 3] = j;
}
```

If the point is white, the color of the current face in the loop is added to the cube array at the current point.

Now, the cube array is translated so that it is in the same format as the solver.

```c++
// Orange side
cube[1][0][0] = copyOfCube[1][2][0];
cube[1][0][1] = copyOfCube[1][1][0];
cube[1][0][2] = copyOfCube[1][0][0];
cube[1][1][0] = copyOfCube[1][2][1];
cube[1][1][2] = copyOfCube[1][0][1];
cube[1][2][0] = copyOfCube[1][2][2];
cube[1][2][1] = copyOfCube[1][1][2];
cube[1][2][2] = copyOfCube[1][0][2];

...

// Blue side
cube[2][0][0] = copyOfCube[2][2][0];
cube[2][0][1] = copyOfCube[2][1][0];
cube[2][0][2] = copyOfCube[2][0][0];
cube[2][1][0] = copyOfCube[2][2][1];
cube[2][1][2] = copyOfCube[2][0][1];
cube[2][2][0] = copyOfCube[2][2][2];
cube[2][2][1] = copyOfCube[2][1][2];
cube[2][2][2] = copyOfCube[2][0][2];

...
```

Finally, some small error correction is applied so that it, then it is sent to the solver.

```c++
// Change the center pieces to their respective color because the scan is based of the center
for (int i = 0; i < 6; i++)
{
    cube[i][1][1] = i;
}

// Now the cube is scanned and the cube array is filled with numbers that are not -1 (Hopefully)
solveCube(cube);
```

## Demonstration

<img alt="Demonstration of scanner" src="scannerDemo.png">

# Cube Solver

The solver uses a three dimensional array to store the state of the cube.

```c++
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
```

First, the validity of the scanned cube is checked.

```c++
// Check if the cube is valid
for (size_t i = 0; i < cube.size(); ++i)
{
    for (size_t j = 0; j < cube[0].size();+j)
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
```

This ensures that the cube is not already solved and the scan was correct.

Each rotation of the cube is predefined in terms of the faces of the cube.

```c++
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
```

This is an example of a rotation of the right side of the Rubik's Cube. This is done for all twelve possible moves.

To solve the cube, the yellow side is solved first. All yellow edges on the yellow side are first removed, then put into place.

```c++
// Find an edge to position it
    findYellowEdges(side, pos);
    // Now based on the side which it is on,position it correctly
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
    // If yellow edge is on the bottom (whiteside)
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
```

Similar steps are taken to solve the yellow corners.

Next the middle edges are solved.

```c++
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
```

Finally, the white side is solved.

The edges and corners are essentially solved with predefined moves. The permutation of the white side is determined, then moves are performed accordingly.

For example,

```c++
// Rotate the edges
void rotateEdges(int face, bool rotClockwise)
{
    // Uses the face and if the rotation is clockwise or not to rotate the edges with pre defined moves
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
```

This is used to solve the white edges.

Finally, a solved Rubik's Cube is output with a list of moves to perform for the solution.

```c++
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
```

## Demonstration

```c++
            0 0 0
            0 0 0
            0 0 0
4 4 4 3 3 3 2 2 2 1 1 1
4 4 4 3 3 3 2 2 2 1 1 1
4 4 4 3 3 3 2 2 2 1 1 1
            5 5 5
            5 5 5
            5 5 5
            
R L BI RI R UI R L LI BI DI RI U U LI RI FI UI 
Solving yellow edges
U U F F U U 
U FI DI UI L BI LI U F DI UI U U L BI LI UI UI R D D U L BI LI UI D D U U L L UI UI 
            5 0 2 
            0 0 0 
            3 0 0 
2 1 5 4 2 2 3 3 1 5 4 3 
5 1 2 3 2 3 4 3 4 1 4 3 
4 5 3 0 5 1 0 2 0 1 5 5 
            4 1 2 
            4 5 1 
            1 2 4 
Solving yellow corners
D RI D R U U U U DI DI U R D RI UI DI DI U U U BI DI B UI UI UI DI DI DI DI U U BI DI B UI UI DI DI DI DI DI R D RI 
            0 0 0 
            0 0 0 
            0 0 0 
1 1 1 2 2 2 3 3 3 4 4 4 
5 1 2 3 2 4 5 3 2 1 4 3 
2 5 5 4 3 2 3 5 4 5 1 1 
            1 4 5 
            2 5 1 
            5 4 3 
Solving middle
D D B DI BI DI LI D L DI DI BI D B D R DI RI DI FI D F D L DI LI D F DI FI DI RI D R 
            0 0 0 
            0 0 0 
            0 0 0 
1 1 1 2 2 2 3 3 3 4 4 4 
1 1 1 2 2 2 3 3 3 4 4 4 
5 4 3 5 1 4 5 5 4 1 5 2 
            2 5 3 
            5 5 2 
            1 3 5 
Solving white side
D R R D FI B R R F BI D R R B B D RI L B B R LI D B B FI U F R U RI D R UI RI FI UI F DI FI U F R U RI D R UI RI FI UI F DI RI U R B U BI D B UI BI RI UI R DI R UI D B B D D U U F D FI U U D D B B DI U RI DI 
            0 0 0 
            0 0 0 
            0 0 0 
1 1 1 2 2 2 3 3 3 4 4 4 
1 1 1 2 2 2 3 3 3 4 4 4 
1 1 1 2 2 2 3 3 3 4 4 4 
            5 5 5 
            5 5 5 
            5 5 5 
Number of turns: 208
```