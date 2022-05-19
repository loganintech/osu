package cs361.battleships.models;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.Random;

import static cs361.battleships.models.AttackStatus.INVALID;

public class Game {

    @JsonProperty private Board playersBoard = new Board();
    @JsonProperty private Board opponentsBoard = new Board();

    public boolean placeShip(Ship ship, int x, char y, boolean isVertical) {
        return placeShip(ship, x, y, isVertical, false);
    }

    /*
	DO NOT change the signature of this method. It is used by the grading scripts.
	 */
    public boolean placeShip(Ship ship, int x, char y, boolean isVertical, boolean isSubmerged) {
        boolean successful = playersBoard.placeShip(ship, x, y, isVertical, isSubmerged);
        if (!successful)
            return false;

        Ship opponentShip = new Ship(ship.getKind());
        boolean opponentPlacedSuccessfully;
        do {
            // AI places random ships, so it might try and place overlapping ships
            // let it try until it gets it right
            opponentPlacedSuccessfully = opponentsBoard.placeShip(opponentShip, randRow(), randCol(), randVertical());
        } while (!opponentPlacedSuccessfully);

        return true;
    }

    /*
	DO NOT change the signature of this method. It is used by the grading scripts.
	 */
    public boolean attack(int x, char  y) {
        Result playerAttack = opponentsBoard.attack(x, y);
        if (playerAttack.getResult() == INVALID) {
            return false;
        }

        Result opponentAttackResult;
        do {
            // AI does random attacks, so it might attack the same spot twice
            // let it try until it gets it right
            opponentAttackResult = playersBoard.attack(randRow(), randCol());

        } while(opponentAttackResult.getResult() == INVALID);

        return true;
    }

    public boolean sonarPulse(int x, char y) {
        return opponentsBoard.sonarPulse(x, y);
    }

    private char randCol() {
        return (char) (Math.abs((new Random()).nextInt() % 10) + 'A');
    }

    private int randRow() {
        return (Math.abs((new Random()).nextInt() % 10)) + 1;
    }

    private boolean randVertical() {
        return (new Random()).nextBoolean();
    }
}
