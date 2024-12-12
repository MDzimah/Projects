package tp1.logic;

//Represents the allowed directions in the game
public enum Direction {
	LEFT(-1,0), RIGHT(1,0), DOWN(0,1), UP(0,-1),
	LEFT_DOWN(-1,1), LEFT_UP(-1,-1), RIGHT_DOWN(1,1), RIGHT_UP(1,-1), 
	NONE(0,0);
	
	private final int x;
	private final int y;
	
	private Direction(int x, int y) {
		this.x=x;
		this.y=y;
	}
	
	/*---GETTERS---*/
	
	int getX() { return this.x; }	
	int getY() { return this.y; }	
}
