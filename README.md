# ~Dot-Connector

# Description:
Dot Connector is a mind-bending and captivating puzzle game designed to be played between two opponents. It challenges their intellect, patience, and logical abilities. Each opponent is presented with a screen filled with dots, and their objective is to strategically connect the dots, create square cycles, and dominate the board. With every move, players exert pressure on their opponents to make more squares quickly and with the fewest possible moves.

# CONTROL:
The game presents a n*n grid of empty nodes. Players are tasked with connecting edges between two nodes in a single move by inputting the serialwise representations of the nodes they wish to connect. It is prohibited to overwrite an existing edge, and edges can only be drawn vertically or horizontally—diagonal edges are not allowed. When a player successfully forms a square of 1 square unit, they earn an extra move and a point. The game concludes once all nodes are visited. The winner is determined by comparing the scores of "Player 1" and "Player 2" with the player scoring the most points declared as the winner.

# Gameplay:
A player will join through a desktop/mobile. If the player wants to initiate a new game, they will click on "NEW GAME" and then click "PLAY" to start the game. Two players can participate in the game: Player 1 can invite Player 2, and if Player 2 accepts the invitation, they can play the game together. Alternatively, there is an option for an offline game where both players can play using a single device.
In this game, each player must connect the dots. If a player can create a square of one square unit using the dots, they will earn an additional move also a point. This process continues until there are no possible edges left. The game concludes when there are no more opportunities to create squares. The player who can make the most squares of one square unit using the dots will be declared the winner.

# Goal:
The player's objective is to connect the dots and create cycles. At the end of the game, the player with the highest number of squares in their domination will emerge victorious. Points are awarded for every square created, and the player with the highest point total will be declared the winner.

# Development Goal:
Elevate player engagement and strategic depth in "Dot Connector" by introducing an online multiplayer mode with cross-platform compatibility. Implement a dynamic scoring system based on square sizes, ensuring a challenging yet rewarding gameplay experience. Enhance the game's visual appeal through an intuitive interface. The ultimate goal is to provide a seamless and competitive gaming experience, fostering strategic thinking and healthy competition across different devices. As part of future enhancements, explore the possibility of accommodating more than two players simultaneously, expanding the game's social and competitive aspects. 

# Installation Guide:

1.Install sfml: <br>
sudo apt-get install libsfml-dev <br>

2.To compile the project:<br>
g++ -c *.cpp; g++ main.o Board.o Box.o -o sfml.app -lsfml-graphics -lsfml-window -lsfml-system;<br>

3.To run the app:<br>
 ./sfml.app <br>

# Team members
*1.Mahdi Hasan Qurishi (Reg: 2021331090) - @Enigmah-00<br>
2.Zubayer Hossain Uday (Reg: 2021331002) - @ZH-Uday<br>
3.Shafiuzzaman Akash (Reg: 2021331034) - @ZamanAkash*
