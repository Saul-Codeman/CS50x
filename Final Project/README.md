# SNAKE GAME
#### Video Demo:  <https://youtu.be/Z-fsc8J4o_E>
#### Description:

I decided to make the snake game using python and the turtle library. To start, it is best to think of the design of the game in small chunks. The screen, snake, scoreboard, and food are all unique pieces that can be altered independently of each other. These pieces can later be placed into the main file to run the game.

Starting with the screen, I wanted to have a black, square screen that would exit the game on click. I also wanted the screen to update only when all the pieces of the snake had moved. I also used the time library during the game to determine how fast the snake should be moving.

The snake class consisted of itself, create_snake, add_segment, extend, move, up, down, right, and left. I designated the snake head to be the first segment of the array. The move function govererned the movement of the snake by giving the head a single forward movement speed. The head [0] was the only piece controlling the movement since the other pieces behind the head would just go to the spot in front of them or [i - 1]. The movement keys were implemented using event listeners "onkey", and they would change the heading of the head of the snake. Finally, when the snake ate, it would use the extend function to call the add_segment function to append another segment to the end of the snake.

The food class had self and refresh methods. The food was made blue, and it was made to be slightly smaller than the snake. The refresh function would be called whenever the distance between the snake and the food was less than 15.

The scoreboard class had self, update_score, and game_over methods. These functions were used to increase the score whenever the food was eaten by the snake. They were also used to display "GAME OVER" to the user whenever there was a collision with the tail or the wall.

The main.py file is where the entire program comes together and the logic is put together. The game begins with the screen opening and displaying the title. As soon as it opens the objects are made from the classes discussed above, and the snake head is immediately moving. The user can control the snake heading using the arrow keys. When the snake collides with the food, the food is refreshed to another point on the screen, the snake extends, and the scoreboard is updated. The game is constantly detecting whether or not the snake has collided with the wall or the tail. If the snake comes into distance of either of these parameters, the game is set to end using the gameover function and ending the while loop.