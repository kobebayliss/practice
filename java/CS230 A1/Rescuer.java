/**
 * Name: Kobe Bayliss
 * Username: kbay678
 * Description: Represents a rescuer that moves around a grid, rescues animals,
 * and tracks energy, score, and rescued animals.
 */

import java.awt.Point;
import java.util.ArrayList;

class Rescuer {

    private Point location;
    private int energy;
    private int score;
    private ArrayList<Animal> rescuedAnimals;

    public Rescuer() {
        location = new Point(0, 0);
        energy = 10;
        score = 0;
        rescuedAnimals = new ArrayList<>();
    }

    public Rescuer(int energy) {
        location = new Point(0, 0);
        this.energy = energy;
        score = 0;
        rescuedAnimals = new ArrayList<>();
    }

    public int getEnergy() {
        return energy;
    }

    public int getScore() {
        return score;
    }

    public double getDistance(Animal a) {
        Point p = a.getLocation();
        return Math.sqrt(Math.pow(location.x - p.x, 2) + Math.pow(location.y - p.y, 2));
    }

    public void moveTo(Point position) {
        location = position;
    }

    public void increaseEnergy(int amount) {
        energy += amount;
    }

    public void decreaseEnergy(int amount) {
        energy = Math.max(0, energy - amount);
    }

    public void addScore(int score) {
        this.score += score;
    }

    public void rescueAnimal(Animal a) {
        moveTo(a.getLocation());
        a.rescue(this);
        rescuedAnimals.add(a);
    }

    @Override
    public String toString() {
        return "Final Status:\n" +
               "Location: (" + location.x + ", " + location.y + ")\n" +
               "Energy: " + energy + "\n" +
               "Score: " + score + "\n" +
               "Rescued Animals: " + rescuedAnimals.size() + "\n" +
               "Details: " + rescuedAnimals;
    }
}