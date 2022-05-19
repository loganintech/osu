package cs361.battleships.models;

@SuppressWarnings("unused")
public class Square {

	private int row;
	private char column;
	private SquareType sqrType;
	private boolean armored;
	private boolean captains;

	public Square() {}

	public Square(int row, char column) {
		this.row = row;
		this.column = column;
		this.sqrType = SquareType.EMPTY;
		this.armored = false;
		this.captains = false;
	}

	public Square(int row, char column, SquareType type) {
		this.row = row;
		this.column = column;
		this.sqrType = type;
		this.armored = false;
		this.captains = false;
	}

	public Square(int row, char column, SquareType type, boolean armor, boolean quarter) {
		this.row = row;
		this.column = column;
		this.sqrType = type;
		this.armored = armor;
		this.captains = quarter;
	}

	public char getColumn() {
		return column;
	}

	public void setColumn(char column) {
		this.column = column;
	}

	public int getRow() {
		return row;
	}

	public void setRow(int row) {
		this.row = row;
	}

	public SquareType getType() {
		return this.sqrType;
	}

	public void setType(SquareType type) {
		this.sqrType = type;
	}

	public boolean getArmored() { return this.armored; }

	public void setArmored(boolean armor) { this.armored = armor; }

	public boolean getCaptains() { return this.captains; }

	public void setCaptains(boolean quarter) { this.captains = quarter; }

	public static boolean squareEquality(Square sq1, Square sq2) {
        return sq1.getColumn() == sq2.getColumn() && sq1.getRow() == sq2.getRow();
	}

	public boolean equals(Square sq2) {
		return squareEquality(this, sq2);
	}

	public void debugPrint() {
		System.out.println("Row: " + row + " Col: " + column + " Type: " + sqrType);
	}
}
