/**
 * @author Hosty Khurana
 * @date March 12, 2021
 * @file View.java
 * @details This module generates a 4x4 matrix in console for user to play the game.
 */

import java.util.Scanner;

/**
 * @brief This class handles user experience.
 * @details This class contains methods to display game on console and to handle the input from user
 */
public class View {
    Model gameBoard;
    Scanner scanner;
    boolean continueGame;

    /**
     * @brief This is a constructor for View class
     * @details This method initializes the View class object to display game.
     */
    View(){
        this.gameBoard = new Model();
        this.scanner = new Scanner(System.in);
        this.continueGame = true;
    }


    /**
     * @brief This method displays the instructions and handles the command from console given by user.
     * @details This method handles the movement of the board (up, down, right, left), reset and exit commands, and the commands for game over and game completed.
     */
    public void runGame(){
        Instructions();

        while (this.continueGame){

            System.out.println(this.gameBoard.toString());
            System.out.print("Please make a move: ");

            char input = this.scanner.next().charAt(0);

            if (input == 'w' || input == 'W'){
                System.out.println("Up");
                this.gameBoard.action("Up");
            }
            if (input == 'a' || input == 'A'){
                System.out.println("Left");
                this.gameBoard.action("Left");
            }
            if (input == 's' || input == 'S'){
                System.out.println("Down");
                this.gameBoard.action("Down");
            }
            if (input == 'd' || input == 'D'){
                System.out.println("Right");
                this.gameBoard.action("Right");
            }
            if (input == 'e' || input == 'E'){
                System.out.println("Exit");
                this.continueGame = false;
            }
            if (input == 'r' || input == 'R'){
                System.out.println("Reset");
                this.gameBoard = new Model();
            }
            if(gameBoard.checkLucky()){
                System.out.println("Game Completed!, YOU WON");
            }

            if(gameBoard.checkUnlucky()){
                System.out.println("Game Over!");
            }
        }
    }

    /**
     * @brief This method displays instructions for game.
     */
    public static void Instructions(){
        System.out.println("Lets Play 2048!");
        System.out.println("How To Play: ");
        System.out.println("w or W to move upwards");
        System.out.println("a or A to move leftwards");
        System.out.println("s or S to move downwards");
        System.out.println("d or D to move rightwards");
        System.out.println("e or E to exit the game");
        System.out.println("r or R to reset the game");
        System.out.println(" ");
        System.out.println(" ");
    }
}

