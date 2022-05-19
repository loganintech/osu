package cs361.battleships.models;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.List;
import java.util.ArrayList;

public class Ship {

	@JsonProperty private List<Square> occupiedSquares = new ArrayList<>();
	@JsonProperty private String kind;
	@JsonProperty private int shipSize;
	@JsonProperty private int shipLength;
	@JsonProperty private int shipWidth;
	@JsonProperty private boolean isSubmerged;

	public Ship() {
		occupiedSquares = new ArrayList<>();
	}

	public Ship(String kind) {
		this.kind = kind;
		this.shipSize = this.getShipSize();
		this.shipLength = this.getShipLength();
		this.shipWidth = this.getShipWidth();
		this.isSubmerged = false;
	}

	public Ship(String kind, List<Square> occupiedSquares) {
		this.kind = kind;
		this.occupiedSquares = occupiedSquares;
		this.shipSize = this.getShipSize();
		this.shipLength = this.getShipLength();
		this.shipWidth = this.getShipWidth();
		this.isSubmerged = false;
	}

	public Ship(String kind, List<Square> occupiedSquares, boolean isSubmerged) {
		this.kind = kind;
		this.occupiedSquares = occupiedSquares;
		this.shipSize = this.getShipSize();
		this.shipLength = this.getShipLength();
		this.shipWidth = this.getShipWidth();
		this.isSubmerged = isSubmerged;
	}

	public void setOccupiedSquares(List<Square> occupiedSquares) {
		this.occupiedSquares = occupiedSquares;
	}

	public int getShipSize() {
		switch (this.kind) {
			case "MINESWEEPER":
				return 2;
			case "DESTROYER":
				return 3;
			case "BATTLESHIP":
				return 4;
			case "SUBMARINE":
				return 5;
			default:
				return -1;
		}
	}

	public int getShipLength() {
		switch (this.kind) {
		case "MINESWEEPER":
			return 2;
		case "DESTROYER":
			return 3;
		case "BATTLESHIP":
			return 4;
		case "SUBMARINE":
			return 4;
		default:
			return -1;
		}
	}

	public int getShipWidth() {
		switch (this.kind) {
		case "MINESWEEPER":
			return 1;
		case "DESTROYER":
			return 1;
		case "BATTLESHIP":
			return 1;
		case "SUBMARINE":
			return 2;
		default:
			return -1;
		}
	}

	public String getKind() {
		return this.kind;
	}

	public boolean getSubmerged() { return this.isSubmerged; }
	public void setSubmerged(boolean submerged) { this.isSubmerged = submerged; }

	public List<Square> getOccupiedSquares() {
		return this.occupiedSquares;
	}

	public boolean containsSquare(Square sqr) {
		for(Square shipSquare: this.getOccupiedSquares()) {
			if (shipSquare.equals(sqr)) {
				return true;
			}
		}
		return false;
	}
}
