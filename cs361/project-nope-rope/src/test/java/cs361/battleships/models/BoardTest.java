package cs361.battleships.models;

import org.junit.Test;

import static cs361.battleships.models.AttackStatus.*;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.List;
import java.util.ArrayList;

public class BoardTest {

    @Test
    public void testInvalidPlacement() {
        Board board = new Board();
        assertFalse(board.placeShip(new Ship("MINESWEEPER"), 11, 'C', true));
    }

    @Test
    public void validPlacement() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 7, 'B', true));

        List<Square> squares = new ArrayList<>();
        squares.add(new Square(7, 'B'));
        squares.add(new Square(8, 'B'));

        assertTrue(equalSquares(squares.get(0), board.getShips().get(0).getOccupiedSquares().get(0)));
        assertTrue(equalSquares(squares.get(1), board.getShips().get(0).getOccupiedSquares().get(1)));
    }

    @Test
    public void invalidColPlacement() {
        Board board = new Board();
        assertFalse(board.placeShip(new Ship("BATTLESHIP"), 5, 'H', false));
    }

    private boolean equalSquares(Square sq1, Square sq2) {
        return sq1.getColumn() == sq2.getColumn() && sq1.getRow() == sq2.getRow();
    }

    @Test
    public void validColPlacement() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 7, 'G', false));

        List<Square> squares = new ArrayList<>();
        squares.add(new Square(7, 'G'));
        squares.add(new Square(7, 'H'));

        assertTrue(equalSquares(squares.get(0), board.getShips().get(0).getOccupiedSquares().get(0)));
        assertTrue(equalSquares(squares.get(1), board.getShips().get(0).getOccupiedSquares().get(1)));

    }

    @Test
    public void placeSubmarineHorizontally() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("SUBMARINE"), 5, 'D', false));

        List<Square> squares = new ArrayList<>();
        squares.add(new Square(5, 'D'));
        squares.add(new Square(5, 'E'));
        squares.add(new Square(5, 'F'));
        squares.add(new Square(5, 'G'));
        squares.add(new Square(4, 'F'));

        assertTrue(equalSquares(squares.get(0), board.getShips().get(0).getOccupiedSquares().get(0))
                && equalSquares(squares.get(1), board.getShips().get(0).getOccupiedSquares().get(1))
                && equalSquares(squares.get(2), board.getShips().get(0).getOccupiedSquares().get(2))
                && equalSquares(squares.get(3), board.getShips().get(0).getOccupiedSquares().get(3))
                && equalSquares(squares.get(4), board.getShips().get(0).getOccupiedSquares().get(4)));
    }

    @Test
    public void placeSubmarineVertically() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("SUBMARINE"), 5, 'D', true));

        List<Square> squares = new ArrayList<>();
        squares.add(new Square(5, 'D'));
        squares.add(new Square(6, 'D'));
        squares.add(new Square(7, 'D'));
        squares.add(new Square(8, 'D'));
        squares.add(new Square(7, 'E'));

        assertTrue(equalSquares(squares.get(0), board.getShips().get(0).getOccupiedSquares().get(0))
                && equalSquares(squares.get(1), board.getShips().get(0).getOccupiedSquares().get(1))
                && equalSquares(squares.get(2), board.getShips().get(0).getOccupiedSquares().get(2))
                && equalSquares(squares.get(3), board.getShips().get(0).getOccupiedSquares().get(3))
                && equalSquares(squares.get(4), board.getShips().get(0).getOccupiedSquares().get(4)));
    }

    @Test
    public void placeSubmarineHorizontallySubmerged() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 5, 'D', false, false));
        assertTrue(board.placeShip(new Ship("SUBMARINE"), 5, 'D', false, true));

        List<Square> squares = new ArrayList<>();
        squares.add(new Square(5, 'D'));
        squares.add(new Square(5, 'E'));
        squares.add(new Square(5, 'F'));
        squares.add(new Square(5, 'G'));
        squares.add(new Square(4, 'F'));

        assertTrue(equalSquares(squares.get(0), board.getShips().get(1).getOccupiedSquares().get(0))
                && equalSquares(squares.get(1), board.getShips().get(1).getOccupiedSquares().get(1))
                && equalSquares(squares.get(2), board.getShips().get(1).getOccupiedSquares().get(2))
                && equalSquares(squares.get(3), board.getShips().get(1).getOccupiedSquares().get(3))
                && equalSquares(squares.get(4), board.getShips().get(1).getOccupiedSquares().get(4)));
    }

    @Test
    public void placeSubmarineVerticallySubmerged() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 5, 'D', true, false));
        assertTrue(board.placeShip(new Ship("SUBMARINE"), 5, 'D', true, true));

        List<Square> squares = new ArrayList<>();
        squares.add(new Square(5, 'D'));
        squares.add(new Square(6, 'D'));
        squares.add(new Square(7, 'D'));
        squares.add(new Square(8, 'D'));
        squares.add(new Square(7, 'E'));

        assertTrue(equalSquares(squares.get(0), board.getShips().get(1).getOccupiedSquares().get(0))
                && equalSquares(squares.get(1), board.getShips().get(1).getOccupiedSquares().get(1))
                && equalSquares(squares.get(2), board.getShips().get(1).getOccupiedSquares().get(2))
                && equalSquares(squares.get(3), board.getShips().get(1).getOccupiedSquares().get(3))
                && equalSquares(squares.get(4), board.getShips().get(1).getOccupiedSquares().get(4)));
    }



    @Test
    public void shouldhit() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 2, 'G', false));
        Result playerAttack = board.attack(2, 'H');
        assertTrue(playerAttack.getResult() == HIT);
    }

    @Test
    public void shouldMiss() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 2, 'G', false));
        Result playerAttack = board.attack(8, 'H');
        assertTrue(playerAttack.getResult() == MISS);
    }

    @Test
    public void charColToIntTest() {
        assertTrue(Board.charToColInt('A') == 1 && Board.charToColInt('B') == 2 && Board.charToColInt('C') == 3
                && Board.charToColInt('D') == 4 && Board.charToColInt('E') == 5 && Board.charToColInt('F') == 6
                && Board.charToColInt('G') == 7 && Board.charToColInt('H') == 8 && Board.charToColInt('I') == 9
                && Board.charToColInt('J') == 10);
    }

    @Test
    public void intToColChar() {
        assertTrue(Board.intToColChar(1) == 'A' && Board.intToColChar(2) == 'B' && Board.intToColChar(3) == 'C'
                && Board.intToColChar(4) == 'D' && Board.intToColChar(5) == 'E' && Board.intToColChar(6) == 'F'
                && Board.intToColChar(7) == 'G' && Board.intToColChar(8) == 'H' && Board.intToColChar(9) == 'I'
                && Board.intToColChar(10) == 'J');
    }

    @Test
    public void noOverlapShips() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 7, 'G', false));
        assertFalse(board.placeShip(new Ship("MINESWEEPER"), 7, 'G', false));
    }

    @Test
    public void checkIfBoardHasShip() {
        Board board = new Board();
        assertFalse(board.hasShip("MINESWEEPER"));
        board.placeShip(new Ship("MINESWEEPER"), 2, 'C', true);
        assertTrue(board.hasShip("MINESWEEPER"));
    }

    @Test
    public void checkIfDuplicateShipType() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("BATTLESHIP"), 2, 'C', false));
        assertFalse(board.placeShip(new Ship("BATTLESHIP"), 3, 'C', false));
        assertTrue(board.placeShip(new Ship("MINESWEEPER"), 4, 'C', false));
        assertFalse(board.placeShip(new Ship("MINESWEEPER"), 5, 'C', false));
        assertTrue(board.placeShip(new Ship("DESTROYER"), 6, 'C', false));
        assertFalse(board.placeShip(new Ship("DESTROYER"), 7, 'C', false));
    }

    @Test
    public void checkSonarPulse() {
        Board board = new Board();
        assertTrue(board.placeShip(new Ship("DESTROYER"), 2, 'C', false));
        board.sonarPulse(3, 'C');

        List<Square> squares = board.getVisibleSquares();
        assertTrue(squares.size() == 13);
        assertTrue(squares.get(0).getType() == SquareType.EMPTY);
        assertTrue(squares.get(3).getType() == SquareType.SHIP);
        assertTrue(squares.get(2).getType() == SquareType.SHIP);
    }

    @Test
    public void cornerPulse() {
        Board board = new Board();
        board.sonarPulse(1, 'A');

        List<Square> squares = board.getVisibleSquares();
        assertTrue(squares.size() == 6);
    }

    @Test
    public void hitCaptainQuarters() {
        Board board = new Board();
        board.placeShip(new Ship("DESTROYER"), 2, 'C', false);
        Result playerAttack = board.attack(2, 'D');
        assertTrue(playerAttack.getResult() == MISS);
    }

    @Test
    public void minesweeperQuarters() {
        Board board = new Board();
        board.placeShip(new Ship("DESTROYER"), 5, 'C', false);
        board.placeShip(new Ship("MINESWEEPER"), 2, 'C', false);
        Result playerAttack = board.attack(2, 'C');

        assertTrue(playerAttack.getResult() == SUNK);
    }

    @Test
    public void instantSink() {
        Board board = new Board();
        board.placeShip(new Ship("DESTROYER"), 5, 'C', false);
        board.placeShip(new Ship("BATTLESHIP"), 2, 'C', false);
        assertTrue(board.getShips().size() == 2);
        Result playerAttack = board.attack(2, 'E');
        assertTrue(playerAttack.getResult() == MISS);
        playerAttack = board.attack(2, 'E');
        assertTrue(playerAttack.getResult() == SUNK);
        assertTrue(board.getShips().size() == 1);
    }

    @Test
    public void regularSink() {
        Board board = new Board();
        board.placeShip(new Ship("DESTROYER"), 2, 'C', false);
        board.placeShip(new Ship("MINESWEEPER"), 4, 'B', false);
        Result playerAttack = board.attack(2, 'C');
        assertTrue(playerAttack.getResult() == HIT);
        playerAttack = board.attack(2, 'E');
        assertTrue(playerAttack.getResult() == HIT);
        playerAttack = board.attack(2, 'D');
        assertTrue(playerAttack.getResult() == MISS);
        playerAttack = board.attack(2, 'D');
        assertTrue(playerAttack.getResult() == SUNK);
    }

    @Test
    public void surrenderWithCQ() {
        Board board = new Board();
        board.placeShip(new Ship("DESTROYER"), 2, 'C', false);
        board.placeShip(new Ship("MINESWEEPER"), 4, 'B', false);
        board.placeShip(new Ship("BATTLESHIP"), 6, 'B', false);
        Result playerAttack = board.attack(2, 'D');
        playerAttack = board.attack(2, 'D');
        assertTrue(playerAttack.getResult() == SUNK);
        playerAttack = board.attack(4, 'B');
        assertTrue(playerAttack.getResult() == SUNK);
        playerAttack = board.attack(6, 'D');
        playerAttack = board.attack(6, 'D');
        assertTrue(playerAttack.getResult() == SURRENDER);

    }
}
