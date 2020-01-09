#ifndef ISOMETRICCONVERSIONS_H
#define ISOMETRICCONVERSIONS_H


struct IsometricConversions
{
    int tileWidth = 128;
    int tileHeight = 64;




    sf::Vector2i screenToMapCoords(sf::Vector2f screenCoords)
    {
        //Determine rectangle
        int i = (screenCoords.y / (tileHeight / 2));
        int halfTileHeight = tileHeight / 2;
        int halfTileWidth = tileWidth / 2;
        int j = 0;


        sf::Vector2f tileCoords;

        //If i is even
        if(i % 2 == 0)
            j = (screenCoords.x / tileWidth);
        else
            j = ((screenCoords.x - (tileWidth / 2)) / tileWidth);

       //Tiles width is twice the length of its height.
        //Positive slope is 1/2, negative slow is -1/2
        //Find the formula for the hypotenuse of the triangle formed at the corners
        //The formula of a line through a given point is y = m(x - x1) + y1. x1 and y1 are the known points and m is the slope
        //To find the corner, check where the y value of the screen coords is in relation to the y value of the line
        tileCoords = mapToScreenCoords(sf::Vector2i(i, j));


        //Determine quadrant.
        //If in upper left corner, the map coords are (i - 1, j)
        //If in upper right corner, the map coords are (i + 1, j - 1)
        //If in bottom left corner, the map coords are (i, j + 1)
        //If in bottom right corner, the map coords are (i + 1, j + 1)
        //If in tht middle, the map coords are (i, j)

        //Only need to check the top corners because of the way tile coordinates were found

        //Top Left.
        if(screenCoords.x < tileCoords.x + halfTileWidth / 1.1 && screenCoords.y < (1 / 2) * (screenCoords.x - tileCoords.x) + (tileCoords.y + halfTileHeight))
        {
           // std::cout << "Upper left of (" << i << ", " << j << ")\n";

            //Upper left of an even tile is 1 row less and 1 column less
            //Upper left of an odd column is 1 row less
            if(i % 2 == 0)
            {
                i -= 1;
                j -= 1;
            }
            else
                i -= 1;
        }
        //Top Right
        else if(screenCoords.x > tileCoords.x + halfTileWidth * 1.1 && screenCoords.y < (-1 / 2) * (screenCoords.x - (tileCoords.x + tileWidth) ) + (tileCoords.y + halfTileHeight))
        {
         //  std::cout << "Upper right of (" << i << ", " << j << ")\n";

           //Upper right of an even tile is 1 row less
           //Upper right of an odd column is 1 row less and 1 column more
           if(i % 2 == 0)
           {
                i -= 1;
           }
           else
           {
                i -= 1;
                j += 1;

           }

        }

        //Should be able to remove the checks for bottom right and left because of the way tile coordinates are initially located
      /*  //Bottom Right
        else if(screenCoords.x > tileCoords.x + halfTileWidth && screenCoords.y > (1 / 2) * (screenCoords.x - (tileCoords.x + tileWidth) ) + (tileCoords.y + halfTileHeight))
        {
            i += 1;
            j += 1;
            std::cout << "Bottom Right\n";
        }
        //Bottom left
        else if(screenCoords.x < tileCoords.x + halfTileWidth && screenCoords.y >  (-1 / 2) * (screenCoords.x - tileCoords.x) + (tileCoords.y + halfTileHeight))
        {
            i += 1;
            std::cout << "Bottom left\n";
        }*/



        //Otherwise the coordinates are in the middle and the map coords are (i, j)
        return sf::Vector2i(i, j);
    }

    sf::Vector2f mapToScreenCoords(sf::Vector2i mapCoords)
    {
        //Map coords should be in the form (row, column);
    float screenYPos = mapCoords.x * (tileHeight / 2);
    float screenXPos = 0;

    if(mapCoords.x % 2 != 0)
        screenXPos = mapCoords.y * tileWidth + (tileWidth / 2);
    else
        screenXPos = mapCoords.y * tileWidth;

    return sf::Vector2f(screenXPos, screenYPos);
    }

};

#endif // ISOMETRICCONVERSIONS_H
