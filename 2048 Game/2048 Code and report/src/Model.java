/**
 * @author Hosty Khurana
 * @date March 12, 2021
 * @file Model.java
 * @details This module handles the logic used in game.
 */


import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Random;

/**
 * @brief This class handles the calculation and logic for game.
 * @details This class contains methods to generate the board and initiate necessary moves to play the game.
 */
public class Model {
    private int[][] game;
    private final Random randomNumber;
    private boolean lucky;
    private boolean unlucky;

    /**
     * @brief This is a constructor for Model class
     * @details This method initializes the Model class object to form a new board(4x4 matrix).
     */
    Model(){
        game = new int[4][4];
        randomNumber = new Random();
        lucky = true;
        unlucky = false;
        newGame();
    }

    /**
     * @brief This method stores two digits at two random positions in the board.
     */
    private void newGame() {
        for (int i = 0; i < 2; i++) {
            int x = randomNumber.nextInt(4);
            int y = randomNumber.nextInt(4);
            if(game[x][y] == 0){
                if (randomNumber.nextDouble() < 0.1){
                    game[x][y] = 4;
                }
                else {
                    game[x][y] = 2;
                }
            }
            else {
                i--;
            }
        }
    }

    /**
     * @brief This method spawns a new number in board after movement.
     * @details This method only spawns a new number(2 or 4) if there is an empty space or a place with value zero.
     */
    private void placeNumber(){
        while(isEmpty()){
            int x = randomNumber.nextInt(4);
            int y = randomNumber.nextInt(4);
            if(game[x][y] == 0){
                if (randomNumber.nextDouble() < 0.10){
                    game[x][y] = 4;
                }
                else {
                    game[x][y] = 2;
                }
                break;
            }
        }
    }

    /**
     * @brief This method returns true if there is some position where the value is 0
     */
    private boolean isEmpty(){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j <4; j++) {
                if(game[i][j] == 0){
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * @brief This method rotates the board to accommodate merge at time of movement
     * @param angle is of type int
     * @param rightRotate is of type boolean
     */
    private void rotation(int angle, boolean rightRotate) {
        int length = game.length;

        for (int k = 0; k < angle; k+=90) {
            int[][] rotate = new int[length][length];
            for (int i = 0; i < length; ++i)
                for (int j = 0; j < length; ++j)
                    if (rightRotate){
                        rotate[i][j] = game[length - j -1][i];
                    }
                    else{
                        rotate[i][j] = game[j][length - i - 1];
                    }
            game = rotate;
        }

    }

    /**
     * @brief This accommodates the logic of slide and merge of numbers.
     * @details For slide it uses rotation() and for merge it uses calculateMerge().
     * @param move is of type String. move contains the command provided by the user.
     */
    public void action(String move){
        if (move.equals("Up")){
            rotation(90, false);
            calculateMerge();
            rotation(90, true);
        }
        else if (move.equals("Down")){
            rotation(90, true);
            calculateMerge();
            rotation(90, false);
        }
        else if (move.equals("Left")){
            calculateMerge();
        }
        else if (move.equals("Right")){
            rotation(180, true);
            calculateMerge();
            rotation(180, false);
        }

        placeNumber();
    }

    /**
     * @breif This method handles the merge of two numbers.
     * @details This method uses LinkedList to calculate the merge at time of movement like up,down,right and left.
     */
    private void calculateMerge() {
        for (int i = 0; i < 4; i++) {
            LinkedList<Integer> calculate = new LinkedList<Integer>();
            for (int j = 0; j < 4; j++) {
                if(game[i][j] == 0){
                    continue;
                }
                calculate.addLast(game[i][j]);
                game[i][j] = 0;
            }

            for (int j = 1; j < calculate.size(); j++) {
                if((int)calculate.get(j - 1) == (int)calculate.get(j)){
                    calculate.set(j - 1, calculate.get(j-1)*2);
                    calculate.remove(j);
                }
            }

            for (int j = 0; j < calculate.size(); j++) {
                game[i][j] = calculate.get(j);
            }
        }
    }

    /**
     * @brief This method determines if user won the game.
     * @details This method search for a position in board that have value equal to 2048, if this position is found it returns true.
     */
    public boolean checkLucky() {
        boolean lucky = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (game[i][j] == 2048) {
                    lucky = true;
                    break;
                }
            }
        }
        this.lucky = lucky;
        return lucky;
    }

    /**
     * @brief This method determines if user lost the game.
     * @details This method search for a position in board that have value equal to 0, if this position is found it returns true.
     */
    public boolean checkUnlucky() {
        Model checkGame = new Model();
        boolean unlucky = true;

        if(checkLucky()){
            this.unlucky = false;
            return false;
        }

        String[] moves = new String[]{ "Up", "Down", "Left", "Right"};
        for(String m: moves){

            for (int i = 0; i < 4; i++) {
                System.arraycopy(game[i], 0, checkGame.game[i], 0, 4);
            }

            checkGame.action(m);
            if(Arrays.deepEquals(game, checkGame.game)){
                unlucky = unlucky;
            }
            else{
                unlucky = false;
            }
        }
        this.unlucky = unlucky;
        return unlucky;
    }


    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.append(game[i][j]).append(" ");
            }
            result.append('\n');
        }
        return result.toString();
    }

    /**
     *
     * @return Boolean value of lucky
     */
    public boolean islucky() {
        return lucky;
    }

    /**
     *
     * @return Boolean value of unlucky
     */
    public boolean isunlucky() {
        return unlucky;
    }

    /**
     * @brief The board of the game is returned (a 2D array of size 4x4 is returned)
     */
    public int[][] getGame() {
        return game;
    }
}

