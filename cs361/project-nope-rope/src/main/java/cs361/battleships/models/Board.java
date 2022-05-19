package cs361.battleships.models;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.ArrayList;
import java.util.List;

public class Board {

    private List<Ship> ships;
    private List<Result> attacks;
    private List<Square> visibleSquares;

    private static int rows = 10;
    private static int cols = 10;

    /*
     * DO NOT change the signature of this method. It is used by the grading
     * scripts.
     */
    public Board() {
        this.ships = new ArrayList<>();
        this.attacks = new ArrayList<>();
        this.visibleSquares = new ArrayList<>();
    }

    public Board(List<Ship> ships, List<Result> attacks, List<Square> visibleSquares) {
        this.ships = ships;
        this.attacks = attacks;
        this.visibleSquares = visibleSquares;
    }

    // The one-offset is to match the board
    public static int charToColInt(char col) {
        return (((int) col) - 'A') + 1;
    }

    // The one-offset is to match the board
    public static char intToColChar(int col) {
        return (char) ((col + 'A') - 1);
    }

    public boolean placeShip(Ship ship, int x, char y, boolean isVertical) {
        return placeShip(ship, x, y, isVertical, false);
    }

    /*
     * DO NOT change the signature of this method. It is used by the grading
     * scripts.
     *
     * Places a ship on the corresponding board. Checks to make sure ship is within
     * logical bounds of the array.
     */
    public boolean placeShip(Ship ship, int x, char y, boolean isVertical, boolean isSubmerged) {

        if (this.hasShip(ship.getKind())) {
            return false;
        }

        if (isSubmerged && !ship.getKind().equalsIgnoreCase("SUBMARINE")) {
            return false;
        }

        int length = ship.getShipLength();
        int width = ship.getShipWidth();

        if(isVertical) {
            // If there isn't enough space to place vertically
            if (x > (rows - length) + 1 || x > rows || x <= 0) {
                return false;
            }

            // If there isn't enough space to place horizontally
            if (charToColInt(y) > (cols - width) + 1 || charToColInt(y) > cols || charToColInt(y) <= 0) {
                return false;
            }
        } else {
            // If there isn't enough space to place vertically
            if (x > (rows - width) + 1 || x > rows || x <= 0) {
                return false;
            }

            // If there isn't enough space to place horizontally
            if (charToColInt(y) > (cols - length) + 1 || charToColInt(y) > cols || charToColInt(y) <= 0) {
                return false;
            }
        }

        int squares = ship.getShipSize();
        List<Square> toOccupy = new ArrayList<>();
        for (int i = 0; i < squares; i++) {

            if (isVertical) {
                // System.out.println("Adding ship at: " + (x + i) + ", " + y);

                // This looks for the right square to set as the armored square, unless it's the
                // minesweeper
                if (squares == 2) {
                    if (i == 0) {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, false, true));
                    } else {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, false, false));
                    }
                } else if (squares == 3) {
                    if (i == 1) {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, true, true));
                    } else {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, false, false));
                    }
                } else if (squares == 4) {
                    if (i == 2) {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, true, true));
                    } else {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, false, false));
                    }
                } else if (squares == 5) {
                    // The last one should be a specific space
                    if (i == 4) {
                        toOccupy.add(
                                new Square(x + 2, intToColChar(charToColInt(y) + 1), SquareType.SHIP, false, false));
                    } else if (i == 3) {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, true, true));
                    } else {
                        toOccupy.add(new Square(x + i, y, SquareType.SHIP, false, false));
                    }
                }
            } else {

                // Horizontal

                // This looks for the right square to set as the armored square, unless it's the
                // minesweeper
                if (squares == 2) {
                    if (i == 0) {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, false, true));
                    } else {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, false, false));
                    }
                } else if (squares == 3) {
                    if (i == 1) {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, true, true));
                    } else {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, false, false));
                    }
                } else if (squares == 4) {
                    if (i == 2) {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, true, true));
                    } else {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, false, false));
                    }
                } else if (squares == 5) {
                    // On the last square, go back one and up one
                    if (i == 4) {
                        toOccupy.add(
                                new Square(x - 1, intToColChar(charToColInt(y) + 2), SquareType.SHIP, false, false));
                    } else if (i == 3) {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, true, true));
                    } else {
                        toOccupy.add(new Square(x, intToColChar(charToColInt(y) + i), SquareType.SHIP, false, false));
                    }
                }
            }

        }

        ship.setOccupiedSquares(toOccupy);

        if (!isSubmerged) {
            // check if ship is going to overlap existing ship
            List<Ship> existingShips = this.getShips();
            for (Ship boardShip : existingShips) {
                for (Square existingsquare : boardShip.getOccupiedSquares()) {
                    for (Square newsquare : toOccupy) {
                        if (existingsquare.equals(newsquare)) {
                            return false;
                        }
                    }
                }
            }
        }

        ship.setSubmerged(isSubmerged);
        return this.ships.add(ship);
    }

    /*
     * DO NOT change the signature of this method. It is used by the grading
     * scripts.
     */

    // This encompasses the attack functions
    public Result attack(int x, char y) {
        Result aResult = new Result();
        int count = 0;
        aResult.setResult(AttackStatus.INVALID);
        aResult.setShip(null);
        Square coords = new Square(x, y);
        aResult.setLocation(coords);
        // Check if incoming coordinates are even good, if not, we can skip all this
        if ((x > 10 || x < 1) || (y > 'J' || y < 'A')) {
            return aResult;
        } else {

            for (Ship boardShip : this.ships) {

                for (Square shipSquare : boardShip.getOccupiedSquares()) {
                    // This for loop checks the list of occupied spaces against the coordinates
                    // given to the attack method
                    if (shipSquare.equals(coords)) {

                        // If the two squares are equal, we can add it to the list of hits

                        // If the square is not a Captains quarters, set it as a hit
                        if (!shipSquare.getCaptains()) {
                            aResult.setResult(AttackStatus.HIT);
                            aResult.setShip(boardShip);
                            this.attacks.add(aResult);
                        } else {
                            if (shipSquare.getArmored()) {
                                // If the square is armored, then register a miss and remove the armor
                                aResult.setResult(AttackStatus.MISS);
                                this.attacks.add(aResult);
                                shipSquare.setArmored(false);
                                return aResult;
                            } else if (!shipSquare.getArmored()) {
                                aResult.setResult(AttackStatus.SUNK);
                                ships.remove(boardShip);
                                if (this.ships.size() <= 0) {
                                    aResult.setResult(AttackStatus.SURRENDER);
                                }
                                aResult.setShip(boardShip);
                                this.attacks.add(aResult);
                            }
                        }

                        // To check if sunk:
                        //
                        // this.attacks is a List<result> type that has squares of hits
                        // boardShip.getOccupiedSquares() is a List<Square> that has squares of ships
                        // If these two lists are equal, ship is sunk
                        // if number of sunks is 3, game is surrendered

                        // This for loop looks at each ship and checks its occupied squares against the
                        // squares in attacks, or the list of hits
                        for (Square hitShipSquare : boardShip.getOccupiedSquares()) {
                            for (Result previousAttack : this.attacks) {
                                if (hitShipSquare.equals(previousAttack.getLocation())) {
                                    // if there's hits, increase the count too check against the ship size
                                    count++;
                                    if (count == boardShip.getShipSize()) {
                                        // if the count is equal to the ship size, it's sunk, and we remove it from the
                                        // board
                                        aResult.setResult(AttackStatus.SUNK);
                                        ships.remove(boardShip);
                                        if (this.ships.size() <= 0) {
                                            // by removing it from the board, we can check for surrender conditions by
                                            // checking if the list of ships is size 0!
                                            aResult.setResult(AttackStatus.SURRENDER);
                                        }

                                    }
                                }
                            }
                        }

                        return aResult;
                    }

                }

            }

            aResult.setResult(AttackStatus.MISS);
            this.attacks.add(aResult);
            return aResult;
        }
    }

    public boolean sonarPulse(int x, char y) {

        for (int row = x - 2; row <= x + 2; row++) {
            if (row <= 0 || row > this.rows)
                continue;

            for (int col = charToColInt(y) - (2 - Math.abs(row - x)); col <= charToColInt(y)
                    + (2 - Math.abs(row - x)); col++) {
                if (col <= 0 || col > this.cols)
                    continue;

                boolean outerContinue = false;
                for (Ship ship : this.ships) {
                    if (ship.containsSquare(new Square(row, intToColChar(col)))) {

                        this.visibleSquares.add(new Square(row, intToColChar(col), SquareType.SHIP));
                        outerContinue = true;
                    }
                }
                if (outerContinue)
                    continue;

                this.visibleSquares.add(new Square(row, intToColChar(col), SquareType.EMPTY));
            }
        }

        return true;
    }

    public List<Ship> getShips() {
        return this.ships;
    }

    // Why do we need to even have this function...
    public void setShips(List<Ship> ships) {
        this.ships = ships;
    }

    public List<Result> getAttacks() {
        return this.attacks;
    }

    public void setAttacks(List<Result> attacks) {
        this.attacks = attacks;
    }

    public List<Square> getVisibleSquares() {
        return this.visibleSquares;
    }

    public void setVisibleSquares(List<Square> visibleSquares) {
        this.visibleSquares = visibleSquares;
    }

    public boolean hasShip(String kind) {
        for (Ship ship : this.getShips()) {
            if (ship.getKind() == kind) {
                return true;
            }
        }
        return false;
    }

}
