/**
 * @author Hosty Khurana
 * @date March 12, 2021
 * @file Model.java
 * @details This module Test Model Module.
 */

import org.junit.*;
import static org.junit.Assert.*;

public class TestModel {

    @Test
    public void testBasicModel(){
        int count = 0;
        int[][] g;
        Model m = new Model();
        g = m.getGame();
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (g[i][j] != 0){
                    count++;
                }
            }
        }
        assertTrue(count == 2);
    }

    @Test
    public void testLucky(){
        int[][] g;
        Model m = new Model();
        g = m.getGame();
        int num = 2;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                g[i][j] = num;
                num *= 2;
            }
        }
        assertTrue(m.checkLucky());
        assertFalse(m.checkUnlucky());
    }

    @Test
    public void testUnlucky(){
        int[][] g;
        Model m = new Model();
        g = m.getGame();
        int num = 1;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                g[i][j] = num;
                num += 1;
            }
        }
        assertFalse(m.checkLucky());
        assertTrue(m.checkUnlucky());
    }

    @Test
    public void testUp(){
        Model m = new Model();
        m.getGame()[1][3] = 16;
        m.getGame()[0][3] = 16;
        m.action("Up");
        assertTrue(m.getGame()[0][3] == 32);
    }

    @Test
    public void testDown(){
        Model m = new Model();
        m.getGame()[2][3] = 32;
        m.getGame()[3][3] = 32;
        m.action("Down");
        assertTrue(m.getGame()[3][3] == 64);
    }

    @Test
    public void testRight(){
        Model m = new Model();
        m.getGame()[3][2] = 64;
        m.getGame()[3][3] = 64;
        m.action("Right");
        assertTrue(m.getGame()[3][3] == 128);
    }

    @Test
    public void testLeft(){
        Model m = new Model();
        m.getGame()[3][0] = 1024;
        m.getGame()[3][1] = 1024;
        m.action("Left");
        assertTrue(m.getGame()[3][0] == 2048);
        assertTrue(m.checkLucky());
    }
}

