# cardsgame-repo

## General info
This project is a simple card game made completely in C.
	
## Setup
To run this project, download it locally, then run in a IDE for C programming languaje:

## Explanation
Card battle
The game consists of each player receiving 6 cards from a deck of 52 decks (decks French), you have 2 players, player 1 is the user and player 2 is the machine. 
Before starting the battle, the user must organize his cards according to the criteria that seem convenient to him. Once the battle has started, the cards compete with each other.
There are 4 games where each player receives 6 cards and the fifth game each player receives 2. At the end the scores are verified and it is said who won.
Scores
- Normal battles: 1 point, the cards are killed by numerical value.
- Fight the brave squire: 3 points, ace killed king.
- The 3 Musketeers and D'Artagnan: 8 points, the player has 4 cards of the same denomination in case the other player has the same, it is verified which cards are greater, the largest quartet being 4 aces, followed by 4 k, 4 q, 4j then the other denominations. Individual battles are not evaluated if one of the players has the 4 identical cards and the other does not win the one who automatically owns them.
- Battle of heroes: 2 points. The cards have the same denomination, the red cards win in the even turns and the black ones in the odd ones, the games are counted from 1. If they are of the same color, no one receives points.
Add logic to the machine's card ordering.


Explanation in Spanish.

Batalla de Cartas
El juego consiste en que cada jugador recibe 6 cartas de un mazo de 52 barajas (barajas francesas), se tienen 2 jugadores el jugador 1 es el usuario y el jugador 2 la máquina. 
El usuario antes de iniciar la batalla debe organizar sus cartas de acuerdo con el criterio que le parezca conveniente. Una vez iniciada la batalla las cartas compiten entre sí. 
Se realizan 4 partidas donde cada jugador recibe 6 cartas y la quinta partida cada jugador recibe 2. Al final se verifican las puntuaciones y se dice quien ganó.
Puntuaciones
-	Batallas normales: 1 punto, se matan las cartas por valor numérico.
-	Combate el escudero valiente: 3 puntos as mató a rey.
-	Los 3 mosqueteros y D'Artagnan: 8 puntos, el jugador posee 4 cartas de la misma denominación en caso de que el otro jugador tenga lo mismo se verifican cuales cartas son mayores siendo el cuarteto mayor 4 ases, le siguen 4 k, 4 q, 4j luego las demás denominaciones. No se evalúan batallas individuales si uno de los jugadores tiene las 4 cartas iguales y el otro no gana el que las posea automáticamente. 
-	Batalla de héroes: 2 puntos. Las cartas tienen la misma denominación, ganan las cartas de color rojo en los turnos pares y las negras en las impares, las partidas se cuentan desde 1. En caso de ser del mismo color ninguno recibe puntos.
Agregar una lógica al ordenamiento de cartas de la máquina.



