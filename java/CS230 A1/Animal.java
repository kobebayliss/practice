/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Abstract base class representing an animal on the grid.
 * Each animal has a location, energy cost to rescue, and score rewarded upon capture to a rescuer.
 * Subclasses must implement the rescue behavior due to abstract implementation.
 */

import java.awt.Point;

abstract class Animal {

    protected Point location;
    protected int energy;
    protected int score;

    public Animal() {
        location = new Point(0, 0);
        energy = 1;
        score = 1;
    }

    public Animal(int energy, int score) {
        location = new Point(0, 0);
        this.energy = energy;
        this.score = score;
    }

    public Animal(int x, int y, int energy, int score) {
        location = new Point(x, y);
        this.energy = energy;
        this.score = score;
    }

    public Point getLocation() {
        return location;
    }

    public int getEnergy() {
        return energy;
    }

    public int getScore() {
        return score;
    }

    @Override
    public String toString() {
        return String.format(
            "%s at (%d, %d) [Energy=%d, Score=%d]",
            getClass().getSimpleName(),
            location.x,
            location.y,
            energy,
            score
        );
    }

    public abstract void rescue(Rescuer r);
}